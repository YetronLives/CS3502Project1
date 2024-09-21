//DeadLock Resolution
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


typedef struct Account {
   char* name;
   int accountNumber;
   double amount;
   pthread_mutex_t lock;
} Account;

int accountNumTracker = 0;

void init_account(Account *acc, char* name, double amount) {
   acc->name = name;
   acc->accountNumber = accountNumTracker++;
   acc->amount = amount;
   pthread_mutex_init(&acc->lock, NULL);
}


void* deposit(void* arg) {
   Account* acc = (Account*) arg;
   double dep_amount = 20.0; // Example deposit amount

   pthread_mutex_lock(&acc->lock);
   acc->amount += dep_amount;
   printf("Depositing $%.2f to %s's account...\n", dep_amount, acc->name);
   sleep(2); // Simulating delay
   printf("Updating balance...\n");
   sleep(1);
   printf("Transaction Complete!\n");
   pthread_mutex_unlock(&acc->lock);

   return NULL;
}


void* withdraw(void* arg) {
   Account* acc = (Account*) arg;
   double with_amount = 50.0;

   pthread_mutex_lock(&acc->lock);
   acc->amount -= with_amount;
   printf("Withdrawing $%.2f from %s's account...\n", with_amount, acc->name);
   sleep(2); // Simulating delay
   printf("Updating balance...\n");
   sleep(1);
   printf("Transaction Complete!\n");
   pthread_mutex_unlock(&acc->lock);

   return NULL;
}

//using ordering lock this time
void* transfer_acc1_to_acc2(void* args) {
    Account** acc = (Account**) args;
    Account* acc1 = acc[0];
    Account* acc2 = acc[1];

    // we have to lock acc 1 first before acc 2
    if (acc1->accountNumber < acc2->accountNumber) {
        pthread_mutex_lock(&acc1->lock);
        pthread_mutex_lock(&acc2->lock);
    } else {
        pthread_mutex_lock(&acc2->lock);
        pthread_mutex_lock(&acc1->lock);
    }

    printf("Locked both accounts for transfer from %s to %s...\n", acc1->name, acc2->name);
    acc1->amount -= 50;
    acc2->amount += 50;

    //unlock is called
    pthread_mutex_unlock(&acc1->lock);
    pthread_mutex_unlock(&acc2->lock);

    printf("Transfer of $50 from %s to %s completed.\n", acc1->name, acc2->name);
    return NULL;
}

//same but in reverse
void* transfer_acc2_to_acc1(void* args) {
    Account** acc = (Account**) args;
    Account* acc1 = acc[0];
    Account* acc2 = acc[1];

    if (acc1->accountNumber < acc2->accountNumber) {
        pthread_mutex_lock(&acc1->lock);
        pthread_mutex_lock(&acc2->lock);
    } else {
        pthread_mutex_lock(&acc2->lock);
        pthread_mutex_lock(&acc1->lock);
    }

    printf("Locked both accounts for transfer from %s to %s...\n", acc2->name, acc1->name);
    acc2->amount -= 20;
    acc1->amount += 20;

    pthread_mutex_unlock(&acc1->lock);
    pthread_mutex_unlock(&acc2->lock);

    printf("Transfer of $20 from %s to %s completed.\n", acc2->name, acc1->name);
    return NULL;
}

void show_balance(Account *acc) {
   printf("Name: %s\nCurrent Balance: $%.2f\n", acc->name, acc->amount);
}

int main() {
   Account acc1, acc2;
   init_account(&acc1, "Constant", 100000.0);
   init_account(&acc2, "Abigail", 50000.0);

   pthread_t t1, t2;

   Account* accounts1[] = {&acc1, &acc2};  // Transfer from acc1 to acc2
   Account* accounts2[] = {&acc2, &acc1};  // Transfer from acc2 to acc1

   pthread_create(&t1, NULL, transfer_acc1_to_acc2, (void*)accounts1);
   pthread_create(&t2, NULL, transfer_acc2_to_acc1, (void*)accounts2);

   pthread_join(t1, NULL);
   pthread_join(t2, NULL);

   printf("\n");
   show_balance(&acc1);
   show_balance(&acc2);
    
   pthread_mutex_destroy(&acc1.lock);
   pthread_mutex_destroy(&acc2.lock);
}

