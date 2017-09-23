/******************************************************************************/
/*!
\file   VEgfxCharacters.h
\author James Liao
\par    Course: GAM150
\par    Copyright © 2017 DigiPen (USA) Corporation.
\brief  Handles textures for the ball.
*/
/******************************************************************************/
#pragma once
#include "VEcomComponents.h"

/*------------------------------------------------------------------------------
// Public Consts:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Public Structures:
//----------------------------------------------------------------------------*/

typedef enum
{
  BtNoot,
  BtJustin,
  BtDoug,
  BtDolla,
  BtDojahstiin,
  BtExample,
  BtSize, // The number of elements in the enum, THIS SHOULD ALWAYS BE LAST
} BallTexture;

/*------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------*/

// Load the ball textures.
void VEgfxCharactersLoad();

// Initialize the ball texture.
void VEgfxCharactersInit();

// Unload the ball textures.
void VEgfxCharactersUnload();

// Sets the current ball texture.
void VEgfxBallSet(BallTexture ballTex);