#include <iostream>
#include "Refrigerator.h"
#include "DishWasher.h"
#include "Service.h"
#include "Ui.h"

int main() {
    Service s;
    Ui ui(s);
    ui.Start();
    return 0;
}
