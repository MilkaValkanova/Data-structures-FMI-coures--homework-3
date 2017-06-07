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

#include"RadixTree.h"

Trie::Node::Node() : nodes { nullptr }, flag(false) {};

Trie::Node::Node(int v) : value(v), nodes{ nullptr }, flag(true) {};

void Trie::Node::setValue(int value)
{ 
	this->value = value; flag = true; 
}

Trie::Trie()
{
	root = new Node;
}

Trie:: ~Trie()
{
	cleanNode(root);
}

void Trie::cleanNode(Node* el)
{
	if (el != nullptr)
	{
		for (size_t i = 0; i <= MAXSIZE; i++)
			cleanNode(el->nodes[i]);
		delete el;
	}
}

size_t Trie:: getIDX(char c)
{
	if (c == ' ')
		return MAXSIZE;
	else return c - 'a';
}

void Trie::insert(std::string s, int v)
{
	_insert(root, s, v);
}

void Trie::_insert(Node* node, std::string str, int val)
{
	size_t i = 0;
	int idx = getIDX(str[0]);

	//if a word with this first letter doesn"t exist
	if (node->nodes[idx] == nullptr)
	{
		//insert new node
		Node* newNode = new Node(val);
		node->str[idx] = str;
		node->nodes[idx] = newNode;
		return;
	}
	while (str[i] != '\0' && node->str[idx][i] != '\0' && (str[i] == node->str[idx][i]))
	{
		++i;
	}
	//we have already inserted this word 
	if (str[i] == '\0' && node->str[idx][i] == '\0')
	{
		//update with the new value
		node->nodes[idx]->setValue(val);
	}
	//if the word we insert is a prefix to a existing word
	else if (str[i] == '\0')
	{
		//create new node with word (without the prefix)
		//newNOde->oldNode data 
		//oldNode  -> new node
		Node* newNode = new Node(val);
		std::string newStr(node->str[idx].begin() + i, node->str[idx].end());
		size_t nIdx = getIDX(newStr[0]);

		newNode->nodes[nIdx] = node->nodes[idx];
		newNode->str[nIdx] = newStr;

		node->nodes[idx] = newNode;
		node->str[idx] = str;
		return;
	}
	//there is a word in the dictionary , witch is a prefix to the new word for insert (abc and abcd)
	else if (node->str[idx][i] == '\0')
	{
		std::string newStr(str.begin() + i, str.end());
		_insert(node->nodes[idx], newStr, val);
		return;
	}

	//if the word we we insert and a word in the dictionary have common prefix
	else //if (i<str.size() && i<node->str[idx].size())
	{
		std::string prefix(str.begin(), str.begin() + i);
		std::string suffixStr(str.begin() + i, str.end());
		std::string suffixNode(node->str[idx].begin() + i, node->str[idx].end());

		size_t sIDX = getIDX(str[i]);
		size_t nIDX = getIDX(node->str[idx][i]);

		Node* node1 = new Node();
		node1->str[sIDX] = suffixStr;
		node1->str[nIDX] = suffixNode;

		Node* node2 = new Node(val);

		node1->nodes[sIDX] = node2;
		node1->nodes[nIDX] = node->nodes[idx];

		node->nodes[idx] = node1;
		node->str[idx] = prefix;
	}
}

void Trie::print()const
{
	std::string start;
	_print(root,start);
}

void Trie::_print(Node* node,std::string prefix)const
{
	if (node->flag)
	{
		std::cout << prefix.c_str() << " " << node->value << std::endl;
	}
	for (size_t i = 0; i <= MAXSIZE; i++)
	{
		if (node->nodes[i] != nullptr)
		{
			_print(node->nodes[i], prefix + node->str[i]);
		}
	}
}

//cant give node == nullptur argument to this funktion
void Trie::moveFromPos( Node*& node, const std::string word, size_t& nodePos, size_t& edgePos)const//node vkoi vuzel nodePos - kude vuv vuzela edgePos - kude v rebroto
{
	if (nodePos == INVALID)
	{
		size_t idx = getIDX(word[0]);
		//no such word
		if (node->nodes[idx] == nullptr)
		{
			node = nullptr;
			return;
		}
		else // if (nodePos < 27)
		{
			nodePos = idx;
			edgePos = 1;
			std::string newWord(word.begin() + 1, word.end());
			moveFromPos(node, newWord, nodePos, edgePos);
			
		}
	}
	else
	{
		size_t i = 0;
		while (word[i] != '\0' && node->str[nodePos][edgePos] != '\0' && (word[i] == node->str[nodePos][edgePos]))
		{
			++i;
			++edgePos;
		}
		// found a difference => no such word
		if (word[i] != '\0' && node->str[nodePos][edgePos] != '\0')
		{
			node = nullptr;
			return;
		}
		// we"ve read the word
		else if (word[i] == '\0' && node->str[nodePos][edgePos] != '\0')
		{
			return;
		}
		//we've read the edge
		else// if (node->str[idx][edgePos] == '\0')
		{
			node = node->nodes[nodePos];
			nodePos = INVALID;
			std::string newWord(word.begin() + i, word.end());
			if (word[i] != '\0')
			{
				moveFromPos(node, newWord, nodePos, edgePos);//ето тук
			}
			else return;
		}
	}
}



