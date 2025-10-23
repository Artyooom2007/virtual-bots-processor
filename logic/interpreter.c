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

//======= OVER-BLOATED ver. =======
// 1 - move to X Y
// 2 - shoot to bot X from group Y
// 3 - shoot to point X Y
// 4 - wait X times
// 5 - get nearest Enemy. Recieve ANCHOR if relatively to this BOT, or X Y if relatively to specific point. Returns Group X ID Y
// 6 - get nearest Defence. Recieve ANCHOR if relatively to this BOT, or X Y if relatively to specific point. Returns X Y
// 7 - if near is no enemy then goto X, or goto Y
// 8 - if near is no defence then goto X, or goto Y
// 9 - Stop "if" or move action to X (as "while")
// 19 - Explode. There is a bot, he doin something, and... He just explodes. What a drama.
//============ SLIM ver. ============

// 0 - nothing
// 1 - move to XY
// 2 - shoot to bot X from group Y
// 3 - wait X times

#include "../bots.h"

// SLIM version
void planInterpreter (byte planLine){

	for (byte group =  0; group < MAX_BOTS_GROUPS; group += 1){
		for (byte id = 0; id < MAX_BOTS; id++){
		
		if (bot[group][id].health <= 0) continue;		// Insurance №1
		
		int *thisBotAction = bot[group][id].plan[planLine][bot[group][id].action];     // POINTERS! YES!!! With this line I can simplify code so much.
		
		if (bot[group][id].action > PLAN_LINES) bot[group][id].action = 0;      // Insurance №2
		
		switch (thisBotAction[0]){
		
		
			case 1:				// 1 - move to X Y
				(botMove((dot2d)
						{thisBotAction[1],
						 thisBotAction[2]},
						(tag) {group,id})) > 0 ? bot[group][id].action += 1 : 0;       // ah, perfect
                break;


                case 2:				// 2 - shoot to bot X from group Y
                    if (bot[group][id].nearestEnemy.group < ANCHOR_ID){
                    botShoot((tag){group, id}, (dot2d) {
                        bot[thisBotAction[1]][thisBotAction[2]].position.x,   // kill me
                        bot[thisBotAction[1]][thisBotAction[2]].position.y,
                    });
                    }
                    bot[group][id].action += 1;
                break;
                
                
				case 3:				// 4 - wait X times
					if ((thisBotAction[1] > 0) && (bot[group][id].freeze == 0)){
						bot[group][id].freeze = thisBotAction[1];					// later
						break;
					}

					bot[group][id].freeze -= 1;

					if (bot[group][id].freeze <= 0) bot[group][id].action += 1;

				break;
				
				default:

					bot[group][id].action += 1;
					bot[group][id].action > PLAN_LINES ?                            // Another one insurance
					bot[group][id].action = 0 : 0;

				break;
			}
		}
}

/*										THIS INTERPRETER IS OVER-BLOATED (and old)
void planInterpreter (byte planLine){

    for (byte group = 0; group < MAX_BOTS_GROUPS; group++){
        for (byte id = 0; id < MAX_BOTS; id++){

            if (bot[group][id].health <= 0) continue;       // What if this bot is already dead? Right! We don't need this bot to do something...
                                                            // Because we don't need walking dead. If you wanna undead bots - comment this code.

            int *thisBotAction = bot[group][id].plan[planLine][bot[group][id].action];     // POINTERS! YES!!! With this line I can simplify code so much.

            if (bot[group][id].action > PLAN_LINES) bot[group][id].action = 0;      // Insurance

            switch (thisBotAction[0]){

                case 1:				// 1 - move to X Y
                    (botMove((dot2d)
                            {thisBotAction[1],
                             thisBotAction[2]},
                             (tag) {group,id})) > 0 ? bot[group][id].action += 1 : 0;       // ah, perfect
                break;

                case 2:				// 2 - shoot to bot X from group Y
                    if (bot[group][id].nearestEnemy.group < ANCHOR_ID){
                    botShoot((tag){group, id}, (dot2d) {
                        bot[thisBotAction[1]][thisBotAction[2]].position.x,   // kill me
                        bot[thisBotAction[1]][thisBotAction[2]].position.y,
                    });
                    }
                    bot[group][id].action += 1;
                break;

                case 3:				// 3 - shoot to point X Y
                    botShoot((tag){group, id}, (dot2d) {
                        thisBotAction[1],        // later
                        thisBotAction[2],
                    });
                    bot[group][id].action += 1;
                break;

                case 4:				// 4 - wait X times
                    if ((thisBotAction[1] > 0) && (bot[group][id].freeze == 0)){
                        bot[group][id].freeze = thisBotAction[1];
                        break;
                    }

                    bot[group][id].freeze -= 1;

                    if (bot[group][id].freeze <= 0) bot[group][id].action += 1;

                break;

                case 5:				// 5 - get nearest Enemy. Recieve ANCHOR if relatively to this BOT, or X Y if relatively to specific point. Returns Group X ID Y
                    bot[group][id].nearestEnemy.group = enemyGroup(group);
                    bot[group][id].nearestEnemy.id = nearestEnemy(bot[group][id].position, enemyGroup(group));

                    bot[group][id].action += 1;
                break;

                case 6:				// 6 - get nearest Defence. Recieve ANCHOR if relatively to this BOT, or X Y if relatively to specific point. Returns X Y
                    dot2d whichOneDefence = defences[nearestDefence(bot[group][id].position)];
                    if (whichOneDefence.x < ANCHOR_ID || whichOneDefence.y < ANCHOR_ID){
                        bot[group][id].nearestDefence.x = whichOneDefence.x;
                        bot[group][id].nearestDefence.y = whichOneDefence.y;
                    }

                    bot[group][id].action += 1;
                break;

                case 7:				// 7 - if near is no enemy then goto X, or goto Y

                    if (bot[group][id].nearestEnemy.group == ANCHOR_ID || bot[group][id].nearestEnemy.id == ANCHOR_ID)

                        bot[group][id].action = thisBotAction[1];
                    else
                        bot[group][id].action = thisBotAction[2];

                break;

                case 8:				// 8 - if near is no defence then goto X, or goto Y

                if (bot[group][id].nearestDefence.x == ANCHOR_ID || bot[group][id].nearestDefence.y == ANCHOR_ID)

                        bot[group][id].action = thisBotAction[1];
                    else
                        bot[group][id].action = thisBotAction[2];

                break;


                case 9:				// 9 - Stop "if" or move action to X (as "while")

                    bot[group][id].action = thisBotAction[1];

                break;

                case 19:				// 19 - Explode. There is a bot, he doin something, and... He just explodes. What a drama.

                    bot[group][id].health = 0;      // ha

                break;

                default:

                    bot[group][id].action += 1;
                    bot[group][id].action > PLAN_LINES ?                            // Another one insurance
                    bot[group][id].action = 0 : 0;

                break;
            }
        }
    }
}
*/
