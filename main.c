#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>

#include "user.h"
#include "train.h"
#include "booking.h"

void menu2(Train *trains) {
    char choice;
    do {
        printf("\n------------------MENU-2---------------------------\n");
        printf("R/r: Reserve Ticket\n");
        printf("C/c: Cancel Ticket\n");
        printf("B/b: Booking Details\n");
        printf("Q/q: Quit\n");
        printf("Enter choice: ");
        scanf(" %c", &choice);
        __fpurge(stdin);

        switch (choice) {
                case 'R': case 'r': reserve_ticket(trains); break;
            case 'C': case 'c': cancel_ticket(); break;
            case 'B': case 'b': display_booking(); break;
            case 'Q': case 'q': printf("Exiting...\n");break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 'Q' && choice != 'q');
}

int main() {
    int main_choice;
    Train *trains = load_trains();

    do {
        printf("\n------------------MENU-1---------------------------\n");
        printf("1: Sign-up\n");
        printf("2: Sign-in\n");
        printf("3: Add Train (Admin)\n");
        printf("0: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &main_choice);
        __fpurge(stdin);

        switch (main_choice) {
            case 1:
                sign_up();
                break;
            case 2:
                if (sign_in()) {
                    list_trains(trains);
                    menu2(trains);
                }
                break;
            case 3:
                add_train();
                trains = load_trains(); // Reload updated train list
                break;
            case 0:
                printf("Exiting application.\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (main_choice != 0);

    return 0;
}
