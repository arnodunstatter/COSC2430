#include <iostream>
#include "stack.cpp"
#include <string>
using namespace std;
int main() {
    
    stack<string> test2;
    string str2 = "world!\n";
    string str1 = "Hello ";
    test2.push(str2);
    test2.push(str1);
    while (!test2.isEmpty())
    {
        cout << test2.top();
        test2.pop();
    }
}