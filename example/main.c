#include "ch32v003fun.h"
#include "servo.h"

int main() {
    SystemInit();

    // Create servo instance
    Servo myServo;

    // Initialize servo on PA2
    servo_init(&myServo, SERVO_PIN_PA2);

    while (1) {
        // Sweep from 0 to 90 degrees
        for (int angle = 0; angle <= 90; angle += 1) {
            servo_write(&myServo, angle);
            Delay_Ms(15);
        }
        Delay_Ms(2000);
        // Sweep from 90 to 0 degrees
        for (int angle = 90; angle >= 0; angle -= 1) {
            servo_write(&myServo, angle);
            Delay_Ms(15);
        }
        Delay_Ms(2000);
    }
}
