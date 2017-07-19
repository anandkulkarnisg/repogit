/*
 * EmptyTemplate.cpp
 *
 *  Created on: Jul 7, 2017
 *      Author: anand
 */

#include<iostream>
#include<vector>
#include<string>

using namespace std;

class CustomStringClass
{

	private:
		std::string _internalString;
		char _seperator;
		long _counter;

	public:
		CustomStringClass();
		void addItem(const std::string&);
		std::string subtractWordFromFront();
		std::string subtractWordFromEnd();
		void show();
		std::string get();
};

CustomStringClass::CustomStringClass()
{
	_internalString = "";
	_seperator=' ';
	_counter=0;
}

void CustomStringClass::addItem(const std::string& addItem)
{
	_internalString += addItem;
	_internalString += _seperator;
	_counter++;
}

void CustomStringClass::show()
{
	cout << _internalString << endl;
}

std::string CustomStringClass::get()
{
	return(_internalString);
}

std::string CustomStringClass::subtractWordFromFront()
{
	if(_counter>1)
	{
		std::size_t indexPosition = _internalString.find(_seperator);
		if(indexPosition != std::string::npos)
		{
			std::string result = _internalString.substr(0, indexPosition);
			cout << "result = "<< result << endl;
			_counter--;
			if( _counter == 0)
				_internalString = "";
			else
				_internalString = _internalString.substr(indexPosition+1, _internalString.length()-1);
			return(result);
		}
		else
			return(nullptr);
	}
	return(nullptr);
}


int main(int argc, char* argv[])
{
	CustomStringClass testObject;
	testObject.addItem("Anand");
	testObject.addItem("Apparao");
	testObject.addItem("Kulkarni");
	testObject.show();
	std::string testItem = testObject.subtractWordFromFront();
	cout << testItem << endl;
	testObject.show();
	testItem = testObject.subtractWordFromFront();
	cout << testItem << endl;
	testObject.show();
    testItem = testObject.subtractWordFromFront();
    cout << testItem << endl;
    testObject.show();


}



