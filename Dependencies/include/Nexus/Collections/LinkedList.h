#pragma once

#include <initializer_list>

#include <Nexus/Utility/Maths.h>

using std::initializer_list;

namespace Nexus
{
	template<typename T>
	class LinkedList
	{
	public:
		struct Node
		{
			T value;
			Node* next = nullptr;
			Node* prev = nullptr;

		public:
			explicit Node(const T& _value);

		public:
			T operator*();

		};

		struct Iterator
		{
		public:
			Node* node = nullptr;

		public:
			Iterator();
			explicit Iterator(Node* _node);

		public:
			Iterator& Next();
			Iterator& Prev();

		public:
			//Increment / decrement operators
			Iterator& operator++();
			Iterator& operator--();

			//Equality 
			bool operator==(const Iterator& _rhs);
			bool operator!=(const Iterator& _rhs);

			//Iterator Getters
			Iterator& operator+(int _shiftAmount);
			Iterator& operator-(int _shiftAmount);

			//Dereference operators
			T& operator*();
			T& operator->();

		};

	public:
		LinkedList(initializer_list<T> _values);
		LinkedList(const LinkedList<T>& _other);
		LinkedList(LinkedList<T>&&) = delete;

		~LinkedList();

	public:
		void PushBack(T _value);
		void PopBack();

		void PushFront(T _value);
		void PopFront();

		void Clear();

		//return the iterator that would be in this location after removing
		Iterator Remove(Iterator _iter);

		Iterator RemoveAt(ullong _index);

		//find the first iterator / node that contains this value
		Iterator Find(T _value);

		void Insert(Iterator _iter, const T& _value);

		//return the value at this index - loop through this many times and return the item
		T At(ullong _index);
		T At(ullong _index) const;

		//check if any nodes contain this value
		bool Contains(const T& _value);

		//implement a sorting algo, don't use bubble
		void Sort(int(*_comparer)(Iterator, Iterator));

		//find the index of this value, otherwise return -1
		int IndexOf(const T& _value);

		//Is this list completely Empty
		bool IsEmpty();

		//Amount of items in the list
		[[nodiscard]] ullong size() const;

		Iterator begin();
		Iterator end();

		Node* Front();
		Node* Back();

	public:
		LinkedList& operator=(const LinkedList<T>& _other);
		LinkedList& operator=(LinkedList<T>&& _other) = delete;

		bool operator==(const LinkedList& _other) const;
		bool operator!=(const LinkedList& _other) const;

		T operator[](ullong _index);
		T operator[](ullong _index) const;

	private:
		Node* m_first = nullptr;
		Node* m_last = nullptr;

		ullong m_count = 0;

	};

	template <typename T>
	LinkedList<T>::Node::Node(const T& _value)
		: value{ _value }
	{

	}

	template <typename T>
	T LinkedList<T>::Node::operator*()
	{
		return value;
	}

	template <typename T>
	LinkedList<T>::Iterator::Iterator()
		: node{ nullptr }
	{

	}

	template <typename T>
	LinkedList<T>::Iterator::Iterator(Node* _node)
		: node{ _node }
	{

	}

	template <typename T>
	typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::Next()
	{
		if (node != nullptr)
			node = node->next;

		return *this;
	}

	template <typename T>
	typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::Prev()
	{
		if (node != nullptr)
			node = node->prev;

		return *this;
	}

	template <typename T>
	typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++()
	{
		return Next();
	}

	template <typename T>
	typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator--()
	{
		return Prev();
	}

	template <typename T>
	bool LinkedList<T>::Iterator::operator==(const Iterator& _rhs)
	{
		return node == _rhs.node;
	}

	template <typename T>
	bool LinkedList<T>::Iterator::operator!=(const Iterator& _rhs)
	{
		return node != _rhs.node;
	}

	template <typename T>
	typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator+(const int _shiftAmount)
	{
		Iterator iter = *this;
		for (int i = 0; i < _shiftAmount; i++)
		{
			iter = iter.Next();

			//check if ended
			if (iter == m_last)
				return iter;
		}

		return iter;
	}

	template <typename T>
	typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator-(const int _shiftAmount)
	{
		Iterator iter = *this;
		for (int i = _shiftAmount; i > 0; i--)
		{
			iter = iter.Prev();

			//check if we are outside the bounds of the list
			if (iter == m_first)
				return iter;
		}

		return iter;
	}

	template <typename T>
	T& LinkedList<T>::Iterator::operator*()
	{
		return node->value;
	}

	template <typename T>
	T& LinkedList<T>::Iterator::operator->()
	{
		return &node->value;
	}

	template <typename T>
	LinkedList<T>::LinkedList(initializer_list<T> _values)
	{
		for (auto iter = _values.begin(); iter != _values.end(); ++iter)
			PushBack(*iter);
	}

	template <typename T>
	LinkedList<T>::LinkedList(const LinkedList<T>& _other)
	{
	}

	template <typename T>
	LinkedList<T>::~LinkedList()
	{
		Clear();
	}

	template <typename T>
	void LinkedList<T>::PushBack(T _value)
	{
		Node* node = new Node(_value);
		m_count++;
		if (IsEmpty())
		{
			m_first = node;
			m_last = node;
		}
		else
		{
			m_last->next = node;
			node->prev = m_last;
			m_last = node;
		}
	}

