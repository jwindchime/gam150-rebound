/******************************************************************************/
/*!
\file   VEgmstCharSelect.h
\author James Liao
\par    Course: GAM150
\par    Copyright © 2017 DigiPen (USA) Corporation.
\brief  The entry point to the Main Menu gamestate.
*/
/******************************************************************************/
#pragma once

/*------------------------------------------------------------------------------
// Public Consts:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Public Structures:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------*/

// Load the resources associated with the CharSelect game state.
extern void VEgmstCharSelectLoad();

// Initialize the memory associated with the CharSelect game state.
extern void VEgmstCharSelectInit();

// Update the CharSelect game state.
extern void VEgmstCharSelectUpdate(float dt);

// Draw the CharSelect game state.
extern void VEgmstCharSelectDraw();

// Shutdown any memory associated with the CharSelect game state.
extern void VEgmstCharSelectShutdown();

// Unload the resources associated with the CharSelect game state.
extern void VEgmstCharSelectUnload();