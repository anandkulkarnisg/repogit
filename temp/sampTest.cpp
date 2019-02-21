#include<iostream>
#include<string>
#include<typeinfo>
#include<cxxabi.h>
#include<type_traits>
#include<memory>

using namespace std;

template <typename T, bool WithCVCorrections = true> string typeName()
{
    typedef typename remove_reference<T>::type TR;

    unique_ptr<char, void(*)(void*)> own(
    abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
        free
    );
    string r = (own != nullptr) ? own.get() : typeid(TR).name();
    if (WithCVCorrections) {
        if (is_const<TR>::value)
            r += " const";
        if (is_volatile<TR>::value)
            r += " volatile";
        if (is_lvalue_reference<T>::value)
            r += "&";
        else if (is_rvalue_reference<T>::value)
            r += "&&";
    }
    return r;
}

string classname(const type_info& info)
{
	int status;
	char* rslt=abi::__cxa_demangle(info.name(),0,0,&status);
	string result(rslt);
	free(rslt);
	return result;
}

int main(int argc, char* argv[])
{
	int* ptr = new int(10);
	decltype(move(ptr)) pval = move(ptr);
	cout << classname(typeid(pval)) << endl;			 // as per typeid information the type of pval is int*.
	cout << typeName<decltype(pval)>() << endl;			 // accurate information ie typeid plus additional info which is missed by typeid

	bool isSame = is_same<decltype(pval), int*>::value;  // What then is the pval not same as int* as per is_same ? 	
	cout << "isSame status = " << isSame << endl;  

	isSame = is_same<decltype(pval), int*&&>::value;  // What then is the pval not same as int* as per is_same ?     
    cout << "isSame status = " << isSame << endl;

	cout << is_same<int*, int*>::value << endl;
	delete[] ptr;
	
	return(0);	
}

