
#include <string.h>
#include <stdlib.h>
#include "../include/repository.h"
#include "../include/constants.h"
static Repository repository;

Repository* getRepository() {
    return &repository;
}

void initRepository() {
    repository.tickets = (Ticket*)malloc(sizeof(Ticket) * MAX_TICKET_COUNT);
    repository.rides = (Ride*)malloc(sizeof(Ride) * DEFAULT_RIDE_COUNT);
    repository.rideId = 0;
    repository.pinNumber = 0;
    repository.size = 0;
    repository.capacity = REPOSITORY_INITIAL_CAPACITY;
}

Ticket createTicket(char* userName,time_t usageDate, PassType passType, int magicPassUsageCount) {
    Ticket ticket;
    strcpy(ticket.userName, userName);
    ticket.pinNumber = repository.pinNumber++;
    ticket.usageDate = usageDate;
    ticket.passType = passType;
    ticket.magicPassUsageCount = magicPassUsageCount;
    saveTicket(ticket);
    return ticket;
}

void saveTicket(Ticket ticket) {
    repository.tickets[repository.pinNumber] = ticket;
}

Ticket* getTicketByPin(int pinNumber) {
    for (int i = 0; i < MAX_TICKET_COUNT; i++) {
        if (repository.tickets[i].pinNumber == pinNumber) {
            return &repository.tickets[i];
        }
    }
    return NULL;
}

Ride createRide(char* name,int maxRiders, RideStatus status) {
    Ride ride = {0,};
    if (repository.rideId == DEFAULT_RIDE_COUNT) {
        printf("놀이기구를 더 이상 추가할 수 없습니다. \n");
        return ride;
    }

    strcpy(ride.name, name);
    ride.id = repository.rideId++;
    ride.maxRiders = maxRiders;
    ride.reservedRiders = 0;
    ride.status = status;
    saveRide(ride);
    return ride;
}

void saveRide(Ride ride) {
    repository.rides[repository.rideId] = ride;
}

Ride* getRideById(int rideId) {
    for (int i = 0; i < DEFAULT_RIDE_COUNT; i++) {
        if (repository.rides[i].id == rideId) {
            return &repository.rides[i];
        }
    }

    printf("해당 ID의 놀이기구가 없습니다. \n");
    return NULL;
}

Ride* getAllRides() {
    return repository.rides;
}

void saveTicketsToFile(const char* filename, Ticket* tickets, size_t size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }

    for (size_t i = 1; i <= size; ++i) {
        fprintf(file, "%d %s %lld %d %d\n", tickets[i].pinNumber, tickets[i].userName,
                tickets[i].usageDate, tickets[i].passType, tickets[i].magicPassUsageCount);
    }

    fclose(file);
}

// 놀이기구 정보를 TXT 파일에 저장하는 함수
void saveRidesToFile(const char* filename, Ride* rides, size_t size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }

    for (size_t i = 1; i <= size; ++i) {
        fprintf(file, "%d %s %d %d %d\n", rides[i].id, rides[i].name, rides[i].maxRiders,
                rides[i].reservedRiders, rides[i].status);
    }

    fclose(file);
}

// Repository의 모든 정보를 TXT 파일로 저장하는 함수
void saveRepositoryToFile() {

    saveTicketsToFile("../ticket.txt", repository.tickets, repository.pinNumber);
    saveRidesToFile("../ride.txt", repository.rides, repository.rideId);
}







