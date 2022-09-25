#include <mbed.h>

// 0 to hold speed, 1 to simulate motor
#define HOLD_OR_MOTOR 0
#define HOLD_SPEED 11
#define MOTOR_START_SPEED 1
#define MOTOR_TOP_SPEED 55
#define RUN_DELAY 3


DigitalOut led1(D13);

void holdRps(int rps) {
    int usTime = 500000 / rps;
    for (int i = 0; i < 112; i++) {
      led1 = !led1;
      wait_us(usTime);
    }
}


// Simulates motor ramping up, maintaining, and then slowing down
void simulateMotor() {
  int pulsePerSec = 48;
  led1 = 0;
  int usTime;

  /*
  printf("Starting\n");
  // Ramp up from 1/48rps to 1rps
  for (;pulsePerSec < 3872; pulsePerSec += 1) {
      if (!(pulsePerSec & 0x5)) {
        printf("Current rps %d\n", pulsePerSec / 48); 
      }
      for (int i = 0; i < 10; i++) {
        led1 = !led1;
        wait_us(usTime);
      }
      usTime = 1000000 / pulsePerSec;
      
  }
  printf("At top speed\n");
  */
  
  usTime = 1000000 / 22;
  // Run at 1rps
  for (int i = 0; i < 112; i++) {
      led1 = !led1;
      wait_us(usTime);
  }
  
  /*
  printf("Ramping down\n");
  // Ramp down to 1/48rps
  for (;pulsePerSec > 48; pulsePerSec -= 1) {
      if (!(pulsePerSec & 0x5)) {
        printf("Current rps %d\n", pulsePerSec / 48); 
      }
      for (int i = 0; i < 10; i++) {
        led1 = !led1;
        wait_us(usTime);
      }
      usTime = 1000000 / pulsePerSec; 
  }
  led1 = 0;
  printf("Done\n");
  */
}


int main() {
  
  while(1) {
      holdRps(11);
      wait_us(3000000);
  }
}