/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Milka Valkanova
* @idnumber 45155
* @task 1
* @compiler VC
*
*/

#include "Dictionary.h"

//help funktions
const size_t wordsCount(const char*);
bool isLetter(char c);
void convertor(std::ifstream&, std::string&);

Dictionary::Dictionary(const char* filename)
{
	char buff[1000];
	int value;
	std::string	phrase;
	std::ifstream file(filename);
	while (file)
	{
		std::string	phrase;
		while ((file.peek() <= 'z' && file.peek() >= 'a') || file.peek() == ' ')
		{
			file >> buff;
			file.ignore();
			phrase += buff;
			phrase += " ";
		}
		file >> value;
		file.ignore();
		dictionary.insert(phrase, value);
	}
}

void Dictionary::search(const char* filename)const
{
	int score = 0;

	std::ifstream file(filename);
	std::string buff;
	std::string word;

	size_t nextSearchPos = 0;
	int tempScore = 0;

	while (file)
	{
		//reset posotion & score
		Trie::Node* node = dictionary.root;
		size_t edgePos = 0, nodePos = Trie::INVALID;
		tempScore = 0;

		//move search position in file
		file.seekg(nextSearchPos, std::ios::beg);
	
		//read one word & update position for next read
		convertor(file, buff);
		word = buff;
		nextSearchPos += word.size();
		dictionary.moveFromPos(node, word, nodePos, edgePos);

		//find valid word with value
		if (node != nullptr && nodePos == Trie::INVALID && node->flag == true)
		{
			tempScore = node->value;
		}
		//there is a way in the trie => longer phrase may be found
		while (node != nullptr)
		{
			if (file.eof())
			{
				node = nullptr;
				break;
			}
			//read word
			convertor(file, buff);
			word = buff;
			dictionary.moveFromPos(node, word, nodePos, edgePos);

			if (node != nullptr&&nodePos == Trie::INVALID && node->flag == true)//ima value
			{
				//longer phrase found
				nextSearchPos += word.size();

				//update value
				tempScore = node->value;
			}
		}
		score += tempScore;
	}
	int cnt = wordsCount(filename);
	if(cnt)
	{
	 score /= cnt;
	}
	std::cout << filename << " " << score << "\n";
}


//help funktions
const size_t wordsCount(const char* filename)
{
	int br = 0;
	std::ifstream file(filename);
	while (file)
	{
		char buff[1000];
		file >> buff;
		file.ignore();
		br++;
	}
	return br;
}

bool isLetter(char c)
{
	if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z'))return true;
	return false;
}

void convertor(std::ifstream& ifs, std::string& buff)
{
	buff.clear();
	while (true)
	{
		char c;
		ifs.get(c);
		if (!isLetter(c))
		{
			buff += " ";
			break;
		}
		if (c >= 'A'&&c <= 'Z')
		{
			c = c - 'A' + 'a';
		}
		buff += c;
	}
}