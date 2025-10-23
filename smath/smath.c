/* Copyright 2025 Artyooom2007, Chuovakie
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

// SMATH - Some MATH.
// Port from JS version, with some changes.

#include "../types/types.h"
#include "trigonometry.h" //Mutual use
#include "random.h"

#define PI      3.14f
#define HALFPI  1.57f
#define HALF    0.5f
#define QUAT    0.25f

//#define DGRD 0.0056f   // DGRD STILL works, so please, don't touch it... DGRD is used in degToRad and radToDeg, but I don't need this functions, so...


int mRandom          (void)                                 {return doRandom;}                  // I dunno

int mAbs             (int x)                                {return ((x > 0) ? x : -x);}

float fromToAngle   (int x1, int y1, int x2, int y2)        {return mAtan2(y2 - y1, x2 - x1);}

float moveAngleX    (int angle, float speed)                {return mCos(angle) * speed;}
float moveAngleY    (int angle, float speed)                {return mSin(angle) * speed;}

byte squareArea     (int x, int y, int minX, int minY, int maxX, int maxY)
                    {return (x >= minX && x <= maxX && y >= minY && y <= maxY);}

int invertDeg       (int deg)                               {return (360 - deg);}
 
