# Homework - C Practice Report

Completely answer the report questions below. Make sure to double check the final version to make sure it is easily readable on your github repository. 




1. What is the difference between a standard numeric type (int, float, double) and a pointer?

__Answer__:

```c
int std_type = 4;
printf("std_type = %d\n", std_type);
printf("std_type address is %p\n", &std_type);
int *ptr = &std_type;
printf("what ptr point to = %d\n",  *ptr);
printf("ptr = %p\n", ptr);
// output:
// std_type = 4
// std_type address is 0x7ffc74f12c6c
// what ptr points to = 4
// ptr = 0x7ffc74f12c6c
```
The example above outlines the key differences between standard numeric types and pointers. In short, standard numeric type represents a value while a pointer represents and address to which “points” to an address in memory. Let break down the example above and discuss this firther
On the first line, we assign a value to a basic numeric type int. From there, we print std_type which is the number four, but that number four has a memory address. Using pointers we assign std_type's address to a pointer named ptr. Ptr now represents an address and we can follow the address (using *ptr) to a given value.

   
2. In your test file, we had the following code:
    
    ```c
    int* arr = create_array_of_ints_fib(5);
    int expected[] = {1, 1, 2, 3, 5};
    ```
    Later in the code we only `free(arr)` but not expected. Why is this? What is the difference in where they are stored in memory?

__Answer:__

In that code we are returning a pointer to an array. Given that we want all the array's values to persist, we know that `create_array_of_ints_fib` must have allocated its array values on the heap. Items allocated on the heap persist after function calls and therefore we must `free(arr)` to avoid memory leaks.

3. What is the difference between the heap and stack when related to memory allocation and management?

__Answer:__

```c
int* makeHeapVariable (){
    // heap Memory
    int *arr = malloc(5 * sizeof(int));
    arr[0] = 1; arr[1] = 2; arr[2] = 3; arr[3] = 4; arr[4] = 5;
    return arr;
}
int* makeStackVariable(){ // int* not *int
    int arr[] = {1,2,3,4,5};
    return arr; // This is dangerous!
}
```
Heap and stack memory serve different purposes when it comes to their use in a program. Stack memory gets automatically allocated when functions are called in a program and then gets deallocated once the function call is finished. Heap memory is long-lasting memory and must be allocated and deallocated by the developer.

Let's make use of the example above. The `makeHeapVariable` returns a pointer to an array. An array points to its first memory address and then all other values get their addresses indexed through pointer math (*ptr+1). This array will live past the function call since it is allocated on the heap.

The second function makeStackVariable is a different story. This function also returns a pointer to an array, but the values allocated to the array will get removed from stack memory once finished. The correct address to the pointer will be returned but the value at that array will be different, undefined, or something else completely random.





4. Take the following code:
   ```c
   #include <stdio.h>
   #include <stdlib.h>

   typedef struct {
     int x, y;
   } Point;

   Point * new_point(int x, int y) {
     Point pt = {x, y};
     return &pt;
   }

   int main() {
      Point* point = new_point(10, 10);
      printf("x: %d, y: %d", point->x, point->y);
      return 0;
   }
   ```
   Would the code run correctly? Even if it does compile, what would be some potential runtime issues? After answering your thoughts, put the output of a run below (you may need to run it a few times).

   __Answer__:

I would not expect the code above to run correctly. This is a similar answer to question 3. The issue here is that we are allocating our array to stack memory. Stack memory gets deallocated after the function call is over. An array points to its first memory address and all other values get indexed through pointer math (pointer +1). The issue here is that all those values in that array were deallocated after the call. The address to the array is correct, but the values may still be there, may be allocated with different numbers, or may be undefined.


   ```text
   x: 10, y: 10
   x: 10, y: 10
   x: 10, y: 10
   x: 10, y: 10
   ```

   Fix the code in the following block:
   ```c
   #include <stdio.h>
   #include <stdlib.h>

   typedef struct {
     int x, y;
   } Point;

   Point * new_point(int x, int y) {
    int *arr = malloc(5 * sizeof(int));
    arr[0] = x; 
    arr[1] = y; 
    return arr;
   }

   int main() {
      Point* point = new_point(10, 10);
      printf("x: %d, y: %d", point->x, point->y);
      return 0;
   }
   ```

5. When you use `malloc`, where are you storing the information?

__Answer:__

When we use malloc in C, we are establishing storage in heap memory. This type of storage persists across function calls and must be deallocated or free()d after use.


6. Speaking about `malloc` and `calloc`, what is the difference between the two (you may need to research it!)?