	template <typename T>
	void LinkedList<T>::PopBack()
	{
		if (IsEmpty())
			return;

		const Node* last = m_last;
		m_last = m_last->prev;

		if (m_last != nullptr)
			m_last->next = nullptr;

		if (m_last == nullptr)
			m_first = nullptr;

		delete last;
		m_count--;
	}

	template <typename T>
	void LinkedList<T>::PushFront(T _value)
	{
		Node* front = new Node(_value);
		m_count++;

		if (IsEmpty())
		{
			m_first = front;
			m_last = front;
		}
		else
		{
			m_first->prev = front;
			front->next = m_first;
			m_first = front;
		}
	}

	template <typename T>
	void LinkedList<T>::PopFront()
	{
		if (IsEmpty())
			return;

		const Node* first = m_first;
		m_first = m_first->next;

		if (m_first != nullptr)
			m_first->prev = nullptr;

		if (m_last == nullptr)
			m_first = nullptr;

		delete first;
		m_count--;
	}

	template <typename T>
	void LinkedList<T>::Clear()
	{
		for (ullong i = 0; i < m_count; i++)
			PopBack();

		PopBack();
	}

	template <typename T>
	// ReSharper disable once CppMemberFunctionMayBeStatic
	typename LinkedList<T>::Iterator LinkedList<T>::Remove(Iterator _iter)
	{
		_iter.node->next->prev = _iter.node->prev;
		_iter.node->prev->next = _iter.node->next;
		_iter.node->prev = nullptr;
		_iter.node->next = nullptr;

		delete _iter.node;
		_iter.node = nullptr;

		return _iter;
	}

	template <typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::RemoveAt(const ullong _index)
	{
		Iterator iter = begin();
		for (ullong i = 0; i < _index; i++)
			++iter;

		Remove(iter);
		return iter;
	}

	template <typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::Find(T _value)
	{
		//iterate through all iterators
		//when 
		for (Iterator iter = begin(); iter != end(); ++iter)
		{
			if (iter.node->value == _value)
				return iter;
		}

		return end();
	}

	template <typename T>
	void LinkedList<T>::Insert(Iterator _iter, const T& _value)
	{
		Node* node = new Node(_value);

		node->next = _iter.node->next;
		node->prev = _iter.node;
		node->next->prev = node;
		_iter.node->next = node;
	}

	template <typename T>
	T LinkedList<T>::At(const ullong _index)
	{
		Iterator iter = begin();
		for (ullong i = 0; i < _index; i++)
			iter.Next();

		return iter.node->value;
	}

	template <typename T>
	T LinkedList<T>::At(const ullong _index) const
	{
		Iterator iter = begin();
		for (ullong i = 0; i < _index; i++)
			iter.Next();

		return iter.node->value;
	}

	template <typename T>
	bool LinkedList<T>::Contains(const T& _value)
	{
		//Iterate through all values and return true if any values = _value, else return false
		for (Iterator i = begin(); i != end(); ++i)
		{
			if (i.node->value == _value)
				return true;
		}

		return false;
	}

	template <typename T>
	void LinkedList<T>::Sort(int(*_comparer)(Iterator, Iterator))
	{
		Node* temp = new Node(0);
		for (Iterator i = begin(); i != end().Next(); ++i)
		{
			for (Iterator j = begin(); j != end().Next(); ++j)
			{
				if (_comparer(i, j))
				{
					temp->value = i.node->value;
					i.node->value = j.node->value;
					j.node->value = temp->value;
				}
			}
		}

		delete temp;
		temp = nullptr;
	}

	template <typename T>
	int LinkedList<T>::IndexOf(const T& _value)
	{
		//iterate through list, when iter = value return iter
		int count = 0;
		for (Iterator iter = begin(); iter != end(); ++iter)
		{
			if (iter.node->value == _value)
				return count;

			count++;
		}

		return -1;
	}

	template <typename T>
	bool LinkedList<T>::IsEmpty()
	{
		return m_first == nullptr && m_last == nullptr;
	}

	template <typename T>
	ullong LinkedList<T>::size() const
	{
		return m_count;
	}

	template <typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::begin()
	{
		return Iterator(m_first);
	}

	template <typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::end()
	{
		return Iterator();
	}

	template <typename T>
	typename LinkedList<T>::Node* LinkedList<T>::Front()
	{
		return m_first;
	}

	template <typename T>
	typename LinkedList<T>::Node* LinkedList<T>::Back()
	{
		return m_last;
	}

	template <typename T>
	LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& _other)  // NOLINT(bugprone-unhandled-self-assignment) <- It is, so let's ignore it
	{
		if (*this == _other)
			return *this;

		Clear();
		m_count = _other.m_count;

		for (auto& val : _other)
			PushBack(val);

		return *this;
	}

	template <typename T>
	bool LinkedList<T>::operator==(const LinkedList& _other) const
	{
		if (m_count != _other.m_count)
			return false;

		bool compare = true;

		for(uint i = 0; i < m_count; ++i)
			compare &= At(i) == _other.At(i);

		return compare;
	}

	template <typename T>
	bool LinkedList<T>::operator!=(const LinkedList& _other) const
	{
		return !(*this == _other);
	}

	template <typename T>
	T LinkedList<T>::operator[](const ullong _index)
	{
		return At(_index);
	}

	template <typename T>
	T LinkedList<T>::operator[](const ullong _index) const
	{
		return At(_index);
	}
}
