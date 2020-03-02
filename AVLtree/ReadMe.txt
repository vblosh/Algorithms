The median of  numbers is defined as the middle number after sorting them in order if  is odd. Or it is the average of the middle two numbers if  is even. You start with an empty number list. Then, you can add numbers to the list, or remove existing numbers from it. After each add or remove operation, output the median.

Example: 
For a set of  numbers  the median is the third number in the sorted set , which is . Similarly, for a set of  numbers, , the median is the average of the second and the third element in the sorted set , which is .  

Input: 
The first line is an integer, , that indicates the number of operations. Each of the next  lines is either a x or r x. a x indicates that  is added to the set, and r x indicates that  is removed from the set.

Output: 
For each operation: If the operation is add, output the median after adding  in a single line. If the operation is remove and the number  is not in the list, output Wrong! in a single line. If the operation is remove and the number  is in the list, output the median after deleting  in a single line. (If the result is an integer DO NOT output decimal point. And if the result is a real number, DO NOT output trailing 0s.)

Note 
If your median is 3.0, print only 3. And if your median is 3.50, print only 3.5. Whenever you need to print the median and the list is empty, print Wrong!

Constraints: 
 
For each a x or r x,  will always be a signed integer (which will fit in 32 bits).

Sample Input:

7  
r 1  
a 1  
a 2  
a 1  
r 1  
r 2  
r 1  
Sample Output:

Wrong!  
1  
1.5  
1  
1.5  
1  
Wrong!
Note: As evident from the last line of the input, if after remove operation the list becomes empty, you have to print Wrong!. 