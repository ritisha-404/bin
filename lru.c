#include <stdio.h>
#define MAX_FRAMES 10
#define MAX_PAGES 50

// Function to find the Least Recently Used (LRU) page
int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; ++i) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int pages[MAX_PAGES];
    int n, m; // n = number of pages, m = number of frames
    int frames[MAX_FRAMES], time[MAX_FRAMES];
    int count = 0, faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &m);

    // Initialize all frames as empty (-1)
    for (int i = 0; i < m; ++i)
        frames[i] = -1;

    printf("\nStep\tPage\tFrames\t\tPage Fault\n");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < n; ++i) {
        int flag = 0;

        // Check if page is already in a frame (Page Hit)
        for (int j = 0; j < m; ++j) {
            if (frames[j] == pages[i]) {
                count++;
                time[j] = count;  // Update last used time
                flag = 1;
                break;
            }
        }

        // Page not found → Page Fault
        if (!flag) {
            int empty = -1;

            // Check for an empty frame
            for (int j = 0; j < m; ++j) {
                if (frames[j] == -1) {
                    empty = j;
                    break;
                }
            }

            count++;
            if (empty != -1) {
                frames[empty] = pages[i];
                time[empty] = count;
            } else {
                int pos = findLRU(time, m); // Find least recently used
                frames[pos] = pages[i];
                time[pos] = count;
            }
            faults++;
        }

        // Display the current frame state
        printf("%2d\t%d\t", i + 1, pages[i]);
        for (int j = 0; j < m; ++j) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\t%s\n", flag ? "No" : "Yes");
    }

    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}
