/*
 * BinaryTree.cpp
 *
 *  Created on: Jul 21, 2017
 *      Author: anand
 */

#include<iostream>
#include<string>

using namespace std;

template<typename T> class BinaryTreeNode {

private:

	T* _data;
	BinaryTreeNode<T>* _leftChild;
	BinaryTreeNode<T>* _rightChild;

public:
	BinaryTreeNode();
	void createNode(T data);
};