__Answer:__

malloc and calloc are similar because they both define storage on the heap. They differ in respect to how they define that storage. malloc merely sets aside a block of memory while calloc zeros out that memory. calloc and malloc also have different parameters. malloc just needs the size of the memory to set aside while calloc needs the unit size and the number of units.

7. What are some common built in libraries used for C, list at least 3 and explain each one in your own words. Name a few (at least 3) functions in those libraries (hint: we used two of the most common ones in this assignment. There are many resources online that tell you functions in each library - you need to include at least 1 reference, but ideally for every library, you should have a reference to it)?
   - Example: stdlib.h - provides functions for general-purpose operations including
              memory management and random numbers [1].
     - void * malloc(size_t) - allocates memory specified in size on the heap and returns a pointer to that location
     - void * calloc(size_t num_elements, size_t element_size) - contiguous allocation for allocating arrays with the default value of 0. Slower than malloc. 
     - int rand(void) - returns a random integer between 0 and RAND_MAX. Seed should be set before hand. 


   1. math.h: this is `c` mathematical library and it contains basic and common math operations. 
      * ceil(x) -> returns a number rounded to the nearest whole number
      * log(x) ->  returns the natrual log of x
      * pow(x,y) -> calculates x^y

      reference: https://www.w3schools.com/c/c_ref_math.php
   
   2. string.h: this library contains logic for manipulating and mutating strings in C 
      * strcat() -> concats two string together
      * strlen() - > returns the length of a string
      * strtok() -> splits a string by a delimiter, and then you can index each string piece
 reference: https://www.w3schools.com/c/c_ref_string.php

   3. stdio.h: This library contains all the functions for input and output logic in c.
      * fclose() -> closes a file 
      * printf() -> writes a formated strings to the console
      * puts() -> prints a string to the console
 

8. Looking at the struct Point and Polygon, we have a mix of values on the heap, and we make ample use of pointers. Take a moment to draw out how you think that looks after `create_triangle(2,3)` is called (see an example below). The important part of the drawing it to see that not everything is stored together in memory, but in different locations! Store the image file in your github repo and link it here. You can use any program to draw it such as [drawIO](https://app.diagrams.net/), or even draw it by hand and take a picture of it. 


## Technical Interview Practice Questions
For both these questions, are you are free to use what you did as the last section on the team activities/answered as a group, or you can use a different question.

1. Select one technical interview question (this module or previous) from the [technical interview list](https://github.com/CS5008-khoury/Resources/blob/main/TechInterviewQuestions.md) below and answer it in a few sentences. You can use any resource you like to answer the question.

2. Select one coding question (this module or previous) from the [coding practice repository](https://github.com/CS5008-khoury/Resources/blob/main/LeetCodePractice.md) and include a c file with that code with your submission. Make sure to add comments on what you learned, and if you compared your solution with others. 

## Deeper Thinking
In Java and Python, do you think new objects are stored on the stack or the heap? Feel free to work through your thoughts as to why it would be better to store them on the stack or heap. You should consider pass by reference, and how that is similar to pointer in your answer. Feel free to use resources, but make sure to cite them, and include the citation below using ACM format. You will note LLMs are not valid references, but they can give you directions to valid references. Make sure to use your own words. 

Answer here using a paragraph (not just bullet points). 




## References
Add any references you use here. Use ACM style formatting, adding to the numbers as you add the reference. 

1. cppreference.com Contributors. 2025. Standard library header <stdlib.h>. cppreference.com. Retrieved May 1, 2025 from https://en.cppreference.com/w/c/header/stdlib

2. ...

## Resource/Help: Linking to images?
To link an image, you use the following code

```markdown
![alt text](path / link to image)
```
for example
```markdown
![my memory drawing](instructions/rectangle_points.png)
```


Here is a sample using: 
```c
void my_func() {
    Polygon* r = create_rectangle(5,5);
    printf("The area of the rectangle is %d\n", area(r));
}
```

![my memory drawing](instructions/rectangle_points.png)

Note: This is a simplified version. However, it helps illustrate why we need to use `free` on the pointers in the struct. If we do not, we will have memory leaks! (memory that is allocated, but not freed, and thus cannot be used by other programs). In the above example code, `r` is created, and then the variable is destroyed when the function ends. However, the memory allocated for the struct is not freed, and thus we have a memory leak.

When you work on your version for `create_triangle(2, 3)`, you do not have to be exact on the memory structure (the locations on the heap were randomly chosen). The idea is more to show how the memory is stored, and the pointers to different memory addresses. 

