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

//definitely a types.

#ifndef TYPES_H
#define TYPES_H

#define PLAN_LISTS 4
#define PLAN_LINES 20
#define PLAN_CELLS 3

typedef unsigned char byte;     //"unsigned char"? nah. I'm lazy.

typedef struct { // point on 2D space

    int x;
    int y;

} dot2d;                        


typedef struct  { // float point for 2D space

    float x;
    float y;

} dot2df;                        


typedef struct { // Universal Bot tag

    byte group;     // Bots group
    byte id;        // ID of bot in selected group.

} tag;                          


typedef struct { //Bot type
    
    byte health;        // health of this bot.
    dot2d position;     // Position in 2D space.
    
    int plan[PLAN_LISTS][PLAN_LINES][PLAN_CELLS]; // plan lists. If I can turn all in this plans to use only bytes, I will do that and rewrite "int" to "byte". 
    
    byte list;         // Current used plan
    byte action;       // Current action
    
    byte freeze;       // freezes bots
    tag nearestEnemy;   // nearest Enemy of this bot
    dot2d nearestDefence; // nearest Defence of this bot

    dot2d shootTarget;  // Target to shoot
    dot2d walkTarget;   // Target to walk to

} bots;                         


typedef struct {
    int angle;
    byte damage;
    dot2d position;
} projectiles;          // Type for projectile


typedef struct {    // Tag, that modified for using in logical map.

    byte thing;         // We need to know - what exactly in this point.        0 - nothing; 1 - bot;
    byte group;         // group of this thing, if it have group.
    byte id;            // id of this thing. Feels like id have everything.
} maptag;


#endif
