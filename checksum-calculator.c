/*=============================================================================
| Assignment: pa02 - Calculating an 8, 16, or 32 bit
| checksum on an ASCII input file
|
| Author: Jack Miller
| Language: C
|
| To Compile: gcc -o pa02 pa02.c
|
| To Execute: C ./pa02 inputFile.txt 8
|               where inputFile.txt is an ASCII input file
|               and the number 8 could also be 16 or 32
|               which are the valid checksum sizes, all
|               other values are rejected with an error message
|               and program termination
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing
+=============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int main(int argc, char *argv[]) {
    FILE *inputFile;  // Pointer to a file
    int checksumSize; // Size of the checksum in bits
    int characterCnt = 0; // Counter for characters processed
    char currentChar; // Variable to store the current character being read
    unsigned long checksum = 0; // Variable to store the checksum value

    // Check if the correct number of command-line arguments are inputted by user
    if (argc != 3) {
        fprintf(stderr, "To Execute: ./pa02 inputFile.txt checksumSize\n", argv[0]);
        return -1; // Return an error code
    }

    // Convert the checksum size argument from string to integer
    checksumSize = atoi(argv[2]);

    // Check if the provided checksum size is valid
    if (checksumSize != 8 && checksumSize != 16 && checksumSize != 32) {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return -1; // Return an error code
    }

    // Open the input file in read mode
    inputFile = fopen(argv[1], "r");

    // Check if the file was successfully opened
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return -1; // Return an error code if failed
    }

    // Read characters from the file until the end of file (EOF) is reached
    while (fscanf(inputFile, "%c", &currentChar) != EOF) {
        // Print a newline every 80 characters
        if (characterCnt % 80 == 0) {
            printf("\n");
        }

        // Print the current character
        printf("%c", currentChar);

        // Calculate the shift amount based on the checksum size and update the checksum value
        int shiftAmount = checksumSize - (8 * (characterCnt % (checksumSize / 8) + 1));
        checksum += ((unsigned long)(currentChar & 0xFF) << shiftAmount);

        // Increment the character count
        characterCnt++;
    }

    // Pad the remaining characters with 'X' until the checksum is complete
    while (characterCnt % (checksumSize / 8) != 0) {
        currentChar = 'X';
        int shiftAmount = checksumSize - (8 * (characterCnt % (checksumSize / 8) + 1));
        checksum += ((unsigned long)(currentChar & 0xFF) << shiftAmount);
        characterCnt++;
        printf("X");
        if (characterCnt % 80 == 0) {
            printf("\n");
        }
    }

    // Print the final checksum value
    printf("\n");
    printf("%2d bit checksum is %8lx for all %4d chars\n",
           checksumSize, checksum & ((1UL << checksumSize) - 1), characterCnt);

    // Close the input file
    fclose(inputFile);

    return 0;
}