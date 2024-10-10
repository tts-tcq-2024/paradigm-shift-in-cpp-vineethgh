#include <iostream>
#include <cassert>
#include <string>
using namespace std;
bool checkForRange(float element , float lowerLimit, float upperLimit)
{
    if(element > lowerLimit && element > upperLimit)
    {
        return true;
    }
    return false;
}
void checkForTempWarning(float temperature, std::string &messageTemp) {
    if ( checkForRange(temperature,0,2.25)) {
        messageTemp = "Warning: Approaching low Temperature";
    } else if (checkForRange(temperature,42.75,45)) {
        messageTemp = "Warning: Approaching High Temperature";
    }
}
void checkForSocWarning(float soc, std::string &messageSoc) {
    if (checkForRange(soc,20,24)) {
        messageSoc = "Warning: Approaching discharge";
    } else if (checkForRange(soc,76,80) {
        messageSoc = "Warning: Approaching charge-peak";
    }
}
void checkForChargeRateWarning(float chargeRate, std::string &messageChargeRate) {
    if (checkForRange(chargeRate,0.76,0.8)) {
        messageChargeRate = "Warning: Approaching high chargeRate";
    }
}
bool checkTemperature(float temperature, std::string &messageTemp) {
    if (temperature < 0) {
        messageTemp = "Temperature too low!";
        return false;
    } else if (temperature > 45) {
        messageTemp = "Temperature too high!";
        return false;
    }
    return true;
}
bool checkSOC(float soc, std::string &messageSoc) {
    if (soc < 20) {
        messageSoc = "State of Charge too low!";
        return false;
    } else if (soc > 80) {
        messageSoc = "State of Charge too high!";
        return false;
    }
    return true;
}
bool checkChargeRate(float chargeRate, std::string &messageChargeRate) {
    if (chargeRate > 0.8) {
        messageChargeRate = "Charge Rate too high!";
        return false;
    }
    return true;
}
bool performCheck(float temperature, float soc, float chargeRate, std::string &message) {
    std::string messageTemp;
    std::string messageSoc;
    std::string messageChargeRate;
    bool temperatureOk = checkTemperature(temperature, messageTemp);
    bool socOk = checkSOC(soc, messageSoc);
    bool chargeRateOk = checkChargeRate(chargeRate, messageChargeRate);
    message = messageTemp + messageSoc + messageChargeRate;
    return temperatureOk && socOk && chargeRateOk;
}

void performWarningCheck(float temperature, float soc, float chargeRate,std::string &messageWarning) {
    std::string messageTemp;
    std::string messageSoc;
    std::string messageChargeRate;
    checkForTempWarning(temperature, messageTemp);
    checkForSocWarning(soc, messageSoc);
    checkForChargeRateWarning(chargeRate, messageChargeRate);
    messageWarning = messageTemp + messageSoc + messageChargeRate;
}

bool batteryIsOk(float temperature, float soc, float chargeRate, std::string &message,std::string &messageWarning) {
    bool allChecksOk = performCheck(temperature, soc, chargeRate, message);
    if (allChecksOk) {
        message = "Battery is OK.";
        performWarningCheck(temperature, soc, chargeRate, messageWarning);
    }
    return allChecksOk;
}
void testBatteryIsOk() {
    std::string message;
    std::string messageWarning;
    // Test case where battery is OK
    assert(batteryIsOk(25, 70, 0.7, message, messageWarning) == true);
    assert(message == "Battery is OK.");
    // Test case where temperature is too low
    assert(batteryIsOk(-1, 70, 0.7, message, messageWarning) == false);
    assert(message == "Temperature too low!");
    // Test case where temperature is too high
    assert(batteryIsOk(50, 70, 0.7, message, messageWarning) == false);
    assert(message == "Temperature too high!");
    // Test case where SOC is too low
    assert(batteryIsOk(25, 10, 0.7, message, messageWarning) == false);
    assert(message == "State of Charge too low!");
    // Test case where SOC is too high
    assert(batteryIsOk(25, 100, 0.7, message, messageWarning) == false);
    assert(message == "State of Charge too high!");
    // Test case where charge rate is too high
    assert(batteryIsOk(25, 70, 0.9, message, messageWarning) == false);
    assert(message == "Charge Rate too high!");
    //Test case where temperature is too low, SOC is too low, charge rate is too high
    assert(batteryIsOk(-1, 19, 0.9, message, messageWarning) == false);
    assert(message == "Temperature too low!State of Charge too low!Charge Rate too high!");

    //Test case where warning messages are present
    //Test case for low temperature warning
    assert(batteryIsOk(2, 70, 0.7, message, messageWarning) == true);
    assert(message == "Battery is OK.");
    assert(messageWarning == "Warning: Approaching low Temperature");
    //Test case for high temperature warning
    assert(batteryIsOk(44, 70, 0.7, message, messageWarning) == true);
    assert(messageWarning == "Warning: Approaching High Temperature");
    //Test case for discharge warning
    assert(batteryIsOk(30, 21, 0.7, message, messageWarning) == true);
    assert(messageWarning == "Warning: Approaching discharge");
    //Test case for charge-peak warning
    assert(batteryIsOk(30, 79, 0.7, message, messageWarning) == true);
    assert(messageWarning == "Warning: Approaching charge-peak");
    //Test case for high chargeRate warning
    assert(batteryIsOk(30, 70, 0.79, message, messageWarning) == true);
    assert(messageWarning == "Warning: Approaching high chargeRate");
    //Test case for All have warnings
    assert(batteryIsOk(2, 21, 0.79, message, messageWarning) == true);
    assert(messageWarning == "Warning: Approaching low TemperatureWarning: Approaching dischargeWarning: Approaching high chargeRate");
}
int main() {
    testBatteryIsOk();
    cout << "All tests passed.\n";
    return 0;
}
