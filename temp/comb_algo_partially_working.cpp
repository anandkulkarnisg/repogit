#include<iostream>
#include<string>
#include<vector>

using namespace std;

void printArr1(int arr[], int size) 
{
	for (int i = 1; i < size; ++i)
		cout << arr[i] << " , ";
	cout << arr[size] << endl;
}

void combGen(int arr[], int n, int r, int breakIdx) 
{
	printArr1(arr, r);
	int startIdx = r;

	while (arr[breakIdx] != (n - r + breakIdx)) 
	{
		while (arr[startIdx] != (n - r + startIdx)) 
		{
			arr[startIdx] += 1;
			printArr1(arr, r);
		}
		if (startIdx > breakIdx) 
		{
			startIdx--;
			if (startIdx == breakIdx && arr[startIdx] < (n - r + breakIdx)) 
			{
				arr[startIdx] += 1;
				for (int i = startIdx + 1; i <= r; ++i)
					arr[i] = arr[i - 1] + 1;

				startIdx = r;
				printArr1(arr, r);
			}
		}
	}
}

void combinationGenerator() 
{

	int n, r;
	cin >> n >> r;
	int arr[n+1];
	for(int i=1; i<=n; ++i)
		arr[i]=i;

	if(r<=0)
		return;

	//int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	//int n = sizeof(arr) / sizeof(arr[0]) - 1;
	//int r = 2;

	int tempArr[r + 1];

	for (int i = 1; i <= r; ++i)
		tempArr[i] = arr[i];

	int breakIdx = r;
	int bumpFactor = 1;

	if(r > n)
	{
		return;
	}

	if (n == r) 
	{
		combGen(tempArr, n, r, breakIdx);
		return;
	}

	if (n > r) 
	{
		while (tempArr[1] != (n - r + 1)) 
		{
			combGen(tempArr, n, r, breakIdx);
			breakIdx--;

			if (breakIdx == 0)
				break;

			for (int i = 1; i < breakIdx; ++i)
				tempArr[i] = arr[i];

			for (int i = breakIdx; i <= r; ++i)
				tempArr[i] = arr[i] + bumpFactor;

			if(tempArr[1] == (n - r + 1))
				printArr1(tempArr, r);
		}

	}

}

int main(int argc, char* argv[]) 
{
	combinationGenerator();
	return (0);
}
