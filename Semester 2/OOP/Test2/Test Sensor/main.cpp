#include <iostream>
#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "Device.h"
#include "Ui.h"

int main() {
    Device d;
    Ui ui{d};
    ui.Start();
    return 0;
}
