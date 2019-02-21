#include<iostream>
#include<string>
#include<climits>

using namespace std;

const int V=5;

int minKey(int key[V], bool mstSet[V])
{
	int min;
	int min_index;
	min=INT_MAX;
	for(int i=0; i<V; ++i)
	{
		if(key[i]<min && mstSet[i]==false)
		{
			min=key[i];
			min_index=i;
		}
	}
	return(min_index);
}

void printMST(int parent[V], int graph[V][V])
{
	for(int i=1; i<V; ++i)
		cout << parent[i] << "," << i << " , " << graph[i][parent[i]] << endl;
}

void primsMST(int graph[V][V])
{
	int parent[V];
	int key[V];
	bool mstSet[V];

	for(int i=0; i<V; ++i)
	{
		mstSet[i]=false;
		key[i]=INT_MAX;
	}

	parent[0]=-1;
	key[0]=0;

	for(int i=0; i<V; ++i)
	{
		int u=minKey(key, mstSet);
		mstSet[u]=true;

		for(int v=0; v<V; ++v)
		{
			if(graph[u][v]>0 && mstSet[v]==false && graph[u][v]<key[v])
			{
				key[v]=graph[u][v];
				parent[v]=u;
			}
		}
	}

	printMST(parent, graph);
}


int main(int argc, char* argv[])
{
	/* Let us create the following graph 
	   2 3 
	   (0)--(1)--(2) 
	   | / \ | 
	   6| 8/ \5 |7 
	   | /     \ | 
	   (3)-------(4) 
	   9         */

	int graph[V][V] =
	{
		{0, 2, 0, 6, 0},
		{2, 0, 3, 8, 5},
		{0, 3, 0, 0, 7},
		{6, 8, 0, 0, 9},
		{0,5, 7, 9, 0}
	};

	// Print the solution 
	primsMST(graph);
	return(0);
}

