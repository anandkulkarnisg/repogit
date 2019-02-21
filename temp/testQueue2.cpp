#include<iostream>
#include<string>
#include<vector>

using namespace std;

int* array = new int[10];
int frontIdx=-1;
int rearIdx=-1;
int CAPACITY=10;
int SIZE=0;

void enqueue(const int& item)
{
	if(CAPACITY==SIZE)
	{
		cout << "queue is full" << endl;
		return;
	}

	// Is this the first item in the queue.
	if(SIZE==0)
	{
		frontIdx=0;
		rearIdx=0;
		cout << "special inserting at position = " << frontIdx << endl;
		array[frontIdx]=item;
	}
	else
	{
		int insertIdx=(rearIdx+1)%CAPACITY;
		array[insertIdx]=item;
		cout << "inserting at position = " << insertIdx << endl;
		rearIdx=insertIdx;
	}
	++SIZE;		
}

int dequeue()
{
	int returnItem;
	if(SIZE==0)
	{
		cout << "Error : The queue is empty. Nothing to dequeue!" << endl;
		return(-1);
	}

	// Special case only 1 item present in the queue.
	if(SIZE==1 && frontIdx==rearIdx)
	{	
		returnItem=array[frontIdx];
		frontIdx=rearIdx=-1;
	}
	else
	{
		// Rest of all the cases simply return the item at frontIdx and increment it.
		returnItem=array[frontIdx];
		frontIdx=(frontIdx+1)%CAPACITY;
	}
	--SIZE;
	return(returnItem);
}

int remove(const int& item)
{
	if(SIZE==0)
		return(0);

	if(frontIdx<=rearIdx)
	{
		int j=frontIdx;
		int currentIdx=frontIdx;
		while(currentIdx<=rearIdx)
		{
			if(array[currentIdx]!=item)
			{
				++currentIdx;
				++j;
			}
			else
				++currentIdx;
			if(currentIdx!=j)
				array[j]=array[currentIdx];		
		}
	}
}

int main(int argc, char* argv[])
{
	vector<int> items = { 100, 200 , 300 , 400, 1, 2, 3, 4, 5, 4 };
	for(const int& iter : items)
		enqueue(iter);

	for(int i=0; i<4;++i)
		cout << dequeue() << endl;

	enqueue(8);
	enqueue(6);
	enqueue(7);
	enqueue(4);
	
	// remove a specific element from the queue [ could be multiple locations ].
	cout << frontIdx << rearIdx << endl; 

	return(0);

}

