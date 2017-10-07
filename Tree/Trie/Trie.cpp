#include"Trie.h"
Trie::~Trie()
{
	free(root);
}
void Trie::free(Node * x)
{
	if (x == nullptr)
		return;
	for (int i = 0; i < R; ++i)
	{
		free(x->next[i]);
	}
	delete x;
}
Trie::Node* Trie::get(Node * x, string & key, int d)
{
	if (x == nullptr)
		return nullptr;
	if (d == key.size())
		return x;
	char c = key[d];
	return get(x->next[c - 97], key, d + 1);
}
Trie::Node * Trie::put(Node * x, string & key, int val, int d)
{
	if (x == nullptr)
		x = new Node();
	if (d == key.size())
	{
		x->val = val;
		x->condition = true;
		return x;
	}
	char c = key[d];
	x->next[c - 97] = put(x->next[c - 97],key, val, d + 1);
	return x;
}
int Trie::get(string  key)
{
	Node*x = get(root, key, 0);
	if (x == nullptr)
		return 0;
	else
		return x->val;
}
void Trie::put(string  key, int val)
{
	root = put(root, key, val, 0);
}
queue<string> Trie::keys()
{
	return keysWithPrefix("");
}
queue<string> Trie::keysWithPrefix(string pre)
{
	queue<string>q;
	collectByPre(get(root, pre, 0), pre, q);
	return q;
}
void Trie::collectByPre(Node * x, string & pre, queue<string>& q)
{
	if (x == nullptr)
		return;
	if (x->condition == true)
		q.push(pre);
	for (char c = 'a'; c != 'z'; ++c)
		collectByPre(x->next[c-97], pre + c, q);
}
queue<string> Trie::keysThatMatch(string pat)
{
	queue<string>q;
	collectByMatch(root, pat,string(), q);
	return q;
}
void Trie::collectByMatch(Node * x, string&pre,string & pat, queue<string>& q)
{
	int d = pre.size();
	if (x == nullptr)
		return;
	if (d == pat.size() && x->condition == true)
		q.push(pre);
	if (d == pat.size())
		return;
	char next = pat[d];
	for (char c = 'a'; c != 'z'; ++c)
		if (next == '.' || next == c)
			collectByMatch(x->next[c - 97], pre+c, pat,q);
}
string Trie::longestPrefixOf(string s)
{
	int length = search(root, s,0, 0);
	return s.substr(0, length);
}
int Trie::search(Node * x, string&pat,int d, int length)
{
	if (x == nullptr)
		return length;
	if (x->condition==true)
		length = d;
	if (d == pat.size())
		return length;
	char c = pat[d];
	return search(x->next[c - 97], pat,d + 1, length);
}
void Trie::Delete(string s)
{
	root = Delete(root,s, 0);
}
Trie::Node * Trie::Delete(Node * x,string&pat, int d)
{
	if (x == nullptr)
		return nullptr;
	if (d == pat.size())
		x->condition = false;
	else
	{
		char c = pat[d];
		x->next[c - 97] = Delete(x->next[c - 97],pat, d + 1);
	}
	if (x->condition == true)
		return x;
	for (char c = 'a'; c != 'z'; ++c)
		if (x->next[c - 97] != nullptr)
			return x;
	delete x;
	return nullptr;
}