#ifndef STM32F_TIM_H
#define STM32F_TIM_H

#include <stdint.h>

#define __IO volatile

#define TIM10_BASE (0x40014400UL) // base address of TIM10
#define TIM11_BASE (0x40014800UL) // base address of TIM11

// TIM10 will be used for the pitch
// TIM11 will be used for the duration
typedef struct {
    volatile uint32_t CEN     :1;
    volatile uint32_t UDIS    :1;
    volatile uint32_t URS     :1;
    volatile uint32_t OPM     :1;
    volatile uint32_t         :3;
    volatile uint32_t ARPE    :1;
    volatile uint32_t CKD     :2;
    volatile uint32_t         :6;
    volatile uint32_t         :16;
} CR1;

// Interrupt enable register
typedef struct {
    volatile uint32_t UIE     :1;
    volatile uint32_t CC1IE   :1;
    volatile uint32_t         :30;

} DIER;

// Status register
typedef struct {
    volatile uint32_t UIF     :1;
    volatile uint32_t CC1IF   :1;
    volatile uint32_t         :7;
    volatile uint32_t CC1OF   :1;
    volatile uint32_t         :6;
    volatile uint32_t         :16;
} SR;

// Event generation register
typedef struct {
    volatile uint32_t UG      :1;
    volatile uint32_t CC1G    :1;
    volatile uint32_t         :30;
} EGR;

typedef struct {
    volatile uint32_t CC1S     :2;
    volatile uint32_t OC1FE    :1;
    volatile uint32_t OC1PE    :1;
    volatile uint32_t OC1M     :3;
    volatile uint32_t          :25;
} CCMR1;

typedef struct {
    volatile uint32_t CC1E      :1;
    volatile uint32_t CC1P      :1;
    volatile uint32_t           :1;
    volatile uint32_t CC1NP     :1;
    volatile uint32_t           :28;
} CCER;

typedef struct {
    volatile uint32_t CNT       :16;
    volatile uint32_t           :16;
} CNT;

typedef struct {
    volatile uint32_t PSC       :16;
    volatile uint32_t           :16;
} PSC;

typedef struct {
    volatile uint32_t ARR       :16;
    volatile uint32_t           :16;
} ARR;

typedef struct {
    volatile uint32_t CCR1      :16;
    volatile uint32_t           :16;
} CCR1;

typedef struct {
    volatile uint32_t TI1_RMP   :2;
    volatile uint32_t           :30;
} OR;

typedef struct {
  // OFFSET: 0x00
  __IO CR1 cr1Bits;
  // 0x04
  volatile uint32_t res1;
  // 0x08
  volatile uint32_t res2;  // SMCR
  // 0x0C
  __IO DIER dierBits;
  // OFFSET: 0x10
  __IO SR srBits;
  // OFFSET: 0x14
  __IO EGR egrBits;
  // OFFSET: 0x18
  __IO CCMR1 ccmr1Bits;
  // 0x1c offset
  volatile uint32_t res3;
  // OFFSET: 0x20
  __IO CCER ccerBits;
  // OFFSET: 0x24
  __IO CNT cntBits;
  // OFFSET: 0x28
  __IO PSC pscBits;
  // OFFSET: 0x2C
  __IO ARR arrBits;
  // OFFSET: 0x30
  volatile uint32_t res4;
  // OFFSET: 0x34
  __IO CCR1 ccr1Bits;
  // 0x38
  volatile uint32_t CCR2;
  // 0x3c...
  volatile uint32_t;
} TIM_TypeDef;


#define TIM10 ((TIM_TypeDef *) TIM10_BASE)
#define TIM11 ((TIM_TypeDef *) TIM11_BASE)

void configPitchT();
void configLenT();

#endif