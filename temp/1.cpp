#include<iostream>
#include<vector>
#include<string>
#include<utility>

using namespace std;

class CustomStringClass
{

	private:
		std::string _internalString;
		char _seperator;
		long _counter;

	public:
		CustomStringClass(const char);
		void addItem(const std::string&);
		std::string subtractWordFromFront();
		std::string subtractWordFromEnd();
		void show();
		std::string get();
};

CustomStringClass::CustomStringClass(const char seperator)
{
	_internalString = "";
	_seperator=seperator;
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
	if(_counter > 0)
	{
		std::size_t indexPosition = _internalString.find(_seperator);
		if(indexPosition != std::string::npos)
		{
			std::string result = _internalString.substr(0, indexPosition);
			_counter--;
			if( _counter == 0)
				_internalString.clear();
			else
				_internalString = _internalString.substr(indexPosition+1, _internalString.length()-1);
			return(result);
		}			
		else
			return("");
	}
	return("");
}


std::string CustomStringClass::subtractWordFromEnd()
{

	if(_counter > 0)
	{
		std::string temp = _internalString.substr(0,_internalString.length()-1);
		std::size_t indexPosition = _internalString.find_last_of(_seperator);
		if(indexPosition != std::string::npos)
		{
			std::string result = _internalString.substr(indexPosition+1, _internalString.length()-1);
			_counter--;
			if(_counter == 0)
				_internalString.clear();
			else
				_internalString = _internalString.substr(0, indexPosition);
			return(result); 	
		}
		else
			return("");
	}
	return("");
}


class PartList
{
public:
    static std::vector<std::pair <std::string, std::string>> partlist(const std::vector<std::string> &arr);
};

std::vector<std::pair <std::string, std::string>> PartList::partlist(const std::vector<std::string>& arr)
{

	std::vector<std::pair<std::string, std::string>> results;	
	results.reserve(arr.size());	 
 
	// First prepare the full padded string using the CustomStringClass.
	CustomStringClass testObject(' ');
	for(auto iter : arr)
		testObject.addItem(iter);

	// Now we simply iterate for the whole list of vector and keep 
	std::size_t size=arr.size();
	std::string firstItem, secondItem;
	firstItem.clear();
	secondItem.clear();
	while(--size)
	{
		firstItem += testObject.subtractWordFromFront();
		firstItem += " ";
		secondItem = testObject.get();
		auto pair = make_pair(firstItem.substr(0, firstItem.length()-1), secondItem.substr(0, secondItem.length()-1));
		results.push_back(pair);
	}
	
	return(results);
}

int main(int argc, char* argv[])
{
	CustomStringClass testObject('|');
	vector<std::string> testItems = { "Anand" , "Apparao", "Kulkarni" , "Is" , "A" , "dumb" , "stupid" , "immature" , "person"};
	for(auto iter : testItems)
	{
		testObject.addItem(iter);
		testObject.show();
	}

	std::size_t size = testItems.size();
	cout << "size = " << size << endl;
	while(size > 0)
	{
		cout << "Item popped out is = " << testObject.subtractWordFromFront() << endl;
		testObject.show();	
		--size;
	}	

	vector<std::string> someMoreTestItems = { "AssHole", "Big Jugs", "Pig Headed Sucker" };
	for(auto iter : someMoreTestItems)
	{
		testObject.addItem(iter);
		testObject.show();
	}

	cout << "----------Actual test below -------------------" << endl;
	std::vector<std::pair<std::string, std::string>> results = PartList::partlist(testItems);
	for(auto iter : results)
		cout << "first item = " << iter.first << "., second item = " << iter.second << "." << endl;	 	

	return(0);

}
