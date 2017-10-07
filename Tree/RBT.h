#include<iostream>
#include<queue>
using std::cout;
using std::endl;
using std::queue;
const bool BLACK = false;
const bool RED = true;
template<typename T>
class Node
{
public:
	T Key;
	Node<T>*left;
	Node<T>*Right;
	int N;
	bool Color;
	Node(T key, bool color)
	{
		Key = key;
		Color = color;
		N = 1;
		left = nullptr;
		Right = nullptr;
	}
};
template<typename T>
class RBT
{
private:
	Node<T>*Root;
	int size(Node<T>*h);
	bool IsRed(Node<T>*h);
	Node<T>* RotateLeft(Node<T>*h);
	Node<T>* RotateRight(Node<T>*h);
	Node<T>* Balance(Node<T>*h);
	Node<T>* get(Node<T>*h, T key);
	Node<T>* put(Node<T>*h, T key);
	void FlipColor(Node<T>*h);
	Node<T>* MoveRedLeft(Node<T>*h);
	Node<T>*MoveRedRight(Node<T>*h);
	Node<T>*DeleteMin(Node<T>*h);
	Node<T>*DeleteMax(Node<T>*h);
	Node<T>*DeleteKey(Node<T>*h, T key);
	void DeleteTree(Node<T>*h);
	Node<T>*GetMax(Node<T>*h);
	Node<T>*GetMin(Node<T>*h);
	int Rank(Node<T>*h, T key);
	Node<T>*Select(Node<T>*h, int k);
	Node<T>*Ceiling(Node<T>*h, T key);
	Node<T>*Floor(Node<T>*h, T key);
	
public:
	int Rank(T key) { return Rank(Root, key); }
	T Select(int k) { Node<T>*temp = Select(Root,k); if (temp == nullptr)return T(); return temp->Key; }
	RBT(){}
	~RBT() { DeleteTree(Root); }
	int size() { return size(Root); }
	void put(T key) { Root = put(Root, key); }
	void InOrderKey();
	void InOrderColor();
	T GetMax()
	{
		Node<T>*temp = GetMax(Root);
		if (temp == nullptr)
			return T();
		return temp->Key;
	}
	T GetMin()
	{
		Node<T>*temp = GetMin(Root);
		if (temp == nullptr)
			return T();
		return temp->Key;
	}
	void DeleteMin()
	{
		if (Root == nullptr)
			return;
		if (!IsRed(Root->left) && !IsRed(Root->Right))
			Root->Color = RED;
		Root = DeleteMin(Root);
		if (Root)
			Root->Color = BLACK;
	}
	void DeleteMax()
	{
		if (Root == nullptr)
			return;
		if (!IsRed(Root->left) && !IsRed(Root->Right))
			Root->Color = RED;
		Root = DeleteMax(Root);
		if (Root)
			Root->Color = BLACK;
	}
	void DeleteKey(T key)
	{
		Node<T>*temp = get(Root, key);
		if (temp == nullptr)
			return;
		if (Root == nullptr)
			return;
		if (!IsRed(Root->left) && !IsRed(Root->Right))
			Root->Color = RED;
		Root = DeleteKey(Root, key);
		if (Root)
			Root->Color = BLACK;
	}
	T Floor(T key)
	{
		Node<T>*temp = Floor(Root, key);
		if (temp == nullptr)
			return T();
		return temp->Key;
	}
	T Ceiling(T key)
	{
		Node<T>*temp = Ceiling(Root, key);
		if (temp == nullptr)
			return T();
		return temp->Key;
	}
};
template<typename T>
bool RBT<T>::IsRed(Node<T>* h)
{
	if (h == nullptr)
		return false;
	return h->Color == RED;
}
template<typename T>
Node<T>* RBT<T>::RotateLeft(Node<T>* h)
{
	Node<T>*x = h->Right;
	h->Right = x->left;
	x->left = h;
	x->Color = h->Color;
	h->Color = RED;
	x->N = h->N;
	h->N = size(h->left) + size(h->Right) + 1;
	return x;
}
template<typename T>
Node<T>* RBT<T>::RotateRight(Node<T>* h)
{
	Node<T>*x = h->left;
	h->left = x->Right;
	x->Right = h;
	x->Color = h->Color;
	h->Color = RED;
	x->N = h->N;
	h->N = size(h->left) + size(h->Right) + 1;
	return x;
}
template<typename T>
inline int RBT<T>::size(Node<T>* h)
{
	if (h == nullptr)
		return 0;
	return h->N;
}
template<typename T>
Node<T>* RBT<T>::Balance(Node<T>* h)
{
	if (IsRed(h->Right))
		h = RotateLeft(h);
	if (h->left&&IsRed(h->left) && IsRed(h->left->left))
		h = RotateRight(h);
	if (IsRed(h->left) && IsRed(h->Right))
		FlipColor(h);
	h->N = size(h->left) + size(h->Right) + 1;
	return h;
}
template<typename T>
void RBT<T>::FlipColor(Node<T>* h)
{
	h->Color = !h->Color;
	if (h->left)
		h->left->Color = !h->left->Color;
	if (h->Right)
		h->Right->Color = !h->Right->Color;
}
template<typename T>
Node<T>* RBT<T>::put(Node<T>* h, T key)
{
	if (h == nullptr)
	{
		Node<T>*temp = new Node<T>(key, RED);
		return temp;
	}
	if (h->Key > key)
		h->left = put(h->left, key);
	else if (h->Key < key)
		h->Right = put(h->Right, key);
	else
		return h;
	if (IsRed(h->Right) && !IsRed(h->left))
		h = RotateLeft(h);
	if (h->left&&IsRed(h->left) && IsRed(h->left->left))
		h = RotateRight(h);
	if (IsRed(h->left) && IsRed(h->Right))
		FlipColor(h);
	h->N = size(h->left) + size(h->Right) + 1;
	return h;
}
template<typename T>
Node<T>* RBT<T>::get(Node<T>* h, T key)
{
	if (h == nullptr)
		return nullptr;
	if (h->Key > key)
		return get(h->left,key);
	else if (h->Key < key)
		return get(h->Right,key);
	else
		return h;
}
template<typename T>
void RBT<T>::InOrderColor()
{
	if (Root == nullptr)
		return;
	queue<Node<T>*>s;
	s.push(Root);
	while (!s.empty())
	{
		Node<T>*h;
		int j = s.size();
		for (int i = 0; i < j; i++)
		{
			h = s.front();
			s.pop();
			cout << h->Color << " ";
			if (h->left)
				s.push(h->left);
			if (h->Right)
				s.push(h->Right);
		}
		cout << endl;
	}
}
template<typename T>
inline Node<T>* RBT<T>::MoveRedLeft(Node<T>* h)
{
	FlipColor(h);
	if (IsRed(h->Right->left))
	{
		h->Right = RotateRight(h->Right);
		h = RotateLeft(h);
		FlipColor(h);
	}
	return h;
}

