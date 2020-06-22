#include <mbed.h>

#include "pindef.h"

#if defined(DEVICE_CAN)

DigitalOut led1(LED1);
DigitalOut led2(LED2);

CAN can1(CAN1_RX, CAN1_TX);
CAN can2(CAN2_RX, CAN2_TX);

Ticker canTxTicker;

char countId = 0;

// WARNING: This method is NOT safe to call in an ISR context (if RTOS is enabled)
// This method is Thread safe (CAN is Thread safe)
bool sendCANMessage(const char *data, const unsigned char len = 8)
{
    if (len > 8 || !can1.write(CANMessage(1337, data, len)))
        return false;

    return true;
}

// WARNING: This method will be called in an ISR context
void canTxIrqHandler()
{
    if (sendCANMessage(&countId, 1))
    {
        led1 = !led1;
        printf("Message sent: %d\n", countId); // This should be removed except for testing CAN
        ++countId;
    }
}

// WARNING: This method will be called in an ISR context
void canRxIrqHandler()
{
    CANMessage receivedCANMessage;
    while (can2.read(receivedCANMessage))
    {
        led2 = !led2;
        printf("Message received: %d\n", receivedCANMessage.data[0]); // This should be changed to copying the CAN data to a global variable, except for testing CAN
    }
}

void canInit()
{
    canTxTicker.attach(&canTxIrqHandler, 1); // float, in seconds
    can2.attach(&canRxIrqHandler, CAN::RxIrq);
}

int main()
{
    canInit();

    char mainLoopCount = 0;
    while (1)
    {
        printf("main() loop #%d\n", mainLoopCount);
        ++mainLoopCount;

        thread_sleep_for(1000); // in ms
    }
}

#else
#error CAN NOT SUPPORTED

#endif