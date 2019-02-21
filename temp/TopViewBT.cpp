#include<iostream>
#include<string>
#include<map>
#include<vector>

using namespace std;

struct BTNode
{
	int data;
	BTNode* leftChild;
	BTNode* rightChild;
	BTNode(const int& item)
	{
		data=item;
		leftChild=rightChild=nullptr;
	}
};

map<int, int> m_lmap;   // Level order information.
map<int, int> m_vmap;  // Vertical order traversal information.

int levelDepth=0;

void doLevelOrderTraversal(const BTNode* node, const int& levelInfo=0)
{
	if(node==nullptr)
		return;

	m_lmap[node->data]=levelInfo;
	if(levelInfo>levelDepth)
		levelDepth=levelInfo;

	doLevelOrderTraversal(node->leftChild,  levelInfo+1);
	doLevelOrderTraversal(node->rightChild, levelInfo+1);
}

void doVerticalOrderTraversal(const BTNode* node, const int& hdInfo=0)
{
	if(node==nullptr)
		return;

	m_vmap[node->data]=hdInfo;

	doVerticalOrderTraversal(node->leftChild, hdInfo-1);
	doVerticalOrderTraversal(node->rightChild, hdInfo+1); 
}

int main(int argc, char* argv[])
{
	BTNode* rootNode = new BTNode(3);
	rootNode->leftChild = new BTNode(2);
	rootNode->rightChild = new BTNode(5);
	rootNode->leftChild->leftChild = new BTNode(1);
	rootNode->rightChild->leftChild = new BTNode(4);
	rootNode->rightChild->rightChild = new BTNode(6);

	doLevelOrderTraversal(rootNode);

	for(const auto& iter : m_lmap)
		cout << iter.first << " , " << iter.second << endl;

	cout << "====" << endl;

	doVerticalOrderTraversal(rootNode);	
	for(const auto& iter : m_vmap)
		cout << iter.first  << " , " << iter.second << endl;

	cout << "======" << endl;

	vector<int> levelData;
	levelData.reserve(10);

	for(int i=0; i<levelDepth; ++i)
	{
		for(const auto& iter : m_lmap)
			if(iter.second == i)
				levelData.push_back(iter.first);
	}

	vector<int> verticalInfo;
	verticalInfo.reserve(10);

	map<int, int> topViewMap;

	for(int i=-2; i<3; ++i)
	{
		for(const auto& iter : m_vmap)
			if(iter.second == i)
			{
				auto iter2 = topViewMap.find(iter.second);
				if(iter2==topViewMap.end())
					topViewMap[iter.second]=iter.first;
				verticalInfo.push_back(iter.first);
			}
	}

	for(const auto& iter : topViewMap)
		cout << iter.second << " , ";
	cout << '\n';
	return(0);
}
