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

#include "smath.h"      // Mutual use


// sin, cos, and... oh fuck.

// It's all I need 
float sinTable[91] = {              

    0.000, 0.017, 0.034, 0.052, 0.069, 0.087, 0.104, 0.121, 0.139, 0.156, 0.173, 0.190, 0.207, 0.224, 0.241, 0.258, 0.275, 0.292, 0.309, 0.325, 0.342, 0.358, 0.374, 
    0.390, 0.406, 0.422, 0.438, 0.453, 0.469, 0.484, 0.500, 0.515, 0.529, 0.544, 0.559, 0.573, 0.587, 0.601, 0.615, 0.629, 0.642, 0.656, 0.669, 0.681, 0.694, 0.707,
    0.719, 0.731, 0.743, 0.754, 0.766, 0.777, 0.788, 0.798, 0.809, 0.819, 0.829, 0.838, 0.848, 0.857, 0.866, 0.874, 0.882, 0.891, 0.898, 0.906, 0.913, 0.920, 0.927, 
    0.933, 0.939, 0.945, 0.951, 0.956, 0.961, 0.965, 0.970, 0.974, 0.978, 0.981, 0.984, 0.987, 0.990, 0.992, 0.994, 0.996, 0.997, 0.998, 0.999, 0.999, 1.000

};  



// Return sin of current degree
float mSin (int degree){

    if      ((degree >=   0) && (degree <=  90))     return  sinTable[degree      ];
    else if ((degree >=  90) && (degree <= 180))     return  sinTable[180 - degree];
    else if ((degree >= 180) && (degree <= 270))     return -sinTable[degree - 180];
    else if ((degree >= 270) && (degree <= 360))     return -sinTable[360 - degree];

    else return 0;
}



// Return cos of current degree
float mCos (int degree){

    if      ((degree >=    0) && (degree <   90))    return  sinTable[90 -  degree];
    else if ((degree >=   90) && (degree <  180))    return -sinTable[degree -  90];
    else if ((degree >=  180) && (degree <  270))    return -sinTable[270 - degree];
    else if ((degree >=  270) && (degree <= 360))    return  sinTable[degree - 270];

    else return 1;
}

// Return tan of current degree
float mTan (int degree){

    return sin(degree) / cos(degree);       // Division is for pussies. I'm pussy D:

}



// atan2 that not perfect at all.
float mAtan2 (int y, int x){

    if ((x == 0) && (y == 0)) return 0;

    float angle = 90.0f * (abs(y) / (abs(x) + abs(y)) );

    if (x < 0) angle = 180 - angle;
    if (y < 0) angle = 360 - angle;

    return angle;
}

// P.S: DEGREE CAN'T BE HIGHER THAN 360!!! I SAID THAT!!!
// P.S 2: Actually, it technically can't be. I don't rotate things- I only give directions.
// P.S 3: I put "m" in all func names, because GCC does some shit.
