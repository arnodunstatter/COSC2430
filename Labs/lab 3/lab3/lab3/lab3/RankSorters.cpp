#include "RankSorters.h"

RankSorters::RankSorters(string inputFile, string outputFile)
{
	ifstream read(inputFile.c_str());

	if (!read.is_open())
	{
		cout << "InputFile didn't open properly.\n";
		return;
	}
	//else...
	
	int loader;
	read >> loader; //gets the size of our vector
	numDPs = loader; //how long our vector should be

	auto start = chrono::high_resolution_clock::now();
	while (read >> loader)
	{
		push_back(loader);
	}
	read.close();
	ofstream write(outputFile.c_str());
	if (!write.is_open())
	{
		cout << "Output file did not open properly.\n";
		return;
	}
	//else...
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	tfDPload = duration.count();

	
	bubbleSort();
	//cout << "For bubble sorter: ";
	//checkVecIsSorted(dswBub);
	//printTime("bubble");
	//cout << endl;

	selectionSort();
	//cout << "For selection sorter: ";
	//checkVecIsSorted(dswSel);
	//printTime("selection");
	//cout << endl;
	
	insertionSort();
	//cout << "For insertion sorter: ";
	//checkVecIsSorted(dswIns);
	//printTime("insertion");
	//cout << endl;

	mergeSort();
	//cout << "For merge sorter: ";
	//checkVecIsSorted(dswMer);
	//printTime("merge");
	//cout << endl;
	
	quickSort();
	//cout << "For quick sorter: ";
	//checkVecIsSorted(dswQui);
	//printTime("quick");
	//cout << endl;
	
	
	vector<double> times = { tfQui, tfMer, tfIns, tfSel, tfBub };
	times = quickSort(times, 0, times.size() - 1);
	for (int i = 0; i < times.size(); ++i)
	{
		if (times[i] == tfQui)
			write << "Quick Sort";
		else if (times[i] == tfMer)
			write << "Merge Sort";
		else if (times[i] == tfIns)
			write << "Insertion Sort";
		else if (times[i] == tfSel)
			write << "Selection Sort";
		else if (times[i] == tfBub)
			write << "Bubble Sort";
		if (i < times.size() - 1)
			write << ", ";
	}
	write.close();
}

void RankSorters::push_back(int addMe)
{
	dataPoints.push_back(addMe);
}

void RankSorters::printVec(string name)
{
	if (name == "original")
	{
		for (int i = 0; i < dataPoints.size(); ++i) 
		{
			cout << dataPoints[i] << " ";

			if ((i+1) % 16 == 0) cout << endl;
		}
		cout << endl;
	}
	else if (name == "bubble")
	{
		for (int i = 0; i < dswBub.size(); ++i)
		{
			cout << dswBub[i] << " ";

			if ((i+1) % 16 == 0) cout << endl;
		}
		cout << endl;
	}
	else if (name == "selection")
	{
		for (int i = 0; i < dswSel.size(); ++i)
		{
			cout << dswSel[i] << " ";

			if ((i + 1) % 16 == 0) cout << endl;
		}
		cout << endl;
	}
	else if (name == "insertion")
	{
		for (int i = 0; i < dswIns.size(); ++i)
		{
			cout << dswIns[i] << " ";

			if ((i + 1) % 16 == 0) cout << endl;
		}
		cout << endl;
	}
	else if (name == "merge")
	{
		for (int i = 0; i < dswMer.size(); ++i)
		{
			cout << dswMer[i] << " ";

			if ((i + 1) % 16 == 0) cout << endl;
		}
		cout << endl;
	}
	else if (name == "quick")
	{
		for (int i = 0; i < dswQui.size(); ++i)
		{
			cout << dswQui[i] << " ";

			if ((i + 1) % 16 == 0) cout << endl;
		}
		cout << endl;
	}
	else
	{
		cout << "Error: invalid print name was passed.\n";
		cout << "Valid names are as follows: \"original\", \"bubble\", \"selection\", \"insertion\", \"merge\", or \"quick\".\n";
		cout << "Please re-run the program and check the argument passed to the print statements.\n";
	}
}

void RankSorters::checkVecIsSorted(vector<int> v)
{
	bool sorted = true;
	for (int i = 0; i < v.size() - 1; ++i)
	{
		if (v[i] > v[i + 1]) 
			sorted = false;
	}
	
	if (sorted)
	{
		cout << "Yes, this vector is sorted properly and it took ";
	}
	else
	{
		cout << "No, that vector is not sorted properly.\n";
	}
}

