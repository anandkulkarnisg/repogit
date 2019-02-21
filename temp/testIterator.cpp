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

void showQueueItems()
{
	if(SIZE==0)
		return;

	if(rearIdx>=frontIdx)
	{
		for(int i=frontIdx; i<rearIdx; ++i)
			cout << array[i] << " , ";
		cout << array[rearIdx] << '\n';
	}
	else
	{
		for(int i=frontIdx; i<CAPACITY;++i)
			cout << array[i] << " , ";
		for(int i=0; i<rearIdx; ++i)
			cout << array[i] << ", ";
		cout << array[rearIdx] << '\n';
	}
}

bool removeAll(const int& item)
{
	// remove all instances of the item present in the queue. i.e the first occurance if any found. 
	// return true is modification was done else false.

	// case 1 : empty queue. do nothing.
	if(SIZE==0)
		return(false);

	// case 2 : one item and is same as the item to be removed. simply reset the queue and return true.
	if(SIZE==1&&array[frontIdx]==item)
	{
		frontIdx=rearIdx=-1;
		SIZE=0;
		return(true);
	}

	// case 3 : The queue has not wrapped around end , i.e rearIdx>=frontIdx.
	if(rearIdx>frontIdx)
	{
		int j=frontIdx;
		int skipCount=0;
		for(int i=frontIdx; i<=rearIdx; ++i)
		{
			if(array[i]!=item)
			{
				array[j]=array[i];
				++j;

			}
			else
				++skipCount;		
		}
		--j;
		rearIdx=j;
		SIZE-=skipCount;
		if(SIZE==0)
			frontIdx=rearIdx=-1;

		if(skipCount)
			return(true);		
	}

	// case 4 : The queue is wrapped around. This can be more tricky and complicated to implement.
	if(rearIdx<frontIdx)
	{
		cout << "I am running the special case" << endl;

		int j=frontIdx;
		int skipCount=0;

		// Front frontIdx to capacity-1.
		for(int i=frontIdx; i<CAPACITY;++i)
		{
			if(array[i]!=item)
			{
				array[j]=array[i];
				++j;
				j=j%CAPACITY;
			}
			else
				++skipCount;
		}

		// From index 0 to rearIdx.
		for(int i=0; i<=rearIdx; ++i)
		{
			if(array[i]!=item)
			{
				array[j]=array[i];
				++j;
				j=j%CAPACITY;
			}
			else
				++skipCount;
		}
		--j;
		if(j==-1)
			j=CAPACITY-1;
		rearIdx=j;
		SIZE-=skipCount;
		if(SIZE==0)
			frontIdx=rearIdx=-1;

		if(skipCount)
			return(true);
	}
	return(false);
}

template<typename T> class Iterator
{
	private:
		const T* m_data;
		int m_idx = -1;
		const size_t m_frontIdx;
		const size_t m_rearIdx;
		const size_t m_size;
		const size_t m_capacity;

	public:
		Iterator(const T* startIdx, const size_t& frontIdx, const size_t& rearIdx, const size_t& size, const size_t& capacity): 
								m_data(startIdx), m_frontIdx(frontIdx), m_rearIdx(rearIdx), m_size(size), m_capacity(capacity)
		{
			// Nothing else needs to be done here.
		}
		bool hasNext()
		{

			// case 1 : empty queue.
			if(m_size==0)
				return(false);
	
			// case 2 : rearIdx is greater than frontIdx [ not wrapped around yet ].
			if(m_rearIdx>=m_frontIdx)
			{
				if(m_idx==-1)
				{
					m_idx=m_frontIdx;
					return(true);
				}
				else
				{
					if(m_idx+1<=m_rearIdx)
					{
						++m_idx;
						return(true);
					}
					else
					{
						reset();
						return(false);
					}
				}	
			}
			// case 3 : rearIdx is less than frontIdx [ wrapped around queue ].
			if(m_rearIdx < m_frontIdx)
			{
				if(m_idx==-1)
				{
					m_idx=m_frontIdx;
					return(true);
				}
				else
				{		
					if(m_idx>=m_frontIdx)					
					{
						if(m_idx+1<m_capacity)
						{
							++m_idx;
							return(true);
						}	
						else
						{
							++m_idx;
							m_idx=m_idx%m_capacity;
							return(true);
						}
					}
					if(m_idx>=0 && m_idx<=m_rearIdx)
					{
						if(m_idx+1<=m_rearIdx)
						{
							++m_idx;
							return(true);
						}
						else
							reset();
							return(false);
					}
				}
			}		
		}
		
		T getNext()
		{
			return(m_data[m_idx]);
		}
	
		void reset()
		{
			m_idx=-1;
		}
};

int main(int argc, char* argv[])
{
	vector<int> items = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; 
	for(const int& iter : items)
		enqueue(iter);

	frontIdx=8;
	rearIdx=2;
	SIZE=10;

	Iterator<int> iterator(&array[0], frontIdx, rearIdx, 5, 10);

	while(iterator.hasNext())
		cout << iterator.getNext() << ",";
	cout << '\n';
	while(iterator.hasNext())
        cout << iterator.getNext() << ",";
    cout << '\n';


	delete[] array;
	return(0);
}

