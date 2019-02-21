#include<iostream>
#include<string>

enum class Color { black , red};

struct RBTreeNode
{
	T m_data;
	RBTreeNode* m_leftChild;
	RBTreeNode* m_rightChild;
	Color	m_color;
};	
