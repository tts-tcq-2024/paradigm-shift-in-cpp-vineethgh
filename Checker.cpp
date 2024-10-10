#include <iostream>
#include <cassert>
#include <string>
using namespace std;
checkForTempWarning(float temperature, std::string &messageTemp) {
    if (temperature > 0 && temperature < 2.25) {
        messageTemp = "Warning: Approaching low Temperature";
        return false;
    } else if (temperature > 42.75 && temperature < 45) {
        messageTemp = "Warning: Approaching High Temperature";
        return false;
    }
    return true;
}
checkForSocWarning(float soc, std::string &messageSoc) {
    if (soc > 20 && soc < 24) {
        messageSoc = "Warning: Approaching discharge";
        return false;
    } else if (soc > 76 && soc < 80) {
        messageSoc = "Warning: Approaching charge-peak";
        return false;
    }
    return true;
}
bool checkForChargeRateWarning(float chargeRate, std::string &messageChargeRate) {
    if (chargeRate > 0.76 && chargeRate < 0.8) {
        messageChargeRate = "Warning: Approaching high chargeRate";
        return false;
    }
    return true;
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

bool performWarningCheck(float temperature, float soc, float chargeRate,std::string &messageWarning) {
    std::string messageTemp;
    std::string messageSoc;
    std::string messageChargeRate;
    bool temperatureOk = checkTemperature(temperature, messageTemp);
    bool socOk = checkSOC(soc, messageSoc);
    bool chargeRateOk = checkChargeRate(chargeRate, messageChargeRate);
    messageWarning = messageTemp + messageSoc + messageChargeRate;
    return temperatureOk && socOk && chargeRateOk;
}

bool batteryIsOk(float temperature, float soc, float chargeRate, std::string &message,std::string &messageWarning) {
    bool allChecksOk = performCheck(temperature, soc, chargeRate, message);
    if (allChecksOk) {
        message = "Battery is OK.";
        performWarningCheck(temperature, soc, chargeRate, messageWarning)
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
    assert(batteryIsOk(-1, 19, 0.9, message, messageWarning) == false);
    assert(message == "Temperature too low!State of Charge too low!Charge Rate too high!");

    //Test case where warning messages are present
    assert(batteryIsOk(23, 70, 0.7, message, messageWarning) == true);
    assert(message == "Battery is OK.");
    assert(messageWarning == "Warning: Approaching low Temperature");
}
int main() {
    testBatteryIsOk();
    cout << "All tests passed.\n";
    return 0;
}
