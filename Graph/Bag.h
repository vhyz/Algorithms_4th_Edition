#pragma once
#include<vector>
#include<iostream>
template<typename T>
class Bag
{
private:
	class Node
	{
	public:
		T val;
		Node* next;
		Node(T v, Node*x) :
			val(v), next(x) {}
	};
	Node* head;
public:
	Bag() :head(nullptr) {}
	~Bag()
	{
		while (head)
		{
			Node*temp = head;
			head = head->next;
			delete temp;
			std::cout << "delete";
		}
	}
	void put(T val)
	{
		head = new Node(val, head);
	}
	std::vector<T> Travel()
	{
		Node*temp = head;
		std::vector<T>result;
		while (temp)
		{
			result.push_back(temp->val);
			temp = temp->next;
		}
		return result;
	}
};