template<typename T>
Node<T>* RBT<T>::MoveRedRight(Node<T>* h)
{
	FlipColor(h);
	if (IsRed(h->left->left))
	{
		h = RotateRight(h);
		FlipColor(h);
	}
	return h;
}
template<typename T>
Node<T>* RBT<T>::DeleteMin(Node<T>* h)
{
	if (h->left == nullptr)
	{
		delete h;
		cout << "delete" << endl;
		return nullptr;
	}
	if (!IsRed(h->left) && !IsRed(h->left->left))
		h = MoveRedLeft(h);
	h->left = DeleteMin(h->left);
	return Balance(h);
}
template<typename T>
Node<T>* RBT<T>::DeleteMax(Node<T>* h)
{
	if (IsRed(h->left))
		h = RotateRight(h);
	if (h->Right == nullptr)
	{
		delete h;
		cout << "delete" << endl;
		return nullptr;
	}
	if (!IsRed(h->Right) && !IsRed(h->Right->left))
		h = MoveRedRight(h);
	h->Right = DeleteMax(h->Right);
	return Balance(h);
}
template<typename T>
Node<T>* RBT<T>::DeleteKey(Node<T>* h, T key)
{
	if (h->Key > key)
	{
		if (!IsRed(h->left) && !IsRed(h->left->left))
			h = MoveRedLeft(h);
		h->left = DeleteKey(h->left, key);
	}
	else
	{
		if(IsRed(h->left))
			h = RotateRight(h);
		if (h->Key == key&&h->Right == nullptr)
		{
			delete h;
			cout << "delete" << endl;
			return nullptr;
		}
		if (!IsRed(h->Right) && !IsRed(h->Right->left))
			h = MoveRedRight(h);
		if (h->Key == key)
		{
			Node<T>*temp = GetMin(h->Right);
			h->Key = temp->Key;
			h->Right = DeleteMin(h->Right);
		}
		else
			h->Right = DeleteKey(h->Right, key);
	}
	return Balance(h);
}
template<typename T>
void RBT<T>::InOrderKey()
{
	if (Root == nullptr)
		return;
	queue<Node<T>*>s;
	s.push(Root);
	while (!s.empty())
	{
		Node<T>*h;
		int j = s.size();
		for (int i = 0; i < j; i++)
		{
			h = s.front();
			s.pop();
			cout << h->Key << " ";
			if (h->left)
				s.push(h->left);
			if (h->Right)
				s.push(h->Right);
		}
		cout << endl;
	}
}
template<typename T>
inline void RBT<T>::DeleteTree(Node<T>* h)
{
	if (h == nullptr)
		return;
	DeleteTree(h->left);
	DeleteTree(h->Right);
	delete h;
	cout << "delete" << endl;
}
template<typename T>
Node<T>* RBT<T>::GetMax(Node<T>* h)
{
	if (h==nullptr||h->Right == nullptr)
		return h;
	return GetMax(h->Right);
}
template<typename T>
Node<T>* RBT<T>::GetMin(Node<T>* h)
{
	if (h==nullptr||h->left == nullptr)
		return h;
	return GetMin(h->left);
}
template<typename T>
int RBT<T>::Rank(Node<T>* h, T key)
{
	if (h == nullptr)
		return 0;
	if (h->Key > key)
		return Rank(h->left, key);
	else if (h->Key < key)
		return size(h->left) + 1 + Rank(h->Right, key);
	else
		return size(h->left);
}
template<typename T>
Node<T>* RBT<T>::Select(Node<T>* h, int k)
{
	if (h == nullptr)
		return nullptr;
	int j = size(h->left);
	if (j > k)
		return Select(h->left, k);
	else if (j < k)
		return Select(h->Right, k - j - 1);
	else
		return h;
}
template<typename T>
Node<T>* RBT<T>::Ceiling(Node<T>* h, T key)
{
	if (h == nullptr)
		return nullptr;
	if (h->Key < key)
		return Ceiling(h->Right, key);
	else if (h->Key == key)
		return h;
	Node<T>*temp = Ceiling(h->left, key);
	if (temp != nullptr)
		return temp;
	return h;
}
template<typename T>
Node<T>* RBT<T>::Floor(Node<T>* h, T key)
{
	if (h == nullptr)
		return nullptr;
	if (h->Key > key)
		return Floor(h->left, key);
	else if (h->Key == key)
		return h;
	Node<T>*temp = Floor(h->Right, key);
	if (temp != nullptr)
		return temp;
	return h;
}