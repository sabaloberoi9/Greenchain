#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define DATA_FILE "users.txt"

typedef struct {
    int id;
    char name[50];
    float balance;
    float total_recycled_kg;
} User;

typedef struct TransactionNode {
    char action[100];
    float value_change;
    struct TransactionNode* next;
} TransactionNode;

User users[MAX_USERS];
int user_count = 0;
TransactionNode* history_head = NULL;

void load_data();
void save_data();
void add_transaction(char* action, float value);
void print_history();
void recycle_menu(int user_index);
void leaderboard();
void register_user();
int login_user();
void clear_buffer();

int main() {
    load_data();
    int choice;
    int current_user_idx = -1;

    printf("\n============================================\n");
    printf("   WELCOME TO GREENCHAIN: ECO-CURRENCY SYSTEM\n");
    printf("============================================\n");

    while(1) {
        if (current_user_idx == -1) {
            printf("\n1. Login\n2. Register New User\n3. Exit\nSelect: ");
            scanf("%d", &choice);
            clear_buffer();

            switch(choice) {
                case 1: current_user_idx = login_user(); break;
                case 2: register_user(); break;
                case 3:
                    save_data();
                    printf("[System] Shutdown Complete. Goodbye!\n");
                    return 0;
                default: printf("Invalid option.\n");
            }
        } else {
            printf("\n--- Dashboard: %s (Balance: %.2f Credits) ---\n",
                   users[current_user_idx].name, users[current_user_idx].balance);
            printf("1. Recycle Items (Earn Credits)\n");
            printf("2. View Community Leaderboard\n");
            printf("3. View Session History\n");
            printf("4. Logout\n");
            printf("Select: ");
            scanf("%d", &choice);
            clear_buffer();

            switch(choice) {
                case 1: recycle_menu(current_user_idx); break;
                case 2: leaderboard(); break;
                case 3: print_history(); break;
                case 4:
                    current_user_idx = -1;
                    printf("Logged out successfully.\n");
                    break;
                default: printf("Invalid option.\n");
            }
        }
    }
    return 0;
}

void load_data() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL) return;
    while (fscanf(fp, "%d %s %f %f", &users[user_count].id, users[user_count].name,
                  &users[user_count].balance, &users[user_count].total_recycled_kg) != EOF) {
        user_count++;
    }
    fclose(fp);
}

void save_data() {
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        printf("Disk error.\n");
        return;
    }
    for (int i = 0; i < user_count; i++) {
        fprintf(fp, "%d %s %.2f %.2f\n", users[i].id, users[i].name,
                users[i].balance, users[i].total_recycled_kg);
    }
    fclose(fp);
}

void recycle_menu(int user_index) {
    int material;
    float weight, credits = 0;
    char action_desc[100];

    printf("\n1. Glass (10)\n2. Plastic (25)\n3. Aluminum (50)\nSelect: ");
    scanf("%d", &material);
    printf("Enter Weight (kg): ");
    scanf("%f", &weight);

    if (material == 1) credits = weight * 10;
    else if (material == 2) credits = weight * 25;
    else if (material == 3) credits = weight * 50;
    else return;

    users[user_index].balance += credits;
    users[user_index].total_recycled_kg += weight;

    sprintf(action_desc, "Recycled %.2fkg of Material ID %d", weight, material);
    add_transaction(action_desc, credits);
}

void add_transaction(char* action, float value) {
    TransactionNode* newNode = (TransactionNode*)malloc(sizeof(TransactionNode));
    strcpy(newNode->action, action);
    newNode->value_change = value;
    newNode->next = history_head;
    history_head = newNode;
}

void print_history() {
    TransactionNode* current = history_head;
    while (current != NULL) {
        printf("Action: %s | Value: +%.2f\n", current->action, current->value_change);
        current = current->next;
    }
}

void leaderboard() {
    User temp_users[MAX_USERS];
    for(int i=0; i<user_count; i++) temp_users[i] = users[i];

    for (int i = 0; i < user_count - 1; i++) {
        for (int j = 0; j < user_count - i - 1; j++) {
            if (temp_users[j].total_recycled_kg < temp_users[j+1].total_recycled_kg) {
                User temp = temp_users[j];
                temp_users[j] = temp_users[j+1];
                temp_users[j+1] = temp;
            }
        }
    }

    for (int i = 0; i < user_count; i++) {
        printf("#%d %s %.2f kg\n", i+1, temp_users[i].name, temp_users[i].total_recycled_kg);
    }
}

void register_user() {
    if (user_count >= MAX_USERS) return;
    printf("Enter username: ");
    scanf("%s", users[user_count].name);
    users[user_count].id = user_count + 1;
    users[user_count].balance = 0.0;
    users[user_count].total_recycled_kg = 0.0;
    user_count++;
}

int login_user() {
    char name[50];
    printf("Enter username: ");
    scanf("%s", name);
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].name, name) == 0) return i;
    }
    return -1;
}

void clear_buffer() {
    while (getchar() != '\n');
}