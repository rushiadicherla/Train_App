#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "booking.h"
#include "train.h"

#define BOOKINGS_FILE "bookings.txt"

Booking* load_bookings() {
    FILE *fp = fopen(BOOKINGS_FILE, "r");
    if (!fp) return NULL;

    Booking *head = NULL, *tail = NULL, *new_booking;
    while (!feof(fp)) {
        new_booking = malloc(sizeof(Booking));
        if (fscanf(fp, "%d %s %d %s %d %c", &new_booking->train_number, new_booking->journey_date,
                   &new_booking->seat_no, new_booking->passenger_name, &new_booking->age, &new_booking->gender) != 6) {
            free(new_booking);
            break;
        }
        new_booking->next = NULL;
        if (!head) head = new_booking;
        else tail->next = new_booking;
        tail = new_booking;
    }
    fclose(fp);
    return head;
}

void save_booking(Booking *booking) {
    FILE *fp = fopen(BOOKINGS_FILE, "a");
    if (!fp) return;
    fprintf(fp, "%d %s %d %s %d %c\n", booking->train_number, booking->journey_date,
            booking->seat_no, booking->passenger_name, booking->age, booking->gender);
    fclose(fp);
}

void reserve_ticket(Train *trains) {
    int train_no, n;
    char date[DATE_LEN];
    char str[3];
    printf("Enter train number: ");
    scanf("%d", &train_no);
    printf("Enter journey date (YYYY-MM-DD): ");
    scanf("%s", date);

    strcpy(str,date+8);
    int dd = atoi(str);
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int today = t->tm_mday;

    int diff = dd-today;
if(diff>=0 && diff<=3)
{
    Train *train = trains;
    while (train && train->train_number != train_no) train = train->next;
    if (!train) {
        printf("Train not found.\n");
        return;
    }

    printf("Available seats: %d\n", train->available_seats);
    printf("Enter number of seats to reserve: ");
    scanf("%d", &n);

    if (n > train->available_seats) {
        printf("Only %d seats available. Booking that many.\n", train->available_seats);
        n = train->available_seats;
    }

    for (int i = 0; i < n; i++) {
        Booking *new_booking = malloc(sizeof(Booking));
        new_booking->train_number = train_no;
        strcpy(new_booking->journey_date, date);
        new_booking->seat_no = train->total_seats - train->available_seats + 1;

        printf("Enter passenger name: ");
        scanf("%s", new_booking->passenger_name);
        printf("Enter age: ");
        scanf("%d", &new_booking->age);
        printf("Enter gender (M/F): ");
        scanf(" %c", &new_booking->gender);

        new_booking->next = NULL;
        save_booking(new_booking);
        train->available_seats--;
        printf("seats__%d\n",train->available_seats);
        printf("Seat %d booked successfully.\n", new_booking->seat_no);
    }
}
else printf("Please enter valid date of journey.\n");
}

void cancel_ticket() {
    int train_no, seat_no;
    char date[DATE_LEN];
    printf("Enter train number: ");
    scanf("%d", &train_no);
    printf("Enter journey date (YYYY-MM-DD): ");
    scanf("%s", date);
    printf("Enter seat number to cancel: ");
    scanf("%d", &seat_no);

    Booking *head = load_bookings();
    FILE *fp = fopen(BOOKINGS_FILE, "w");
    Booking *curr = head;
    while (curr) {
        if (!(curr->train_number == train_no && strcmp(curr->journey_date, date) == 0 && curr->seat_no == seat_no)) {
            fprintf(fp, "%d %s %d %s %d %c\n", curr->train_number, curr->journey_date,
                    curr->seat_no, curr->passenger_name, curr->age, curr->gender);
        }
        curr = curr->next;
    }
    fclose(fp);
    printf("Seat %d cancelled successfully.If seat is present.\n", seat_no);
}

void display_booking() {
    int train_no, seat_no;
    char date[DATE_LEN];
    printf("Enter train number: ");
    scanf("%d", &train_no);
    printf("Enter journey date (YYYY-MM-DD): ");
    scanf("%s", date);
    printf("Enter seat number to view: ");
    scanf("%d", &seat_no);

    Booking *head = load_bookings();
    Booking *curr = head;
    while (curr) {
        if (curr->train_number == train_no && strcmp(curr->journey_date, date) == 0 && curr->seat_no == seat_no) {
            printf("Booking Details:\n");
            printf("Passenger: %s\nAge: %d\nGender: %c\n", curr->passenger_name, curr->age, curr->gender);
            return;
        }
        curr = curr->next;
    }
    printf("Booking not found.\n");
}
