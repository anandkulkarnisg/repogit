#include<iostream>
#include<string>
#include<map>
#include<type_traits>
#include<functional>

using namespace std;

std::map<std::string, std::string> m_configMapItems;

template<typename T> T getTvalue(const std::string& key, const T& defaultVal)
{
    T returnVal = defaultVal;
    auto iter = m_configMapItems.find(key.c_str());
    if(iter != m_configMapItems.end())
    {
        // Case of bool.
        if(std::is_same<T, bool>::value)
        {
            if(iter->second == "true" || iter->second == "1")
                returnVal=true;
        }

        // Case for the long.
        if(std::is_same<T,long>::value)
        {
            try
            {
                returnVal = std::stol(iter->second);
            }
            catch(const std::invalid_argument& e)
            {
                std::cout << "Exception happened while converting " << iter->second << " Into a long value." << std::endl;
            }
        }
    }
    return(returnVal);
}

template<typename T> struct S
{
	T operator()(const std::string& str, const T& tval) { return(getTvalue<T>(str, tval)); }	
};

int main(int argc, char* argv[])
{
	std::result_of<S<long>(const std::string&, const long&)>::type p;
	decltype(p) q;

	//decltype(S<long>(const std::string&, const long&)) r;	// This does not work!. what decltype needs is an expression which can be evaluated.

	if(std::is_same<decltype(p), decltype(q)>::value)
		std::cout << "Yes they are same" << std::endl;
	else
		std::cout << "No they are not the same" << std::endl;	

	using type_name = typename std::result_of<S<long>(const std::string&, const long&)>::type;
	if(std::is_same<long,type_name>::value)
		std::cout << "Yes they are same" << std::endl;
	else
		std::cout << "No they are not the same" << std::endl;
}

