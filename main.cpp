/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <cstdint>

#define RECHTS true
#define LINKS false

DigitalOut A(PC_3);
DigitalOut a(PC_2);
DigitalOut B(PC_1);
DigitalOut b(PC_0);

int Bestromung_rechts[4][4] = 
                                {
                                    {0,1,1,0}, //6
                                    {0,1,0,1}, //5 
                                    {1,0,0,1}, //9
                                    {1,0,1,0}  //A
                                };
int state;
bool richtung; // false links. true rechts
void init();

void init_TIM6(void);
void isr_TIM6(void);
void stopp_TIM6(void);
void start_TIM6(void);

void schritt_rechts(void);
void schritt_links(void);

void init()
{
    state = 0;
    richtung = RECHTS;
    A.write(Bestromung_rechts[state][0]);
    a.write(Bestromung_rechts[state][1]);
    B.write(Bestromung_rechts[state][2]);
    b.write(Bestromung_rechts[state][3]);
}

void init_TIM6()
{
    //Timer mit Takt versorgen
    RCC->APB1ENR |= 0b10000;

    //AutoRelodRegister auf 250ms
    TIM6->ARR = 250;

    //Precaler einstellen auf 1ms
    TIM6->PSC = 31999;

    //Zähler auf Wert Setzten
    TIM6->CNT = 0;

    //Überlaufflag löschen
    TIM6->SR = 0;

    //ISR in die VactorTabelle eintagen
    NVIC_SetVector(TIM6_IRQn, (uint32_t) &isr_TIM6);

    //Inertupt freigeben NIVC
    HAL_NVIC_EnableIRQ(TIM6_IRQn);

    //Interrupt Freigen
    TIM6->DIER = 1;

    //glogabe freigebe
    __enable_irq();
}

void isr_TIM6()
{
    if (richtung == RECHTS)
    {
        schritt_rechts();
    }
    else
    {
        schritt_links();
    }
    TIM6->SR = 0;
}

void stopp_TIM6()
{
    TIM6->CR1 = 0;
}

void start_TIM6()
{
    TIM6->CR1 = 1;
}

void schritt_rechts()
{
    state++;
    state %= 4;
    A.write(Bestromung_rechts[state][0]);
    a.write(Bestromung_rechts[state][1]);
    B.write(Bestromung_rechts[state][2]);
    b.write(Bestromung_rechts[state][3]);
}

void schritt_links()
{
    state += 3;
    state %= 4;
    A.write(Bestromung_rechts[state][0]);
    a.write(Bestromung_rechts[state][1]);
    B.write(Bestromung_rechts[state][2]);
    b.write(Bestromung_rechts[state][3]);
}

int main()
{ 
    init();
    init_TIM6();
    start_TIM6();

    while (true)
    {
        
    }
}
