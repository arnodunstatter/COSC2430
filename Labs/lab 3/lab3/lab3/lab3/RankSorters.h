#ifndef RANKSORTERS_H
#define RANKSORTERS_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
class RankSorters
{
private:
	vector<int> dataPoints;
	int numDPs;
	double tfDPload; //time to load dataPoints

	vector<int> dswBub; //data sorted with bubble sort
	double tfBub; //time for bubble sort

	vector<int> dswSel; //data sorted with selection sort
	double tfSel; //time for selection sort

	vector<int> dswIns; //data sorted with insertion sort
	double tfIns; //time for insertion sort

	vector<int> dswMer; //data sorted with merge sort
	double tfMer; //time for merge sort

	vector<int> dswQui; //data sorted with quick sort
	double tfQui; //time for quick sort

public:
	RankSorters(string, string);

	void push_back(int);
	void printVec(string);

	void checkVecIsSorted(vector<int>);
	void printTime(string);

	void bubbleSort();
	void selectionSort();
	void insertionSort();
	void mergeSort();
	vector<int> mergeSort(vector<int>&);
	vector<int> merge(vector<int>&, vector<int>&);

	void quickSort();
	template<typename T>
	vector<T> quickSort(vector<T>&, int, int);
	template<typename T>
	int partition(vector<T>&, int, int);

};
#endif
