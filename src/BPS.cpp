#include "BPS.h"

// prints ON if sig is true, OFF if sig is false
string ONOFF(bool sig) { return sig ? "ON" : "OFF"; }

BPS::BPS(uint32_t addr)
{
    ecuID = addr;
}

uint32_t BPS::parse(const CANMessage &msg)
{
    uint32_t messageID = msg.id;

    // msg.id = uint32_t
    // msg.data = uint8_t[msg.len<=8]

    // message 1: error codes, highest priority, 24 ms transmit cycle
    if (messageID == 1)
        bpsErrors = *(BPSErrors *)msg.data;
    // message 2: battery status, middle priority, 16 ms transmit cycle
    else if (msg.id == 2)
        batteryStatus = *(BatteryStatus *)msg.data;
    // message 3: bps status, lowest priority, 8 ms transmit cycle
    else if (msg.id == 3)
        bpsStatus = *(BPSStatus *)msg.data;

    return messageID;
}

void BPS::print() const
{
    printf("Battery Status:\n");
    printf("Pack Current: %u.%u A\n", batteryStatus.packCurrent / 10, batteryStatus.packCurrent % 10);
    printf("Pack Voltage: %u.%u V\n", batteryStatus.packVoltage / 10, batteryStatus.packVoltage % 10);
    printf("Pack SOC: %u.%u%%\n", batteryStatus.packSOC / 2, batteryStatus.packSOC % 2 * 5);
    printf("Pack High Temperature: %u deg C\n", batteryStatus.packHighTemp);
    printf("Pack Average Temperature: %u deg C\n\n", batteryStatus.packAvgTemp);

    /*
    printf("BPS Status:\n");
    printf("Discharge Relay: %s\n", ONOFF(bpsStatus.relayStatus.dischargeEnable));
    printf("Charge Relay: %s\n", ONOFF(bpsStatus.relayStatus.chargeEnable));
    printf("Charger Safety: %s\n", ONOFF(bpsStatus.relayStatus.chargerSafetyEnable));
    printf("Malfunction Indicator: %s\n", ONOFF(bpsStatus.relayStatus.malfunction));
    printf("Multi-purpose Output: %s\n", ONOFF(bpsStatus.relayStatus.multiPurposeOutputStatus));
    printf("Always-On Signal: %s\n", ONOFF(bpsStatus.relayStatus.alwaysOn));
    printf("Is-Ready Signal: %s\n", ONOFF(bpsStatus.relayStatus.isReady));
    printf("Is-Charging Signal: %s\n", ONOFF(bpsStatus.relayStatus.isCharging));
    printf("Pack Charge Current Limit: %u A\n", bpsStatus.packCCL);
    printf("Pack Discharge Current Limit: %u A\n", bpsStatus.packDCL);
    printf("Pack Discharge Current Limit Status: %X\n\n", bpsStatus.currentLimitStatus);
    */

    // TODO: instead of printing all errors ON/OFF, only print ON errors?
    /*
    printf("BPS Errors:\n");
    printf("Internal Comm Fault (P0A1F): %s\n", ONOFF(bpsErrors.P0A1F));
    printf("Internal Conversion Fault (P0A00): %s\n", ONOFF(bpsErrors.P0A00));
    printf("Weak Cell Fault (P0A80): %s\n", ONOFF(bpsErrors.P0A80));
    printf("Low Cell Voltage Fault (P0AFA): %s\n", ONOFF(bpsErrors.P0AFA));
    printf("Comm Fault? (U0100): %s\n", ONOFF(bpsErrors.U0100));
    printf("Open Wiring Fault (P0A04): %s\n", ONOFF(bpsErrors.P0A04));
    printf("Current Sensor Fault (P0AC0): %s\n", ONOFF(bpsErrors.P0AC0));
    printf("Pack Voltage Sensor Fault (P0A01): %s\n", ONOFF(bpsErrors.P0A01));
    printf("Weak Pack Fault (P0A02): %s\n", ONOFF(bpsErrors.P0A02));
    printf("Voltage Redundancy Fault (P0A03): %s\n", ONOFF(bpsErrors.P0A03));
    printf("Fan Monitor Fault (P0A81): %s\n", ONOFF(bpsErrors.P0A81));
    printf("Thermistor Fault (P0A9C): %s\n", ONOFF(bpsErrors.P0A9C));
    printf("Always-On Supply Fault (P0560): %s\n", ONOFF(bpsErrors.P0560));
    printf("High Voltage Isolation Fault (P0AA6): %s\n", ONOFF(bpsErrors.P0AA6));
    printf("12 V Power Supply Fault (P0A05): %s\n", ONOFF(bpsErrors.P0A05));
    printf("Charge Limit Enforcement Fault (P0A06): %s\n", ONOFF(bpsErrors.P0A06));
    printf("Discharge Limit Enforcement Fault (P0A07): %s\n", ONOFF(bpsErrors.P0A07));
    printf("Charger Safety Relay Fault (P0A08): %s\n", ONOFF(bpsErrors.P0A08));
    printf("Internal Memory Fault (P0A09): %s\n", ONOFF(bpsErrors.P0A09));
    printf("Internal Thermistor Fault (P0A0A): %s\n", ONOFF(bpsErrors.P0A0A));
    printf("Internal Logic Fault (P0A0B): %s\n", ONOFF(bpsErrors.P0A0B));
    */
}