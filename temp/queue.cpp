#include<iostream>
#include<string>

using namespace std;

template<typename T> class ArrayBlockingQueue 
{
private:
		T* m_data;			// Acts as a circular buffer internally.	
		int m_frontIdx;		// Index of the front of the queue.
		int m_rearIdx;		// Index of the rear of the queue.
		size_t size;		// The size of the queue at any given time.
		size_t capacity;	// Initial capacity allocated for the queue.


};




int main(int argc, char* argv[])
{
	int* ptr = new int[10];
	for(int i=0;i<10;++i)
		ptr[i]=3*i;
	for(int i=0;i<10;++i)
		cout << ptr[i] << endl;
}
