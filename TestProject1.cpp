/*This programme allows the user to enter a sequence of integers with unknown length terminated by 0 */
#include<iostream>
#include <fstream>
#include<string>
#include<vector>

using namespace std;

void main() {
	vector<string> words;
	string line;
	bool a = true;
	int count = 1;
	ifstream myfile ("W2_ExerciseData.csv");
	
	while (a) {
		if (count % 2) {
			if (getline(myfile, line, ',')) {
				a = true;
				words.push_back(line);
				count++;
			}
			else {
				a = false;
			}
		}
		else {
			if (getline(myfile, line)) {
				a = true;
				words.push_back(line);
				count++;
			}
			else {
				a = false;
			}
		}
	}

	for (int i = 0; i < words.size(); i++) {
		cout << words[i] << "AAAAAAAA";
	}
	myfile.close();

	system("pause");


};