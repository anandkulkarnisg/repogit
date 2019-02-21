#include<iostream>
#include<string>

using namespace std;

void printMaxBuySellPossible(const int arr[], const size_t& size)
{
	int min = arr[0];
	int minIdx=0;
	int max = arr[1];
	int maxIdx=1;
	int diffAmt=0;

	// Time complexity is 0(n).
	for(unsigned int i=1; i<size; ++i)
	{
		if((arr[i]-min)>=diffAmt)
		{
			diffAmt=arr[i]-min;
			max=arr[i];
			maxIdx=i;
		
			if(arr[i] <= min)
			{
				min=arr[i];
				minIdx=i;
			}
		}
	
		if(arr[i]==min && i>minIdx) // choose the min closest to the maxIdx to reduce holding period.
		{
			min=arr[i];
			minIdx=i;
		}
	}
	cout << "The best buy and sell possible is " << min << ", " << max << endl;
	cout << "The indices for buy and sell are = " << minIdx << " , " << maxIdx << endl;
	cout << "profit amount is = " << diffAmt << endl;
}

int maxDiff(int arr[], int arr_size) 
{ 
     // Maximum difference found so far 
     int max_diff = arr[1] - arr[0]; 
     int minIdx=0, maxIdx=1;
       
     // Minimum number visited so far  
     int min_element = arr[0]; 
     for(int i = 1; i < arr_size; i++) 
     {      
       if (arr[i] - min_element > max_diff)                              
		{
	       max_diff = arr[i] - min_element; 
		   maxIdx=i;
		}
         
       if (arr[i] < min_element) 
		{
	       min_element = arr[i];                      
		   minIdx=i;
		}
     } 

	 cout << "minIdx = " << minIdx << " , " << "maxIdx = " << maxIdx << ", amount = " << max_diff << endl;       
     return max_diff; 
}  

int main(int argc, char* argv[])
{
	//int arr[] = { 7, 8, 5, 3, 2, 7, 11, 1, 10, 15, 13, 17, 12 };
	//int arr[] = { 4, 4, 4, 4, 4, 4, 4, 4, 5 };
	int arr[] = { 4, 20, 2, 14 };
	size_t size = sizeof(arr)/sizeof(arr[0]);
	//printMaxBuySellPossible(arr, size);
	maxDiff(arr, size);
	return(0);
}
