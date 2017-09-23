/******************************************************************************/
/*!
\file   VEgfxCharacters.c
\author James Liao
\par    Course: GAM150
\par    Copyright © 2017 DigiPen (USA) Corporation.
\brief  Handles textures for the ball.
*/
/******************************************************************************/

#include "VaporEngine.h"
#include "VEgfxCharacters.h"
#include "VEengSaveManager.h"

/*------------------------------------------------------------------------------
// Public Consts:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Public Structures:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------*/

AEGfxTexture *pTexBall;
char *particleTexture;
BallTexture currBallTex;
bool hasParticle;
float isUnlocked;
char *lockText;
char *ballName;

/*------------------------------------------------------------------------------
// Private Variables:
//----------------------------------------------------------------------------*/

// Ball Textures
static AEGfxTexture *pTex1;
static AEGfxTexture *pTex2;
static AEGfxTexture *pTex3;
static AEGfxTexture *pTex4;
static AEGfxTexture *pTex5;
static AEGfxTexture *pTex6;

/*------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------*/

// Load the ball textures.
void VEgfxCharactersLoad()
{
  // Load in the ball textures
  pTex1 = AEGfxTextureLoad("Assets/Noot.png");
  AE_ASSERT_MESG(pTex1, "Failed to create NootNoot texture!!");
  pTex2 = AEGfxTextureLoad("Assets/Justin.png");
  AE_ASSERT_MESG(pTex2, "Failed to create Justin texture!!");
  pTex3 = AEGfxTextureLoad("Assets/Doug.png");
  AE_ASSERT_MESG(pTex3, "Failed to create Doug texture!!");
  pTex4 = AEGfxTextureLoad("Assets/DollaDollaSchillz.png");
  AE_ASSERT_MESG(pTex4, "Failed to create DollaDollaSchillz texture!!");
  pTex5 = AEGfxTextureLoad("Assets/example_ball_new.png");
  AE_ASSERT_MESG(pTex5, "Failed to create DefaultBall texture!!");
  pTex6 = AEGfxTextureLoad("Assets/GladiatorJustin.png");
  AE_ASSERT_MESG(pTex5, "Failed to create GladiatorJustin texture!!");
}

// Initialize the ball texture.
void VEgfxCharactersInit()
{
  // Initializes the displayed ball as Noot Noot
  VEgfxBallSet(BtNoot);
  particleTexture = "Assets/Particles/effect_dolla.txt";
}

// Unload the ball Textures.
void VEgfxCharactersUnload()
{
  // Unload the ball textures.
  AEGfxTextureUnload(pTex1);
  AEGfxTextureUnload(pTex2);
  AEGfxTextureUnload(pTex3);
  AEGfxTextureUnload(pTex4);
  AEGfxTextureUnload(pTex5);
  AEGfxTextureUnload(pTex6);
}

// Sets the current ball texture.
void VEgfxBallSet(BallTexture ballTex)
{
  if (ballTex < 0)
    currBallTex = ballTex + BtSize;
  else
    currBallTex = ballTex % BtSize;

  hasParticle = false;
  isUnlocked = (float) VEengSaveSkinisUnlocked(currBallTex);
  lockText = "";

  switch (currBallTex)
  {
    case BtJustin:
      pTexBall = pTex2;
      ballName = "Justin";
      lockText = "Reach a height of 500m";
      break;

    case BtDoug:
      pTexBall = pTex3;
      ballName = "Doug";
      lockText = "Reach a height of 1000m";
      break;

    case BtDolla:
      pTexBall = pTex4;
      ballName = "Dolla Dolla Schillz";
      hasParticle = true;
      particleTexture = "Assets/Particles/effect_dolla.txt";
      lockText = "Reach a height of 2000m";
      break;

    case BtDojahstiin:
      pTexBall = pTex6;
      ballName = "Dojahstiin";
      hasParticle = true;
      particleTexture = "Assets/Particles/effect_syllabus.txt";
      lockText = "Reach a height of 3000m";
      break;

    case BtExample:
      pTexBall = pTex5;
      ballName = "Bob";
      lockText = "Reach a height of 9001m";
      break;

    default: // Noot Noot
      pTexBall = pTex1;
      ballName = "Noot Noot K'Ne";
      lockText = "You done did a thing now, this was never supposed to happen";
      // But seriously though, if this text shows up, something's messed up
  }

  if (isUnlocked < 1.0f)
    ballName = "???";
}
