
#include "../include/service.h"

typedef struct {
    int pinNumber;
    int rideId;
} RideDoneRequest;

typedef struct {
    int pinNumber;
    int rideId;
} RideReservationRequest;

typedef struct RideClient {
    void (*send)(void*);
} RideClient;
static RideClient* rideClient;

void httpRidedone(RideDoneRequest* request) {
    rideDone(request->rideId, request->pinNumber);
}

void httpRideReservation(RideReservationRequest* request) {
    //stub
    rideClient->send(request);
}

