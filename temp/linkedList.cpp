#include<iostream>
#include<string>
#include<vector>
#include<set>

using namespace std;

struct SingleLinkedList
{
	int _data;
	SingleLinkedList* next;
	SingleLinkedList(const int& input)
	{
		_data=input;
		next=nullptr;
	}
};

int main(int argc, char* argv[])
{
	vector<int> vec = { 2, 3, 4, 2, 3, 7, 3, 4, 2 };
	SingleLinkedList* head = new SingleLinkedList(vec[0]);
	size_t size = vec.size();
	SingleLinkedList* currNode = head;
	for(unsigned int i=1; i<size;++i)
	{
		currNode->next=new SingleLinkedList(vec[i]);
		currNode = currNode->next;	
	}
	currNode=head;
	set<int> uniqueItems;
	while(currNode != nullptr)
	{
		uniqueItems.insert(currNode->_data);
		currNode=currNode->next;
	}
	currNode=head;
	for(const auto& iter : uniqueItems)
	{
		currNode->_data=iter;
		currNode=currNode->next;
	}
	SingleLinkedList* lastNode=currNode;
	currNode=head;
	while(currNode != lastNode)
	{
		cout << currNode->_data << endl;
		currNode=currNode->next;
	}
	
	return(0);
}

