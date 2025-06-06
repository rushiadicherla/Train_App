#ifndef BOOKING_H
#define BOOKING_H

#include "train.h"

#define MAX_NAME 50
#define DATE_LEN 11

typedef struct Booking {
    int train_number;
    char journey_date[DATE_LEN];
    int seat_no;
    char passenger_name[MAX_NAME];
    int age;
    char gender;
    struct Booking *next;
} Booking;

Booking* load_bookings();
void save_booking(Booking *);
void reserve_ticket(Train *);
void cancel_ticket();
void display_booking();

#endif
