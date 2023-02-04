#pragma once
using namespace std;
template <class T>
class Node
{
public:
	Node(T value, Node<T>* next = nullptr)
		:value(value), next(next)
	{}
	void setValue(T v) { value = v; }
	void setNext(Node<T>* n) { next = n; }
	T getValue()const { return value; }
	Node<T>* getNext()const { return next; }
	void Print()const { cout << value; }
private:
	T value;
	Node<T>* next;
};

template <class T>
class FList
{
public:
	FList();
	FList(const FList<T>& other);
	void push_back(T v);
	void push_front(T v);
	void insert(T v, size_t pos);
	void pop_front();
	void pop_back();
	void clear();
	void print()const;
	Node<T>* findNode(size_t pos)const;
	template<class T>
	friend ostream& operator <<(ostream& out, const FList<T>& other);
	size_t Size()const { return count; }
	~FList();
private:
	Node<T>* head;
	Node<T>* tail;
	size_t count;
};

template<class T>
FList<T>::FList()
{
	head = nullptr;
	tail = nullptr;
	count = 0;
}

template<class T>
inline FList<T>::FList(const FList<T>& other):FList()
{
	Node<T>* cur = other.head;

	while (cur)
	{
		push_back(cur->getValue());
		cur = cur->getNext();
	}
}

template<class T>
void FList<T>::push_back(T v)
{
	Node<T>* node = new Node<T>(v);
	if (tail) {
		tail->setNext(node);
	}
	else {
		head = node;
	}
	tail = node;
	count++;
}

template<class T>
void FList<T>::print() const
{
	Node<T>* cur = head;
	while (cur)
	{
		cur->Print();
		cur = cur->getNext();
	}
}

template<class T>
void FList<T>::push_front(T v)
{
	head = new Node<T>(v, head);
	if (!tail) {
		tail = head;
	}
	count++;
}

template<class T>
Node<T>* FList<T>::findNode(size_t pos) const
{
	if (pos >= count)return nullptr;
	size_t i = 0;
	Node<T>* cur = head;
	while (cur)
	{
		if (i == pos) break;
		cur = cur->getNext();
		i++;
	}
	return cur;
}

template<class T>
void FList<T>::insert(T v, size_t pos)
{
	if (pos == 0) {
		push_front(v);
		return;
	}
	if (pos == count) {
		push_back(v);
		return;
	}
	Node<T>* prev = findNode(pos - 1);
	if (!prev)return;

	Node<T>* node = new Node<T>(v, prev->getNext());
	prev->setNext(node);
	count++;
}

template<class T>
void FList<T>::pop_front()
{
	if (!head)return;
	Node<T>* del = head;
	head = head->getNext();
	if (!head) tail = nullptr;
	count--;
	delete del;
}

template<class T>
void FList<T>::pop_back()
{
	if (tail == head) { pop_front(); return; }
	Node<T>* del = tail;
	tail = findNode(count - 2);
	tail->setNext(nullptr);

	count--;
	delete del;
}

template<class T>
void FList<T>::clear()
{
	while (head) {
		pop_front();
	}
}

template<class T>
FList<T>::~FList()
{
	clear();
}

template<class T>
ostream& operator<<(ostream& out, const FList<T>& other)
{
	if (other.Size() == 0)
	{
		out << "List empty";
		return out;
	}
	Node<T>* temp = other.findNode(0);
	while (temp)
	{
		out << temp->getValue();
		temp = temp->getNext();
	}
	return out;
}