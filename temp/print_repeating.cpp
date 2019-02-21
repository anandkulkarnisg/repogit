#include <stdio.h>
#include <stdlib.h>

void printRepeating(int arr[], int size)
{
  int i;
  printf("The repeating elements are: \n");
  for (i = 0; i < size; i++)
  {
    if (arr[abs(arr[i])] >= 0)
	{
	  printf("turning value at index %d to -ve\n", abs(arr[i]));
      arr[abs(arr[i])] = -arr[abs(arr[i])];
	}
    else
      printf(" %d ", abs(arr[i]));
  }
}
 
int main()
{
  int arr[] = {99, 2, 3, 99};
  int arr_size = sizeof(arr)/sizeof(arr[0]);
  printRepeating(arr, arr_size);
  return 0;
}
