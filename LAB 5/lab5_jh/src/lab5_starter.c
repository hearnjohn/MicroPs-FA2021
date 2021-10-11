// lab5_starter.c
// Fur Elise, E155 Lab 5
// Updated Fall 2021

#include "STM32F401RE_TIM.h"
#include "STM32F401RE_FLASH.h"
#include "STM32F401RE_GPIO.h"
#include "STM32F401RE_RCC.h"

// Pitch in Hz, duration in ms
const int notes[][2] = {
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	250},
{  0,	125},
{494,	125},
{523,	125},
{587,	125},
{659,	375},
{392,	125},
{699,	125},
{659,	125},
{587,	375},
{349,	125},
{659,	125},
{587,	125},
{523,	375},
{330,	125},
{587,	125},
{523,	125},
{494,	250},
{  0,	125},
{330,	125},
{659,	125},
{  0,	250},
{659,	125},
{1319,	125},
{  0,	250},
{623,	125},
{659,	125},
{  0,	250},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	500},
{  0,	  0}};

// Pass in the duration, do math
int newDuration(int duration) {
    TIM11->cntBits.CNT = 0;
    TIM11->egrBits.UG = 1;
    return (131072 * .001 * duration);
}

// Pass in the frequency of the note, do math
void changePitch(int freq) {
    volatile int newCount = (freq != 0) ? (14e6 / freq) : 0;
    TIM10->cntBits.CNT = 0;
    TIM10->arrBits.ARR = newCount;
    TIM10->ccr1Bits.CCR1 = newCount / 2;  // The duty cycle is 50%
    TIM10->egrBits.UG = 1;
}

int main(void) {
    // Enable the GPIOA pins, both timers (for pitch and duration)
    RCC->AHB1ENR.GPIOAEN = 1;
    RCC->AHB1ENR.GPIOBEN = 1;
    RCC->APB2ENR.TIM10EN = 1;
    RCC->APB2ENR.TIM11EN = 1;

    // Set output pins
    GPIOB->AFRH |= (1 << 1) | (1 << 0);
    
    // Pinmodes
    pinMode(GPIOB, 8, GPIO_ALT);

    // configure flash, clock, pitch & length timers
    configureFlash();
    configureClock();
    configPitchT();
    configLenT();

    volatile int currDuration;
    for(volatile int i = 0; i < 108; i++) {
        currDuration = newDuration(notes[i][1]);
        changePitch(notes[i][0]);
        while(TIM11->cntBits.CNT < currDuration);
    }
    changePitch(0);
    newDuration(0);
    while(1);
}
