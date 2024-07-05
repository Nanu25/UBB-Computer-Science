#include <iostream>
#include "Client.h"
#include "Person.h"
#include "RealEstateAgency.h"
#include "Ui.h"

int main() {
    RealEstateAgency a;
    Ui ui{a};
    ui.Start();
    return 0;
}
