#include "STM32F401RE_TIM.h"


void configPitchT() {
    
    TIM10->cr1Bits.ARPE = 1;

    

    TIM10->ccmr1Bits.OC1M = 0b110;

    TIM10->ccerBits.CC1E = 1;

    // TIM10->cntBits.CNT = 0b0000;

    TIM10->pscBits.PSC = 0b0101;

    TIM10->arrBits.ARR = 0xFFFF;

    // TIM10->ccr1Bits.CCR1 = 32767;
    uint32_t* access = (uint32_t*) 0x40014434UL;
    *access = 32767;
    // ((uint32_t*)(0x40014400 + 0x34))* = 32767;
    TIM10->egrBits.UG = 1;
    TIM10->cr1Bits.CEN = 1;
}

void configLenT() {
    TIM11->cr1Bits.CEN = 1;
    TIM11->cr1Bits.ARPE = 1;

    TIM11->egrBits.UG = 1;

    TIM11->ccmr1Bits.OC1M = 0b110;

    TIM11->ccerBits.CC1E = 1;

    // TIM11->cntBits.CNT = 0b0000;

    TIM11->pscBits.PSC = 640;

    TIM11->arrBits.ARR = 0xFFFF;

    TIM11->ccr1Bits.CCR1 = 32767;
}