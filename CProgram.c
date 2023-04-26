// IT 355: Created by Ryan Leone, Curtis Bryant, Aneel Gillan, Kaden Hargrove, Nathan Brose, Thomas Gray
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

const int BUFFER1_SIZE = 32;
const int BUFFER2_SIZE = 16;

int main(int argc, char *argv[])
{
    // CWE-789:Memory Allocation with Excessive Size Value
    // CWE-467: Use of sizeof() on a Pointer Type
    char *heapBuffer1 = malloc(BUFFER1_SIZE * sizeof(char));
    // CWE-188: Avoiding Reliance on Data/Memory Layout -- We let the compiler do its job and allocate where needed... we don't rely on heapBuffer1 for our memory allocation
    char *heapBuffer2 = malloc(BUFFER2_SIZE * sizeof(char));

    // note: there are errors squiggles but it works
    char stackBuffer1[BUFFER1_SIZE];
    char stackBuffer2[BUFFER2_SIZE];

    char *arr = malloc(BUFFER1_SIZE * sizeof(char));

    printf("Please enter a line of input to be stored in the heap buffers: ");
    // Avoiding CWE-122: Heap-based Buffer Overflow
    // Avoiding CWE-242: Use of Inherently Dangerous Function - NOT using gets()
    fgets(heapBuffer1, BUFFER1_SIZE, stdin);

    // Avoiding CWE-122: Heap-based Buffer Overflow
    strncpy(heapBuffer2, heapBuffer1, BUFFER2_SIZE);

    // Avoiding CWE-126: Buffer Over-read
    printf("The contents of heapBuffer1 is: %.*s\n", BUFFER1_SIZE, heapBuffer1);
    printf("The contents of heapBuffer2 is: %.*s\n", BUFFER2_SIZE, heapBuffer2);

    fflush(stdin);
    printf("\n");

    // Avoiding CWE-787: Out-of-bounds Write
    printf("Please enter a line of input to be stored in the stack buffers: ");
    // Avoiding CWE-121: Stack-based Buffer Overflow
    fgets(stackBuffer1, BUFFER1_SIZE, stdin);

    // Avoiding CWE-121: Stack-based Buffer Overflow
    strncpy(stackBuffer2, stackBuffer1, sizeof(stackBuffer2));

    // Avoiding CWE-126: Buffer Over-read
    printf("The contents of stackBuffer1 is: %.*s\n", BUFFER1_SIZE, stackBuffer1);
    printf("The contents of stackBuffer2 is: %.*s\n", BUFFER2_SIZE, stackBuffer2);

    fflush(stdin);
    printf("\n");

    int index;
    printf("\nPlease enter an index of stackBuffer 2 to retrieve: ");
    fgets(heapBuffer1, BUFFER1_SIZE, stdin);
    index = atoi(heapBuffer1);

    // Avoiding: CWE-119: Improper Restriction of Operations within the Bounds of a Memory Buffer, CWE-126: Buffer Over-read, and CWE-127: Buffer Under-read
    // Also avoiding CWE-806: Buffer Access Using Size of Source Buffer
    // Also avoiding CWE-129: Improper Validation of Array Index
    while (index >= BUFFER2_SIZE || index < 0)
    {
        printf("Invalid index. Please enter an index of stackBuffer1 to retrieve: ");
        fgets(heapBuffer1, BUFFER1_SIZE, stdin);
        index = atoi(heapBuffer1);
    }

    printf("stackBuffer2 at %d is %c\n", index, stackBuffer2[index]);

    printf("\n");

    // CWE-124: Buffer Underwrite (‘Buffer Underflow’)
    for (int i = 0; i < BUFFER1_SIZE; i++)
    {
        // CWE-480: Use of Incorrect Operator - use static analysis to find this
        // do random math with pointer index
        int index = (i % BUFFER2_SIZE) - 5;

        // verify it is still in bounds to prevent buffer underwrite error
        if (index >= 0 && index < BUFFER1_SIZE)
        {
            arr[index] = i;
            printf("Wrote %d at arr[%d]\n", i, index);
        }
    }

    printf("\n");

    // CWE-125: Out-of-bounds Read
    for (int i = 0; i < 5; i++)
    {
        int index = i - 2;

        if (index >= 0 && index < BUFFER1_SIZE)
        {
            printf("Read %d at arr[%d]\n", arr[index], index);
        }
        else
        {
            printf("Cannot read out of bounds! (index %d)\n", index);
        }
    }

    char *arr2 = malloc(BUFFER1_SIZE * sizeof(char));
    char buf[BUFFER2_SIZE];

    // CWE-170: Improper Null Termination
    strncpy(arr2, arr, sizeof(arr2)); // using sizeof destination buffer ensures proper copy and null term

    int fd = open("hello.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("c1");
        exit(1);
    }
    printf("\nopened the fd = % d\n", fd);

    int readRet = read(fd, buf, BUFFER2_SIZE);
    if (readRet == -1)
    {
        printf("Read error!\n");
        exit(1);
    }

    buf[readRet] = '\0'; // manually set null term

    printf("%s\n", buf); // print line from file

    if (close(fd) < 0)
    {
        perror("c1");
        exit(1);
    }
    printf("closed the fd.\n");

    // CWE-910: Use of Expired File Descriptor (set it to invalid value)
    fd = -1;

    // Avoiding CWE-416: Use After Free
    free(heapBuffer1);
    free(heapBuffer2);
    free(arr);
    free(arr2);
}
