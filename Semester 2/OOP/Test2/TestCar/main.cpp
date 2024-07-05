#include <iostream>
#include "Service.h"
#include "Ui.h"

int main() {
    Service serv;
    Ui ui{serv};
    ui.start();
    return 0;
}
