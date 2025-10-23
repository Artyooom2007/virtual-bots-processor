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

#include "../bots.h"
#include "../interpreter.h"

#define PLAN_1 0     // - Takes post
#define PLAN_2 1     // - Defensive actions / Ambush
#define PLAN_3 2     // - Attack / Counterattack actions
#define PLAN_4 3     // - Distracting maneuver


// TODO : Do something!

/*	OVER-BLOATED things				
 
#define MOVE_XY         (byte)  1   // 1 - move to X Y
#define SHOOT_BOT       (byte)  2   // 2 - shoot to bot X from group Y
#define SHOOT_XY        (byte)  3   // 3 - shoot to point X Y
#define WAIT            (byte)  4   // 4 - wait X times
#define NEAREST_ENEMY   (byte)  5   // 5 - get nearest Enemy. Recieve ANCHOR if relatively to this BOT, or X Y if relatively to specific point. Returns Group X ID Y
#define NEAREST_DEFENCE (byte)  6   // 6 - get nearest Defence. Recieve ANCHOR if relatively to this BOT, or X Y if relatively to specific point. Returns X Y
#define IF_NO_ENEMY     (byte)  7   // 7 - if near is no enemy then goto X, or goto Y
#define IF_NO_DEFENCE   (byte)  8   // 8 - if near is no defence then goto X, or goto Y
#define JUMP            (byte)  9   // 9 - Stop "if" or move action to X (as "while"
#define EXPLODE         (byte)  19  // 19 - Explode. There is a bot, he doin something, and... He just explodes. What a drama.


// Takes post
void setPlan1(byte group, byte id){     // complete
	
	
    bot[group][id].plan[PLAN_1][0][0] = NEAREST_ENEMY;
    bot[group][id].plan[PLAN_1][0][1] = 0;
    bot[group][id].plan[PLAN_1][0][2] = 0;

    bot[group][id].plan[PLAN_1][1][0] = IF_NO_ENEMY;
    bot[group][id].plan[PLAN_1][1][1] = 2;
    bot[group][id].plan[PLAN_1][1][2] = 5;

    bot[group][id].plan[PLAN_1][2][0] = MOVE_XY;
    bot[group][id].plan[PLAN_1][2][1] = bot[group][id].position.x;      // There will be specific points, but
    bot[group][id].plan[PLAN_1][2][2] = bot[group][id].position.y;      // not now

    bot[group][id].plan[PLAN_1][3][0] = WAIT;
    bot[group][id].plan[PLAN_1][3][1] = 3;
    bot[group][id].plan[PLAN_1][3][2] = 0;

    bot[group][id].plan[PLAN_1][4][0] = JUMP;
    bot[group][id].plan[PLAN_1][4][1] = 0;
    bot[group][id].plan[PLAN_1][4][2] = 0;

    bot[group][id].plan[PLAN_1][5][0] = SHOOT_BOT;
    bot[group][id].plan[PLAN_1][5][1] = bot[group][id].nearestEnemy.group;
    bot[group][id].plan[PLAN_1][5][2] = bot[group][id].nearestEnemy.id;

    bot[group][id].plan[PLAN_1][6][0] = JUMP;                           // END
    bot[group][id].plan[PLAN_1][6][1] = 0;
    bot[group][id].plan[PLAN_1][6][2] = 0;
}


// Defensive actions / Ambush
void setPlan2(byte group, byte id){

    bot[group][id].plan[PLAN_2][0][0] = NEAREST_ENEMY;
    bot[group][id].plan[PLAN_2][0][1] = 0;
    bot[group][id].plan[PLAN_2][0][2] = 0;

    bot[group][id].plan[PLAN_2][1][0] = NEAREST_DEFENCE;
    bot[group][id].plan[PLAN_2][1][1] = 0;
    bot[group][id].plan[PLAN_2][1][2] = 0;

    bot[group][id].plan[PLAN_2][2][0] = IF_NO_ENEMY;
    bot[group][id].plan[PLAN_2][2][1] = 3;
    bot[group][id].plan[PLAN_2][2][2] = 3;

    bot[group][id].plan[PLAN_2][3][0] = IF_NO_DEFENCE;
    bot[group][id].plan[PLAN_2][3][1] = 5;
    bot[group][id].plan[PLAN_2][3][2] = 4;

    bot[group][id].plan[PLAN_2][4][0] = MOVE_XY;
    bot[group][id].plan[PLAN_2][4][1] = bot[group][id].nearestDefence.x;
    bot[group][id].plan[PLAN_2][4][2] = bot[group][id].nearestDefence.y;

    bot[group][id].plan[PLAN_2][5][0] = JUMP;
    bot[group][id].plan[PLAN_2][5][1] = 8;
    bot[group][id].plan[PLAN_2][5][2] = 0;

    bot[group][id].plan[PLAN_2][6][0] = MOVE_XY;
    bot[group][id].plan[PLAN_2][6][1] = bot[group][id].position.x + random(5);
    bot[group][id].plan[PLAN_2][6][2] = bot[group][id].position.y + random(5);

    bot[group][id].plan[PLAN_2][7][0] = JUMP;
    bot[group][id].plan[PLAN_2][7][1] = 0;
    bot[group][id].plan[PLAN_2][7][2] = 0;

    bot[group][id].plan[PLAN_2][8][0] = WAIT;
    bot[group][id].plan[PLAN_2][8][1] = 1;
    bot[group][id].plan[PLAN_2][8][2] = 0;

}
*/
