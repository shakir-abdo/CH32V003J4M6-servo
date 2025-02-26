#include "servo.h"

// Convert angle to pulse width
static uint16_t angle_to_pulse(uint8_t angle) {
    // Map angle (0-180) to pulse width (40-120)
    // 40 = 1ms pulse (0 degrees)
    // 120 = 2ms pulse (180 degrees)
    return 40 + ((angle * 80) / 180);
}

void servo_init(Servo* servo, ServoPin pin) {
    servo->pin = pin;
    servo->current_angle = 90;  // Initialize at center position

    // Enable GPIO ports
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC;

    // Enable Timer1
    RCC->APB2PCENR |= RCC_APB2Periph_TIM1;

    // Configure GPIO based on selected pin
    switch (pin) {
        case SERVO_PIN_PA2:
            // Configure PA2 as Timer1 CH2N
            GPIOA->CFGLR &= ~(0xf << (4 * 2));
            GPIOA->CFGLR |= (GPIO_Speed_10MHz | GPIO_CNF_OUT_PP_AF) << (4 * 2);
            break;

        case SERVO_PIN_PC4:
            // Configure PC4 as Timer1 CH4
            GPIOC->CFGLR &= ~(0xf << (4 * 4));
            GPIOC->CFGLR |= (GPIO_Speed_10MHz | GPIO_CNF_OUT_PP_AF) << (4 * 4);
            break;
    }

    // Timer1 Configuration
    TIM1->PSC = 1200 - 1;  // Prescaler for 50Hz (48MHz/1200 = 40kHz)
    TIM1->ATRLR = SERVO_PWM_PERIOD - 1;  // Auto-reload value

    // Configure channels based on selected pin
    if (pin == SERVO_PIN_PA2) {
        // Configure Timer1 CH2N
        TIM1->CHCTLR1 |= TIM_OC2M_2 | TIM_OC2M_1;  // PWM mode 1
        TIM1->CHCTLR1 |= TIM_OC2PE;                // Preload enable
        TIM1->CCER |= TIM_CC2NE;                   // Enable CH2N output
    } else {
        // Configure Timer1 CH4
        TIM1->CHCTLR2 |= TIM_OC4M_2 | TIM_OC4M_1;  // PWM mode 1
        TIM1->CHCTLR2 |= TIM_OC4PE;                // Preload enable
        TIM1->CCER |= TIM_CC4E;                    // Enable CH4 output
    }

    // Enable Timer1 counter and outputs
    TIM1->BDTR |= TIM_MOE;
    TIM1->CTLR1 |= TIM_CEN;

    // Set initial position (90 degrees)
    servo_write(servo, 90);
}

void servo_write(Servo* servo, uint8_t angle) {
    // Constrain angle
    if (angle > SERVO_MAX_ANGLE) angle = SERVO_MAX_ANGLE;

    uint16_t pulse = angle_to_pulse(angle);

    // Update the appropriate compare register based on pin selection
    if (servo->pin == SERVO_PIN_PA2) {
        TIM1->CH2CVR = pulse;
    } else {
        TIM1->CH4CVR = pulse;
    }

    servo->current_angle = angle;
}

uint8_t servo_read(Servo* servo) { return servo->current_angle; }
