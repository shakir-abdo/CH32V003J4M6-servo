#ifndef __SERVO_H
#define __SERVO_H

#include "ch32v003fun.h"

// Servo angles
#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 180

// PWM period for 50Hz (20ms)
#define SERVO_PWM_PERIOD \
    800  // For 50Hz with 48MHz system clock and prescaler of 1200

// Pin options for servo (based on Timer1 channels)
typedef enum {
    SERVO_PIN_PA2,  // TIM1_CH2N
    SERVO_PIN_PC4   // TIM1_CH4
} ServoPin;

// Servo structure
typedef struct {
    ServoPin pin;
    uint16_t current_angle;
} Servo;

// Function prototypes
void servo_init(Servo* servo, ServoPin pin);
void servo_write(Servo* servo, uint8_t angle);
uint8_t servo_read(Servo* servo);

#endif
