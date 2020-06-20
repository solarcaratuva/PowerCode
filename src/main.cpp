#include <mbed.h>

#include "pindef.h"

#if defined(DEVICE_CAN) || defined(DOXYGEN_ONLY)

DigitalOut led1(LED1);
DigitalOut led2(LED2);
/** The constructor takes in RX, and TX pin respectively.
  * These pins, for this example, are defined in mbed_app.json
  */
CAN can1(CAN1_RX, CAN1_TX);
CAN can2(CAN2_RX, CAN2_TX);

bool receivedCAN = false;
CANMessage receivedCANMessage;

bool sendCANMessage(const char *data, const unsigned char len = 8)
{
    if (len > 8 || !can1.write(CANMessage(1337, data, len)))
        return false;

    led1 = !led1;
    return true;
}

void CAN_RxIrqHandler()
{
    if (can2.read(receivedCANMessage))
    {
        receivedCAN = true;
        led2 = !led2;
    }
}

int main()
{
    can2.attach(&CAN_RxIrqHandler, CAN::RxIrq);
    char count = 0;

    while (1)
    {
        if (sendCANMessage(&count, 1))
        {
            printf("Message sent: %d\n", count);
            ++count;
        }

        if (receivedCAN)
        {
            printf("Message received: %d\n", receivedCANMessage.data[0]);
            receivedCAN = false;
        }
        //wait(0.2);
        thread_sleep_for(1000); // in ms
    }
}

#else
#error CAN NOT SUPPORTED

#endif