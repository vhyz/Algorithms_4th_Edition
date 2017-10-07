#pragma once
#include<string>
#include<queue>
using std::queue;
using std::string;
class TST
{
private:
	class Node
	{
	public:
		char c;
		int val;
		bool condition;
		Node*left;
		Node*mid;
		Node*right;
		Node() :
			val(0), left(nullptr), mid(nullptr), right(nullptr),condition(false) {}
	};
	Node*root;
	Node*put(Node*x,string&s,int &val,int d);
	Node*get(Node*x, string&s,int d);
	Node*Delete(Node*x, string&s,int d);
	void free(Node*x);
	void collectByMatch(Node*x, string&pre, string&pat, int d,queue<string>&q);
	void collectByPre(Node*x, string&pre,queue<string>&q);
public:
	TST() :
		root(nullptr) {}
	~TST();
	TST& put(string s,int val);
	int get(string s);
	queue<string>keys();
	queue<string>keysWithPrefix(string s);
	queue<string>keysThatMatch(string s);
	void Delete(string s);
};