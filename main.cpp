#include <mbed.h>


// 0 to hold speed, 1 to simulate motor
#define HOLD_OR_MOTOR 0
#define HOLD_RPS 1
#define MOTOR_START_RPS 0.234 // Corresponds to 1mph
#define MOTOR_TOP_RPS 12.87 // Corresponds to 55mph
#define RUN_DELAY 3


/*///////// TOUCH CODE BELOW AT YOUR OWN RISK ///////////*/

DigitalOut led1(D13);

// Holds at specified rps for approx 5 sec
void holdRps() {
    int usTime = 500000 / (HOLD_RPS * 48);
    int numCycles = 5000000 / usTime;
    for (int i = 0; i < numCycles; i++) {
      led1 = !led1;
      wait_us(usTime);
    }
}


// Simulates motor ramping up, maintaining, and then slowing down
void simulateMotor() {
  int pulsePerSec = MOTOR_START_RPS * 48;
  static const int maxPulseSec = MOTOR_TOP_RPS * 48;
  led1 = 0;
  int usTime;

  
  printf("Starting\n");
  // Ramp up from 1/48rps to 1rps
  for (;pulsePerSec < maxPulseSec; pulsePerSec += 1) {
      // Print every time pulse increments by 48
      if ((pulsePerSec & 0x63) == 0x30) {
        printf("Current rps: %d\n", pulsePerSec >> 6); 
      }
      for (int i = 0; i < 10; i++) {
        led1 = !led1;
        wait_us(usTime);
      }
      usTime = 500000 / pulsePerSec;
      
  }
  printf("At top speed\n");
  static const int numCycles = 10 * maxPulseSec;
  // Hold at top speed for 5s
  for (int i = 0; i < numCycles; i++) {
      led1 = !led1;
      wait_us(usTime);
  }
  
  printf("Ramping down\n");
  // Ramp down to 1/48rps
  for (;pulsePerSec > 48; pulsePerSec -= 1) {
      // Print every time pulse increments by 48
      if ((pulsePerSec & 0x63) == 0x30) {
        printf("Current rps: %d\n", pulsePerSec >> 6); 
      }
      for (int i = 0; i < 10; i++) {
        led1 = !led1;
        wait_us(usTime);
      }
      usTime = 500000 / pulsePerSec; 
  }
  led1 = 0;
  printf("Done\n");
}


int main() {
  int delay = RUN_DELAY * 1000000;
  while(1) {
      if (HOLD_OR_MOTOR) {
        simulateMotor();
      } else {
        holdRps();
      }
      
      wait_us(delay);
  }
}