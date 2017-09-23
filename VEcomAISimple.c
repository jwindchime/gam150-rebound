/******************************************************************************/
/*!
\file   VEcomAISimple.c
\author James Liao
\par    Course: GAM150
\par    Copyright © 2017 DigiPen (USA) Corporation.
\brief  Contains functions for simple AI handling.
*/
/******************************************************************************/

#include "VEcomComponents.h"
#include "VEmathUtil.h"

static float angle_sec; // Only used in circular motion AI

/*!
\brief  Dictates how the object will move with the given AI.
\param  obj  The object being updated (VEcomOBject *).
\param  dt   Time passed since last update (float).
\return None (void).
*/
void VEcomAIUpdate(VEcomObject *obj, float dt)
{
  // If the VEcomObject has an AI attached to it
  if (obj->mpVEcomAI)
  {
    // Update the AI counter
    obj->mpVEcomAI->mCounter -= dt;

    // Get the object's velocity
    AEVec2 *velocity = VEcomGetVelocity(obj);

    // Update velocity based on Behavior type
    switch (obj->mpVEcomAI->mBehavior)
    {
      case QUAD:
        if (obj->mpVEcomAI->mCounter <= 0)
        {
          float temp;
          if (obj->mpVEcomAI->mReversed)
          {
            // Object will turn 90 degrees counter-clockwise
            temp = -velocity->y;
            velocity->y = velocity->x;
            velocity->x = temp;
          }
          else
          {
            // Object will turn 90 degrees clockwise
            temp = -velocity->x;
            velocity->x = velocity->y;
            velocity->y = temp;
          }

          // Update the object's velocity
          VEcomSetVelocity(obj, velocity);

          // Reset the AI counter
          obj->mpVEcomAI->mCounter = obj->mpVEcomAI->mDuration;
        }

        break;

      case CIRCLE:
        // Calculate the radius of the movement
        if (!angle_sec)
        {
          angle_sec = 2 * PI / obj->mpVEcomAI->mDuration; // angle/sec
        }

        if (obj->mpVEcomAI->mCounter <= 0)
        {
          obj->mpVEcomAI->mCounter = obj->mpVEcomAI->mDuration;
        }
      
        if (obj->mpVEcomAI->mReversed)
        {
          // Rotate clockwise?
          VEmathVec2Rotate(velocity, velocity, 2 * PI - angle_sec * dt);
        }
        else
        {
          // Rotate counter-clockwise?
          VEmathVec2Rotate(velocity, velocity, angle_sec * dt);
        }

        VEcomSetVelocity(obj, velocity);

        break;

      case SWOOP:
        if (obj->mpVEcomAI->mCounter > 0)
        {
          // Center the swoop on the ball's position at the time this AI was created
          float midpoint = VEcomGetPosition(obj)->x - obj->mpVEcomAI->mBallPos.x;

          // Dive towards the ball at the specified location
          velocity->y = -1.25 * fabs(velocity->x) / (1 + midpoint * midpoint / (200 * 200));

          // Rotate the object to the proper orientation for its velocity
          VEcomSetRotation(obj, atan(velocity->y / velocity->x));
        }
        else
        {
          // You should be off-screen, stop moving
          AEVec2Zero(velocity);
        }

        // Update the velocity
        VEcomSetVelocity(obj, velocity);
        
        break;

      default: // Linear movement
        if (obj->mpVEcomAI->mCounter <= 0)
        {
          // Reverse the object's direction
          AEVec2Scale(velocity, velocity, -1);

          // Update the object's velocity
          VEcomSetVelocity(obj, velocity);

          // Reset the AI counter
          obj->mpVEcomAI->mCounter = obj->mpVEcomAI->mDuration;
        }
      }
  }
  else
    AESysPrintf("No AI assosciated with this object!\n");
}

void VEcomAddAI(VEcomObject *obj, VEAIBehavior behavior, float period)
{
  if (obj)
  {
    obj->mpVEcomAI = (VEcomAI *) calloc(1, sizeof(VEcomAI));
    obj->mpVEcomAI->mBehavior = behavior;
    obj->mpVEcomAI->mDuration = period;
    obj->mpVEcomAI->mCounter = period;
    obj->mpVEcomAI->mReversed = false;
    obj->mpVEcomAI->funcUpdate = VEcomAIUpdate;
    obj->mpVEcomAI->mpOwner = obj;
  }
  else
  {
    AESysPrintf("No object to attach AI to.\n");
  }
}

void VEcomRemoveAI(VEcomObject *obj)
{
  // If the VEcomObject has an AI attached to it
  if (obj->mpVEcomAI)
  {
    free(obj->mpVEcomAI);
    obj->mpVEcomAI = NULL;
  }
}

void VEcomReverseDir(VEcomObject *obj)
{
  if (obj && obj->mpVEcomAI)
  {
    obj->mpVEcomAI->mReversed = !(obj->mpVEcomAI->mReversed);

    obj->mpVEcomAI->mCounter = obj->mpVEcomAI->mDuration - obj->mpVEcomAI->mCounter;
    
    //Reverse the velocity vector
    AEVec2 *velocity = VEcomGetVelocity(obj);
    AEVec2Scale(velocity, velocity, -1);
    VEcomSetVelocity(obj, velocity);
  }
  else
    AESysPrintf("No object or AI associated with the object!\n");
}