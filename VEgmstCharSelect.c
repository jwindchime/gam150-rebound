/******************************************************************************/
/*!
\file   VEgmstCharSelect.c
\author James Liao
\par    Course: GAM150
\par    Copyright © 2017 DigiPen (USA) Corporation.
\brief  The Character Select gamestate.
*/
/******************************************************************************/

#include "VaporEngine.h"
#include "VEgmstCharSelect.h"
#include "VEgfxButton.h"

/*------------------------------------------------------------------------------
// Private Consts:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Private Structures:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------*/

extern AEGfxTexture* pTexBall;
extern BallTexture currBallTex;
extern float isUnlocked;
extern char *lockText;
extern char *ballName;

/*------------------------------------------------------------------------------
// Private Variables:
//----------------------------------------------------------------------------*/

static VEBackgroundPtr pBackground;

static ObjectList buttons;
static AEGfxTexture *pTexArrowRight;
static AEGfxTexture *pTexArrowLeft;
static AEGfxTexture *pTexLock;
static AEGfxVertexList* pMeshBall;
static AEGfxVertexList* pMeshLock;

static float scale;

/*------------------------------------------------------------------------------
// Private Function Declarations:
//----------------------------------------------------------------------------*/

void Start_Click(VEcomObject *button);
void Back_Click(VEcomObject *button);
void Right_Click(VEcomObject *button);
void Left_Click(VEcomObject *button);

/*------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------*/

// Load the resources associated with the CharSelect game state.
void VEgmstCharSelectLoad()
{
	scale = AEMin(VEengGetWindowWidth() / 1920.0f, VEengGetWindowHeight() / 1080.0f);
	pBackground = VEgfxBackgroundCreate("Assets\\Cliffside.png", 0.0f, 1024 * (0.75f * scale), 1024 * (0.75f * scale));

	pMeshBall = VEgfxCreateRectangleWithTex(1.0f, 1.0f, 0x00FFFFFF, 1.0f, 1.0f);
	AE_ASSERT_MESG(pMeshBall, "Failed to create the ball!!");
	pMeshLock = VEgfxCreateRectangleWithTex(1.0f, 1.0f, 0x00FFFFFF, 1.0f, 1.0f);
	AE_ASSERT_MESG(pMeshLock, "Failed to create the lock!!");
	
	pTexArrowRight = AEGfxTextureLoad("Assets/Arrow_Button_Right.png");
	AE_ASSERT_MESG(pTexArrowRight, "Failed to create arrow texture!!");
	pTexArrowLeft = AEGfxTextureLoad("Assets/Arrow_Button_Left.png");
	AE_ASSERT_MESG(pTexArrowLeft, "Failed to create arrow texture!!");

	pTexLock = AEGfxTextureLoad("Assets/Lock.png");
	AE_ASSERT_MESG(pTexArrowLeft, "Failed to create lock texture!!");
}

// Initialize the memory associated with the CharSelect game state.
void VEgmstCharSelectInit()
{
	VEcomAddButton(&buttons, 350, 0, 125, 125, "", 3.25, false, false, 0x005FA2B8, Right_Click);
	AEGfxTextureUnload(buttons.tail->pObject->mpVEcomSprite->mpTexture);
	buttons.tail->pObject->mpVEcomSprite->mpTexture = pTexArrowRight;
	VEcomAddButton(&buttons, -350, 0, 125, 125, "", 3.25, false, false, 0x005FA2B8, Left_Click);
	AEGfxTextureUnload(buttons.tail->pObject->mpVEcomSprite->mpTexture);
	buttons.tail->pObject->mpVEcomSprite->mpTexture = pTexArrowLeft;
	VEcomAddButton(&buttons, -200, -400, 300, 80, "Back", 3.25, false, true, 0x005FA2B8, Back_Click);
	VEcomAddButton(&buttons, 200, -400, 300, 80, "Start", 3.25, false, true, 0x005FA2B8, Start_Click);

	//VEsndSoundInit();
	//VEsndPlaySong("./Assets/Sound/music/main_menu.wav");
}

