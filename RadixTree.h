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

#pragma once
#include <iostream>
#include <fstream>

class Trie
{
	friend class Dictionary;

	private:
		struct Node
		{
			int value;
			bool flag;
			Node* nodes[27];
			std::string str[27];

			Node();
			Node(int);
			void setValue(int);
		};
		Node* root;

	public:
		Trie();
		~Trie();
		Trie(const Trie&) = delete;
		Trie& operator=(const Trie&) = delete;
		void insert(std::string, int);
		void print()const;

	private:
		static	size_t getIDX(char);
		void cleanNode(Node*);
		void _insert(Node*, std::string, int);
		void _print(Node*, std::string)const;
		void moveFromPos(Node*&, const std::string, size_t&, size_t&)const;
		static const size_t MAXSIZE = 26;
		static const size_t INVALID = 27;
};

