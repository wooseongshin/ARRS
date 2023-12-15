
#include "../include/repository.h"
#include "../include/service.h"
#include "../include/input_interface.h"

int main() {
    initRepository();
    initService();
    startCLI();
    return 0;
}

