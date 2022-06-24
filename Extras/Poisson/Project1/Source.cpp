#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int numOfCustJustArrived(int avgNCpM, int timer, int customersAlreadyArrived);
int factorial(int);
int indexOfHighestProb(vector<double>);

int main()
{
    int avgNCpM = 2;
    int timer = 0;
    int numCustAlreadyArrived = 0;
    int maxRunTime = 60;

    //clock moving forward
    for (; timer < 60; ++timer)
    {
        cout << "At time " << timer << " we had " << numOfCustJustArrived(avgNCpM, timer, numCustAlreadyArrived) << " customers arrive.\n";

        numCustAlreadyArrived += numOfCustJustArrived(avgNCpM, timer, numCustAlreadyArrived);
    }
    cout << endl << endl << "Total number of customers that have arrived in the 60 minutes: " << numCustAlreadyArrived << endl;
    return 0;
}

int numOfCustJustArrived(int avgNCpM, int timer, int customersAlreadyArrived)
{
    vector<double> probs = { 0 };
    double probToLoad;
    for (int numCust = 0; numCust < 4 * pow(avgNCpM * timer, 0.5); ++numCust) //4 * pow(avgNCpM*timer, 0.5)
    {
        double lambdaRaisedToNumCust = pow(avgNCpM * timer, numCust);
        double eRaisedToNegativeLambda = exp(-1 * avgNCpM * timer);
        int denominator = factorial(numCust);
        probToLoad = lambdaRaisedToNumCust * eRaisedToNegativeLambda / denominator; //(pow(avgNCpM * timer, numCust) * exp(-1 * avgNCpM * timer)) / factorial(numCust)
        probs.push_back(probToLoad);
    }
    int numCustArrivedInGivenTime = indexOfHighestProb(probs);
    int numCustJustArrived = numCustArrivedInGivenTime - customersAlreadyArrived;
    if (numCustJustArrived >= 0) return numCustJustArrived;
    else return 0;
}


int factorial(int x)
{
    if (x == 1 || x == 0) return 1;

    return x * factorial(x - 1);
}

int indexOfHighestProb(vector<double> probs)
{
    double max = probs[0];
    int indexOfMax = 0;
    for (int i = 0; i < probs.size(); ++i)
    {
        if (max < probs[i])
        {
            max = probs[i];
            indexOfMax = i;
        }
    }
    return indexOfMax;
}