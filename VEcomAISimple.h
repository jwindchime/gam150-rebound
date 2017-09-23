/******************************************************************************/
/*!
\file   VEcomAISimple.h
\author James Liao
\par    Course: GAM150
\par    Copyright © 2017 DigiPen (USA) Corporation.
\brief  Contains functions for simple AI handling.
*/
/******************************************************************************/

#pragma once

#include "VEcomComponents.h"

/*!
\brief Reverses the current direction of the object's AI.
\param obj   The object to be affected (VEcomObject *).
\return None (Void).
*/
void VEcomReverseDir(VEcomObject *obj);

void VEcomAIUpdate(VEcomObject *obj, float dt);