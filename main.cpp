#include <mbed.h>

DigitalOut led1(D13);

// Simulates motor ramping up, maintaining, and then slowing down
void simulateMotor() {
  int pulsePerSec = 48;
  led1 = 0;
  int usTime;

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

  // Run at 1rps
  for (int i = 0; i < 19360; i++) {
      led1 = !led1;
      wait_us(usTime);
  }

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
}


int main() {
  
  while(1) {
      simulateMotor();
      wait_us(3000000);
  }
}