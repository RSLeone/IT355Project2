
//IT 355: Created by Ryan Leone, Curtis Bryant, Aneel Gillan, Kaden Hargrove, Nathan Brose, Thomas Gray
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.locks.ReentrantLock;
import java.lang.Thread;

public class ArrayProgram extends Thread {
    // CWE-582: Array Declared Public, Final, and Static
    // CWE-500: Public Static Final Field Not Marked Final
    private static int[] arr;
    private ReentrantLock mutex = new ReentrantLock();
    private static final int ARRAY_SIZE = 10;
    private static int count = 0;

    public static void main(String args[]) throws InterruptedException {

        int numThreads = 2;

        System.out.println("Outside the threads.");

        Scanner scanner = new Scanner(System.in);

        arr = new int[ARRAY_SIZE];

        // CWE-572: Call to Thread run() instead of start() (run is bad)
        List<Thread> threads = new ArrayList<>();
        for (int i = 0; i < numThreads; i++) {
            ArrayProgram thread = new ArrayProgram();
            thread.start();
            threads.add(thread);
        }

        for (Thread thread : threads) {
            thread.join();
        }

        System.out.println("First value of the array after the threads ran is " + arr[0]);
        System.out.println("Count is " + getCount() + " after threads ran.");

        System.out.println();

        // Get the values for the array
        for (int i = 0; i < ARRAY_SIZE; i++) {

            System.out.println("Enter an integer value 10 over the value you want to be stored in the array: ");

            int currentVal = 0;
            try {
                currentVal = scanner.nextInt();
            } catch (InputMismatchException e) {
                // CWE-248: Uncaught Exception
                // CWE-209 Generation of Error Message Containing Sensitive Information
                System.err.println("Invalid Input: enter an integer value");
                System.exit(1);
            }

            // Avoiding CWE-191: Integer Underflow (Wrap or Wraparound)
            // If integer underflow would occur just store the lowest possible integer value
            if (currentVal - 10 > currentVal) {
                currentVal = Integer.MIN_VALUE;
            }

            arr[i] = currentVal;

        }

        System.out.println(
                "The values of the array after being entered are (should be 10 less than the values entered):");

        for (int i = 0; i < ARRAY_SIZE; i++) {
            System.out.println("arr[" + i + "] = " + arr[i]);
        }

        System.out.println();

        System.out.println("Please select and option:");
        System.out.println("1. Multiply all array values by 10");
        System.out.println("2. Add 10 to all array values");
        System.out.print("Option: ");

        int option = 0;

        try {
            option = scanner.nextInt();
        } catch (InputMismatchException e) {
            // CWE-209 Generation of Error Message Containing Sensitive Information
            System.err.println(e.getMessage());
            System.exit(1);
        }

        if (option == 1) // Avoiding CWE-481: Assigning instead of Comparing
        {
            for (int i = 0; i < ARRAY_SIZE; i++) {
                arr[i] = arr[i] * 10;
            }
        } else if (option == 2) // Avoiding CWE-481: Assigning instead of Comparing
        {
            for (int i = 0; i < ARRAY_SIZE; i++) {
                arr[i] = arr[i] + 10;
            }
        } else // Avoiding CWE-478: Missing Default Case in Multiple Condition Expression
        {
            System.out.println("Invalid option entered. Not array modification done");
        }

        System.out.println();

        System.out.println("The values of the array after modification using option " + option + " are:");

        for (int i = 0; i < ARRAY_SIZE; i++) {
            System.out.println("arr[" + i + "] = " + arr[i]);
        }

        scanner.close();

    }

    // CWE-572: Call to Thread run() instead of start()
    public void run() {
        System.out.println("Inside thread: " + Thread.currentThread().threadId() + ". count is " + getCount());
        increment();

        // CWE-366: Race Condition within a Thread
        try {
            mutex.lock();
            addToArrayAtIndex(0, (int) Thread.currentThread().threadId(), arr);
        } finally {
            mutex.unlock();
        }

    }

    public void addToArrayAtIndex(int index, int addValue, int[] array) {
        // CWE-476: NULL Pointer Dereference
        // Check to ensure array is not null then use it.
        // Avoiding CWE-395: Use of NullPointerException Catch to Detect NULL Pointer
        // Dereference
        if (array != null) {
            array[index] += addValue;
        }
    }

    // CWE-585: Empty Synchronized Block
    public synchronized void increment() {
        count++;
    }

    public static synchronized int getCount() {
        return count;
    }
}