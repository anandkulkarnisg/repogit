#include<iostream>
#include<string>
#include<vector>

using namespace std;

template<typename T> class Iterator
{
	private:
		const vector<T>& m_vec;
		int m_index=-1;

	public:
		Iterator(const vector<T>& ref) : m_vec(ref)
	{ 

	}
		bool hasNext()
		{
			if(m_index+1<m_vec.size())
			{
				++m_index;
				return(true);
			}
			else
			{
				reset();
				return(false);
			}
		}

		int getNext()
		{
			return(m_vec[m_index]);
		}
	
		void reset()
		{
			m_index=-1;	
		}
};

int main(int argc, char* argv[])
{
	vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Iterator<int> iter(vec);

	while(iter.hasNext())
		cout << iter.getNext() << ",";
	cout << '\n';

	while(iter.hasNext())
		cout << iter.getNext() << ",";
	cout << '\n';

	return(0);	
}
