#include <mbed.h>

DigitalOut led1(LED1);

void simulateMotor() {
  int pulsePerSec = 1;
  led1 = 0;
  int usTime;
  // Ramp up
  for (;pulsePerSec < 49; pulsePerSec++) {
      usTime = 1000000 / pulsePerSec;
      for (int i = 0; i < 10; i++) {
          led1 = !led1;
          wait_us(usTime);
      }
  }
  // Run at 1rps
  for (int i = 0; i < 480; i++) {
      led1 = !led1;
      wait_us(usTime);
  }

  // Ramp down
  for (;pulsePerSec > 0; pulsePerSec--) {
      usTime = 1000000 / pulsePerSec;
      for (int i = 0; i < 10; i++) {
          led1 = !led1;
          wait_us(usTime);
      }
  }
  led1 = 1;
}


int main() {
  
  // What you do in the main loop is not important
  while(1) {
      simulateMotor();
      wait_us(3000000);
  }
}