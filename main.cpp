/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

DigitalOut A(PC_3);
DigitalOut a(PC_2);
DigitalOut B(PC_1);
DigitalOut b(PC_0);

int main()
{
int Bestromung[4][4] = 
                        {
                            {0,1,1,0}, //6
                            {0,1,0,1}, //5 
                            {1,0,0,1}, //9
                            {1,0,1,0}  //A
                        };

    while (true)
    {
        for (int i = 0; i < 4; i++)
        {
            A.write(Bestromung[i][0]);
            a.write(Bestromung[i][1]);
            B.write(Bestromung[i][2]);
            b.write(Bestromung[i][3]);

            ThisThread::sleep_for(250ms);
        }
    }
}
