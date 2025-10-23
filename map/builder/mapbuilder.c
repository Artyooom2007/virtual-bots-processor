/* Copyright 2025 Chuovakie
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



/* So, i will say how this works. 
 * We have 2 arrays - first for containing visible for player map ("mapBuffer[][]"),
 * and second for containing comressed map or level actually ("levelBuffer[][]").
 * In level buffer we have 6 columns, where:
 * 
 * 1. Type of fill
 * 2. Type of block/object
 * 3-4. position XY (from up-left corner)
 * 5-6. size width/height
 * 
 * We don't have types of blocks/objects now, but from type of fill... we have only straight fill - it fills everything as said in levelBuffer.
 * I guess, with principles of how this works... this can be named like "Level Vectorization".
*/


#define MAX_X 20
#define MAX_Y 20

#define LEVEL_DETALIZATION 100
#define LEVEL_COLUMS 6

unsigned char mapBuffer[MAX_X][MAX_Y];

unsigned char levelBuffer[LEVEL_DETALIZATION][LEVEL_COLUMS]; // TODO : change LEVEL_COLUMS  to 6 when time comes.

//==================MAP=DECOMPRESSION==================

void levelDeassemble (void)
{

    //All we need to know- rows of assembled level
    short levelBufferRows = sizeof(levelBuffer) / sizeof(levelBuffer[0]);

    //Cleaning buffer
    for (short fillX = 0; fillX < MAX_X; fillX++){
        
            for (short fillY = 0; fillY < MAX_Y; fillY++){
            
                mapBuffer[fillX][fillY] = 0;
            }
        }

    //Building walls

    //Row of one segment
    for (short make = 0; make < levelBufferRows; make++)
    {
        //horisontal
        if (levelBuffer[make][2] >= levelBuffer[make][3]){
        
            for (short h = 0; h < (short)levelBuffer[make][2]; h++){
            
                for(short w = 0; w < (short)levelBuffer[make][3]; w++){
                
                    mapBuffer [w + levelBuffer[make][0]] [h + levelBuffer[make][1]] = 1;
                }
            }
        }

        //vertical
        else if (levelBuffer[make][2] < levelBuffer[make][3]){
        
            for (short w = 0; w < (short)levelBuffer[make][3]; w++){
            
                for(short h = 0; h < (short)levelBuffer[make][2]; h++){
                
                    mapBuffer [w + levelBuffer[make][0]] [h + levelBuffer[make][1]] = 1;
                }
            }
        }
        else if ((levelBuffer[make][2] == levelBuffer[make][3]) && (levelBuffer[make][2] == 1)){
            mapBuffer [levelBuffer[make][2] + levelBuffer[make][0]] [levelBuffer[make][3] + levelBuffer[make][1]] = 1;
        }
             
    }
}
