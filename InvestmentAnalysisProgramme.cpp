// InvestmentAnalysisProgramme.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
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
	vector<double> profit;
	int indexCount = 1; //To save the index of all cells in the input file.
	double allInvestment = 0;

	while (!process) {
		cout << "Please enter the path of the input file:" << endl;
		cin >> path;
		process = isExist(path);
		if (!process) {
			cout << "Invalid path. Check and enter again!\n" << endl;
		}
	}

	auto start = chrono::steady_clock::now();//Start counter

	ifstream file(path);//Open input file

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

	file.close();//Close input file

	vector<string> rows;
	for (int i = 0; i < words.size(); i += 4) {
		rows.push_back(words[i] + "," + words[i + 1] + "," + words[i + 2] + "," + words[i + 3]);
	}//combine every row of original file

	for (int i = 1; i < investment.size(); i++) {
		allInvestment = allInvestment + stod(investment[i]);
	}//calculate the total investment

	if (!(allInvestment == 0)) {
		for (int i = 1; i < investment.size(); i++) {
			contribution.push_back(stod(investment[i]) / allInvestment);
		}
		for (int i = 0; i < contribution.size(); i++) {
			if (stod(investment[i + 1]) > 0) {
				profit.push_back(contribution[i] * 0.2 * allInvestment);
			}
			else {
				profit.push_back(0);
			}
		}
	}
	else {
		cout << "Sorry, the total investment in your input file is not positive. Please check and correct it then run this programme again." << endl;
		exit(0);
	}//Investment must be positive, or it will output error.

	ofstream ofile("test.csv");
	
	ofile << rows[0] << ",Contribution of the investor,expected profit" << endl;
	for (int i = 1; i < rows.size(); i++) {
		ofile << rows[i] << "," << fixed << setprecision(2) << contribution[i - 1] * 100 << "%," << profit[i - 1] << endl;
	}

	ofile.close();

	auto end = chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_time = end - start;
	cout << fixed << setprecision(8) << "The processing time is " << elapsed_time.count() << " seconds." << endl;

	system("pause");
}
