#include<iostream>
#include<string>
#include<vector>

using namespace std;

template<typename T> class SampleClass
{
	private:
		const vector<T>& m_vec;
	public:
		SampleClass(const vector<T>&);
		void show();
};

template<typename T> SampleClass<T>::SampleClass(const vector<T>& vec) : m_vec(vec) { } 

template<typename T> void SampleClass<T>::show() 
{
	for(const auto& ref : m_vec)
		cout << "Item is = " << ref << endl;
}

int main(int argc,char* argv[])
{
	vector<int> ivector = { 1,2,3,4 };
	SampleClass<int> test(ivector);
	test.show();

	ivector = { 5,6 };
	test.show();

	vector<std::string> istring = { "Anand" , "Apparao", "Kulkarni" };
	SampleClass<std::string> test2(istring);
	test2.show();
}
