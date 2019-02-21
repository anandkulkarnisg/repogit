#include<string>
#include<iostream>

using namespace std;

void getItemDigit(const int arr[], const size_t& size, const int& divisor)
{
	for(unsigned int i=0; i<size; ++i)
		cout << "The digit for number = " << arr[i] << " is = " << (arr[i]/divisor)%10 << endl;
	cout << "-----------------------" << endl;
}

int main(int argc, char* argv[])
{
	int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	int maxItem=arr[0];
	for(unsigned int i=0; i<size; ++i)
	{
		if(arr[i]>maxItem)
			maxItem=arr[i];
	}
	
	int numPasses = to_string(maxItem).length();
	int exp=1;
	for(unsigned int i=0; i<numPasses; ++i)
	{
		getItemDigit(arr, size, exp);
		exp*=10;
	}
	return(0);	
}
