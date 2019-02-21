#include<iostream>
#include<string>
#include<tuple>

using namespace std;

tuple<size_t, size_t, int, int, int> maxDiff(int arr[], int arr_size)
{ 
	// Maximum difference found so far 
	int max_diff = arr[1] - arr[0]; 
	size_t minIdx=0;
	size_t maxIdx=1;

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

	// We need to find the closest buy to the sell on left side of array [ time optimization ].
	for(int i=maxIdx-1;i>=0;--i)
	{
		if(arr[maxIdx]-arr[i] == max_diff)
		{
			minIdx=i;
			break;
		}
	}
	
	tuple<size_t, size_t, int, int, int> result=make_tuple(minIdx, maxIdx, arr[minIdx], arr[maxIdx], max_diff);
	return(result);
}  

int main(int argc, char* argv[])
{
	int arr[] = { 7, 8, 5, 3, 2, 7, 11, 1, 10, 15, 13, 17, 12 };
	//int arr[] = { 4, 4, 4, 4, 4, 4, 4, 4, 5 };
	//int arr[] = { 4, 20, 2, 14 };
	size_t size = sizeof(arr)/sizeof(arr[0]);
	tuple<size_t, size_t, int, int, int> resultItem = maxDiff(arr, size);
	cout << "You should buy the stock at day = " << get<0>(resultItem) << " at price = " << get<2>(resultItem) <<  " and sell at day = " << get<1>(resultItem) << " at price = " << get<3>(resultItem);
	cout << " for a net profit of amount = " << get<4>(resultItem) << endl;
	return(0);
}
