/*
 * Sliding Window Protocol Simulation with Random Frame Loss
 * 
 * This program simulates the transmission of data frames using a sliding window protocol.
 * The sender transmits frames in a window of a specified size and waits for acknowledgments.
 * If an acknowledgment is lost (simulated with a 20% probability), the entire window is retransmitted.
 * The process continues until all frames are successfully acknowledged.
 * 
 * User inputs:
 * - Total number of frames to be sent
 * - Window size (number of frames sent at a time)
 * 
 * The program outputs:
 * - Frames being sent
 * - Frame loss notifications and retransmissions
 * - Confirmation when all frames are successfully transmitted
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
void sendFrames(int start, int windowSize, int totalFrames);
int isFrameLost();

int main() {
    int windowSize, totalFrames;
    
    // User input for total frames and window size
    printf("Enter the total number of frames: ");
    scanf("%d", &totalFrames);
    printf("Enter the window size: ");
    scanf("%d", &windowSize);

    int base = 0;  // Track the first unacknowledged frame
    srand(time(NULL));  // Seed the random number generator for frame loss simulation

    // Sliding window loop
    while (base < totalFrames) {
        sendFrames(base, windowSize, totalFrames);  // Send frames in current window
        int ack = base;

        // Try to acknowledge each frame in the window
        for (int i = base; i < base + windowSize && i < totalFrames; i++) {
            if (isFrameLost()) {  // Check if frame acknowledgment is lost
                printf("Acknowledgment for Frame %d lost. Retransmitting window...\n", i);
                break;  // If frame is lost, break and retransmit the window
            }
            ack++;  // Move the acknowledgment pointer forward
        }
        base = ack;  // Slide the window forward
    }

    printf("All frames successfully transmitted!\n");  // All frames are sent and acknowledged
    return 0;
}

// Function to simulate sending frames in a window
void sendFrames(int start, int windowSize, int totalFrames) {
    printf("Sending frames: ");
    for (int i = start; i < start + windowSize && i < totalFrames; i++) {
        printf("%d ", i);  // Print the frame numbers being sent
    }
    printf("\n");
}

// Function to simulate frame loss with 20% probability
int isFrameLost() {
    return rand() % 5 == 0;  // 20% chance of frame loss
}

/*
 * Simulated Output Example:
 * (Note: The actual output may vary due to randomness in frame loss.)
 *
 * Enter the total number of frames: 10
 * Enter the window size: 4
 * Sending frames: 0 1 2 3 
 * Sending frames: 4 5 6 7 
 * Acknowledgment for Frame 6 lost. Retransmitting window...
 * Sending frames: 4 5 6 7 
 * Sending frames: 8 9 
 * All frames successfully transmitted!
 */

