/////////////////////////////////////////////////////////////////////////////

An Introduction to the Longest Increasing Subsequence Problem
The task is to find the length of the longest subsequence in a given array of integers such that all elements of the subsequence are sorted in strictly ascending order. 
This is called the Longest Increasing Subsequence (LIS) problem.
For example, the length of the LIS for [5 2 8 6 3 6 9 7] is [4] since the longest increasing subsequence is {2,3,6,9}.


Knapsack function
Given an array of integers and a target sum, determine the sum nearest to but not exceeding the target that can be created. To create the sum, use any element of your array zero or one time.
For example, if arr=[2,3,4] and your target sum is 10, you might select [2,2,2,2,2] or [2,2,3,3] or [3,3,3,1]. In this case, you can arrive at exactly the target.
Function Description
Complete the unboundedKnapsack function in the editor below. It must return an integer that represents the sum nearest to without exceeding the target value.
unboundedKnapsack has the following parameter(s):


unboundedKnapsack function
Given an array of integers and a target sum, determine the sum nearest to but not exceeding the target that can be created. To create the sum, use any element of your array zero or more times.
For example, if arr=[2,3,4] and your target sum is 10, you might select [2,2,2,2,2] or [2,2,3,3] or [3,3,3,1]. In this case, you can arrive at exactly the target.
Function Description
Complete the unboundedKnapsack function in the editor below. It must return an integer that represents the sum nearest to without exceeding the target value.
unboundedKnapsack has the following parameter(s):


Самая длинная общая подпоследовательность
Предположим , Алекс ввел строку fosh. Какое слово он имел в виду: fish
илиfоrt?
Мы сравниваем самую длинную общую подстроку, а на самом деле нужно
сравнивать самую длинную общую подпоследовательность: количество
букв в последовательности, общих для двух слов.

/////////////////////////////////////////////////////////////////////////////
