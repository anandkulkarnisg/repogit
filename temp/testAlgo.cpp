#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(int argc, char* argv[])
{
 vector<int> arr = { 1, 3, 2 };
 long misPlacedIdx=1;
 sort(arr.begin(), arr.begin()+misPlacedIdx+1, less<int>());
 for(const auto& item : arr)
	cout << item << endl;	
 return(0);
}
