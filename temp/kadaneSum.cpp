#include<iostream>
#include<string>
#include<algorithm>
#include<tuple>

using namespace std;

int maxSumSubArray(const int arr[], const size_t& size)
{
	long maxEndingHere=0;
	long maxSoFar=0;

	for(unsigned int i=0; i<size; ++i)
	{	
		maxEndingHere = maxEndingHere + arr[i];
		if(maxEndingHere<0)
		{
			maxEndingHere=0;
		}
		else if(maxSoFar<maxEndingHere)
		{
			maxSoFar=maxEndingHere;
		}	
	}
	return(maxSoFar);	
}

tuple<int, int, long> maxSubArray(const int arr[], const size_t& size)
{
	long maxEndingHere=0;
	long maxSoFar=0;
	int maxIdx=0;

	// Core of the algorithm : 0(n)
	for(unsigned int i=0; i<size; ++i)
	{
		maxEndingHere=max<long>(arr[i], maxEndingHere+arr[i]);
		if(maxEndingHere>maxSoFar)
			maxIdx=i;
		maxSoFar=max<long>(maxSoFar, maxEndingHere);
	}

	// Iterate back to get the minIdx.
	int runningSum=arr[maxIdx];
    int iter=maxIdx-1;
    while(runningSum!=maxSoFar)
    {
        runningSum+=arr[iter];
        --iter;
    }
    int minIdx=iter+1;

	return(make_tuple(minIdx, maxIdx, maxSoFar));
}

int main(int argc, char *argv[])
{
	int arr[] = { -2, -3, 4, -1, -2, 1, 5, -3 };
	//int arr[] = { 1, 2, 3, 4, -3, -2, 1 };
	size_t size = sizeof(arr)/sizeof(arr[0]);
	int solution = maxSumSubArray(arr, size);
	cout << solution << endl;

	tuple<int, int, long> altSolution = maxSubArray(arr, size);
	cout << "minIdx = " << get<0>(altSolution) << ", maxIdx = " << get<1>(altSolution) << ", sum = " << get<2>(altSolution) << endl;
	return(0);	 
}
