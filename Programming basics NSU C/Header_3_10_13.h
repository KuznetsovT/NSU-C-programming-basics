#pragma once


#include <algorithm>
#include <iostream>



template <class T>
class DoubleLinkedList {

private:
	template<class C>
	class cell;

	 cell<T> *ENTRY;   //  ... <-> ENTRY <-> first <-> second <-> ..... <-> last but one <-> last <-> ENTRY <-> ...
	 size_t size = 0;

public:

	DoubleLinkedList() : ENTRY(initEntry()) {}

	~DoubleLinkedList()
	{
		while(size != 0) pop_back();
		delete ENTRY;
	}

	template<typename ...ARRAY_OF>
	DoubleLinkedList(ARRAY_OF ...Args) : DoubleLinkedList() {
		for (auto arg : {Args...}) {
			push_back(arg);
		}
	}

	void push_back(T val);
	void push_front(T val);

	T & peek_back();
	T & peek_front();

	T pop_front();
	T pop_back();


	T &operator[](const size_t num);

	void insert(T val, size_t position);

	T erase(size_t position);

	class iterator {
	private:
		cell<T> *data;
		DoubleLinkedList<T> &list;
		iterator(DoubleLinkedList<T> &list, cell<T> *data) : list(list), data(data) {}
	public:
		
		iterator & operator++() {
			data = data->foll;
			return *this;
		}
		iterator & operator++(int) {
			return this->operator++();
		}

		iterator & operator--() {
			data = data->prev;
			return *this;
		}
		iterator & operator--(int) {
			return this->operator--();
		}

		iterator operator-(const size_t num) const { iterator i = *this; for (size_t j = 0; j < num; j++) i--; return i; }

		T &operator*() { return data->val; }
		bool operator!=(const iterator & opp) const { return data != opp.data; }

		friend iterator DoubleLinkedList<T>::begin();
		friend iterator DoubleLinkedList<T>::end();
	};

	iterator begin() { return iterator(*this, ENTRY->foll); }
	iterator end() { return iterator(*this, ENTRY); }

	//void sort() { std::sort(begin(), end()); }

	template<class T>
	friend std::ostream & operator<<(std::ostream & out, const DoubleLinkedList<T> &list);

private:
	

	template<class C>
	class cell {
	public:
		cell *prev = NULL, *foll = NULL;
		C val;
		cell(cell *prev = NULL, cell *foll = NULL) : prev(prev), foll(foll) {}
		cell(cell *prev, cell *foll, C val) : prev(prev), foll(foll), val(val) {}
	};


	cell<T> * initEntry() {
		cell <T> *Entry = new cell<T>;
		Entry->prev = Entry->foll = Entry;
		return Entry;
	}

	T pop_cell(cell<T> *pop);

	cell<T> *iterate_front(size_t num_front);
	cell<T> *iterate_back(size_t num_back);

	cell<T> *find_cell(size_t num);
};








template<class T>
inline void DoubleLinkedList<T>::push_back(T val)
{
	ENTRY->prev = ENTRY->prev->foll = new cell<T>(ENTRY->prev, ENTRY, val); //ÀÀÀÀÀ€€€€€€€€€€€∆∆∆∆∆∆∆∆∆∆∆∆∆€€€€€€€€€€€€€€€€€€
	size++;
}

template<class T>
inline void DoubleLinkedList<T>::push_front(T val)
{
	ENTRY->foll = ENTRY->foll->prev = new cell<T>(ENTRY, ENTRY->foll, val);
	size++;
}

template<class T>
inline T & DoubleLinkedList<T>::peek_back()
{
	return ENTRY->prev->vall;
}

template<class T>
inline T & DoubleLinkedList<T>::peek_front()
{
	return ENTRY->foll->val;
}

template<class T>
inline T DoubleLinkedList<T>::pop_front()
{
	return pop_cell(ENTRY->foll);
}

template<class T>
inline T DoubleLinkedList<T>::pop_back()
{
	return pop_cell(ENTRY->prev);
}

template<class T>
inline T & DoubleLinkedList<T>::operator[](const size_t num)
{
	return find_cell(num)->val;
}

template<class T>
inline void DoubleLinkedList<T>::insert(T val, size_t position)
{
	auto neighbour = find_cell(position);
	neighbour->prev = neighbour->prev->foll = new cell<T>(neighbour->prev, neighbour, val);
	size++;
}

template<class T>
inline T DoubleLinkedList<T>::erase(size_t position)
{
	return pop_cell(find_cell(position));
}

template<class T>
inline T DoubleLinkedList<T>::pop_cell(cell<T>* pop)
{
	pop->prev->foll = pop->foll;  //link
	pop->foll->prev = pop->prev;  //link
	T val = pop->val;             
	delete pop;
	size--;
	return val;
}

template<class T>
inline DoubleLinkedList<T>::cell<T>* DoubleLinkedList<T>::iterate_front(size_t num_front)
{
	cell<T> *p = ENTRY->foll;
	for (size_t i = 0; i != num_front; i++) p = p->foll;
	return p;
}

template<class T>
inline DoubleLinkedList<T>::cell<T>* DoubleLinkedList<T>::iterate_back(size_t num_back)
{
	cell<T> *p = ENTRY->prev;
	for (size_t i = 0; i != num_back; i++) p = p->prev;
	return p;
}

template<class T>
inline DoubleLinkedList<T>::cell<T>* DoubleLinkedList<T>::find_cell(size_t num)
{
	if (num >= size) throw size_t(size);
	if (num < (size >> 2))
		return iterate_front(num);
	else
		return iterate_back(size - 1 - num);
}

template<class T>
inline std::ostream & operator<<(std::ostream & out, DoubleLinkedList<T>& list)
{
	out << "{ ";
	for (class DoubleLinkedList<T>::iterator i = list.begin(),
		last = --(list.end());
		i != last;
		i++)
		out << *i << ", ";
	out << *(--list.end()) << " }";
	return out;
}
