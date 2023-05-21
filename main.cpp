// main.cpp
#include "VendingMachine.h"
#include "Service.h"
#include "UI.h"

int main() {
    VendingMachine vm("products.txt", "currencies.txt");
    Service service(vm);
    UI ui(service);

    ui.start();
}