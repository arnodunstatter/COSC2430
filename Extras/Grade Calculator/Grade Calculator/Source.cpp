#include <iostream>
#include <string>
#include <vector>

bool containsChar(std::string);

int main()
{
	using namespace std;

	vector<double> homeworks, labs, groupAssignments;
	double Exam1 = 0, Exam2 = 0, finalExam = 0;
	cout << "This program is intended to give you a rough idea of what your grade in COSC2430 is currently.\n";
	cout << "\nThis will not account for dropped grades.\nIf you know a particular HW is going to be dropped, simply do not enter it when prompted for homework grade input.\n";
	cout << "\nThis program uses the grade distribution from the syllabus, namely that the overall contributions to the final grade is the following:\n";
	cout << "25% from Homework\n10% from Lab Work\n10% from Group Assignments\n15% from Exam 1\n15% from Exam 2\n25% from Final Exam\n";
	cout << "\nIt should also be noted that this program will fail to work if you made a 0 on any exams.\nIf you wish to utilize this program but made a 0 on any exam, then please enter something like 0.0001 for those grades.\n";


	//let's get the grades:
	cout << "\nTo begin you will enter each homework grade. When you are finished entering homework grades please simply enter the character 'd' for done:\n";
	string input;
	while (cin >> input)
	{
		if (input == "d") break;
		homeworks.push_back(stod(input));
	}
	cout << endl << endl;
	cout << "Now enter in each lab grade. When you are finished entering lab grades please simply enter the character 'd' for done:\n";
	while (cin >> input)
	{
		if (input == "d") break;
		labs.push_back(stod(input));
	}
	cout << endl << endl;
	cout << "Now enter in each group assignment grade. When you are finished entering group assignment grades please simply enter the character 'd' for done:\n";
	while (cin >> input)
	{
		if (input == "d") break;
		groupAssignments.push_back(stod(input));
	}

	cout << "\n\nFor the following three grades please enter 0 if you have not yet taken the exam. If you scored a 0 please enter something like 0.0001.\n";
	cout << "What did you score on exam 1? (Include the points earned from 'Lab Assignment 10/15') "; cin >> Exam1; Exam1 /= 100; //gets exam1 grade as a fraction of points earned out of possible points
	cout << "What did you score on exam 2? "; cin >> Exam2; Exam2 /= 100; //gets exam2 grade as a fraction of points earned out of possible points
	cout << "What did you score on the final? "; cin >> finalExam; finalExam /= 100; //gets finalExam grade as a fraction of points earned out of possible points

	double ptsFromHw = 0, ptsFromLabs = 0, ptsFromGA = 0;

	for (int i = 0; i < homeworks.size(); ++i)
		ptsFromHw += homeworks[i];
	if(homeworks.size() > 0)
		ptsFromHw /= 100 * static_cast<double>(homeworks.size()); //ptsFromHw is now the fraction of points earned out of those possible to earn

	for (int i = 0; i < labs.size(); ++i)
		ptsFromLabs += labs[i];
	if (labs.size() > 0)
		ptsFromLabs /= 100 * static_cast<double>(labs.size()); //ptsFromLabs is now the fraction of points earned out of those possible to earn

	for (int i = 0; i < groupAssignments.size(); ++i)
		ptsFromGA += groupAssignments[i];
	if (groupAssignments.size() > 0)
		ptsFromGA /= 100 * static_cast<double>(groupAssignments.size()); //ptsFromGA is now the fraction of points earned out of those possible to earn

	double grade = 25*ptsFromHw + 10*ptsFromLabs + 10*ptsFromGA; //points earned out of all possible homework points, lab points, and group assignment points

	if (Exam1 == 0) //if you haven't gotten a grade yet for Exam1 (this is probably not necessary, but i included it just for the sake of completeness) 
	{
		cout << "You've earned " << grade << " pts out of 45 possible points, so your current grade is roughly " << grade / 45 * 100 << "%.\n";
	}
	else if (Exam2 == 0) //if you haven't gotten a grade yet for Exam2
	{
		grade += 15*Exam1;
		cout << "You've earned " << grade << " pts out of 60 possible points, so your current grade is roughly " << grade / 60 * 100 << "%.\n";
	}
	else if (finalExam == 0) //if you haven't gotten a grade yet for the finalExam
	{
		grade += 15*Exam1 + 15*Exam2;
		cout << "You've earned " << grade << " pts out of 75 possible points, so your current grade is roughly " << grade / 75 * 100 << "%.\n";
	}
	else //calculating final total grade
	{
		grade += 15*Exam1 + 15*Exam2 + 25*finalExam;
		cout << "You've earned " << grade << " pts out of 100 possible points, so your current grade is roughly " << grade << "%.\n";
	}
}
