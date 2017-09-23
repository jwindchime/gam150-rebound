/******************************************************************************/
/*!
\file   VEengSaveManager.h
\author James Liao
\par    Course: GAM150
\par    Copyright © 2017 DigiPen (USA) Corporation.
\brief  Handles saving/loading to a save file.
*/
/******************************************************************************/

#pragma once
#include <stdbool.h>
#include "VEgfxCharacters.h"

/*!
\brief  Loads the local save file, if one exists.
\return None (void).
*/
void VEengLoadSaveFile();

/*!
\brief  Write the current info to a save file.
\return None (void).
*/
void VEengUpdateSaveFile();

/*!
\brief  Unlock a skin in the save file.
\param  ball  The skin to unlocked (BallTexture).
\return None (void).
*/
void VEengSaveUnlockSkin(BallTexture ball);

/*!
\brief  Checks if a ball skin is unlocked.
\param  ball  The skin to check (BallTexture).
\return 0 if the skin is unlocked, 1 otherwise.
*/
int VEengSaveSkinisUnlocked(BallTexture ball);

/*!
\brief  Checks if the score unlocks anything.
\param  score  The score for the latest round (int).
\return None (void).
*/
void VEengSaveCheckUnlocks(int score);

/*!
\brief  Updates the recorded high score.
\param  score  The new high score (int).
\return None (void).
*/
void VEengSaveSetHighScore(int score);

/*!
\brief  Returns the recorded high score.
\return The recorded high score (int).
*/
int VEengSaveGetHighScore();

/*!
\brief  Unlocks everything (Debug purposes).
\return None (void).
*/
void VEengSaveUnlockAll();
