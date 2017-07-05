/*
 * main.cpp
 *
 *  Created on: Jun 28, 2017
 *      Author: anand
 */

#include<iostream>
#include<string>

using namespace std;

extern void basicLinkedListDemo();
extern void extraExamplesDemo();
extern void demoInsertionSort();
extern void demobubbleSort();
extern void demoselectionSort();
extern void demoquickSort();
extern void demoheapSort();
extern void demomergeSort();
extern void deleteatEndTestDemo();
extern void demoShellSort();

void linkedListDemo() {

	basicLinkedListDemo();
	extraExamplesDemo();
	deleteatEndTestDemo();
}


void runSortDemo() {
		demoInsertionSort();
		demobubbleSort();
		demoselectionSort();
		demoquickSort();
		demoheapSort();
		demomergeSort();
		demoShellSort();
}


int main(int argc, char* argv[]) {

	linkedListDemo();
	runSortDemo();
	return (0);

}
