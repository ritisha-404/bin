#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

int main() {
    int frames[MAX_FRAMES], pages[MAX_PAGES];
    int n, f, i, j, k, page_faults = 0;
    int front = 0; // Points to the oldest page (for FIFO)
    
    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    printf("Enter the page reference string:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    
    printf("Enter number of frames: ");
    scanf("%d", &f);
    
    // Initialize all frames as empty (-1)
    for(i = 0; i < f; i++) {
        frames[i] = -1;
    }

    printf("\nPage\tFrames\t\tPage Fault\n");
    printf("----------------------------------------\n");

    for(i = 0; i < n; i++) {
        int found = 0;

        // Check if page is already in a frame (Page Hit)
        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // If not found, replace the oldest page (FIFO)
        if(!found) {
            frames[front] = pages[i];
            front = (front + 1) % f;  // Move front pointer circularly
            page_faults++;
        }

        // Display current frame status
        printf("%d\t", pages[i]);
        for(k = 0; k < f; k++) {
            if(frames[k] != -1)
                printf("%d ", frames[k]);
            else
                printf("- ");
        }
        printf("\t%s\n", found ? "No" : "Yes");
    }

    printf("\nTotal Page Faults = %d\n", page_faults);
    return 0;
}
