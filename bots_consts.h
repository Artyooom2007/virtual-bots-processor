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

#ifndef BOT_CONSTS
#define BOT_CONSTS

#define BUFFER_X (unsigned char) 100                // Buffer is used for simplifying movement
#define BUFFER_Y (unsigned char) 100                // and for simplifying collision

#define MAX_BOTS_GROUPS (unsigned char) 2           // Max amount of bots groups
#define MAX_BOTS (unsigned char) 10                 // Max amount of bots by IDs
#define MAX_BOTS_DISTANCE (unsigned char) 50        // This is how far bots can see
#define MAX_BOTS_SPEED (unsigned char) 1            // This is how fast bots can move

#define MAX_DEFENCES (unsigned char) 25             // Max amount of defence points

#define MAX_PROJECTILES 60                          // Max amount of projectiles for each group
#define PROJECTILES_SPEED 1                         // speed of projectiles

#define ANCHOR_ID (unsigned char) 255           // If function returns for you this value - you should pray.

#endif
