//IT 355: Created by Ryan Leone, Curtis Bryant, Aneel Gillan, Kaden Hargrove, Nathan Brose, Thomas Gray
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int BUFFER1_SIZE = 32;
const int BUFFER2_SIZE = 16;

int main(int argc, char* argv[])
{

    char* heapBuffer1 = malloc(BUFFER1_SIZE * sizeof(char));
    char* heapBuffer2 = malloc(BUFFER2_SIZE * sizeof(char));

    char stackBuffer1[BUFFER1_SIZE];
    char stackBuffer2[BUFFER2_SIZE];

    printf("Please enter a line of input to be stored in the heap buffers: ");
    //Avoiding CWE-122: Heap-based Buffer Overflow  
    fgets(heapBuffer1, BUFFER1_SIZE, stdin);

    //Avoiding CWE-122: Heap-based Buffer Overflow 
    strncpy(heapBuffer2, heapBuffer1, BUFFER2_SIZE);

    //Avoiding CWE-126: Buffer Over-read  
    printf("The contents fo heapBuffer1 is: %.*s\n", BUFFER1_SIZE, heapBuffer1);
    printf("The contents fo heapBuffer2 is: %.*s\n", BUFFER2_SIZE, heapBuffer2);

    fflush(stdin);
    printf("\n");

    printf("Please enter a line of input to be stored in the stack buffers: ");
    //Avoiding CWE-121: Stack-based Buffer Overflow 
    fgets(stackBuffer1, BUFFER1_SIZE, stdin);

    //Avoiding CWE-121: Stack-based Buffer Overflow 
    strncpy(stackBuffer2, stackBuffer1, sizeof(stackBuffer2));

    //Avoiding CWE-126: Buffer Over-read 
    printf("The contents fo stackBuffer1 is: %.*s\n", BUFFER1_SIZE, stackBuffer1);
    printf("The contents fo stackBuffer2 is: %.*s\n", BUFFER2_SIZE, stackBuffer2);

    fflush(stdin);
    printf("\n");

    int index;
    printf("\nPlease enter an index of stackBuffer 1 to retrieve: ");
    fgets(heapBuffer1, BUFFER1_SIZE, stdin);
    index = atoi(heapBuffer1);

    //Avoiding CWE-126: Buffer Over-read and CWE-127: Buffer Under-read 
    while(index >= BUFFER1_SIZE || index < 0)
    {
        printf("Invalid index. Please enter an index of stackBuffer1 to retrieve: ");
        fgets(heapBuffer1, BUFFER1_SIZE, stdin);
        index = atoi(heapBuffer1);
    }

    printf("stackBuffer1 at %d is %c\n", index, stackBuffer1[index]);

    free(heapBuffer1);
    free(heapBuffer2);

}

