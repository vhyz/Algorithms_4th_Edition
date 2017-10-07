#include "TST.h"

TST::~TST()
{
	free(root);
}
void TST::free(Node * x)
{
	if (x == nullptr)
		return;
	free(x->left);
	free(x->mid);
	free(x->right);
	delete x;
}
TST& TST::put(string s,int val)
{
	root = put(root, s,val, 0);
	return *this;
}
TST::Node * TST::put(Node * x, string & s,int& val, int d)
{
	char c = s[d];
	if (x == nullptr)
	{
		x = new Node();
		x->c = c;
	}
	if (x->c < c)
		x->left = put(x->left, s,val, d);
	else if (x->c > c)
		x->right = put(x->right, s,val, d);
	else if (d < s.size() - 1)
		x->mid = put(x->mid, s,val, d + 1);
	else
	{
		x->val = val;
		x->condition = true;
	}
	return x;
}
int TST::get(string s)
{
	Node*x = get(root, s, 0);
	if (x == nullptr)
		return 0;
	return x->val;
}
TST::Node * TST::get(Node * x, string & s, int d)
{
	if (x == nullptr)
		return nullptr;
	char c = s[d];
	if (x->c < c)
		return get(x->left, s, d);
	else if (x->c > c)
		return get(x->right, s, d);
	else if (d < s.size() - 1)
		return get(x->mid, s, d + 1);
	else
		return x;
}
queue<string> TST::keysWithPrefix(string s)
{
	if (s == "")
		return keys();
	queue<string>q;
	Node*x = get(root, s, 0);
	if (x == nullptr)
		return q;
	if (x->condition == true)
		q.push(s);
	collectByPre(x->mid, s, q);
	return q;
}
void TST::collectByPre(Node * x, string & pre, queue<string>&q)
{
	if (x == nullptr)
		return;
	collectByPre(x->left, pre, q);
	if (x->condition == true)
		q.push(pre + x->c);
	pre.push_back(x->c);
	collectByPre(x->mid, pre, q);
	pre.erase(pre.end()-1);
	collectByPre(x->right, pre, q);
}
queue<string> TST::keys()
{
	queue<string>q;
	collectByPre(root, string(), q);
	return q;
}
queue<string> TST::keysThatMatch(string s)
{
	queue<string>q;
	collectByMatch(root, string(), s,0, q);
	return q;
}
void TST::collectByMatch(Node * x, string & pre, string & pat,int d, queue<string>& q)
{
	if (x == nullptr)
		return;
	char c = pat[d];
	if (c == '.' || c < x->c)
		collectByMatch(x->left, pre, pat, d, q);
	if (c == '.' || c == x->c)
	{
		if (d == pat.size() - 1 && x->condition == true)
			q.push(pre + x->c);
		if (d < pat.size() - 1)
		{
			pre.push_back(x->c);
			collectByMatch(x->mid, pre, pat, d + 1, q);
			pre.erase(pre.end() - 1);
		}
	}
	if (c == '.' || c > x->c)
		collectByMatch(x->right, pre, pat, d, q);
}
void TST::Delete(string s)
{
	if (s == "")
		return;
	root = Delete(root, s, 0);
}
TST::Node * TST::Delete(Node * x, string & s, int d)
{
	if (x == nullptr)
		return nullptr;
	char c = s[d];
	if (x->c < c)
		x->left = Delete(x->left, s, d);
	else if (x->c > c)
		x->right = Delete(x->right, s, d);
	else if (d < s.size() - 1)
		x->mid = Delete(x->mid, s, d + 1);
	else
		x->condition = false;
	if (x->condition == true)
		return x;
	if (x->left != nullptr || x->right != nullptr || x->mid != nullptr)
		return x;
	delete x;
	return nullptr;
}