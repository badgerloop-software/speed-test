/**Calculates rps of a motor assuming the motor produces an interrupt every 1/48th
of a rotation. The program waits until 48 interrupts have occurred (one full 
rotation) to calculate rps but could be edited to caluclate on an arbitrary cycle
*/
#include "mbed.h"

InterruptIn button(LED1);
int counter = 0;

int incrementCounter()
{
counter++;
return 0;
}

int resetCounter() 
{
counter = 0;
return 0;
}


int main()
{
    button.rise(&incrementCounter);
    time_t start = time(NULL);
    printf("starting!\n");
    while(1) {
       if (counter == 48) {   //one roto has occurred
       //rotations per second calculation:
           time_t end = time(NULL);
           time_t total = (end - start);
           //do something to output this number, I don't know what
            printf("It took %d units\n", total);
           //prepare for new rps calculation
           if (resetCounter()) {
               printf("Error occurred while resetting counter");
           }
           start = time(NULL);
       }
    }
    
}
