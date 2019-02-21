#include<iostream>
#include<vector>

using namespace std;

void printArr(int arr[], int size)
{
	for(unsigned int i=1; i<size; ++i)
		cout << arr[i] << " , ";
	cout << arr[size] << endl; 
}

void combGen(int arr[], int n, int r, int breakIdx)
{
	printArr(arr, r);
	int startIdx = r;

	while(arr[breakIdx] != (n-r+breakIdx))
	{
		while(arr[startIdx] != (n-r+startIdx))
		{
			arr[startIdx] +=1;	
			printArr(arr, r);
		}
		if(startIdx > breakIdx)
		{
			startIdx--;
		}
	}
}


int main(int argc, char* argv[])
{

	int arr[] = { 0, 1, 2, 3, 4, 5 };
	int n = sizeof(arr)/sizeof(arr[0])-1;
	int r  = 3;

	int tempArr[r+1];

	for(unsigned int i=1; i<=r; ++i)
		tempArr[i]=arr[i];

	int breakIdx = r;	
	int bumpFactor = 0;
	combGen(tempArr, n, r, breakIdx);

	breakIdx--;
	bumpFactor++;
	for(unsigned int i=1; i<breakIdx;++i)
		tempArr[i]=arr[i];
	for(unsigned int i=breakIdx; i<=r;++i)
		tempArr[i]=arr[i] + bumpFactor;

	combGen(tempArr, n, r, breakIdx);
	breakIdx--;
	for(unsigned int i=1; i<breakIdx;++i)
		tempArr[i]=arr[i];
	for(unsigned int i=breakIdx; i<=r; ++i)
		tempArr[i]=arr[i] + bumpFactor;			

	combGen(tempArr, n, r, breakIdx);
	return(0);

}

