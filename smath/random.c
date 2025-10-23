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

// Stuff for "random"

// You know... "C" is the only language that always pushes me to invent the bycicle...
// Because stock bycicle is piece of shit, and I want to build bycicle for myself.

#define RANDOM_START        36

unsigned char random_table[256] =
{
    143, 72 , 247, 101, 167, 105, 109, 90 , 36 , 165, 1  , 19 , 112, 219, 20 , 10 , 143, 198, 0  , 223,
    81 , 208, 155, 161, 156, 189, 22 , 108, 218, 24 , 114, 71 , 138, 186, 248, 86 , 46 , 254, 112, 213,
    157, 114, 54 , 167, 161, 138, 190, 69 , 49 , 160, 154, 10 , 144, 0  , 41 , 23 , 143, 251, 16 , 83 ,
    69 , 184, 125, 210, 130, 12 , 230, 91 , 123, 234, 198, 99 , 91 , 152, 83 , 211, 47 , 1  , 76 , 63 ,
    178, 238, 161, 88 , 185, 11 , 18 , 219, 215, 246, 87 , 50 , 105, 163, 4  , 95 , 202, 2  , 177, 216,
    176, 79 , 7  , 111, 173, 129, 205, 60 , 149, 66 , 88 , 169, 28 , 136, 104, 153, 96 , 104, 111, 79 ,
    146, 255, 40 , 76 , 204, 116, 210, 77 , 204, 174, 216, 170, 14 , 3  , 174, 149, 146, 103, 117, 225,
    133, 45 , 105, 179, 242, 57 , 138, 245, 230, 60 , 47 , 201, 251, 192, 14 , 226, 12 , 238, 69 , 202,
    63 , 119, 54 , 131, 245, 186, 205, 121, 163, 62 , 250, 73 , 56 , 28 , 118, 182, 215, 243, 181, 119,
    40 , 113, 170, 196, 132, 54 , 47 , 98 , 76 , 165, 203, 152, 31 , 23 , 58 , 248, 196, 147, 71 , 172,
    19 , 38 , 162, 13 , 244, 229, 194, 18 , 224, 223, 2  , 6  , 11 , 62 , 35 , 37 , 72 , 130, 90 , 80 ,
    116, 150, 152, 108, 185, 173, 5  , 214, 150, 134, 48 , 174, 74 , 40 , 116, 202, 27 , 44 , 100, 119,
    52 , 159, 172, 116, 38 , 2  , 140, 102, 103, 205, 109, 146, 207, 99 , 155, 4
};

//counters

int random_count = RANDOM_START; //random counter

//Stupid af random function
unsigned char doRandom (void)
{
    random_count = (random_count + 1) & 0xff;
    
    // return ((random_table[random_count]) > x) ? (random_table[random_count] * 0.5) : random_table[random_count];    // I wish this works fine... P.S: NO!!!
    return random_table[random_count];
}

