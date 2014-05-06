#include "lexical.h"
#include <cstdlib>
using namespace std;

lexical::lexical()
{
	wordCheck = " "; //i don't know if we need this

	DictionaryFile.open("dictionary.txt", fstream::in | fstream::out | fstream::app);

	if(DictionaryFile.is_open() == false)
    {
        throw "Failed to open dictionary.txt!";
    }

	ReservedWordFile.open("reserved.txt", fstream::in | fstream::out | fstream::app);

	if(ReservedWordFile.is_open() == false)
    {
        throw "Failed to open reserved.txt!";
    }
}

lexical::~lexical()
{
	wordCheck = " "; //i don't know if we need this

	ReservedWordFile.close();
	DictionaryFile.close();
}

/* the checkReserve opens the reservedWord.txt and
 *
 * checks to see if the word being passed into the
 *
 * function is already part of the reserved words.
 *
 * if it is then it classifies it as some token type.
 *
 * but if it is not part of the reserved words, then it
 *
 * it is passed into addLexical function were it is added into
 *
 * the dictionary
 * */

void lexical::checkReserve(const string &word)
{
	int wordLength = word.size()-1;

	string reserve = " ";

	string others = " ";

	string token_string;

	WordType token_type;

	if(ReservedWordFile.is_open())
	{
		while(!ReservedWordFile.eof())
		{

			ReservedWordFile >> reserve;

			ReservedWordFile >> token_string;

			if(token_string.at(0) == '(')
			{
				others = token_string;

				ReservedWordFile >> token_string;
			}

			//add in error handling later
			token_type = (WordType)atoi(token_string.c_str());

			/*once the token has hit the eofm im not sure if
			 * i should append the eofm into the output file
			 * */
			if(token_type == EOFM)
			{
				cout << "------------------->> " << "end of file marker" << endl;

				switch(word.at(wordLength))
				{
					case 'a':
					case 'u':
					case 'o':
					case 'n':
						OutputWord(word, WORD1);
						AddWordToDictionary(word, " ");
						break;

					case 'i':
					case 'e':
						OutputWord(word, WORD2);
						AddWordToDictionary(word, " ");
						break;

					case '.':
						OutputWord(word, PERIOD);
						break;

					default:
						break;

				}

				break;

			}
			else
			{
				if(word == reserve)
				{

					if(token_type == PRONOUN || token_type == CONNECTOR)
					{
						OutputWord(reserve, token_type);
						AddWordToDictionary(reserve, others);
						break;
					}

					OutputWord(reserve, token_type);
					break;
				}
			}

		}


	}
	else
	{
		cout << "needs to be reserved.txt" << endl;
	}

}

/* if the word is not part of the reserved word it is passed
 *
 * over to the addLexical to be added into the dictionary


void lexical::addLexical(const string &word, const string &token)
{
	ofstream openFile;

	openFile.open("output.txt", ios::app);

	cout << "writing output...\n\n";

	openFile << word << setw(20) << token << "\t" << "\n\n";

	openFile.close();
}
* */

void lexical::OutputWord(const string &word, WordType token)
{
	ofstream openFile;

	openFile.open("output.txt", ios::app);

	cout << "writing output...\n\n";

	openFile << word << setw(20) << token << "\t" << "\n\n";

	openFile.close();
}
//////////////////////////////////////////

void lexical::AddWordToDictionary(const string &word, const string &others)
{

	string eng = " ";

	unsigned int i = 0;

	//ofstream DictionaryFile;

	//DictionaryFile.open("dictionary.txt", ios::app);

	while(i<others.size())
	{
		if(others.at(i) >= 'a' && others.at(i) <= 'z')
		{
			eng += others.at(i);
			i++;
		}
		else
		{
			if(others.at(i) == '/')
			{
				eng += ", ";
				i++;
			}
			else
			{
				i++;
			}
		}
	}



	if(!CheckWordAgainstDictionary(word))
	{
		DictionaryFile << word << setw(20) << eng << endl;

	}
	else
	{
		cout << "word is already in the dictionary" << endl;

	}

	DictionaryFile.close();
}

bool lexical::CheckWordAgainstDictionary(const string &word)
{

	string checkFileInput = " ";

    DictionaryFile.seekg(0);

	while(!DictionaryFile.eof())
	{
		DictionaryFile >> checkFileInput;

		if(checkFileInput == word)
		{
			return (true);
		}
	}


	return (false);
}
