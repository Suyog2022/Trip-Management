#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PEOPLE 100
int i,j;

struct Person {
    char name[20];
    float totalPaid;
    float totalOwed;
};

struct Person people[MAX_PEOPLE];
int numPeople = 0;

// Function to add a person's data
void addPerson() {
    if (numPeople >= MAX_PEOPLE) {
        printf("Cannot add more people. Maximum limit reached.\n");
        return;
    }
    printf("\n\t\t\t\tEnter member name: ");
    scanf("%s", people[numPeople].name);
    printf("\n\t\t\t\tEnter amount paid (Rs.): ");
    scanf("%f", &people[numPeople].totalPaid);
    people[numPeople].totalOwed = 0; 
    numPeople++;
}


float calculateTotalExpenses() {
    float total = 0;
    for (i = 0; i < numPeople; i++) {
        total += people[i].totalPaid;
    }
    return total;
}


void settleExpenses() {
    float totalExpenses = calculateTotalExpenses();
    printf("Total expenses: %.2f\n", totalExpenses);
    
    // Calculate equal share for each person
    float equalShare = totalExpenses / numPeople;
    
    
    for (i = 0; i < numPeople; i++) {
        people[i].totalOwed = equalShare;
    }
    
   
    for (i = 0; i < numPeople; i++) {
        printf("%s paid %.2f and owes %.2f\n", people[i].name, people[i].totalPaid, people[i].totalOwed);
    }

   
    for (i = 0; i < numPeople; i++) {
        if (people[i].totalPaid > people[i].totalOwed) {
            float excess = people[i].totalPaid - people[i].totalOwed;
            for (j = 0; j < numPeople; j++) {
                if (i != j && people[j].totalPaid < people[j].totalOwed) {
                    float deficit = people[j].totalOwed - people[j].totalPaid;
                    float transferAmount = (excess < deficit) ? excess : deficit;

                    printf("%s should pay %.2f to %s\n", people[j].name, transferAmount, people[i].name);
                    
                    people[i].totalPaid -= transferAmount;
                    people[j].totalPaid += transferAmount;
                    
                    if (people[i].totalPaid <= people[i].totalOwed) break;
                }
            }
        }
    }
}

int main() {
    int ch, n;

    // Title
    printf("Project Name = Trip Management System\n");

    // Main menu
    printf("\n\n\t\t\t\t##=======================================##\n");
    printf("\t\t\t\t##           Welcome to Trip            ##\n");
    printf("\t\t\t\t##=======================================##\n");

    // Group members
    printf("\n\n\t\t\t\tHow many members in your group? ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        addPerson();
    }

    while (1) {
        printf("\n\t\t\t\t1] Add more data");
        printf("\n\t\t\t\t2] Settle expenses");
        printf("\n\t\t\t\t3] Exit");
        printf("\n\t\t\t\tEnter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: 
                addPerson();
                break;

            case 2:
                settleExpenses();
                break;

            case 3:
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }

    return 0;
}

