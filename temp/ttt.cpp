#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<string>

using namespace std;

int solution(const std::string& input)
{
    std::size_t size = input.length();
    vector<int> valley;
    valley.reserve(size);
    int seaLevelCounter=0;

    for(unsigned int i=0; i<size; ++i)
    {
        if(input[i] == 'U')
            seaLevelCounter++;
        else
            seaLevelCounter--;        
        valley.push_back(seaLevelCounter);                
    }
    
    int resultCount=0;
   
	for(unsigned int i=0; i<size; ++i)
		cout << valley[i] << ",";
	cout << endl;
 
    for(unsigned int i=0; i<size-1; ++i)
    {
        if(valley[i] <0 && valley[i+1] == 0)
        {
            resultCount++;        
        }
    }
    
    return(resultCount);    
}

int main() 
{
    
    int n;
    cin >> n;
    char ch;
    std::string input;
    input.clear();
    
    for(unsigned int i=0; i<n; ++i)
    {
        cin >> ch;
        input += ch;
    }
     
    cout << solution(input) << endl;              
}

