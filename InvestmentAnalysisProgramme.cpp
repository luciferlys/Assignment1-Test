// InvestmentAnalysisProgramme.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

bool isExist(string add) {
	ifstream file(add);
	if (file.is_open()) {
		return true;
	}
	return false;
}

int main()
{
	string path; //To save the name of the input file.
	string line;
	bool readFile = true; //To judge if the input file has been entirely read.
	bool process = false; //To judge if users enter the correct file name.
	vector<string> words; //To save all original data from input file.
	vector<string> investment; //To save all investment data.
	vector<double> contribution;
	int indexCount = 1; //To save the index of all cells in the input file.
	double allInvestment = 0;

	while (!process) {
		cout << "Please enter the path of the input file:" << endl;
		cin >> path;
		process = isExist(path);
		if (!process) {
			cout << "Invalid path. Please enter a valid path." << endl;
		}
	}

	ifstream file(path);

	while (readFile) {
		if (indexCount % 4) {
			if (getline(file, line, ',')) {
				readFile = true;
				words.push_back(line);
				indexCount++;
			}
			else {
				readFile = false;
			}
		}
		else {
			if (getline(file, line)) {
				readFile = true;
				words.push_back(line);
				investment.push_back(line);
				indexCount++;
			}
			else {
				readFile = false;
			}
		}
	}//All original data is read into words. All investment data is read into investment.

	for (int i = 1; i < investment.size(); i++) {
		allInvestment = allInvestment + stod(investment[i]);
	}

	if(!allInvestment)
	for (int i = 1; i < investment.size(); i++) {
		contribution.push_back(stod(investment[i]) / allInvestment);
	}

	for (int i = 0; i < contribution.size(); i++) {
		cout << contribution[i] << endl;
	}

	cout << fixed << setprecision(2) << allInvestment << endl;

	for (int i = 0; i < words.size(); i++) {
		cout << words[i] << endl;
	}

	for (int i = 1; i < investment.size(); i++) {
		cout << investment[i] << endl;
	}
	file.close();

	

	ofstream ofile("test.csv");
	ofile << "1" << "," << "2" << endl;
	ofile << "3" << "," << "4" << endl;
	ofile.close();


	//string address = "newFile.csv";

	//ifstream myfile(address);
	system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file