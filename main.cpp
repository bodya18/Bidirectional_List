#include <iostream>

template <typename T>
class List
{
	template <typename T>
	class Node
	{
	public:
		Node* pNext;
		Node* pPrev;
		T data;
		Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
	};

	int Size;
	Node<T>* head;
	Node<T>* tail;
public:
	List();
	~List();
	int GetSize() { return Size; }
	void push_back(T data);
	void push_front(T data);
	void pop_back();
	void pop_front();
	void clear();
	void removeAt(int index);
	void insert(int index, T data);
	void swap(int index1, int index2);
	T& operator[](const int index);
};

template <typename T>
List<T>::List()
{
	Size = 0;
	head = nullptr;
	tail = nullptr;
}

template <typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
void List<T>::push_back(T data)
{
	Node<T>* temp = new Node<T>(data, nullptr, tail);

	if (Size == 0)
		head = tail = temp;
	else
	{
		tail->pNext = temp;
		temp->pPrev = tail;
		tail = temp;
	}
	Size++;
}

template<typename T>
void List<T>::push_front(T data)
{
	Node<T>* temp = new Node<T>(data, head);		

	if (Size == 0)
		head = tail = temp;
	else
	{	
		head->pPrev = temp;
		head = temp;
	}
	Size++;
}

template<typename T>
void List<T>::pop_back()
{
	if (Size == 1)
		pop_front();
	else
	{	
		Node<T>* temp = this->tail;
		tail = temp->pPrev;
		delete temp;
		Size--;
	}
}

template<typename T>
void List<T>::pop_front()
{
	if (Size == 1)
	{
		tail = nullptr;
	}
	Node<T>* temp = this->head;
	head = head->pNext;
	delete temp;
	Size--;
}

template<typename T>
void List<T>::clear()
{
	while (Size)
		pop_front();
}

template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		if (index < (Size / 2))
		{
			Node<T>* previous = this->head;
			for (int i = 0; i < index - 1; i++)
				previous = previous->pNext;
			Node<T>* toDelete = previous->pNext;
			previous->pNext = toDelete->pNext;
			toDelete->pNext->pPrev = toDelete->pPrev;
			delete toDelete;
			Size--;
		}
		else
		{
			Node<T>* next = this->tail;
			for (int i = Size - 1; i > index + 1; i--)
				next = next->pPrev;
			Node<T>* toDelete = next->pPrev;
			next->pPrev = toDelete->pPrev;
			toDelete->pPrev->pNext = toDelete->pNext;
			delete toDelete;
			Size--;
		}
	}
}

template<typename T>
void List<T>::insert(int index, T data)
{
	if (index == 0)
	{
		push_front(data);
	}
	else if (index == Size)
	{
		push_back(data);
	}
	else
	{
			Node<T>* Ins = head;
			for (int i = 0; i < index; i++)
				Ins = Ins->pNext;

			Node<T>* PrevIns = Ins->pPrev;
			Node<T>* temp = new Node<T>(data, Ins);

			PrevIns->pNext = temp;
			temp->pPrev = PrevIns;
			Ins->pPrev = temp;

			Size++;
	}
}

template<typename T>
void List<T>::swap(int index1, int index2)
{
	Node<T>* current1 = this->head;
	for (int i = 0; i < index1; i++)
	{
		current1 = current1->pNext;
	}
	Node<T>* current2 = this->head;
	for (int i = 0; i < index2; i++)
	{
		current2 = current2->pNext;
	}
	T data = current1->data;
	current1->data = current2->data;
	current2->data = data;
}

template<typename T>
T& List<T>::operator[](const int index)
{
	if (index < (Size / 2))
	{
		Node<T>* current = this->head;
		for (int i = 0; i <= index; i++)
		{
			if (i == index)
				return current->data;
			current = current->pNext;
		}
	}
	else
	{
		Node<T>* current = this->tail;
		for (int i = Size - 1; i >= index; i--)
		{
			if (i == index)
				return current->data;
			current = current->pPrev;
		}
	}
}

int main()
{
	List<int> lst;

	lst.push_back(2); // 2
	lst.push_back(3); // 2 3
	lst.push_front(1); // 1 2 3

	for (int i = 0; i < lst.GetSize(); i++)
		std::cout << lst[i] << std::ends;

	lst.insert(1, -2); // 1 -2 2 3
	lst.insert(1, -2); // 1 -2 -2 2 3
	lst.insert(3, -2); // 1 -2 -2 -2 2 3
	lst.insert(5, -2); // 1 -2 -2 -2 2 -2 3

	std::cout << std::endl << std::endl;
	for (int i = 0; i < lst.GetSize(); i++)
		std::cout << lst[i] << std::ends;

	lst.removeAt(1); // 1 -2 -2 2 -2 3
	lst.removeAt(4); // 1 -2 -2 2 3
	lst.removeAt(2); // 1 -2 2 3
	lst.removeAt(1); // 1 2 3

	std::cout << std::endl << std::endl;
	for (int i = 0; i < lst.GetSize(); i++)
		std::cout << lst[i] << std::ends;
	std::cout << std::endl;
}
