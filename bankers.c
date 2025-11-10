// CSE3PM11A - Operating Systems Lab
// Department of Computer Engineering and Technology
// Assignment 6: Banker's Algorithm for Deadlock Avoidance

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Clears leftover characters in input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Safety Algorithm: Checks if the system is in a safe state
void BankerssafeSequence(int r, int c, bool pFinish[], int need[][c], int avl[], int alloc[][c]) {
    int processCount = 0;
    int k = 0;
    bool temp, process = false;
    int safeorder[10]; // Stores safe execution order (up to 10 processes)

    while (processCount < r) {
        process = false;
        for (int i = 0; i < r; i++) {
            if (pFinish[i]) continue; // Skip finished processes
            temp = true;
            for (int j = 0; j < c; j++) {
                if (need[i][j] > avl[j]) {
                    temp = false;
                    break;
                }
            }
            if (!temp) continue;

            // Process can safely execute
            for (int j = 0; j < c; j++)
                avl[j] += alloc[i][j]; // Release resources

            pFinish[i] = true;
            processCount++;
            safeorder[k++] = i;
            process = true;
        }

        if (!process) {
            printf("\n\nDeadlock occurred.\n");
            return;
        }
    }

    printf("\nSystem is in a safe state.\nSafe sequence is:\n");
    for (int i = 0; i < r; i++)
        printf("P%d ", safeorder[i]);
    printf("\n");

    printf("\nFinal available resources:\n");
    for (int i = 0; i < c; i++)
        printf("%d ", avl[i]);
    printf("\n");
}

// Handles additional resource requests
void ResourcesRequest(int r, int c, int avl[], bool pFinish[], int need[][c], int alloc[][c]) {
    clearInputBuffer();
    char ch;
    printf("\n\nDo you want to request additional resources? (y/n)\n>> ");
    scanf("%c", &ch);

    if (ch == 'y' || ch == 'Y') {
        int p;
        printf("\nFor which process?\n>> ");
        scanf("%d", &p);

        int addResources[10];
        printf("Enter amount of each resource requested:\n>> ");
        for (int i = 0; i < c; i++)
            scanf("%d", &addResources[i]);

        // Validate request
        for (int i = 0; i < c; i++) {
            if (addResources[i] > need[p][i]) {
                printf("\nError: Request exceeds process need.\n");
                return;
            }
            if (addResources[i] > avl[i]) {
                printf("\nError: Request exceeds available resources.\n");
                return;
            }
        }

        // Grant the request
        for (int i = 0; i < c; i++) {
            alloc[p][i] += addResources[i];
            avl[i] -= addResources[i];
            need[p][i] -= addResources[i];
        }

        printf("\nResources granted temporarily. Rechecking safety...\n");
        BankerssafeSequence(r, c, pFinish, need, avl, alloc);
    }
}

// Main function
int main() {
    char again;
    do {
        int r, c;
        printf("Enter number of processes and resources (r c):\n>> ");
        scanf("%d %d", &r, &c);

        int max[r][c], alloc[r][c], need[r][c], avl[c], avlCopy[c];
        bool pFinish[r];

        printf("\nEnter Max matrix:\n");
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                scanf("%d", &max[i][j]);

        printf("\nEnter Allocation matrix:\n");
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                scanf("%d", &alloc[i][j]);

        printf("\nEnter Available resources:\n");
        for (int i = 0; i < c; i++)
            scanf("%d", &avl[i]);

        for (int i = 0; i < c; i++)
            avlCopy[i] = avl[i];

        for (int i = 0; i < r; i++)
            pFinish[i] = false;

        // Calculate Need = Max - Allocation
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                need[i][j] = max[i][j] - alloc[i][j];

        printf("\nNeed matrix:\n");
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++)
                printf("%d ", need[i][j]);
            printf("\n");
        }

        // Run Safety Algorithm
        BankerssafeSequence(r, c, pFinish, need, avl, alloc);

        // Reset available and finish arrays for next check
        for (int i = 0; i < c; i++)
            avl[i] = avlCopy[i];
        for (int i = 0; i < r; i++)
            pFinish[i] = false;

        // Handle optional request
        ResourcesRequest(r, c, avl, pFinish, need, alloc);

        clearInputBuffer();
        printf("\n\nDo you want to run the program again? (y/n)\n>> ");
        scanf("%c", &again);

    } while (again == 'y' || again == 'Y');

    printf("\nProgram terminated.\n");
    return 0;}

//gcc banker.c -o bankers
}
