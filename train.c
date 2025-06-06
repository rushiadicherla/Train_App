#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "train_ticket.h"
#include "train.h"
#define TRAINS_FILE "trains.txt"

Train* load_trains() {
        FILE *fp = fopen(TRAINS_FILE,"r");
        if(!fp) return NULL;

        Train *head = NULL, *temp = NULL;
        Train *new_train;

        while(!feof(fp)){
                new_train = malloc(sizeof(Train));
                if(fscanf(fp,"%d %s %s %s %d %d",&new_train->train_number,new_train->train_name,new_train->source,new_train->destination,&new_train->total_seats,&new_train->available_seats)!=6){
                        free(new_train);
                        break;
                }
                new_train->next = NULL;
                if (!head) head = new_train;
                else temp->next = new_train;
                temp = new_train;
        }
        fclose(fp);
        return head;
}

void save_train(Train *train){
        FILE *fp = fopen(TRAINS_FILE,"a"); //a
        if(!fp){
                printf("Error saving train.\n");
                return;
        }
        fprintf(fp,"%d %s %s %s %d %d\n",train->train_number,train->train_name,train->source,train->destination,train->total_seats,train->available_seats);
        fclose(fp);
}

void list_trains(Train *head){
        if(!head){
        printf("NO Available Trains");
        }
        printf("\nAvailable Trains:\n");
        printf("%-10s %-15s %-15s %-15s %-10s \n","Number","Name","Source","Destination","Total Seats");
        for(Train *t = head; t ;t = t->next){
                printf("%-10d %-15s %-15s %-15s %-10d \n",t->train_number,t->train_name,t->source,t->destination,t->total_seats);
        }
}

void add_train() {
        Train *trains = load_trains();
        Train *new_train = malloc(sizeof(Train));
        int found = 0;

        printf("Enter train number: ");
        scanf("%d",&new_train->train_number);
        for(Train *t= trains; t ;t= t->next){
                if(t->train_number == new_train->train_number){
                        printf("Train number already exists.\n");
                        found = 1;
                        break;
                }
        }
        if(found) return;
        printf("Enter train name: ");
        scanf("%s",new_train->train_name);
        printf("Enter source: ");
        scanf("%s",new_train->source);
        printf("Enter destination: ");
        scanf("%s",new_train->destination);
        printf("Enter total seats: ");
        scanf("%d",&new_train->total_seats);

        new_train->available_seats = new_train->total_seats;
        new_train->next = NULL;
        save_train(new_train);
        printf("Train Added Successfully.\n");
}
