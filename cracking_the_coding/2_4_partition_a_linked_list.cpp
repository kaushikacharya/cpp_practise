#include <iostream>
#include <cstdlib> //rand
#include <ctime>

template<typename T>
class Node
{
public:
	Node(T data, Node<T>* next=NULL);
	~Node();
public:
	T data();
	Node<T>* next();
	void setNext(Node<T>* next);
private:
	T data_;
	Node<T>* next_;
};
//---------
template<typename T>
Node<T>::Node(T data, Node<T> *next = 0)
: data_(data)
, next_(next)
{}
template<typename T>
Node<T>::~Node()
{}
template<typename T>
T Node<T>::data()
{
	return data_;
}
template<typename T>
Node<T>* Node<T>::next()
{
	return next_;
}
template<typename T>
void Node<T>::setNext(Node<T>* next)
{
	next_ = next;
}
//---------
template<typename T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();
public:
	Node<T>* head();
	Node<T>* tail();
public:
	// create a linked list with elements generated randomly in the range [init_value_range,final_value_range]
	void create_linked_list(T count, T init_value_range, T final_value_range);
	void partition(T val);
private:
	void empty_list();
private:
	Node<T>* head_;
	Node<T>* tail_;
};
//---
template<typename T>
LinkedList<T>::LinkedList()
{
	head_ = NULL;
	tail_ = NULL;
}
template<typename T>
LinkedList<T>::~LinkedList()
{
	empty_list();
}
template<typename T>
Node<T>* LinkedList<T>::head()
{
	return head_;
}
template<typename T>
void LinkedList<T>::create_linked_list(T count, T init_value_range, T final_value_range)
{
	std::srand(time(NULL));
	T range_size = final_value_range - init_value_range + 1;

	//keep appending new node to the tail of the linked list
	for (T count_i = 0; count_i != count; ++count_i)
	{
		T new_data = rand()%range_size + init_value_range;
		Node<T>* new_node = new Node<T>(new_data);
		if (count_i > 0)
		{
			(*tail_).setNext(new_node);
		}
		else
		{
			head_ = new_node;
		}
		tail_ = new_node;
		int gh = 0;
	}
}
template<typename T>
void LinkedList<T>::partition(T val)
{

}
template<typename T>
void LinkedList<T>::empty_list()
{
	//free the memory as well
	while (head_)
	{
		Node<T>* curNode = head_;
		head_ = (*head_).next();
		delete curNode;
	}
}
//---
int main(int argc, char* argv[])
{
	LinkedList<unsigned int> linked_list;
	unsigned int test_case = 0;
	unsigned int partition_val;

	switch (test_case)
	{
	case 0:
		linked_list.create_linked_list(5, 1, 20);
		partition_val = linked_list.head()->data();
		break;
	}
	return 0;
}
