/**Calculates rps of a motor assuming the motor produces an interrupt every 1/48th
of a rotation. The program waits until 48 interrupts have occurred (one full 
rotation) to calculate rps but could be edited to caluclate on an arbitrary cycle
*/
#include "mbed.h"
#define WAIT_TIME 100ms
/**
How to calculate WAIT_TIME based on diameter of wheel
mph * 5280 * 12 / 3600 / pi / diameter = rps (rotations per second)
rps * 48 = ticks per second
(ticks per second)^-1 = seconds per tick = WAIT_TIME
*/


InterruptIn button(LED1); // the LED which is modeling the interrupt from the motor
Ticker reader; // the timer interrupt that causes rps to be calculated
static int counter = 0; // number of ticks, increments with every interrupt from the LED(motor)
static float rps = 0; // rotations per second of the wheel

void incrementCounter()
{
    counter++;
}

int resetCounter() 
{
    counter = 0;
    return 0;
}

void readCounter()
{
    rps = (counter/48.0)/WAIT_TIME.count()*1000.0;
    resetCounter();
}

int main()
{
    // tell the interrupts which functions to run when they fire
    button.rise(&incrementCounter);
    reader.attach(&readCounter, WAIT_TIME);
    printf("starting!\n");
    while(1) {
        // print out the rps every second
        printf("The rps is: %f\n", rps);
        wait_us(1000000);
    }
}
