#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include "user.h"

#define USERS_FILE  "users.txt"

int is_valid_password(const char *password){
        if(strlen(password)<8)
                return 0;
        int has_upper=0,has_lower=0,has_digit=0,has_special=0;
        for (int i = 0; password[i]; i++) {
                if (password[i] >= 'A' && password[i] <= 'Z') has_upper = 1;
                else if (password[i] >= 'a' && password[i] <= 'z') has_lower = 1;
                else if (password[i] >= '0' && password[i] <= '9') has_digit = 1;
                else has_special = 1;
        }
        return has_upper && has_lower && has_digit && has_special;
}
User* load_users(){
        FILE *fp= fopen(USERS_FILE,"r");
        if(!fp)return NULL;

        User *head=NULL,*temp;
        char uname[MAX_NAME],pass[MAX_PASS];

        while(fscanf(fp,"%s %s",uname,pass)==2){
                User *new_user = malloc(sizeof(User));
                strcpy(new_user->username,uname);
                strcpy(new_user->password,pass);
                new_user->next = NULL;

                if (!head) head = new_user;
                else temp->next = new_user;
                temp = new_user;
        }
        fclose(fp);
        return head;
}

void save_user(User *user){
        FILE *fp = fopen(USERS_FILE,"a");
        if(!fp){
                printf("Error saving user!\n");
                return ;
        }
        fprintf(fp,"%s %s\n",user->username,user->password);
        fclose(fp);
}

int sign_up() {
        char uname[MAX_NAME],pass[MAX_PASS];
        int attempts=0;
        User *users = load_users();

        printf("Enter new username: ");
        scanf("%s",uname);

        for(User *u=users; u ;u=u->next){
                if(strcmp(u->username,uname)==0){
                        printf("Username already exists.\n");
                        return 0;
                }
        }

        while(attempts<5)
        {
                printf("Enter new password: ");
                scanf("%s",pass);

                if(is_valid_password(pass)){
                        User *new_user = malloc(sizeof(User));
                        strcpy(new_user->username,uname);
                        strcpy(new_user->password,pass);
                        new_user->next=NULL;
                        save_user(new_user);
                        printf("User registered successfully!\n");
                        return 1;
                }
                else{
                        printf("Invalid password format. Try again.\n");
                        attempts++;
                }
        }
        printf("TIME OUT. Too many attemps.\n");
        return 0;
}

int sign_in() {
        char uname[MAX_NAME],pass[MAX_PASS];
        int attemps=0;
        User *users = load_users();

        while(attemps<3){
                printf("Username:");
                scanf("%s",uname);
                printf("Password:");
                scanf("%s",pass);

                for(User *u=users; u ;u=u->next){
                        if(strcmp(u->username,uname)==0 && strcmp(u->password,pass)==0){
                                printf("Login successful!\n");
                                return 1;
                        }
                }
                printf("Invalid credentials. Try again.\n");
                attemps++;
        }
        printf("YOU have reached max number of attemps. Please wait 5 minutes.\n");
        return 0;
}
