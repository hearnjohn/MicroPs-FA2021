// STM32F401RE_GPIO.c
// Source code for GPIO functions

#include "STM32F401RE_GPIO.h"

void pinMode(GPIO * GPIOX, int pin, int function) {
    switch(function) {
        case GPIO_INPUT:
            GPIOX->MODER &= ~(0b11 << 2*pin);
            break;
        case GPIO_OUTPUT:
            GPIOX->MODER |= (0b1 << 2*pin);
            GPIOX->MODER &= ~(0b1 << (2*pin+1));
            break;
        case GPIO_ALT:
            GPIOX->MODER &= ~(0b1 << 2*pin);
            GPIOX->MODER |= (0b1 << (2*pin+1));
            break;
        case GPIO_ANALOG:
            GPIOX->MODER |= (0b11 << 2*pin);
            break;
    }
}

int digitalRead(GPIO * GPIOX, int pin) {
    return ((GPIOX->IDR) >> pin) & 1;
}

void digitalWrite(GPIO * GPIOX, int pin, int val) {
    GPIOX->ODR |= (1 << pin);
}

void togglePin(GPIO * GPIOX,  int pin) {
    // Use XOR to toggle
    GPIOX->ODR ^= (1 << pin);
}