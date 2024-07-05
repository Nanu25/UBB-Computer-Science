#include <iostream>
#include "Person.h"
#include "Ui.h"

int main() {
    Person serv;
    Ui ui{serv};
    ui.Start();

    return 0;
}
