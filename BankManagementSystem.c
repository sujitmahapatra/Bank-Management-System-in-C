#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a bank account
struct BankAccount {
    int accountNumber;
    char accountHolder[100];
    float balance;
    struct BankAccount* next;
};

// Function to create a new bank account
struct BankAccount* createAccount(int accountNumber, const char* accountHolder, float initialBalance) {
    struct BankAccount* account = (struct BankAccount*)malloc(sizeof(struct BankAccount));
    account->accountNumber = accountNumber;
    strcpy(account->accountHolder, accountHolder);
    account->balance = initialBalance;
    account->next = NULL;
    return account;
}

// Function to insert a new account into the linked list
struct BankAccount* insertAccount(struct BankAccount* head, struct BankAccount* newAccount) {
    if (head == NULL) {
        return newAccount;
    } else {
        newAccount->next = head;
        return newAccount;
    }
}

// Function to deposit money into an account
void deposit(struct BankAccount* account, float amount) {
    account->balance += amount;
    printf("Deposited %.2f into account %d. New balance: %.2f\n", amount, account->accountNumber, account->balance);
}

// Function to withdraw money from an account
void withdraw(struct BankAccount* account, float amount) {
    if (account->balance >= amount) {
        account->balance -= amount;
        printf("Withdrawn %.2f from account %d. New balance: %.2f\n", amount, account->accountNumber, account->balance);
    } else {
        printf("Insufficient balance in account %d\n", account->accountNumber);
    }
}

// Function to check account balance
void checkBalance(struct BankAccount* account) {
    printf("Account Number: %d\n", account->accountNumber);
    printf("Account Holder: %s\n", account->accountHolder);
    printf("Balance: %.2f\n", account->balance);
}

// Function to delete an account
struct BankAccount* deleteAccount(struct BankAccount* head, int accountNumber) {
    struct BankAccount* current = head;
    struct BankAccount* prev = NULL;

    while (current != NULL) {
        if (current->accountNumber == accountNumber) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Account %d deleted successfully\n", accountNumber);
            return head;
        }
        prev = current;
        current = current->next;
    }

    printf("Account %d not found\n", accountNumber);
    return head;
}

// Function to display all accounts in the linked list
void displayAccounts(struct BankAccount* head) {
    struct BankAccount* current = head;
    printf("\nAccount Details:\n");
    while (current != NULL) {
        printf("Account Number: %d\n", current->accountNumber);
        printf("Account Holder: %s\n", current->accountHolder);
        printf("Balance: %.2f\n", current->balance);
        current = current->next;
    }
}

// Function to free memory and exit the program
void cleanup(struct BankAccount* head) {
    struct BankAccount* current = head;
    while (current != NULL) {
        struct BankAccount* temp = current;
        current = current->next;
        free(temp);
    }
    exit(0);
}

int main() {
    struct BankAccount* head = NULL;
    int choice;
    int accountNumber;
    char accountHolder[100];
    float initialBalance;
    float amount;

    while (1) {
        printf("\nBank Management System Menu:\n");
        printf("1. Create an account\n");
        printf("2. Deposit money\n");
        printf("3. Withdraw money\n");
        printf("4. Check balance\n");
        printf("5. Delete an account\n");
        printf("6. Display all accounts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                printf("Enter account holder name: ");
                scanf("%s", accountHolder);
                printf("Enter initial balance: ");
                scanf("%f", &initialBalance);
                struct BankAccount* newAccount = createAccount(accountNumber, accountHolder, initialBalance);
                head = insertAccount(head, newAccount);
                printf("Account created successfully\n");
                break;
            case 2:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                printf("Enter deposit amount: ");
                scanf("%f", &amount);
                struct BankAccount* depositAccount = head;
                while (depositAccount != NULL && depositAccount->accountNumber != accountNumber) {
                    depositAccount = depositAccount->next;
                }
                if (depositAccount != NULL) {
                    deposit(depositAccount, amount);
                } else {
                    printf("Account not found\n");
                }
                break;
            case 3:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                printf("Enter withdrawal amount: ");
                scanf("%f", &amount);
                struct BankAccount* withdrawAccount = head;
                while (withdrawAccount != NULL && withdrawAccount->accountNumber != accountNumber) {
                    withdrawAccount = withdrawAccount->next;
                }
                if (withdrawAccount != NULL) {
                    withdraw(withdrawAccount, amount);
                } else {
                    printf("Account not found\n");
                }
                break;
            case 4:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                struct BankAccount* checkBalanceAccount = head;
                while (checkBalanceAccount != NULL && checkBalanceAccount->accountNumber != accountNumber) {
                    checkBalanceAccount = checkBalanceAccount->next;
                }
                if (checkBalanceAccount != NULL) {
                    checkBalance(checkBalanceAccount);
                } else {
                    printf("Account not found\n");
                }
                break;
            case 5:
                printf("Enter account number to delete: ");
                scanf("%d", &accountNumber);
                head = deleteAccount(head, accountNumber);
                break;
            case 6:
                displayAccounts(head);
                break;
            case 7:
                cleanup(head);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
