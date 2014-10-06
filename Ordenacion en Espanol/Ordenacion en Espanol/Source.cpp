// Ordenacion en Espanol
// Austin Andrews
// Visual Studio 2013
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const string INPUT = "espanol.in";
const string OUTPUT = "espanol.out";
const string esp[30] = {
	"a", "b", "c", "ch", "d",
	"e", "f", "g", "h", "i",
	"j", "k", "l", "ll", "m",
	"n", "~n", "o", "p", "q",
	"r", "rr", "s", "t", "u",
	"v", "w", "x", "y", "z"
};
const string eng[30] = {
	"a", "b", "c", "d", "e",
	"f", "g", "h", "i", "j",
	"k", "l", "m", "n", "o",
	"p", "q", "r", "s", "t",
	"u", "v", "w", "x", "y",
	"z", "z{", "z|", "z}", "z~"
};

struct Node
{
	string Value;
	int identifier;
};

typedef Node SpanishWord;

// www.algolist.net/Algorighms/Sorting/Quicksort
void quicksort(vector<SpanishWord>& StringVector, int left, int right)
{
	int i = left, j = right;
	string tmp;
	string pivot = StringVector.at((left + right) / 2).Value;

	// partition
	while (i <= j)
	{
		while (StringVector.at(i).Value < pivot)
			i++;
		while (StringVector.at(j).Value > pivot)
			j--;
		if (i <= j)
		{
			tmp = StringVector.at(i).Value;
			StringVector.at(i).Value = StringVector.at(j).Value;
			StringVector.at(j).Value = tmp;
			i++;
			j--;
		}
	}

	// recursion
	if (left < j)
		quicksort(StringVector, left, j);
	if (i < right)
		quicksort(StringVector, i, right);
}

void TranslateToEnglish(vector<SpanishWord>& StringVector)
{
	// for each word in vector
	for (unsigned int i = 0; i < StringVector.size(); i++)
	{
		string spanishWord = StringVector.at(i).Value;
		string newWord;
		// for each letter in word
		for (unsigned int j = 0; j < spanishWord.length(); j++)
		{
			string letter = spanishWord.substr(j, 1);
			// check 4 special cases "aa", "bb", "cc", "dd"
			bool isSpecialCase = false;
			if (letter == "c")
			{
				if (spanishWord.substr(j, 2) == "ch")
				{
					letter = "ch";
					isSpecialCase = true;
				}
			}
			else if (letter == "~")
			{
				letter = "~n";
				isSpecialCase = true;
			}
			else if (letter == "l")
			{
				if (spanishWord.substr(j, 2) == "ll")
				{
					letter = "ll";
					isSpecialCase = true;
				}
			}
			else if (letter == "r")
			{
				if (spanishWord.substr(j, 2) == "rr")
				{
					letter = "rr";
					isSpecialCase = true;
				}
			}

			// for each letter in esp[] and eng[] arrays
			for (int k = 0; k < 30; k++)
			{
				if (letter == esp[k])
				{
					letter = eng[k];
					break;
				}
			}
			if (isSpecialCase)
			{
				j++;
				isSpecialCase = false;
			}
			newWord.append(letter);
		}
		StringVector.at(i).Value = newWord;
	}
}

void TranslateToSpanish(vector<SpanishWord>& StringVector)
{
	// for each word in vector
	for (unsigned int i = 0; i < StringVector.size(); i++)
	{
		string englishWord = StringVector.at(i).Value;
		string newWord;
		// for each letter in word
		for (unsigned int j = 0; j < englishWord.length(); j++)
		{
			string letter = englishWord.substr(j, 1);
			// check 4 special cases "ch", "ll", "~n", "rr"
			bool isSpecialCase = false;
			if (letter == "z")
			{
				if (englishWord.substr(j, 2) == "z{")
				{
					letter = "z{";
					isSpecialCase = true;
				}
				else if (englishWord.substr(j, 2) == "z|")
				{
					letter = "z|";
					isSpecialCase = true;
				}
				else if (englishWord.substr(j, 2) == "z}")
				{
					letter = "z}";
					isSpecialCase = true;
				}
				else if (englishWord.substr(j, 2) == "z~")
				{
					letter = "z~";
					isSpecialCase = true;
				}
			}

			// for each letter in esp[] and eng[] arrays
			for (int k = 0; k < 30; k++)
			{
				if (letter == eng[k])
				{
					letter = esp[k];
					break;
				}
			}
			if (isSpecialCase)
			{
				j++;
				isSpecialCase = false;
			}
			newWord.append(letter);
		}
		StringVector.at(i).Value = newWord;
	}
}

void main()
{
	ifstream fin(INPUT);
	if (fin)
	{
		ofstream fout(OUTPUT);		
		string readline;
		int numberOfWords;
		vector<SpanishWord> StringVector;

		fin >> numberOfWords;
		for (int i = 0; i <= numberOfWords; i++)
		{
			getline(fin, readline);
			if (readline != "")
			{
				SpanishWord NewWord;
				NewWord.identifier = i;
				NewWord.Value = readline;

				StringVector.push_back(NewWord);
			}
		}

		TranslateToEnglish(StringVector);
		quicksort(StringVector, 0, StringVector.size() - 1);
		TranslateToSpanish(StringVector);
		for (unsigned int i = 0; i < StringVector.size(); i++)
		{
			fout << StringVector.at(i).Value << endl;
			cout << StringVector.at(i).Value << endl;
		}

		fout.close();
		fin.close();
	}
	else
	{
		cout << "Input file not found." << endl;
	}
}