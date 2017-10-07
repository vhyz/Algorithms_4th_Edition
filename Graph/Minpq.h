#pragma once
#include<iostream>
using std::cout;
using std::endl;
template<typename T>
class Minpq
{
private:
	template<typename T>
	struct Node
	{
		T val;
		Node*next;
		Node(T v,Node*x):
			val(v),next(x) {}
	};
	Node<T>*head;
	int N;
public:
	Minpq():
		head(nullptr),N(0) {}
	~Minpq();
	void put(T v);
	T DeleteMin();
	bool isEmpty() { return head == nullptr; }
	int size() { return N; }
	void travel();
};
template<typename T>
void Minpq<T>::put(T v)
{
	Node<T>*slow = nullptr;
	Node<T>*fast = head;
	while (fast)
	{
		if (v < fast->val)
			break;
		else if (v > fast->val)
		{
			slow = fast;
			fast = fast->next;
		}
		else
			return;
	}
	++N;
	if (head == nullptr || slow == nullptr)
		head = new Node<T>(v, head);
	else
	{
		Node<T>*temp = new Node<T>(v, fast);
		slow->next = temp;
	}
}
template<typename T>
T Minpq<T>::DeleteMin()
{
	if (head == nullptr)
		return T();
	Node<T>*temp = head;
	head = head->next;
	T v = temp->val;
	delete temp;
	return v;
}
template<typename T>
inline void Minpq<T>::travel()
{
	Node<T>*temp = head;
	while (temp)
	{
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
}
template<typename T>
inline Minpq<T>::~Minpq()
{
	while (head)
	{
		Node<T>*temp = head;
		head = head->next;
		delete temp;
	}
}