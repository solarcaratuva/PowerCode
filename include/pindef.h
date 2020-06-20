#ifndef PINDEF_H
#define PINDEF_H

/***************************/
/* pin definitions for CAN */
/***************************/
#define CAN1_RX PD_0    // BMS CAN
#define CAN1_TX PD_1
#define CAN2_RX PB_12   // Main CAN to rest of car
#define CAN2_TX PB_13
#define CAN3_RX PB_3    // Unused CAN
#define CAN3_TX PB_4

/****************************/
/* pin definitions for LEDs */
/****************************/
#define BMS_ERROR_LED LED1
#define CAN_ERROR_LED LED2
//#define UNUSED_LED LED3

/***********************************/
/* pin definitions for Digital I/O */
/***********************************/
#define DCDC_ON_IN D0

/**********************************/
/* pin definitions for Analog I/O */
/**********************************/
#define AUX_VOLTAGE_IN A0
#define DCDC_VOLTAGE_IN A1

#endif //PINDEF_H