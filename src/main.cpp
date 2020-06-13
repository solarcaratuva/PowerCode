#include <mbed.h>


#if defined(DEVICE_CAN) || defined(DOXYGEN_ONLY)

Ticker ticker;
DigitalOut led1(LED1);
DigitalOut led2(LED2);
/** The constructor takes in RX, and TX pin respectively.
  * These pins, for this example, are defined in mbed_app.json
  */
CAN can1(PD_0, PD_1);
CAN can2(PB_12, PB_13);
char counter = 0;

void send() {
    printf("send()\n");
    if(can1.write(CANMessage(1337, &counter, 1))) {
        printf("wloop()\n");
        counter++;
        printf("Message sent: %d\n", counter);
    } 
    led1 = !led1;
}

int main() {
    printf("main()\n");
    ticker.attach(&send, 1); // in seconds (float)
    CANMessage msg;
    while(1) {
        printf("loop()\n");
        if(can2.read(msg)) {
            printf("Message received: %d\n", msg.data[0]);
            led2 = !led2;
        } 
        //wait(0.2);
        thread_sleep_for(200); // in ms
    }
}

#else
  #error CAN NOT SUPPORTED
  
#endif