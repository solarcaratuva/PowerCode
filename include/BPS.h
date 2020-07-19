/*
 * Arslan Aziz
 * Interface with Orion standard BMS v1 over CAN
 * Updates battery & bps related fields
 */

#ifndef __BPS_H__
#define __BPS_H__

#include <stdint.h>

#include <mbed.h> // for the CANMessage class

#define DEFAULT_ECU_ID 0x7E3

// Struct holding error bits from the BMS
typedef struct BPSErrors
{
    // Custom Flag 0
    bool P0A1F; // internal comm fault
    bool P0A00; // internal conversion fault
    bool P0A80; // weak cell fault
    bool P0AFA; // low cell volt fault
    bool U0100; // comm fault?
    bool P0A04; // open wiring fault
    bool P0AC0; // current sensor fault
    bool P0A01; // pack volt sensor fault

    // Custom Flag 1
    bool P0A02; // weak pack fault
    bool P0A03; // volt redundancy fault
    bool P0A81; // fan monitor fault
    bool P0A9C; // thermistor fault
    bool P0560; // always-on supply fault
    bool P0AA6; // high volt isolation fault
    bool P0A05; // 12 volt power supply fault
    bool P0A06; // charge limit enforemcent fault

    // Custom Flag 2
    bool P0A07;   // discharge limit enforcement fault
    bool P0A08;   // charger safety relay fault
    bool P0A09;   // internal memory fault
    bool P0A0A;   // internal thermistor fault
    bool P0A0B;   // internal logic fault
    bool unused1; // unused
    bool unused2; // unused
    bool unused3; // unused
} BPSErrors;

// Struct holding info related to the state of the battery pack
typedef struct BatteryStatus
{
    uint16_t packCurrent; // in 0.1 A
    uint16_t packVoltage; // in 0.1 V
    uint8_t packSOC;      // in 0.5%
    uint8_t packHighTemp; // in 1 deg C
    uint8_t packAvgTemp;  // in 1 deg C
} BatteryStatus;

// Struct holding status bits related to the relays
// Each bit of a RelayStatus corresponds with a relay control pin or signal status
typedef struct RelayStatus
{
    bool dischargeEnable;
    bool chargeEnable;
    bool chargerSafetyEnable;
    bool malfunction;
    bool multiPurposeOutputStatus;
    bool alwaysOn;
    bool isReady;
    bool isCharging;
} RelayStatus;

// Struct holding reasons why a current limit was decreased
// Each bit of a CurrentLimitStatus corresponds to a reason for reducing the charge and/or discharge current limit
typedef struct CurrentLimitStatus
{
    // Bits 0-7
    bool DCLLowSOC;
    bool DCLHighCellResistance;
    bool DCLTemperature;
    bool DCLLowCellVoltage;
    bool DCLLowPackVoltage;
    bool unused1;
    bool DCLCCLVoltageFailSafe;
    bool DCLCCLCommunicationFailsafe;

    // Bits 8-15
    bool unused2;
    bool CClHighSOC;
    bool CCLHighCellResistance;
    bool CCLTemperature;
    bool CCLHighCellVoltage;
    bool CCLHighPackVoltage;
    bool CCLChargerLatch;
    bool CCLAlternateCurrentLimit;
} CurrentLimitStatus;

// Struct holding info related to the state of the BPS
typedef struct BPSStatus
{
    RelayStatus relayStatus;
    uint16_t packCCL; // in 1 A
    uint16_t packDCL; // in 1 A
    CurrentLimitStatus currentLimitStatus;
} BPSStatus;

class BPS
{
private:
    uint32_t ecuID;
    void printONOFF(bool sig) const;

public:
    BPSErrors bpsErrors;
    BatteryStatus batteryStatus;
    BPSStatus bpsStatus;

    BPS(uint32_t addr = DEFAULT_ECU_ID);

    uint32_t parse(const CANMessage &msg);

    void print() const;
};
#endif