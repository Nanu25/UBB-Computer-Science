#include <iostream>
#include "Block.h"
#include "House.h"
#include "Service.h"
#include "UI.h"

int main() {
    Service s;
    UI ui{s};
    ui.Start();
    return 0;
}