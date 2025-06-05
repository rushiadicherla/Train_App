#ifndef USER_H
#define USER_H

#define MAX_NAME 50
#define MAX_PASS 20
typedef struct User {
    char username[MAX_NAME];
    char password[MAX_PASS];
    struct User *next;
}User;
User * load_users();
void save_user(User *);
int sign_up();
int sign_in();
int is_valid_password(const char *);

#endif
