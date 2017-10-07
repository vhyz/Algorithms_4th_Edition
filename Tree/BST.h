#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using std::vector;
using std::stack;
using std::queue;
template<typename T1, typename T2>
class Node
{
public:
	Node(T1 key, T2 val)
	{
		_Key = key;
		_Val = val;
		_Left = nullptr;
		_Right = nullptr;
		_N = 1;
	}
	T1 _Key;
	T2 _Val;
	Node<T1, T2>*_Left;
	Node<T1, T2>*_Right;
	int _N;//该节点所含节点个数
};
template<typename T1, typename T2>
class MAP
{
private:
	Node<T1,T2>*_root;
	int size(Node<T1, T2>*x);
	T2 get(Node<T1, T2>*x, T1 key);
	Node<T1, T2>*put(Node<T1, T2> *x, T1 key, T2 val);
	Node<T1,T2>* GetMax(Node<T1, T2>*x);
	Node<T1,T2>* GetMin(Node<T1, T2>*x);
	void DeleteMap(Node<T1, T2>*x);
	Node<T1,T2>* Floor(Node<T1, T2>*x, T1 key);
	Node<T1,T2>* Ceiling(Node<T1, T2>*x, T1 key);
	Node<T1, T2>* Select(Node<T1, T2>*x, int k);
	int Rank(Node<T1, T2>*x, T1 key);
	void DeleteMin(Node<T1, T2>*x);
	void DeleteMax(Node<T1, T2>*x);
	Node<T1, T2>* DeleteKey(Node<T1, T2>*x, T1 key);
	void Show(vector<T1>&Keys);
	void keys(Node<T1,T2>*x,vector<T1>&Keys, T1 lo, T1 hi);
	void InOrder(Node<T1, T2>*x,vector<T1>&result);
public:
	MAP() { _root = nullptr; }
	~MAP() { DeleteMap(_root);}
	int size() { return size(_root); }
	T2 get(T1 key) { return get(_root, key); }
	void put(T1 key, T2 val) { _root = put(_root, key, val); }
	T1 GetMax() { Node<T1, T2>*temp = GetMax(_root); return temp->_Key; }
	T1 GetMin() { Node<T1, T2>*temp = GetMin(_root); return temp->_Key; }
	int Rank(T1 key) { return Rank(_root, key); }
	void DeleteMin() {  DeleteMin(_root); }
	void DeleteMax() {  DeleteMax(_root); }
	void DeleteKey(T1 key) { _root = DeleteKey(_root, key); }
	void keys() { vector<T1>Keys; T1 lo = GetMin(); T1 hi = GetMax(); keys(_root,Keys, lo,hi); Show(Keys); }
	void InOrder() { vector<T1>result; InOrder(_root,result); Show(result); }
	void LayerTraversal();
	T1 Select(int k)
	{
		Node<T1, T2>*temp = Select(_root, k);
		if (temp == nullptr)
			return T1();
		return temp->_Key;
	}
	T1 Floor(T1 key) 
	{
		Node<T1,T2>*temp = Floor(_root, key);
		if (temp == nullptr)
			return T1();
		return temp->_Key;
	}
	T1 Ceiling(T1 key)
	{
		Node<T1, T2>*temp = Ceiling(_root, key);
		if (temp == nullptr)
			return T1();
		return temp->_Key;
	}
};
template<typename T1, typename T2>
int MAP<T1, T2>::size(Node<T1, T2>* x)
{
	if (x == nullptr)
		return 0;
	return size(x->_Left) + size(x->_Right) + 1;
}
template<typename T1,typename T2>
void MAP<T1, T2>::DeleteMap(Node<T1, T2>*x)
{
	if (x == nullptr)
		return;
	DeleteMap(x->_Left);
	DeleteMap(x->_Right);
	delete x;
	std::cout << "delete" << std::endl;
}
template<typename T1,typename T2>
Node<T1, T2>* MAP<T1, T2>::GetMax(Node<T1, T2>*x)
{
	if (x->_Right == nullptr)
		return x;
	return GetMax(x->_Right);
}
template<typename T1,typename T2>
Node<T1, T2>* MAP<T1,T2>::GetMin(Node<T1, T2>*x)
{
	if (x->_Left == nullptr)
		return x;
	return GetMin(x->_Left);
}
template<typename T1,typename T2>
Node<T1, T2>*MAP<T1,T2>::put(Node<T1, T2> *x, T1 key, T2 val)
{
	if (x == nullptr)
	{
		Node<T1, T2>*temp = new Node<T1, T2>(key, val);
		return temp;
	}
	if (x->_Key < key)
		x->_Right = put(x->_Right, key, val);
	else if (x->_Key > key)
		x->_Left = put(x->_Left, key, val);
	else
		x->_Val = val;
	x->_N = size(x->_Left) + size(x->_Right) + 1;
	return x;
}
template<typename T1,typename T2>
T2 MAP<T1,T2>::get(Node<T1, T2>*x, T1 key)
{
	if (x == nullptr)
		return T2();
	if (x->_Key < key)
		return get(x->_Right, key);
	else if (x->_Key > key)
		return get(x->_Left, key);
	else
		return x->_Val;
}
template<typename T1, typename T2>
Node<T1,T2>* MAP<T1, T2>::Floor(Node<T1, T2>* x, T1 key)
{
	if (x == nullptr)
		return nullptr;
	if (x->_Key > key)
		return Floor(x->_Left, key);
	else if (x->_Key == key)
		return x;
	Node<T1, T2>*temp = Floor(x->_Right, key);
	if (temp != nullptr)
		return temp;
	return x;
}
template<typename T1, typename T2>
Node<T1, T2>* MAP<T1, T2>::Ceiling(Node<T1, T2>* x, T1 key)
{
	if (x == nullptr)
		return nullptr;
	if (x->_Key < key)
			return Floor(x->_Right, key);
	else if (x->_Key == key)
			return x;
	Node<T1, T2>*temp = Ceiling(x->_Left, key);
	if (temp != nullptr)
		return temp;
	return x;
}
template<typename T1, typename T2>
Node<T1, T2>* MAP<T1, T2>::Select(Node<T1, T2>* x, int k)
{
	if (x == nullptr)
		return nullptr;
	int t = size(x->_Left);
	if (t > k)
		return Select(x->_Left, k);
	else if (t < k)
		return Select(x->_Right, k - t - 1);
	else
		return x;
}
template<typename T1, typename T2>
int MAP<T1, T2>::Rank(Node<T1, T2>* x, T1 key)
{
	if (x == nullptr)
		return 0;
	if (x->_Key < key)
		return 1 + size(x->_Left) + Rank(x->_Right, key);
	else if (x->_Key > key)
		return Rank(x->_Left, key);
	else
		return size(x->_Left);
}
template<typename T1, typename T2>
void MAP<T1, T2>::DeleteMin(Node<T1, T2>* x)
{
	if (x == nullptr)
		return;
	Node<T1, T2>*temp1 = x;
	Node<T1, T2>*temp2 = nullptr;
	while (temp1->_Left)
	{
		temp2 = temp1;
		temp1 = temp1->_Left;
	}
	if (temp2 == nullptr)
		x = x->_Right;
	else
		temp2->_Left = temp1->_Right;
	delete temp1;
	std::cout << "delete" << std::endl;
	x->_N -= 1;
}
template<typename T1, typename T2>
void MAP<T1, T2>::DeleteMax(Node<T1, T2>* x)
{
	if (x == nullptr)
		return;
	Node<T1, T2>*temp1 = x;
	Node<T1, T2>*temp2 = nullptr;
	while (temp1->_Right)
	{
		temp2 = temp1;
		temp1 = temp1->_Right;
	}
	if (temp2 == nullptr)
		x = x->_Left;
	else
		temp2->_Right = temp1->_Left;
	delete temp1;
	std::cout << "delete" << std::endl;
	x->_N -= 1;
}
template<typename T1, typename T2>
Node<T1,T2>* MAP<T1,T2>::DeleteKey(Node<T1,T2>*x,T1 key)
{
	Node<T1, T2>*temp1 = nullptr;
	Node<T1, T2>*temp2 = nullptr;
	if (x == nullptr)
		return nullptr;
	if (x->_Key > key)
		x->_Left = DeleteKey(x->_Left, key);
	else if (x->_Key < key)
		x->_Right = DeleteKey(x->_Right, key);
	else
	{
		if (x->_Left == nullptr)
		{
			temp1 = x->_Right;
			delete x;
			std::cout << "delete" << std::endl;
			return temp1;
		}
		else if (x->_Right == nullptr)
		{
			temp1 = x->_Left;
			delete x;
			std::cout << "delete" << std::endl;
			return temp1;
		}
		else
		{
			temp2 = x;
			temp1 = GetMin(x->_Right);
			x = new Node<T1, T2>(temp1->_Key, temp1->_Val);
			DeleteMin(temp2->_Right);
			x->_Left = temp2->_Left;
			x->_Right = temp2->_Right;
			std::cout << "delete" << std::endl;
			delete temp2;
			x->_N = size(x->_Left) + size(x->_Right) + 1;
		}
	}
	return x;
}
template<typename T1, typename T2>
inline void MAP<T1, T2>::Show(vector<T1>&Keys)
{
	for (int i = 0; i < Keys.size(); i++)
		std::cout << Keys[i] << "   ";
}
template<typename T1, typename T2>
void MAP<T1, T2>::keys(Node<T1,T2>*x,vector<T1>& Keys, T1 lo, T1 hi)
{
	if (x == nullptr)
		return;
	if (lo < x->_Key)
		keys(x->_Left, Keys, lo, hi);
	if (lo <= x->_Key &&hi >= x->_Key)
		Keys.push_back(x->_Key);
	if (hi > x->_Key)
		keys(x->_Right, Keys, lo, hi);
}
template<typename T1, typename T2>
void MAP<T1, T2>::InOrder(Node<T1, T2>* x, vector<T1>& result)
{
	Node<T1, T2>*p = x;
	stack<Node<T1, T2>*>s;
	while (!s.empty() || p)
	{
		if (p)
		{
			s.push(p);
			p = p->_Left;
		}
		else
		{
			p = s.top();
			s.pop();
			result.push_back(p->_Key);
			p = p->_Right;
		}
	}
}
template<typename T1, typename T2>
void MAP<T1, T2>::LayerTraversal()
{
	queue<Node<T1, T2>*>s;
	s.push(_root);
	Node<T1, T2>* CurNode = nullptr;
	Node<T1, T2>* nlast = nullptr;
	Node<T1, T2>* last = _root;
	while (!s.empty())
	{
		CurNode = s.front();
		std::cout << CurNode->_Key << " ";
		s.pop();
		if (CurNode->_Left)
		{
			s.push(CurNode->_Left);
			nlast = CurNode->_Left;
		}
		if (CurNode->_Right)
		{
			s.push(CurNode->_Right);
			nlast = CurNode->_Right;
		}
		if (CurNode == last)
		{
			std::cout << std::endl;
			last = nlast;
		}
	}
}