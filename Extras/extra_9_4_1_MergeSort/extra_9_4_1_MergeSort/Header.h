//old version
#include <iostream>
#include <vector>
using namespace std;

void mergeSort(vector <int>&, int, int);
void merge(vector <int>&, int, int);

int main()
{
    vector<int> mergeSortTest = { 5,9,1,2 };

    cout << "mergeSortTest was ";
    for (int i = 0; i < mergeSortTest.size(); ++i)
    {
        cout << mergeSortTest[i] << " ";
    }
    cout << endl;
    mergeSort(mergeSortTest, 0, mergeSortTest.size() - 1);
    cout << "*cast mergeSort*\n Now mergeSortTest is ";
    for (int i = 0; i < mergeSortTest.size(); ++i)
    {
        cout << mergeSortTest[i] << " ";
    }
    cout << endl;
    cout << endl;

    /*
    vector<int> mergeTest = {1,5,8,9,11,2,3,4,20};

    cout << "mergeTest was ";
    for (int i = 0; i < mergeTest.size(); ++i)
    {
        cout << mergeTest[i] << " ";
    }
    cout << endl;
    merge(mergeTest, 0, mergeTest.size() - 1);
    cout << "*cast merge*\n Now mergeTest is ";
    for (int i = 0; i < mergeTest.size(); ++i)
    {
        cout << mergeTest[i] << " ";
    }
    */
}

void mergeSort(vector <int>& v, int first, int last)
{
    if (last == first) return;


    //else keep splitting
    int leftLast = first + ((last - first) / 2);
    mergeSort(v, first, leftLast); //left 'half'
    mergeSort(v, leftLast + 1, last); //right 'half'


    merge(v, first, last);
}





void merge(vector <int>& v, int first, int last)
{

    //we will make a new vector, hold, and fill it in the correct order, then we will write over the area of the vector v passed in, with the correct order


    //now we fill hold in the right order
    int shift = ((last - first) / 2) + 1;
    vector<int> hold;
    if ((last - first + 1) % 2 == 0) //we have an even number of items in the total merge
    {
        for (int i = 0; i <= (last - first) / 2; ++i)
        {
            if (v[i] < v[i + shift]) //if it's smaller it goes in first
            {
                if (i > 0 && hold[hold.size() - 1] > v[i])
                {
                    int dummy = v[i];
                    swap(hold[hold.size() - 1], dummy);
                    hold.push_back(dummy);
                    hold.push_back(v[i + shift]);
                }
                else
                {
                    hold.push_back(v[i]);
                    hold.push_back(v[i + shift]);
                }
            }
            else //otherwise it goes in second
            {
                if (i > 0 && hold[hold.size() - 1] > v[i + shift])
                {
                    int dummy = v[i + shift];
                    swap(hold[hold.size() - 1], dummy);
                    hold.push_back(dummy);
                    hold.push_back(v[i]);
                }
                else
                {
                    hold.push_back(v[i + shift]);
                    hold.push_back(v[i]);
                }
            }
        }
    }
    else //we have an odd number of items to merge
    {
        for (int i = 0; i < (last - first) / 2; ++i)
        {
            if (v[i] < v[i + shift]) //if it's smaller it goes in first
            {
                if (i > 0 && hold[hold.size() - 1] > v[i])
                {
                    int dummy = v[i];
                    swap(hold[hold.size() - 1], dummy);
                    hold.push_back(dummy);
                    hold.push_back(v[i + shift]);
                }
                else
                {
                    hold.push_back(v[i]);
                    hold.push_back(v[i + shift]);
                }
            }
            else //otherwise it goes in second
            {
                if (i > 0 && hold[hold.size() - 1] > v[i + shift])
                {
                    int dummy = v[i + shift];
                    swap(hold[hold.size() - 1], dummy);
                    hold.push_back(dummy);
                    hold.push_back(v[i]);
                }
                else
                {
                    hold.push_back(v[i + shift]);
                    hold.push_back(v[i]);
                }
            }
        }
        int oddElem = v[first + (last - first) / 2]; //gets the last element in the first odd-numbered half
        if (hold[hold.size() - 1] <= oddElem) //oddElem is greater than or equal the last item in hold so we add it to the end
        {
            hold.push_back(oddElem);
        }
        else //oddElem is smaller than the last item in hold
        {
            int j = hold.size() - 1;
            while (oddElem < v[j]) //gets position we want to insert at
            {
                --j;
            }
            hold.insert(hold.begin() + j, oddElem);
        }
    }

    //now we write over the original passed in portion of the vector with our ordered hold
    for (int i = 0; i < hold.size(); ++i)
    {
        v[first + i] = hold[i];
    }
}
