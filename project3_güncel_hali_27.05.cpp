#define _CRT_SECURE_NO_WARNINGS 0
#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
using namespace std;
int a;
int* shuffleArray(int* arr);
void makeTubes(int a);
void deleteTubes();
void createTubes(int a);
void printTubes(int a);
void printCountAndPrompt();
void getMovement(int*, int*, int a);
int checkMoveIsValid(int, int, int);
int* createRandomArr(int);
void playMove(int, int, int);
bool checkFinish();
void saveToText();
int mainControl();
bool checkIsSaveExist();
int** tubes;

int countPlay = 0;

#include <fstream>
#include <string>
#include <iostream>

bool checkIsSaveExist() {

	ifstream infile("output.txt");
	std::string line;
	int lineCount = -1;
	bool exist = false;
	while (getline(infile, line))
	{
		exist = true;
		if (lineCount == -1) {
			a = stoi(line);
			makeTubes(a);
		}
		else {
			string _data = "";
			int _row = 0;
			for (int i = 0; i < line.size(); i++) {
				if (line.at(i) != '-') {
					_data += line.at(i);
					if (i == line.size() - 1) {
						tubes[_row][lineCount] = stoi(_data);
					}
				}
				else{
					tubes[_row][lineCount] = stoi(_data);
					_data = "";
					_row++;
				}
			}
		}
		lineCount += 1;

	}
	return exist;
}

void saveToText()
{
	ofstream out("output.txt");
	string text = "";
	for (int i = 0; i < a; i++) {
		text += to_string(tubes[0][i]) + "-" + to_string(tubes[1][i]) + "-" + to_string(tubes[2][i]) + "-" + to_string(tubes[3][i]) + "\n";
	}
	out << to_string(a) + "\n" + text;
	out.close();
}

int main() {
	
	mainControl();
}

int mainControl() {
	int countOfLiquid;
	int move1, move2;
	char again;
	if (!checkIsSaveExist()) {
		cout << "Yeni Oyun Başlıyor\n\n";
		cout << "Kac adet tup olusturmak istiyorsunuz: ";
		cin >> a;
		int en_az = 1;
		int en_fazla = a - 2;
		makeTubes(a);
		createTubes(a);
	}
	else {
		cout << "Kayıtlı Olan Oyun Yüklendi";

	}
	

	while (1) {
		printTubes(a);
		printCountAndPrompt();
		getMovement(&move1, &move2, a);
		countOfLiquid = checkMoveIsValid(move1, move2, a);
		while (!countOfLiquid) {

			printTubes(a);
			cout << "Please enter valid move!" << endl;
			printCountAndPrompt();
			getMovement(&move1, &move2, a);
			countOfLiquid = checkMoveIsValid(move1, move2, a);
		}

		playMove(move1, move2, countOfLiquid);

		if (checkFinish()) {
			printTubes(a);
			cout << "GAME FINISHED!" << endl;
			cout << "Your Score is : " << countPlay << endl;
			cout << "Do you want to play again?(y/n)" << endl;
			cin >> again;
			if (again == 'y') {
				system("cls");
				createTubes(a);
			}
			else {
				cout << "Win!" << endl;
				break;
			}
		}

	}
	deleteTubes();
	return 0;
}

void createTubes(int a) {
	countPlay = 0;
	srand(time(NULL));
	int en_az = 1;
	int en_fazla = a - 2;
	int i, j;
	int* randomList = shuffleArray(createRandomArr(a));
	int randomListCounter = 0;
	for (j = 0; j < a; j++) {
		if (j < a - 2) {
			for (i = 0; i < 4; i++) {

				tubes[i][j] = randomList[randomListCounter++];
			}
		}
		else {
			for (i = 0; i < 4; i++) {
				tubes[i][j] = 0;
			}
		}
	}
}

int* shuffleArray(int* arr) {
	int size = (a - 2) * 4;
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(arr, arr + size, g);

	return arr;
}

int* createRandomArr(int size) {
	int* result = new int[(size - 2) * 4];
	int value = 1;
	for (int i = 1; i <= ((size - 2) * 4); i++) {
		result[i - 1] = value;
		if (i % 4 == 0 && i != 0) {
			value++;
		}
	}
	return result;
}


void makeTubes(int a) {
	int i;
	tubes = new int* [a];
	for (i = 0; i < a; i++) {
		tubes[i] = new int[4];
	}


}

void deleteTubes() {
	delete tubes;
}

void printTubes(int a) {
	cout << endl;
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < a; j++) {
			cout << " | " << tubes[i][j] << " | ";
		}
		cout << endl;
	}cout << "---------------------------------------------------------------" << endl;

}



void printCountAndPrompt() {
	cout << "Play count : " << countPlay << endl;
	cout << "Enter a move :";
}

void getMovement(int* move1, int* move2, int a) {
	cin >> *move1 >> *move2;
	if (*move1 > a || *move1 < 1 || *move2> a || *move2 < 1 || *move1 == *move2) {
		system("cls");
		printTubes(a);
		cout << "Please enter valid move!" << endl;
		printCountAndPrompt();
		getMovement(move1, move2, a);
	}
}

int checkMoveIsValid(int move1, int move2, int a) {
	int countOfLiquid = 0;
	int topLiquid = 0;
	for (int i = 0; i <= 3; i++) {
		if (tubes[i][move1 - 1] != 0 && topLiquid == 0) {
			topLiquid = tubes[i][move1 - 1];
			countOfLiquid++;
		}
		else if (tubes[i][move1 - 1] == topLiquid && topLiquid != 0) {
			countOfLiquid++;
		}
		else if (tubes[i][move1 - 1] != topLiquid && topLiquid != 0) {
			break;
		}
	}
	cout << "Liq Count:" << countOfLiquid;
	for (int i = 0; i < countOfLiquid; i++) {
		if (tubes[i][move2 - 1] != 0) {
			return 0;
		}
	}
	return countOfLiquid;
}


void playMove(int move1, int move2, int countOfLiquid) {
	countPlay++;
	int tempCount = countOfLiquid;
	int* temp = new int [4] {-1, -1, -1, -1};
	int tempListCount = 0;
	for (int i = 0; i <= 3; i++) {
		if (tubes[i][move1 - 1] != 0 && tempCount > 0) {
			temp[tempListCount++] = tubes[i][move1 - 1];
			tubes[i][move1 - 1] = 0;
			tempCount--;
		}
	}
	tempListCount = 0;
	for (int i = 3; i >= 0; i--) {
		if (temp[tempListCount] != -1 && tubes[i][move2 - 1] == 0) {
			tubes[i][move2 - 1] = temp[tempListCount++];
		}
	}
	saveToText();
}

bool checkFinish() {
	int temp;
	for (int i = 0; i < a; i++) {
		temp = tubes[i][0];
		for (int j = 1; j < (a - 1); j++) {
			if (tubes[i][j] != temp) {
				return false;
			}
		}
	}
	return true;

}