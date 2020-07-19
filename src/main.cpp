#include <mbed.h>

#include "pindef.h"
#include "BPS.h"

#if defined(DEVICE_CAN)

DigitalOut led1(LED1);
DigitalOut led2(LED2);

CAN can1(CAN1_RX, CAN1_TX);
CAN can2(CAN2_RX, CAN2_TX);

Ticker canTxTicker;

BPS bps;
BatteryStatus testBatteryStatus = {725, 1344, 163, 31, 28};

// WARNING: This method is NOT safe to call in an ISR context (if RTOS is enabled)
// This method is Thread safe (CAN is Thread safe)
bool sendCANMessage(const char *data, const unsigned char len = 8)
{
    if (len > 8 || !can1.write(CANMessage(2, data, len)))
        return false;

    return true;
}

// WARNING: This method will be called in an ISR context
void canTxIrqHandler()
{
    if (sendCANMessage((char *)&testBatteryStatus, 7))
    {
        led1 = !led1;
        printf("Message sent: %u\n", testBatteryStatus.packCurrent); // This should be removed except for testing CAN
        //++testBatteryStatus.packCurrent;
    }
}

// WARNING: This method will be called in an ISR context
void canRxIrqHandler()
{
    CANMessage receivedCANMessage;
    while (can2.read(receivedCANMessage))
    {
        led2 = !led2;
        bps.parse(receivedCANMessage);
        printf("Message received: %u\n", ((BatteryStatus *)receivedCANMessage.data)->packCurrent); // This should be changed to copying the CAN data to a global variable, except for testing CAN
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

    while (1)
    {
        bps.print();
        if(memcmp(&bps.batteryStatus, &testBatteryStatus, sizeof(BatteryStatus)) == 0)
            printf("Correct Output.\n\n");

        thread_sleep_for(1000); // in ms
    }
}

#else
#error CAN NOT SUPPORTED

#endif