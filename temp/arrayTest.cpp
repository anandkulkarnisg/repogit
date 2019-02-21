#include<iostream>
#include<string>

using namespace std;

void workingModule1()
{
	int arr[] = { 1, 2, 3, 4, 4, 5, 7, 4, 4, 10 };
	size_t size = sizeof(arr)/sizeof(arr[0]);
	int itemToRemove=4;

	int j=0;
	int i=0;

	while(i<size-1)
	{
		if(arr[i]!=itemToRemove)
		{
			++j;
			++i;
		}
		else
			++i;
		if(arr[i]!=itemToRemove)
			arr[j]=arr[i];
	}

	for(int i=0;i<j;++i)
		cout << arr[i] << " , ";
	cout << arr[j] << '\n';
}

void workingModule2()
{
	int arr[] = { 8, 6, 7, 4, 1, 2, 3, 4, 5, 4, 4, 4, 7, 8, 9, 4, 4, 4, 4, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	cout << "original array = { 8, 6, 7, 4, 1, 2, 3, 4, 5, 4, 4, 4, 7, 8, 9, 4, 4, 4, 4, 11, 12, 13, 14, 15, 16, 17, 18, 19 }" << endl; 
	size_t size = sizeof(arr)/sizeof(arr[0]);
	int itemToRemove=4;
	int frontIdx=4;
	int rearIdx=3;

	// This is circular buffer queue starting at index 4 and ending at index 3 [ wrapped around ]. We need to remove item 4.
	// part 1 : We consider items from frontIdx till end.

	int i=frontIdx;
	int j=frontIdx;

	while(i<size-1)
	{
		if(arr[i]!=itemToRemove)
		{
			++j;
			++i;
		}
		else
			++i;
		if(arr[i]!=itemToRemove)
			arr[j]=arr[i];
	}

	cout << "The ending index j = " << j << endl;

	for(int i=0;i<j;++i)
		cout << arr[i] << " , ";
	cout << arr[j] << '\n';

	// part 2 : We consider items from index zero till rearIdx.

	i=0;
	++j;

	while(i<=rearIdx)
	{
		if(arr[i]!=itemToRemove)
		{
			arr[j]=arr[i];
			++j;
			j=j%size;
		}
		++i;
	}
	--j;
	if(j==-1)
		j=size-1;

	rearIdx=j;
	
	cout << "The ending index of j = " << j << endl;

	for(int i=frontIdx;i<rearIdx;++i)
		cout << arr[i] << " , ";
	cout << arr[rearIdx] << '\n';
}

int main(int argc, char* argv[])
{
	//workingModule1();
	workingModule2();
	return(0);
}
