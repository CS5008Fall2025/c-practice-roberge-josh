/**
 * Note: The returned array must be malloced, assume caller calls free().
 * Question: Given an array of integers nums and an integer target, return 
 * indices of the two numbers such that they addup to target.
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 * You can return the answer in any order.
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
        int current_i_th_value;
        int addition_results;
        int* my_result_vector;

        for (int i = 0; i < numsSize; i++ ){
            current_i_th_value = nums[i];
            for(int j = i+1; j < numsSize; j++ ){
                addition_results = current_i_th_value + nums[j];
                if ( addition_results == target){
                    my_result_vector = (int*)malloc(2 * sizeof(int));
                    my_result_vector[0] = i;
                    my_result_vector[1] = j;
                    *returnSize = 2;
                    return my_result_vector;
                }
            }
        }
    return NULL;
};
/**
* I think the problem that was given was easy to quickly wrap my head around, and 
* I even understood how to acquire a run of O(n) within a short amount of time. I 
* think what I still find hard about C is the idea of pointers, and not having objects.
* For example, it took me a minute to realize that the user would need a required length
* to know how to run my function.
*/
