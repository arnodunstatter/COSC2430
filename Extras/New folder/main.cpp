#include <iostream>
#include <queue>

using namespace std;

int main() {
  queue<int> q;
  int list[7] = {6, 2, 3, 5, 10, 7, 14};
  for (int i = 0; i < 7; ++i)
  q.push(list[i]);


  int temp;
  int counter = 1;
  while(q.front() >= 2)
  {
    cout << "Counter: " << counter << "\t | \t";
    temp = q.front(); q.pop(); //fetch and destroy front
    for(int i = 1; i < counter % 8; ++i)
    cout << "\t";
    cout << temp << " - 2 = "; //print front's value
    temp = temp - 2; //update value
    cout << temp << endl; //print it
    
    //if (temp >= 2)
      q.push(temp);

    counter++;
  }
  cout << endl << endl << counter;
}