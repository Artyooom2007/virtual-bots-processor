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

#include "types/types.h"
#include "bots_consts.h"

#ifndef BOTS_MAIN
#define BOTS_MAIN

extern bots bot[MAX_BOTS_GROUPS][MAX_BOTS];                         // Actual bots.
extern projectiles projectile[MAX_BOTS_GROUPS][MAX_PROJECTILES];    // Projectiles. Yes.
extern byte projectileAmount[2];                                    // This thing is for counting projectiles. 
extern dot2d defences[MAX_DEFENCES];                                // defence points, aka funny NavMesh analog.
extern maptag botBuffer [BUFFER_X][BUFFER_Y];

#endif