// Update the CharSelect game state.
void VEgmstCharSelectUpdate(float dt)
{
	if (AEInputCheckTriggered(VK_ESCAPE))
	{
		VEgmstGameStateManagerSetNextState(GsMainMenu);
		return;
	}

	if (AEInputCheckTriggered(VK_LEFT))
	{
	  VEgfxBallSet(--currBallTex);
	}
	
	if (AEInputCheckTriggered(VK_RIGHT))
	{
	  VEgfxBallSet(++currBallTex);
	}

	if (pBackground)
	{
		pBackground->translationX -= (60 * scale) * dt;
		pBackground->translationY -= (60 * scale) * dt;
	}

	VEengUpdateListObjects(&buttons, dt);
	//VEsndSoundUpdate();
}

// Draw the CharSelect game state.
void VEgmstCharSelectDraw()
{
	VEgfxBackgroundDraw(pBackground);

	VEgfxSetPrintScale(scale);
	VEgfxSetPrintColor(COLOR_WHITE);
	VEgfxSetPrintMode(CENTERED_H);
	VEgfxSetPrintEffect(DROP_SHADOW);
	VEgfxSetPrintEffectSize(5);
	VEgfxSetPrintEffectColor(COLOR_BLACK);
	VEgfxPrintfAt(0, (VEengGetWindowHeight() / 3.0f), "Character Select");

	VEgfxSetPrintDefaults();
	
	VEgfxSetPrintScale(scale / 2.0f);
	VEgfxSetPrintColor(COLOR_WHITE);
	VEgfxSetPrintMode(CENTERED_H);
	VEgfxPrintfAt(0, -(VEengGetWindowHeight() / 4.0f), ballName);

	VEgfxSetPrintDefaults();

	VEengDrawListObjects(&buttons);
	
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTransparency(1.0f);
	AEGfxSetFullTransform(0, 0, 0.0f, 300.0f, 300.0f);
	AEGfxSetTintColor(isUnlocked, isUnlocked, isUnlocked, 1.0f);
	AEGfxTextureSet(pTexBall, 0.0f, 0.0f);
	AEGfxMeshDraw(pMeshBall, AE_GFX_MDM_TRIANGLES);

	// Draw the lock and unlock requirements if the current skin is locked
	if (isUnlocked < 1.0f)
	{
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTransparency(1.0f);
		AEGfxSetFullTransform(0, 25.0f, 0.0f, 100.0f, 100.0f);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxTextureSet(pTexLock, 0.0f, 0.0f);
		AEGfxMeshDraw(pMeshLock, AE_GFX_MDM_TRIANGLES);
		
		VEgfxSetPrintScale(scale / 4.0f);
		VEgfxSetPrintColor(COLOR_WHITE);
		VEgfxSetPrintMode(CENTERED_H);
		VEgfxPrintfAt(0, -50.0f, lockText);
		
		VEgfxSetPrintDefaults();
	}
	
	// Draw the mouse with it's texture.
	s32 x_cursor, y_cursor;
	AEInputGetCursorPosition(&x_cursor, &y_cursor);
	VEgfxDrawCursorWithImage(VEgfxGetCursorObject(), x_cursor, y_cursor); // Added by Chase.
}

// Shutdown any memory associated with the CharSelect game state.
void VEgmstCharSelectShutdown()
{
	VEengDestroyListObjects(&buttons);
	//VEsndSoundShutDown();
}

// Unload the resources associated with the CharSelect game state.
void VEgmstCharSelectUnload()
{
	VEgfxBackgroundFree(&pBackground);

	AEGfxMeshFree(pMeshBall);
}

/*------------------------------------------------------------------------------
// Private Functions:
//----------------------------------------------------------------------------*/

/* Button click functions */

static void Start_Click(VEcomObject *button)
{
	if (isUnlocked == 1.0f)
	{
		VEsndStopAll();
		VEsndFreeSounds();
		VEgmstGameStateManagerSetNextState(GsScoreMode);
	}
}

static void Right_Click(VEcomObject *button)
{
	VEgfxBallSet(++currBallTex);
}

static void Left_Click(VEcomObject *button)
{
	VEgfxBallSet(--currBallTex);
}

static void Back_Click(VEcomObject *button)
{
	VEgmstGameStateManagerSetNextState(GsMainMenu);
}