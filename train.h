#ifndef TRAIN_H
#define TRAIN_H

#define MAX_NAME 50

typedef struct Train {
    int train_number;
    char train_name[MAX_NAME];
    char source[MAX_NAME];
    char destination[MAX_NAME];
    int total_seats;
    int available_seats;
    struct Train *next;
}Train;

Train* load_trains();
void save_train(Train *);
void list_trains(Train *);
void add_train();

#endif
