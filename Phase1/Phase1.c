#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // for sleep()

// Account structure
typedef struct Account {
    char* name;
    int accountNumber;
    double amount;
} Account;

int accountNumTracker = 0;

// Function to initialize an account
void init_account(Account *acc, char* name, double amount) {
    acc->name = name;
    acc->accountNumber = accountNumTracker++;
    acc->amount = amount;
}

// Function to deposit amount into the account
void* deposit(void* arg) {
    Account* acc = (Account*) arg;
    double dep_amount = 20.0; // Example deposit amount, can be changed

    acc->amount += dep_amount;
    printf("Depositing $%.2f to %s's account...\n", dep_amount, acc->name);
    sleep(2); // Simulating delay
    printf("Updating balance...\n");
    sleep(1);
    printf("Transaction Complete!\n");

    return NULL;
}

// Function to withdraw amount from the account
void* withdraw(void* arg) {
    Account* acc = (Account*) arg;
    double with_amount = 7.0; // Example withdrawal amount, can be changed

    acc->amount -= with_amount;
    printf("Withdrawing $%.2f from %s's account...\n", with_amount, acc->name);
    sleep(2); // Simulating delay
    printf("Updating balance...\n");
    sleep(1);
    printf("Transaction Complete!\n");

    return NULL;
}

// Function to show the account balance
void show_balance(Account *acc) {
    printf("Name: %s\nCurrent Balance: $%.2f\n", acc->name, acc->amount);
}

int main() {
    Account acc1;
    init_account(&acc1, "Constant", 100000.0);

    pthread_t t1, t2, t3, t4, t5, t6;

    // Creating threads to perform deposits and withdrawals
    pthread_create(&t1, NULL, deposit, (void*)&acc1);
    pthread_create(&t2, NULL, withdraw, (void*)&acc1);

    pthread_create(&t3, NULL, deposit, (void*)&acc1);
    pthread_create(&t4, NULL, deposit, (void*)&acc1);

    pthread_create(&t5, NULL, withdraw, (void*)&acc1);
    pthread_create(&t6, NULL, deposit, (void*)&acc1);

    // Joining threads to ensure they complete
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);

    printf("\n");
    show_balance(&acc1);

    return 0;
}


