#include<iostream>
#include<string>
#include<map>
#include<boost/tokenizer.hpp>
#include<set>

using namespace std;

int calcMinCost(const int& n, const map<int, int>& connectedPairs)
{
	map<int, set<int>> mmap;
	set<int> lonely;
	
	for(const auto& iter : connectedPairs)
	{
		int p=iter.first;
		int q=iter.second;
		lonely.add(p);
		lonely.add(q);	

		set<int> hs_q;
		set<int> hs_p;
		int p_i=q_i=-1;

			for(int t=n; t>=1; t--){
				if(map.containsKey(String.valueOf(t))){
					if(map.get(String.valueOf(t)).contains(q)){
						hs_q=map.get(String.valueOf(t));
						q_i=t;
					}
					if(map.get(String.valueOf(t)).contains(p)){
						hs_p=map.get(String.valueOf(t));
						p_i=t;
					}
				}
}






		for(int t=n; t>=1; --t)
		{
			if(mmap.get(t)!=mmap.end())
			{
				const auto& iter = mmap.get(t).find(t);
				if(iter!= mmap.get(t).end())
					
			}r
										
	

		}

	
	
	}	



}





int main(int argc, char* argv[])
{
	int result;
	int n;
	cin >> n;
	int numPairs;
	cin >> numPairs;
	string pairString;

	map<int, int> connectedPairs;
	
	for(unsigned int i=0; i<numPairs; ++i)
	{
		cin >> pairString;	
		tokenizer<char_separator<char>> tokens(pairString, " ");	
		int keyItem=std::stoi(tokens[0]);
		int valueItem=std::stoi(tokens[1]);
		connectedPairs[keyItem]=valueItem;
	}

	int result=calcMinCost(n, connectedPairs);
	cout << result << endl;
	return(0);
}
