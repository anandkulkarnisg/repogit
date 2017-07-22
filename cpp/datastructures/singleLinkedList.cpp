#include<iostream>
#include<string>
#include<vector>
#include <singleLinkedList.h>

using namespace std;

void basicLinkedListDemo() {

	SingleLinkedList<int> testLinkedList;
	for (int i = 1; i <= 10; ++i)
		testLinkedList.insert(i);
	cout << "Before" << endl;
	testLinkedList.print();
	cout << "size = " << testLinkedList.size() << endl;

	// delete few items.
	testLinkedList.remove(7);
	cout << "After" << endl;
	testLinkedList.print();
	cout << "size = " << testLinkedList.size() << endl;

	testLinkedList.remove(110);
	cout << "After" << endl;
	testLinkedList.print();
	cout << "size = " << testLinkedList.size() << endl;

	testLinkedList.remove(static_cast<int>(NULL));
	cout << "After" << endl;
	testLinkedList.print();
	cout << "size = " << testLinkedList.size() << endl;

	testLinkedList.insert(10);
	cout << "After" << endl;
	testLinkedList.print();
	cout << "size = " << testLinkedList.size() << endl;

	testLinkedList.remove(1);
	cout << "After" << endl;
	testLinkedList.print();
	cout << "size = " << testLinkedList.size() << endl;

	testLinkedList.remove(10);
	cout << "After" << endl;
	testLinkedList.print();
	cout << "size = " << testLinkedList.size() << endl;

	testLinkedList.remove(10);
	cout << "After" << endl;
	testLinkedList.print();
	cout << "size = " << testLinkedList.size() << endl;

	testLinkedList.remove(9);
	testLinkedList.remove(8);
	testLinkedList.remove(6);
	testLinkedList.remove(5);
	testLinkedList.remove(4);
	testLinkedList.remove(3);
	testLinkedList.remove(2);
	cout << "After" << endl;
	testLinkedList.print();
	cout << "size = " << testLinkedList.size() << endl;

	testLinkedList.remove(10);
	testLinkedList.remove(10);
	testLinkedList.remove(10);

}

void extraExamplesDemo() {

	SingleLinkedList<int> testLinkedList;
	vector<int> items = { 1, 3, 7, 11, 27 };
	for (const auto& item : items)
		testLinkedList.insert(item);
	cout << "Before" << endl;
	testLinkedList.print();
	cout << "size = " << testLinkedList.size() << endl;

	// Now get the node of the item 7.
	int deleteVal = 7;
	SingleLinkedListNode<int>* nodeToDelete = testLinkedList.getNodeByVal(deleteVal);

	// Attempt to delete this node now.
	bool deleteStatus = testLinkedList.deleteNode(nodeToDelete, false);
	if (deleteStatus)
		cout << "Item = " << deleteVal << " Was successful" << endl;
	cout << "After" << endl;
	testLinkedList.print();
	cout << "size = " << testLinkedList.size() << endl;

	deleteVal = 99;
	nodeToDelete = testLinkedList.getNodeByVal(deleteVal);
	// Attempt to delete this node now.
	deleteStatus = testLinkedList.deleteNode(nodeToDelete, false);
	if (deleteStatus)
		cout << "Item = " << deleteVal << " Was successful" << endl;
	else
		cout << "Item = " << deleteVal << " Was Fail" << endl;
	cout << "After" << endl;
	testLinkedList.print();
	cout << "size = " << testLinkedList.size() << endl;

	vector<int> itemsToDelete = { 1, 3, 11, 27 };
	for (const auto& iter : itemsToDelete) {
		nodeToDelete = testLinkedList.getNodeByVal(iter);
		deleteStatus = testLinkedList.deleteNode(nodeToDelete, false);
		if (deleteStatus)
			cout << "Item = " << iter << " Was successful" << endl;
		else
			cout << "Item = " << iter << " Was Fail" << endl;
	}

	cout << "After" << endl;
	testLinkedList.print();
	cout << "size = " << testLinkedList.size() << endl;

	itemsToDelete = {27};
	for (const auto& iter : itemsToDelete) {
		nodeToDelete = testLinkedList.getNodeByVal(iter);
		deleteStatus = testLinkedList.deleteNode(nodeToDelete, true);
		if (deleteStatus)
			cout << "Item = " << iter << " Was successful" << endl;
		else
			cout << "Item = " << iter << " Was Fail" << endl;
	}

	cout << "After Special" << endl;
	testLinkedList.print();
	cout << "size = " << testLinkedList.size() << endl;
	testLinkedList.remove(27);
	cout << "After Final" << endl;
	testLinkedList.print();

	cout << "Attempting the swap now" << endl;
	SingleLinkedListNode<int>* node1 = testLinkedList.getNodeByVal(11);
	SingleLinkedListNode<int>* node2 = testLinkedList.getNodeByVal(1);
	testLinkedList.swapItems(node1, node2);
	cout << "After the swap" << endl;
	testLinkedList.print();

	node1 = testLinkedList.getNodeByVal(3);
	node2 = testLinkedList.getNodeByVal(99);
	testLinkedList.swapItems(node1, node2);
	cout << "After the swap" << endl;
	testLinkedList.print();

}

void deleteatEndTestDemo() {

	SingleLinkedList<int> testLinkedList;
	vector<int> items = { 1, 3, 7, 11, 27 };
	for (const auto& item : items)
		testLinkedList.insert(item);
	cout << "Before" << endl;
	testLinkedList.print();

	vector<int> itemsToDelete = { 27 };
	vector<bool> modesToTest = { false, true };
	for (const auto& modeIter : modesToTest) {
		for (const auto& iter : itemsToDelete) {
			SingleLinkedListNode<int>* nodeToDelete = testLinkedList.getNodeByVal(iter);
			bool deleteStatus = testLinkedList.deleteNode(nodeToDelete, modeIter);
			if (deleteStatus)
				cout << "Item = " << iter << " Was successful" << endl;
			else
				cout << "Item = " << iter << " Was Fail" << endl;
		}
		cout << "After forceMode = " << modeIter << endl;
		testLinkedList.print();
	}

	// Now test the edge case with just one item.
	itemsToDelete = { 1, 3, 7, 11 };
	 modesToTest = { false, true };
	for (const auto& modeIter : modesToTest) {
		for (const auto& iter : itemsToDelete) {
			SingleLinkedListNode<int>* nodeToDelete = testLinkedList.getNodeByVal(iter);
			bool deleteStatus = testLinkedList.deleteNode(nodeToDelete, modeIter);
			if (deleteStatus)
				cout << "Item = " << iter << " Was successful" << endl;
			else
				cout << "Item = " << iter << " Was Fail" << endl;
		}
		cout << "After forceMode = " << modeIter << endl;
		testLinkedList.print();
	}
}

