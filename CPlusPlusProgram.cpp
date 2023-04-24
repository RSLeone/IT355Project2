//IT 355: Created by Ryan Leone, Curtis Bryant, Aneel Gillan, Kaden Hargrove, Nathan Brose, Thomas Gray
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
// CWE-676: Use of Potentially Dangerous Function
#include "banned.h"

using namespace std;

int main(int argc, char* argv[])
{

    const int ARRAY_SIZE = 3;    

    int* array = new int(ARRAY_SIZE);

    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = 0;
    }

    cout << "Array with size " << ARRAY_SIZE << " was created and filled with 0's\n";

    //CWE-467: Use of sizeof() on a Pointer Type
    cout << sizeof(*array) << " bytes was allocated for the array.\n";

    //CWE-457: Use of Uninitialized Variable
    int index = 0;
    int newValue = 0;

    // CWE-248: Uncaught Exception
    try {
        cout << "Please enter an array index to update between 0 and 2: ";
        cin >> index;

        // CWE-194: Unexpected Sign Extension
        //Avoiding CWE-129: Improper Validation of Array Index 
        while(index < 0 || index > 2)
        {
            cout << "Invalid index entered. Please enter an array index to update between 0 and 2: ";

            cin >> index;
        }

        cout << "Please enter an integer that should be placed into index " << index << ": ";
        cin >> newValue;
    
    //CWE-396: Declaration of Catch for Generic Exception
    } catch (std::out_of_range e) {
        cerr << "Caught Exception: " << e.what() << endl;
    } catch (std::overflow_error i) {
        cerr << "Caught Exception: " << i.what() << endl;
    }

    //Avoiding CWE-416: Use After Free and CWE-476: NULL Pointer Dereference 
    if(array != nullptr)
    {
        //Avoiding CWE-484: Omitted Break Statement in Switch 
        switch(index)
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

    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        cout << "The array at " << i << " = " << array[i] << "\n";
    }

    //for copying old array to new one in reverse order
    int* revArray = new int(ARRAY_SIZE);
    
    //CWE-120: Buffer Copy without Checking Size of Input ('Classic Buffer Overflow')
    //copy array only if sizes are same
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

    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        //CWE-192: Integer Coercion Error
        printf("The array at %d = %0.1lf\n", i, (float) revArray[i]);
    }

    //CWE-415: Double Free
    delete[] array;
    delete[] revArray;
    //Helping to avoid CWE-416: Use After Free 
    array = nullptr;
    revArray = nullptr;

}