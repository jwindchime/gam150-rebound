/******************************************************************************/
/*!
\file   VEengSaveManager.c
\author James Liao
\par    Course: GAM150
\par    Copyright © 2017 DigiPen (USA) Corporation.
\brief  Handles saving/loading to a save file.
*/
/******************************************************************************/

#include "VEengSaveManager.h"
#include "VaporEngine.h"
#include <stdio.h>
#include <stdlib.h>
#include <Shlobj.h>
#include <KnownFolders.h>
#include "StatusEffects.h"
#include "VEgfxNotifications.h"

// Maximum allowed line length
#define MAX_LINE 80

// Character array length for the folder path
#define FOLDER_LENGTH 256

// Line offset to access skin values
#define S_OFFSET 1

// Line offset to access power-up values
#define P_OFFSET 2

// Line offset to high score
#define H_OFFSET 3

// File path for the save file
#define SAVEFILE "\\SaveFile.rbnd"

// Wall quality
extern int VEgenWallChunks;

// Array for holding the full file path of the save file
static char filePath[FOLDER_LENGTH];

// Pointer to the save file
static FILE *saveFile;

// Unlocked skins from save file;
static unsigned long unlockedSkins;

// Unlocked power-ups from save file
static unsigned long unlockedPowers;

// High score from save file
static int highScore;

// Master volume from save file
static float masterVol;

// SFX volume from save file
static float sfxVol;

// Music volume from save file
static float musicVol;

/*!
\brief  Loads the save file if one exists, otherwise creates one.
\return None (void).
*/
void VEengLoadSaveFile()
{
  PWSTR *folderPath = (PWSTR *)malloc(sizeof(PWSTR));
  int hr = SHGetKnownFolderPath(&FOLDERID_LocalAppData, 0, NULL, folderPath);
  if (SUCCEEDED(hr))
  {
    size_t returned;
    wcstombs_s(&returned, filePath, FOLDER_LENGTH * sizeof(char), *folderPath, FOLDER_LENGTH * sizeof(wchar_t));
    CoTaskMemFree(*folderPath);
    free(folderPath);
    strcat(filePath, "\\Rebound");
    CreateDirectory(filePath, NULL);
    strcat(filePath, SAVEFILE);
  }
  
  saveFile = fopen(filePath, "rb");

  if (saveFile)
  {
    fscanf(saveFile, "%lu\n", &unlockedSkins);
    fscanf(saveFile, "%lu\n", &unlockedPowers);
    fscanf(saveFile, "%d\n", &highScore);
    fscanf(saveFile, "%d\n", &VEgenWallChunks);
    fscanf(saveFile, "%f\n", &masterVol);
    fscanf(saveFile, "%f\n", &sfxVol);
    fscanf(saveFile, "%f\n", &musicVol);

    fclose(saveFile);
  }
  else
  {
    unlockedSkins = 1;  // Only unlocks Noot Noot
    unlockedPowers = 3; // Only unlocks first 2 power-ups
    highScore = 0;
    VEgenWallChunks = 100;  // Medium wall quality
    masterVol = 100.0f;  // Set master volume to 100%
    sfxVol = 100.0f;    // Set SFX volume to 100%
    musicVol = 100.0f;  // Set music volume to 100%
  }

  VEsndSetMasterVolume(masterVol);
  VEsndSetSFXVolume(sfxVol);
  VEsndSetMusicVolume(musicVol);
}

/*!
\brief  Write the current info to a save file.
\return None (void).
*/
void VEengUpdateSaveFile()
{
  saveFile = fopen(filePath, "wb");

  if (saveFile)
  {
    // Update the unlocked skins
    fprintf(saveFile, "%lu\n", unlockedSkins);

    // Update the unlocked power-ups
    fprintf(saveFile, "%lu\n", unlockedPowers);

    // Update the high score
    fprintf(saveFile, "%d\n", highScore);

    // Update the wall quality
    fprintf(saveFile, "%d\n", VEgenWallChunks);

    // Update the master volume
    fprintf(saveFile, "%f\n", VEsndGetMasterVolume());

    // Update the SFX volume
    fprintf(saveFile, "%f\n", VEsndGetSFXVolume());

    // Update the music volume
    fprintf(saveFile, "%f\n", VEsndGetMusicVolume());

    fclose(saveFile);
  }
}

/*!
\brief  Unlock a skin in the save file.
\param  ball  The skin to unlocked (BallTexture).
\return None (void).
*/
void VEengSaveUnlockSkin(BallTexture ball)
{
  unlockedSkins = (unlockedSkins | (1L << ball)); // If this breaks, blame Quintin
}

/*!
\brief  Checks if a ball skin is unlocked.
\param  ball  The skin to check (BallTexture).
\return 1 if the skin is unlocked, 0 otherwise.
*/
int VEengSaveSkinisUnlocked(BallTexture ball)
{
  return ((unlockedSkins >> ball) & 1L); // If this breaks, blame Quintin
}

/*!
\brief  Checks if the score unlocks anything.
\param  score  The score for the latest round (int).
\return None (void).
*/
void VEengSaveCheckUnlocks(int score)
{
	if (score >= 500 && !VEengSaveSkinisUnlocked(BtJustin))
	{
		VEengSaveUnlockSkin(BtJustin);
		VEgfxAddNotification("You have unlocked:\n \nJustin", AEGfxTextureLoad("Assets/Justin.png"));
	}
	if (score >= 1000 && !VEengSaveSkinisUnlocked(BtDoug))
	{
		VEengSaveUnlockSkin(BtDoug);
		VEgfxAddNotification("You have unlocked:\n \nDoug", AEGfxTextureLoad("Assets/Doug.png"));
	}
	if (score >= 2000 && !VEengSaveSkinisUnlocked(BtDolla))
	{
		VEengSaveUnlockSkin(BtDolla);
		VEgfxAddNotification("You have unlocked:\n \nDolla Dolla Schillz", AEGfxTextureLoad("Assets/DollaDollaSchillz.png"));
	}
	if (score >= 3000 && !VEengSaveSkinisUnlocked(BtDojahstiin))
	{
		VEengSaveUnlockSkin(BtDojahstiin);
		VEgfxAddNotification("You have unlocked:\n \nDojahstiin", AEGfxTextureLoad("Assets/GladiatorJustin.png"));
	}
	if (score >= 9001 && !VEengSaveSkinisUnlocked(BtExample))
	{
		VEengSaveUnlockSkin(BtExample);
		VEgfxAddNotification("You have unlocked:\n \nBob", AEGfxTextureLoad("Assets/example_ball_new.png"));
	}
}

/*!
\brief  Updates the recorded high score.
\param  score  The new high score (int).
\return None (void).
*/
void VEengSaveSetHighScore(int score)
{
  highScore = score;
}

/*!
\brief  Returns the recorded high score.
\return The recorded high score (int).
*/
int VEengSaveGetHighScore()
{
  return highScore;
}

/*!
\brief  Unlocks everything (Debug purposes).
\return None (void).
*/
void VEengSaveUnlockAll()
{
  unlockedSkins = -1;
  unlockedPowers = -1;
}