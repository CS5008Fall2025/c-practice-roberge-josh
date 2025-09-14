/**
 * Student Name:
 * Semester:
 * 
 * 
 * This file is to test the functions in cpractice.h. You are to write at least *TWO* (maybe more) tests for every function. 
 * Some sample ones have been provided for you.
*/

#include <stdio.h>  // basic input and output
#include <stdlib.h> // standard library

#include "cpractice.h" // header file for cpractice.c
#include <assert.h>

// this may help with some tests, as the array numbers match their index
int * create_simple_array(int size) {
    int * arr = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    return arr;
}

/**
 * Tests a basic swap
*/
int test_swap_one() {
    printf("1. test_swap_one()\n");
    int a = 5;
    int b = 10;
    swap(&a, &b);
    if (a == 10 && b == 5) {
        return 1;
    }
    return 0;
}

/**
 * Tests the create_array_of_ints_fib function
*/
int test_create_array_of_ints_fib() {

    printf("2. test_create_array_of_ints_fib()\n");
    int* arr = create_array_of_ints_fib(5);
    int expected[] = {1, 1, 2, 3, 5};
    for (int i = 0; i < 5; i++) {
        if (arr[i] != expected[i]) {
            free(arr);
            return 0;
        }
    }
    free(arr); // note expected does not need freed.. why is that?
    // everything matched
    return 1;
}

int test_base_cases_fibs() {
    printf("3. test base cases create_array_of_ints_fib()\n");
    int* arr = create_array_of_ints_fib(0);
    if (arr != NULL){
        printf("failed Null basecase for fibs");
        return 0;
    };

    arr = create_array_of_ints_fib(1);
    if (arr[0] != 1){
            return 0;
        };

    return 1;

}




int test_reverse_array(){
    printf("4. test reverse_array()\n");
    // normal even length
    int arr[] = {1,2,3,4};
    int expected[] = {4,3,2,1};
    reverse_array(arr, 4);
    int result = arrays_are_equal(arr,expected, 4);
    if (result == 0){
        printf("Error: Reverse Array normal even length Tests Failed");
        return 0;
    }



    // normal odd
    int arr_1[] = {2, 3, 4};
    int expected_1[] = {4,3,2};
    reverse_array(arr_1, 3);
    result = arrays_are_equal(arr_1, expected_1, 3);
    if (result == 0){
        printf("Error: Reverse Array normal odd length Tests Failed");
        return 0;
    }

    // edge [1]
    int arr_2[] = {1};
    int expected_2[] = {1};
    reverse_array(arr_2, 1);
    result = arrays_are_equal(arr_2, expected_2, 1);
    if (result == 0){
        printf("Error: Reverse Array normal odd length Tests Failed");
        return 0;
    }

    return 1;


}

int test_double_array_size(){
    printf("4. test double_array_size()\n");
    // Normal
    int arr[] = {1,2,3};
    int expected[] = {1,2,3,0,0,0};
    int* new_arr = double_array_size(arr, 3);
    int result = arrays_are_equal(new_arr, expected, 6);
    if (result == 0){
        printf("Error: double_array_size normal case failed");
        return 0;
    }
    return 1;
}


int test_copy_array_start_end_loop(){
    printf("5. test copy_array_start_end_loop()\n");

    // Normal Silice
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {2, 3, 4};
    int new_array_size = 3;
    int* new_arr = copy_array_start_end_loop(arr, 5, 1, 3, &new_array_size );
    int result = arrays_are_equal(new_arr, expected, 6);
    if (result == 0){
        printf("Error: normal slice failed for copy_array_start_end_loop");
        return 0;
    }

    // wrapper slice



    return 1;

}


// this is a list of all the unit tests
int (*unitTests[])() = {
        test_swap_one,
        test_create_array_of_ints_fib,
        test_base_cases_fibs,
        test_reverse_array,
        test_double_array_size,
        test_copy_array_start_end_loop
        // add more test function names here
};

int main(int argc, char const *argv[])
{
    int numTests = sizeof(unitTests) / sizeof(unitTests[0]);
    int numPassed = 0;

    for (int i = 0; i < numTests; i++) {
        if (unitTests[i]()) {
            numPassed++;
        } else {
            printf("Test %d failed\n", i);
        }
    }

    printf("Passed %d out of %d tests\n", numPassed, numTests);
    return 0;
}
