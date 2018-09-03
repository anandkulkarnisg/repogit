/*
 * printer.cpp
 *
 *  Created on: Jun 28, 2017
 *      Author: anand
 */

#include<iostream>
using namespace std;

void printArr(int arr[], int size) {
	for (int i = 0; i <= (size - 2); ++i)
		cout << arr[i] << " , ";
	cout << arr[size - 1] << endl;
}

void swapItems(int* item1, int*  item2)
{
	int temp=*item1;
	*item1=*item2;
	*item2=temp;
}





