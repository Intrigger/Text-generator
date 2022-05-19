#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <limits>

int main() {

	using namespace std;

	srand(time(0));

	ifstream fin;

	fin.open("input.txt");

	vector<char> text;
	char character;

	const int ALPHABET_POWER = 26;

	double** table = new double* [ALPHABET_POWER];

	for (int i = 0; i < ALPHABET_POWER; i++) {
		table[i] = new double[ALPHABET_POWER];
		for (int j = 0; j < 26; j++) {
			table[i][j] = 0.0;
		}
	}



	while (fin.get(character)) {
		if (((character >= 'a') and (character <= 'z')) or ((character >= 'A') and (character <= 'Z')) or (character == ' ')) {
			text.push_back(tolower(character));
		}
	}

	vector<double> first_letters(26);

	for (int i = 0; i < 26; i++) {
		first_letters[i] = 0;
	}

	size_t text_size = text.size();

	size_t total = 0;

	for (int i = 0; i < text_size; i++) {
		if ((text[i] == ' ') and (i + 1 < text_size) and (isalpha(text[i + 1]))) {
			first_letters[text[i + 1] - 'a']++;
			total++;
		}
	}

	for (int i = 0; i < 26; i++) {
		first_letters[i] = first_letters[i] / (double)(total) * 100.0;
	}

	

	for (auto it = text.begin(); it != text.end();) {
		if ((*it) == ' ') {
			it = text.erase(it);
		}
		else {
			it++;
		}
	}

	text_size = text.size();


	char s1, s2;

	s1 = text[0];

	text_size = text.size();

	for (int i = 1; i < text_size; i++) {
		s2 = text[i];
		table[s1 - 'a'][s2 - 'a']++;
		s1 = s2;
	}

	for (int i = 0; i < 26; i++) {
		double sum = 0.0;
		for (int j = 0; j < 26; j++) {
			sum += table[i][j];
		}

		for (int j = 0; j < 26; j++) {
			table[i][j] = (table[i][j] / sum) * 100;
		}
	}
	

	int words_number = 100;

	cout << "Enter the number of words to generate: ";

	while (!(cin >> words_number)){
		cout << "Wrong input! Try again!\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}




	for (int word = 0; word < words_number; word++) {
		int word_length = rand() % 3 + 4;
		

		double r1 = ((rand() % 10000) / 10000.0) * 100;

		int index1 = 0;
		while (r1 > first_letters[index1]) {
			r1 -= first_letters[index1];
			index1++;
		}

		char last_symbol = index1;

		for (int i = 0; i < word_length; i++) {
			double r2 = ((rand() % 10000) / 10000.0) * 100;
			int index2 = 0;
			while (r2 > table[last_symbol][index2]) {
				r2 -= table[last_symbol][index2];
				index2++;
			}
			cout << char(last_symbol + 'a');
			last_symbol = index2;
		}
		cout << " ";
	}
	



	return 0;
}
