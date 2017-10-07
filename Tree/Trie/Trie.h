#pragma once
#include<string>
#include<queue>
using std::string;
using std::queue;
class Trie
{
private:
	static const int R = 26;
	class Node
	{
	public:
		int val;
		bool condition;
		Node * next[R];
		Node(int v = 0) :val(v),condition(false)
		{
			for (int i = 0; i < R; ++i)
				next[i] = nullptr;
		}
	};
	Node*root;
	Node* get(Node*x, string& key, int d);
	Node* put(Node*x, string&key, int val, int d);
	void collectByPre(Node*x, string& pre, queue<string> &q);
	void collectByMatch(Node*x, string& pre,string&pat,queue<string>&q);
	int search(Node*x,string&pat, int d, int length);
	Node*Delete(Node*x, string&pat,int d);
public:
	Trie() :root(nullptr) {}
	~Trie();
	void free(Node*x);
	int get(string key);
	void put(string key, int val);
	queue<string>keys();
	queue<string> keysWithPrefix(string pre);
	queue<string>keysThatMatch(string pat);
	string longestPrefixOf(string s);
	void Delete(string s);
};