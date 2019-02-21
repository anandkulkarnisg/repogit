#include<iostream>
#include<string>
#include<vector>

using namespace std;

int solution(vector<int> ref)
{

	size_t size = ref.size();
	vector<int> deltas;
	deltas.reserve(size-1);
	for(unsigned int i=1;i<=size-1;++i)
		deltas.push_back(ref[i]-ref[i-1]);

	for(const auto& ref : deltas)
		cout << ref << " , ";
	cout << endl;
	return(1);
}

int main(int argc, char* argv[])
{
	vector<int> my_vec = { 1,2,4,5,7,11,29,30 };
	for(const auto& ref : my_vec)
		cout << ref << " , ";
	cout << endl;
	int cost = solution(my_vec);
	cout << "Cost is = " << cost << endl;
}
