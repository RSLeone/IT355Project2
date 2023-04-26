// IT 355: Created by Ryan Leone, Curtis Bryant, Aneel Gillan, Kaden Hargrove, Nathan Brose, Thomas Gray
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
// CWE-676: Use of Potentially Dangerous Function
#include "banned.h"

using namespace std;

int main(int argc, char* argv[])
{

    const int ARRAY_SIZE = 3;

    //CWE-415: Use of Externally-Controlled Format String
    if (argc > 1) {
        cout << "This is a demonstration of CWE-415: Use of Externally-Controlled Format String... NEVER send in a \"string\" as input!";
    }

    int *array = new int(ARRAY_SIZE);

    // CWE-126: Buffer Over-read; CWE-127: Buffer Under-read; 
    // CWE-131: Incorrect Calculation of Buffer Size
    // create an array with the correct number of elements to avoid buffer errors
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = 0;
    }

    cout << "Array with size " << ARRAY_SIZE << " was created and filled with 0's\n";

    // CWE-467: Use of sizeof() on a Pointer Type
    cout << sizeof(*array) << " bytes was allocated for the array.\n";

    //CWE-457: Use of Uninitialized Variable
    int inputIndex = 0;
    unsigned int inputValue = 0;

    // CWE-248: Uncaught Exception
    try
    {
        cout << "Please enter an array index to update between 0 and 2: ";
        cin >> inputIndex;

        // CWE-194: Unexpected Sign Extension
        //Avoiding CWE-129: Improper Validation of Array Index
        while(inputIndex < 0 || inputIndex > 2)
        {
            cout << "Invalid index entered. Please enter an array index to update between 0 and " + (ARRAY_SIZE - 1) << endl;

            cin >> inputIndex;
        }

        cout << "Please enter a positive integer that should be placed into index " << inputIndex << ": " << endl;
        cin >> inputValue;
    
    //CWE-396: Declaration of Catch for Generic Exception
    //CWE-120: Wrap-around Error
    } catch (std::out_of_range e) {
        cerr << "Caught Exception: " << e.what() << endl;
    }
    catch (std::overflow_error i)
    {
        cerr << "Caught Exception: " << i.what() << endl;
    }

    int newValue;
    unsigned int index;
    
    //If the inputValue is larger than the number that can be sottored in an int, store the largest value
    //Avoiding CWE-196: Unsigned to Signed Conversion Error (The array size could be larger than 2147483647)
    if(inputValue > 2147483647)
    {
        newValue = 2147483647;
    }
    else
    {
        //Avoiding CWE-482: Comparing instead of Assigning 
        newValue = inputValue;
    }

    //If the input index is smaller than the value that can be stored in an unsigned int store 0
    //Avoiding CWE-195: Signed to Unsigned Conversion Error 
    if(inputIndex < 0)
    {
        index = 0;
    }
    else 
    {
        index = inputIndex;
    }

    //Avoiding CWE-416: Use After Free and CWE-476: NULL Pointer Dereference 
    if(array != nullptr)
    {
        // Avoiding CWE-484: Omitted Break Statement in Switch
        switch (index)
        {
        case 0:
            array[index] = newValue;
            break;
        case 1:
            array[index] = newValue;
            break;
        case 2:
            array[index] = newValue;
            break;
        default:
            cout << "Invalid index entered. No index updated\n";
        }
    }
    else
    {
        cout << "Array was already freed. No index updated\n";
    }

    cout << "\nThe resulting array:\n";

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        cout << "The array at " << i << " = " << array[i] << "\n";
    }

    // CWE-1341: Multiple Releases of Same Resource or Handle - only do it once
    ofstream myfile ("output.txt");
    if (myfile.is_open())
    {
        myfile << "The resulting array:\n";
        for(int i = 0; i < ARRAY_SIZE; i++)
        {
            myfile << "The array at " << i << " = " << array[i] << "\n";
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    //for copying old array to new one in reverse order
    //CWE-468: Incorrect Pointer Scaling -- it is a bad idea to "create" a new array based on where the old one was in memory... just let the compiler do its job
    int* revArray = new int(ARRAY_SIZE);
    
    //CWE-120: Buffer Copy without Checking Size of Input ('Classic Buffer Overflow')
    //copy array only if sizes are same
    //Avoiding: CWE-124: Buffer Underwrite ('Buffer Underflow')
    if (sizeof(*array) == sizeof(*revArray))
    {
        cout << "\nThe arrays are the same size!\n";
        int j = ARRAY_SIZE - 1;
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            revArray[i] = array[j];
            j--;
        }
    }

    cout << "\nThe reverse array:\n";

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        // CWE-192: Integer Coercion Error
        printf("The array at %d = %0.1lf\n", i, (float)revArray[i]);
    }

    //CWE-415: Double Free
    //CWE-401: Missing Release of Memory after Effective Lifetime -- you need to remove pointers
    delete[] array;
    delete[] revArray;
    // Helping to avoid CWE-416: Use After Free
    array = nullptr;
    revArray = nullptr;
}