#include <iostream>

using namespace std;

int GCD(int, int);

int main()
{
  int first, second;
  cout << "Let's find the GCD of two integers.\n";
  cout << "Please enter the first integer: ";
  cin >> first;
  cout << "Please enter the second integer: ";
  cin >> second;
  cout << "The GCD of " << first << " and " << second << " is " << GCD(first, second) << ".\n";
}

int GCD(int x, int y)
{
  if(y==0) return x;
  else return GCD(y, x%y);
}