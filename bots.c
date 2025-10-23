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

// It uses only stdlib just for debug. Ofc this is wild.

#include "types/types.h"
#include "bots_consts.h"
#include "smath/smath.h"


bots bot[MAX_BOTS_GROUPS][MAX_BOTS];                         // Actual bots.

projectiles projectile[MAX_BOTS_GROUPS][MAX_PROJECTILES];    // Projectiles. Yes.
byte projectileAmount[2] = {0,0};                            // This thing is for counting projectiles.
dot2df projectilecollector[MAX_BOTS_GROUPS][MAX_PROJECTILES]; // With this we going to calculate movement, instead of using "round"

dot2d defences[MAX_DEFENCES];                                // defence points, aka funny NavMesh analog.

maptag botBuffer [BUFFER_X][BUFFER_Y];                       // Logical BOTS map.



// Initializes bots
void initBots(void){

    for (byte group = 0; group < MAX_BOTS_GROUPS; group++){
        for (byte id = 0; id < MAX_BOTS; id++){

            bot[group][id].health = 5;

            bot[group][id].position.x = (byte) mRandom(100);            // Fuck no
            bot[group][id].position.y = (byte) mRandom(100);

            botBuffer[bot[group][id].position.x][bot[group][id].position.y].thing = 1;
            botBuffer[bot[group][id].position.x][bot[group][id].position.y].group = group;
            botBuffer[bot[group][id].position.x][bot[group][id].position.y].id = id;

            bot[group][id].freeze = 0;

            bot[group][id].nearestEnemy.group = ANCHOR_ID;
            bot[group][id].nearestEnemy.id = ANCHOR_ID;

            bot[group][id].nearestDefence.x = ANCHOR_ID;
            bot[group][id].nearestDefence.y = ANCHOR_ID;
        }
    }
}



// Returns nearest enemy to specific point.
byte nearestEnemy(dot2d executor, byte victimGroup){

    byte victim = ANCHOR_ID;
    byte distance;
    byte prevDistance = MAX_BOTS_DISTANCE;

    for (byte i = 0; i < MAX_BOTS; i++){

        if (bot[victimGroup][i].health > 0){

            distance =  mAbs(executor.x - bot[victimGroup][i].position.x) +
                        mAbs(executor.y - bot[victimGroup][i].position.y);

            if (distance < prevDistance){

                victim = i;
                prevDistance = distance;
            }
        }
    }
    return victim;
}



// Returns nearest defence to specific point. Works slightly different than nearestEnemy(), but I can't do something with this.
byte nearestDefence(dot2d executor){

    byte chosenDefence = ANCHOR_ID;
    byte distance;
    byte prevDistance = MAX_BOTS_DISTANCE;

    for (byte i = 0; i < MAX_DEFENCES; i++){

        distance =  mAbs(executor.x - defences[i].x) +
                    mAbs(executor.y - defences[i].y);

        if (distance < prevDistance){
            chosenDefence = i;
            prevDistance = distance;
        }
    }
    return chosenDefence;
}



// Move your bot! returns 1 if bot is come to the target, else returns 0.
byte botMove (dot2d target, tag his){

    botBuffer[bot[his.group][his.id].position.x][bot[his.group][his.id].position.y].thing = 0;      // De-actualize old position

    if (target.x > bot[his.group][his.id].position.x) {bot[his.group][his.id].position.x += MAX_BOTS_SPEED;}    // right
    if (target.x < bot[his.group][his.id].position.x) {bot[his.group][his.id].position.x -= MAX_BOTS_SPEED;}    // left
    if (target.y > bot[his.group][his.id].position.y) {bot[his.group][his.id].position.y += MAX_BOTS_SPEED;}    // up
    if (target.y < bot[his.group][his.id].position.y) {bot[his.group][his.id].position.y -= MAX_BOTS_SPEED;}    // down

    botBuffer[bot[his.group][his.id].position.x][bot[his.group][his.id].position.y].thing = 1;    // Draw new symbol
    botBuffer[bot[his.group][his.id].position.x][bot[his.group][his.id].position.y].group = his.group;
    botBuffer[bot[his.group][his.id].position.x][bot[his.group][his.id].position.y].group = his.id;

    if ((target.x == bot[his.group][his.id].position.x) & (target.y == bot[his.group][his.id].position.y)){
        return 1;
    }
    return 0;
}



// Shoot! Initializes projectile, returns nothing.
void botShoot (tag thisBot, dot2d target){

    projectile[thisBot.group][projectileAmount[thisBot.group]].position.x = bot[thisBot.group][thisBot.id].position.x;
    projectile[thisBot.group][projectileAmount[thisBot.group]].position.y = bot[thisBot.group][thisBot.id].position.y;

    // fuck yeah
    projectile[thisBot.group][projectileAmount[thisBot.group]].angle = fromToAngle(
        projectile[thisBot.group][projectileAmount[thisBot.group]].position.x,
        projectile[thisBot.group][projectileAmount[thisBot.group]].position.y,
        target.x,
        target.y
    );

    projectile[thisBot.group][projectileAmount[thisBot.group]].damage = 1;

    projectileAmount[thisBot.group] += 1;

    if (projectileAmount[thisBot.group] > MAX_PROJECTILES){
            projectileAmount[thisBot.group] = 0;
    }
}



// Basic projectile work
void calculateProjectiles(void){

    for (byte group = 0; group < MAX_BOTS_GROUPS; group++){
        for (byte num = 0; num < MAX_PROJECTILES; num++){
            if (projectile[group][num].damage > 0){

                projectilecollector[group][num].x += moveAngleX(projectile[group][num].angle, PROJECTILES_SPEED);
                projectilecollector[group][num].y += moveAngleY(projectile[group][num].angle, PROJECTILES_SPEED);

                if (projectilecollector[group][num].x > 1.f){

                    projectile[group][num].position.x += 1;
                    projectilecollector[group][num].x -= 1.f;
                }

                if (projectilecollector[group][num].y > 1.f){

                    projectile[group][num].position.y += 1;
                    projectilecollector[group][num].y -= 1.f;
                }


                if (projectile[group][num].position.x > BUFFER_X || projectile[group][num].position.y > BUFFER_Y){
                    projectile[group][num].damage = 0;      // 0 damage means out of existance
                    return; // This is the end.
                }

                if (projectile[group][num].position.x <= 0 || projectile[group][num].position.y <= 0){
                    projectile[group][num].damage = 0;
                    return;
                }

                if (botBuffer[projectile[group][num].position.x][projectile[group][num].position.y].thing != 0){

                    bot[botBuffer[projectile[group][num].position.x][projectile[group][num].position.y].group][botBuffer[projectile[group][num].position.x][projectile[group][num].position.y].id].health -= projectile[group][num].damage;    // big piece of shit
                    projectile[group][num].damage = 0;
                    return;
                }
            }
        }
    }
}

// Get id of current robot, and returns id of enemy
byte enemyGroup(byte id){

    if (id == 0) return 1; else return 0;       // I will make enemy group lists later

}

