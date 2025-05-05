
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 5
#define NAME_LENGTH 50

// Customer structure
typedef struct {
    int id;
    char name[NAME_LENGTH];
    float income;
    int eligible; // 1 if eligible, 0 otherwise
} Customer;

// Linked list node for active loans
typedef struct LoanNode {
    int customerId;
    float loanAmount;
    float emi;
    struct LoanNode* next;
} LoanNode;

// Function to check eligibility
int checkEligibility(float income) {
    return income >= 30000; // Eligible if income >= 30,000
}

// Function to add a loan to the linked list
LoanNode* addLoan(LoanNode* head, int customerId, float loanAmount, float emi) {
    LoanNode* newNode = (LoanNode*)malloc(sizeof(LoanNode));
    newNode->customerId = customerId;
    newNode->loanAmount = loanAmount;
    newNode->emi = emi;
    newNode->next = head;
    return newNode;
}

// Function to display all loans
void displayLoans(LoanNode* head, Customer customers[], int n) {
    printf("\n--- Active Loans ---\n");
    LoanNode* curr = head;
    while (curr != NULL) {
        // Find customer name
        char* cname = "Unknown";
        for (int i = 0; i < n; i++) {
            if (customers[i].id == curr->customerId) {
                cname = customers[i].name;
                break;
            }
        }
        printf("Customer: %s | Loan Amount: %.2f | EMI: %.2f\n", cname, curr->loanAmount, curr->emi);
        curr = curr->next;
    }
}

int main() {
    // Sample customer data
    Customer customers[MAX_CUSTOMERS] = {
        {1, "Alice", 35000, 0},
        {2, "Bob", 25000, 0},
        {3, "Charlie", 40000, 0},
        {4, "Diana", 18000, 0},
        {5, "Eve", 50000, 0}
    };

    // Check eligibility for each customer
    printf("--- Customer Eligibility ---\n");
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        customers[i].eligible = checkEligibility(customers[i].income);
        printf("Customer: %s | Income: %.2f | Eligible: %s\n",
               customers[i].name,
               customers[i].income,
               customers[i].eligible ? "Yes" : "No");
    }

    // Linked list for active loans
    LoanNode* loanList = NULL;

    // Example: Add loans for eligible customers
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        if (customers[i].eligible) {
            float loanAmount = 100000; // Example loan amount
            float emi = loanAmount / 12; // Simple EMI calculation
            loanList = addLoan(loanList, customers[i].id, loanAmount, emi);
        }
    }

    // Display all active loans
    displayLoans(loanList, customers, MAX_CUSTOMERS);

    // Free memory
    LoanNode* temp;
    while (loanList != NULL) {
        temp = loanList;
        loanList = loanList->next;
        free(temp);
    }

    return 0;
}