void RankSorters::printTime(string v)
{
	if (v == "bubble")
	{
		cout << tfBub << "s to sort.\n";
	}
	else if (v == "selection")
	{
		cout << tfSel << "s to sort.\n";
	}
	else if (v == "insertion")
	{
		cout << tfIns << "s to sort.\n";
	}
	else if (v == "merge")
	{
		cout << tfMer << "s to sort.\n";
	}
	else if (v == "quick")
	{
		cout << tfQui << "s to sort.\n";
	}
	else
	{
		cout << "Error: invalid print name was passed.\n";
	}
}

void RankSorters::bubbleSort()
{
	dswBub = dataPoints;
	int length = dswBub.size();

	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < length; ++i)
	{
		for (int j = i + 1; j < length; ++j)
		{
			if (dswBub[i] > dswBub[j])
			{
				swap(dswBub[i], dswBub[j]);
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> duration = end - start;
	tfBub = duration.count();
}

void RankSorters::selectionSort()
{
	dswSel = dataPoints;
	int length = dswSel.size();
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < length; ++i)
	{
		int min_index = i; //where we start looking for our min_index
		for (int j = i + 1; j < length; ++j)
		{
			if (dswSel[min_index] > dswSel[j])
				min_index = j;
		}
		swap(dswSel[i], dswSel[min_index]);
	}
	auto end = chrono::high_resolution_clock::now();
	
	chrono::duration<double> duration = end - start;
	tfSel = duration.count();
}

void RankSorters::insertionSort()
{
	dswIns = dataPoints;
	int length = dswIns.size();

	auto start = chrono::high_resolution_clock::now();
	for (int i = 1; i < length; ++i)
	{
		int x = dswIns[i];
		dswIns.erase(dswIns.begin() + i);

		for (int j = i - 1; j >= 0; --j)
		{
			if (dswIns[j] < x)
			{
				dswIns.insert(dswIns.begin() + j + 1, x);
				break;
			}
			else if (j == 0)
			{
				dswIns.insert(dswIns.begin(), x);
				break;
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> duration = end - start;
	tfIns = duration.count();
}

void RankSorters::mergeSort()
{
	dswMer = dataPoints;
	int length = dswMer.size();
	auto start = chrono::high_resolution_clock::now();
	dswMer = mergeSort(dswMer);
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> duration = end - start;
	tfMer = duration.count();
}

vector<int> RankSorters::mergeSort(vector<int>& v)
{
	if (v.size() == 1) return v;


	//else keep splitting
	//let's make our halves...
	vector<int> left, right;
	{
		//first half...
		for (int i = 0; i < v.size() / 2; ++i)
			left.push_back(v[i]);
		//second half...
		for (int i = v.size() / 2; i < v.size(); ++i)
			right.push_back(v[i]);
	}
	mergeSort(left);
	mergeSort(right);

	v = merge(left, right);
	return v;
}

vector<int> RankSorters::merge(vector<int>& left, vector<int>& right)
{
	vector<int> toReturn;
	while (left.size() > 0 && right.size() > 0) //while both are not empty
	{
		if (left[0] < right[0])
		{
			toReturn.push_back(left[0]);
			left.erase(left.begin()); //removes from left
		}
		else //right[0] must be smaller
		{
			toReturn.push_back(right[0]);
			right.erase(right.begin()); //removes from right
		}
	}
	//one list must have been emptied, we use while loops to check
	while (left.size() > 0)
	{
		toReturn.push_back(left[0]);
		left.erase(left.begin());
	}
	while (right.size() > 0)
	{
		toReturn.push_back(right[0]);
		right.erase(right.begin());
	}

	return toReturn;
}

void RankSorters::quickSort()
{
	dswQui = dataPoints;
	int lastIndex = dswQui.size() - 1;
	auto start = chrono::high_resolution_clock::now();
	dswQui = quickSort(dswQui, 0, lastIndex);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	tfQui = duration.count();
}

template<typename T>
vector<T> RankSorters::quickSort(vector<T>& v, int low, int high)
{
	if (low < high)
	{
		int pivotIndex = partition(v, low, high);
		quickSort(v, low, pivotIndex);
		quickSort(v, pivotIndex + 1, high);
	}
	return v;
}

template<typename T>
int RankSorters::partition(vector<T>& v, int low, int high)
{
	T pivot = v[low];
	int leftwall = low;

	for (int i = low + 1; i <= high; ++i)
	{
		if (v[i] < pivot)
		{
			swap(v[i], v[leftwall]);
			leftwall += 1;
		}
	}

	swap(pivot, v[leftwall]);
	return leftwall;
}