
#include "../include/repository.h"
#include "../include/service.h"
#include "../include/input_interface.h"

void scenario1() {
    createRide("rolercoaster\0", 100, Available);
    createRide("회전목마\0", 100, Available);
    createRide("자이로드롭\0", 100, Closed);
    createRide("자이로스윙\0", 100, Inspection);
    struct tm date;
    date.tm_year = 2023 - 1900;
    date.tm_mon = 12;
    date.tm_mday = 14;
    date.tm_hour = 12;
    date.tm_min = 0;
    date.tm_sec = 0;
    time_t time = mktime(&date);

    Ticket ticket1 = createTicket("woos", time, Daily, 3);
    Ticket ticket2 = createTicket("성주", time, Afternoon, 5);

    reserveRide(0, 0);
    reserveRide(1, 0);
}

int main() {
    initRepository();
    initService();
    scenario1();
    startCLI();
    return 0;
}

