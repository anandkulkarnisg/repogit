#include<iostream>
#include<string>
#include<vector>

using namespace std;

void printSubSets(const vector<int>& vectorRef)
{
	size_t len = vectorRef.size();
	cout << "1<<len = " << (1<<len) << endl;
	// Run a loop for printing all 2^n 
	// subvectors one by obe 
	for (int i = 0; i < (1<<len); i++) 
	{ 
		cout << "value of i = " << i << endl;
		std::cout << "{ "; 

		// Print current subvector 
		for (int j = 0; j < len; j++) 

			// (1<<j) is a number with jth bit 1 
			// so when we 'and' them with the 
			// subvector number we get which numbers 
			// are present in the subvector and which 
			// are not 
			if ((i & (1 << j)) > 0) 
				cout << vectorRef[j]  <<  " "; 

		std::cout << "}\n"; 
	} 		
}

int main(int argc, char* argv[])
{
	vector<int> sampleSet;
	sampleSet.emplace_back(1);
	sampleSet.emplace_back(2);
	sampleSet.emplace_back(3);
	printSubSets(sampleSet);	
	return(0);

}

