#pragma once


#include <iostream>



template <class T>
class DoubleLinkedList {

private:

	class cell;

	 cell *ENTRY;   //  ... <-> ENTRY <-> first <-> second <-> ..... <-> last but one <-> last <-> ENTRY <-> ...
	 size_t size = 0;

public:

	DoubleLinkedList() : ENTRY(initEntry()) {}

	~DoubleLinkedList()
	{
		while(size != 0) pop_back();
		delete ENTRY;
	}


	DoubleLinkedList(std::initializer_list<T> list) : DoubleLinkedList() {
		for (auto arg : list) {
			push_back(arg);
		}
	}

	//allocate
	DoubleLinkedList(size_t size) : DoubleLinkedList(), size(size) {
		for (size_t i = 0; i < size; i++) {
			ENTRY->prev = ENTRY->prev->foll = new cell(ENTRY->prev, ENTRY); //from push_back
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
		cell *data;
		DoubleLinkedList<T> &list;
		iterator(DoubleLinkedList<T> &list, cell *data) : list(list), data(data) {}
	public:
		
		iterator & operator++() {
			data = data->foll;
			return *this;
		}
		iterator operator++(int) {
			iterator _this = *this;
			this->operator++();
			return _this;
		}

		iterator & operator--() {
			data = data->prev;
			return *this;
		}
		iterator & operator--(int) {
			return this->operator--();
		}

		int operator-(const iterator iter) {
			int i = 0;
			for (; this->operator!=(iter); iter++);
			return (i < size) ? i : size - i - 1;
		}

		iterator operator+(const size_t num) const { iterator i = *this; for (size_t j = 0; j < num; j++) i++; return i; }

		iterator operator-(const size_t num) const { iterator i = *this; for (size_t j = 0; j < num; j++) i--; return i; }

		T &operator*() { return data->val; }
		bool operator!=(const iterator & opp) const { return data != opp.data; }

		friend iterator DoubleLinkedList<T>::begin();
		friend iterator DoubleLinkedList<T>::end();
		friend void DoubleLinkedList<T>::insert(T val, iterator i);
		friend T DoubleLinkedList<T>::erase(iterator i);

	};

	iterator begin() { return iterator(*this, ENTRY->foll); }
	iterator end() { return iterator(*this, ENTRY); }
	void insert(T val, iterator i);
	T erase(iterator i);

	void sort();

	template<class T>
	friend std::ostream & operator<<(std::ostream & out, const DoubleLinkedList<T> &list);

private:
	


	class cell {
	public:
		cell *prev = NULL, *foll = NULL;
		T val;
		cell(cell *prev = NULL, cell *foll = NULL) : prev(prev), foll(foll) {}
		cell(cell *prev, cell *foll, T val) : prev(prev), foll(foll), val(val) {}
	};


	cell * initEntry() {
		cell *Entry = new cell;
		Entry->prev = Entry->foll = Entry;
		return Entry;
	}

	T pop_cell(cell *pop);

	cell *iterate_front(size_t num_front);
	cell *iterate_back(size_t num_back);

	cell *find_cell(size_t num);

	void merge_sort(iterator begin, iterator end, size_t size, T*buffer);
	void merge(iterator start, iterator sep, iterator end, size_t size, T*buffer);
};








template<class T>
inline void DoubleLinkedList<T>::push_back(T val)
{
	ENTRY->prev = ENTRY->prev->foll = new cell(ENTRY->prev, ENTRY, val); //ÀÀÀÀÀ€€€€€€€€€€€∆∆∆∆∆∆∆∆∆∆∆∆∆€€€€€€€€€€€€€€€€€€
	size++;
}

template<class T>
inline void DoubleLinkedList<T>::push_front(T val)
{
	ENTRY->foll = ENTRY->foll->prev = new cell(ENTRY, ENTRY->foll, val);
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
	neighbour->prev = neighbour->prev->foll = new cell(neighbour->prev, neighbour, val);
	size++;
}

template<class T>
inline T DoubleLinkedList<T>::erase(size_t position)
{
	return pop_cell(find_cell(position));
}

template<class T>
inline void DoubleLinkedList<T>::insert(T val, iterator i)
{
	auto neighbour = i.data;
	neighbour->prev = neighbour->prev->foll = new cell(neighbour->prev, neighbour, val);
	size++;
}

template<class T>
inline T DoubleLinkedList<T>::erase(iterator i)
{
	return pop_cell(i.data);
}

template<class T>
inline void DoubleLinkedList<T>::sort()
{
	T *buffer = new T[size];
	merge_sort(begin(), end(), size, buffer);
	delete[] buffer;
}

template<class T>
inline T DoubleLinkedList<T>::pop_cell(cell* pop)
{
	pop->prev->foll = pop->foll;  //link
	pop->foll->prev = pop->prev;  //link
	T val = pop->val;             
	delete pop;
	size--;
	return val;
}

template<class T>
inline typename DoubleLinkedList<T>::cell* DoubleLinkedList<T>::iterate_front(size_t num_front)
{
	cell *p = ENTRY->foll;
	for (size_t i = 0; i != num_front; i++) p = p->foll;
	return p;
}

template<class T>
inline typename DoubleLinkedList<T>::cell* DoubleLinkedList<T>::iterate_back(size_t num_back)
{
	cell *p = ENTRY->prev;
	for (size_t i = 0; i != num_back; i++) p = p->prev;
	return p;
}

template<class T>
inline typename DoubleLinkedList<T>::cell* DoubleLinkedList<T>::find_cell(size_t num)
{
	if (num >= size) throw size_t(size);
	if (num < (size >> 1))
		return iterate_front(num);
	else
		return iterate_back(size - 1 - num);
}


template<class T>
void DoubleLinkedList<T>::merge_sort(iterator begin, iterator end, size_t size, T*buffer)
{
	if (size == 1) return;

	size_t lft_sz = size >> 1;
	size_t rght_sz = size - lft_sz;
	auto sep = begin + lft_sz;
	merge_sort(begin, sep, lft_sz, buffer);
	merge_sort(sep, end, rght_sz, buffer);

	merge(begin, sep, end, size, buffer);

}

template<class T>
void DoubleLinkedList<T>::merge(
	typename DoubleLinkedList<T>::iterator start,
	typename DoubleLinkedList<T>::iterator sep, 
	typename DoubleLinkedList<T>::iterator end,
						 size_t size, T*buffer) 
{
	{
		T *iter = buffer, *buffer_end = buffer + size;
		auto li = start, ri = sep;
		for (; iter != buffer_end; iter++)
			if (li != sep)		    
				if (ri != end)		    
					if (*ri < *li) 
						{ *iter = *ri; ri++; }

					else { *iter = *li; li++; }
				else { *iter = *li; li++; }
			else { *iter = *ri; ri++; }
	
 	}
	{
		T *iter = buffer, *buffer_end = buffer + size;
		for (; iter != buffer_end; iter++, start++) *start = *iter;
	}
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
