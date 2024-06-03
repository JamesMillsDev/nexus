#pragma once

#include <cassert>
#include <iostream>
#include <list>

#include <Nexus/Collections/HashEntry.h>
#include <Nexus/Collections/HashFunctions.h>
#include <Nexus/Utility/Maths.h>

using std::list;

namespace Nexus
{
	template<typename DATA, uint(*HASH_FUNCTION)(const char*) = BKDR, uint GROW_SIZE = 128, float LOAD_THRESHOLD = .8f>
	class HashMap
	{
	public:
		HashMap();
		~HashMap();

		HashMap(const HashMap&) = delete;
		HashMap(HashMap&&) = delete;

	public:
		ullong GetAll(const char* _key, list<DATA*>& _values);

		void Insert(const char* _key, DATA* _value);
		bool Contains(const char* _key) const;

		void RemoveFirst(const char* _key);
		void RemoveAll(const char* _key);

		void Clear();
		[[nodiscard]] bool Empty() const;

		[[nodiscard]] uint Count() const;
		[[nodiscard]] uint Size() const;
		[[nodiscard]] float LoadFactor() const;

	public:
		DATA* operator[](const char* _key);
		const DATA* operator[](const char* _key) const;

		HashMap& operator=(const HashMap&) = delete;
		HashMap& operator=(HashMap&&) = delete;

	private:
		HashEntry<DATA>** m_entries;
		uint m_entryCount;
		uint m_maxArraySize;

	private:
		void Expand();

	};

	template <typename DATA, uint(*HASH_FUNCTION)(const char*), uint GROW_SIZE, float LOAD_THRESHOLD>
	HashMap<DATA, HASH_FUNCTION, GROW_SIZE, LOAD_THRESHOLD>::HashMap()
		: m_entries{ new HashEntry<DATA>*[GROW_SIZE] }, m_entryCount{ 0 }, m_maxArraySize{ GROW_SIZE }
	{
		for (uint i = 0; i < m_maxArraySize; ++i)
			m_entries[i] = nullptr;
	}

	template <typename DATA, uint(*HASH_FUNCTION)(const char*), uint GROW_SIZE, float LOAD_THRESHOLD>
	HashMap<DATA, HASH_FUNCTION, GROW_SIZE, LOAD_THRESHOLD>::~HashMap()
	{
		Clear();
		delete[] m_entries;
	}

	template <typename DATA, uint(*HASH_FUNCTION)(const char*), uint GROW_SIZE, float LOAD_THRESHOLD>
	ullong HashMap<DATA, HASH_FUNCTION, GROW_SIZE, LOAD_THRESHOLD>::GetAll(const char* _key, list<DATA*>& _values)
	{
		_values.clear();

		// Calculates the array index this key would be stored in
		const uint index = HASH_FUNCTION(_key) % m_maxArraySize;

		HashEntry<DATA>* entry = m_entries[index];
		while (entry != nullptr)
		{
			_values.emplace_back(entry->Value());
			entry = entry->next;
		}

		return _values.size();
	}

	template <typename DATA, uint(*HASH_FUNCTION)(const char*), uint GROW_SIZE, float LOAD_THRESHOLD>
	void HashMap<DATA, HASH_FUNCTION, GROW_SIZE, LOAD_THRESHOLD>::Insert(const char* _key, DATA* _value)
	{
		if (_value == nullptr)
		{
			std::cerr << "Tried adding empty value to map. This is not supported!\n";
			return;
		}

		// Create a new HashEntry and get the hash index
		HashEntry<DATA>* newEntry = new HashEntry<DATA>(_key, _value);
		const uint index = HASH_FUNCTION(_key) % m_maxArraySize;

		// Add the value into the array, and assign the new elements next to the current
		newEntry->next = m_entries[index];
		m_entries[index] = newEntry;
		m_entryCount++;

		// If the load factor of the map has surpassed the threshold, resize
		if (LoadFactor() > LOAD_THRESHOLD)
			Expand();
	}

	template <typename DATA, uint(*HASH_FUNCTION)(const char*), uint GROW_SIZE, float LOAD_THRESHOLD>
	bool HashMap<DATA, HASH_FUNCTION, GROW_SIZE, LOAD_THRESHOLD>::Contains(const char* _key) const
	{
		// Calculates the array index this key would be stored in
		const uint index = HASH_FUNCTION(_key) % m_maxArraySize;

		// Get the first entry in this index
		HashEntry<DATA>* value = m_entries[index];
		// Whilst this entry is not the one with the correct key, move to the next one
		while (value != nullptr && strcmp(value->Key(), _key) != 0)
			value = value->next;

		// Return whether we actually had a value
		return value != nullptr;
	}

	template <typename DATA, uint(*HASH_FUNCTION)(const char*), uint GROW_SIZE, float LOAD_THRESHOLD>
	void HashMap<DATA, HASH_FUNCTION, GROW_SIZE, LOAD_THRESHOLD>::RemoveFirst(const char* _key)
	{
		// Calculates the array index this key would be stored in
		const uint index = HASH_FUNCTION(_key) % m_maxArraySize;

		// Is there a valid entry at this location
		if (m_entries[index] != nullptr)
		{
			// Get the next entry at this index
			HashEntry<DATA>* next = m_entries[index]->next;

			// Delete the current entry and reassign to the next one
			delete m_entries[index];
			m_entries[index] = next;

			// Decrement the entry count
			m_entryCount--;
		}
	}

	template <typename DATA, uint(*HASH_FUNCTION)(const char*), uint GROW_SIZE, float LOAD_THRESHOLD>
	void HashMap<DATA, HASH_FUNCTION, GROW_SIZE, LOAD_THRESHOLD>::RemoveAll(const char* _key)
	{
		// Calculates the array index this key would be stored in
		const uint index = HASH_FUNCTION(_key) % m_maxArraySize;

		// Is there a valid entry at this location
		while (m_entries[index] != nullptr)
		{
			// Get the next entry at this index
			HashEntry<DATA>* next = m_entries[index]->next;

			// Delete the current entry and reassign to the next one
			delete m_entries[index];
			m_entries[index] = next;

			// Decrement the entry count
			m_entryCount--;
		}
	}

	template <typename DATA, uint(*HASH_FUNCTION)(const char*), uint GROW_SIZE, float LOAD_THRESHOLD>
	void HashMap<DATA, HASH_FUNCTION, GROW_SIZE, LOAD_THRESHOLD>::Clear()
	{
		for (uint i = 0; i < m_maxArraySize; ++i)
		{
			// Is there a valid entry at this location
			while (m_entries[i] != nullptr)
			{
				// Get the next entry at this index
				HashEntry<DATA>* next = m_entries[i]->next;

				// Delete the current entry and reassign to the next one
				delete m_entries[i];
				m_entries[i] = next;

				// Decrement the entry count
				m_entryCount--;
			}
		}
	}

	template <typename DATA, uint(*HASH_FUNCTION)(const char*), uint GROW_SIZE, float LOAD_THRESHOLD>
	bool HashMap<DATA, HASH_FUNCTION, GROW_SIZE, LOAD_THRESHOLD>::Empty() const
	{
		return m_entryCount == 0;
	}

	template <typename DATA, uint(*HASH_FUNCTION)(const char*), uint GROW_SIZE, float LOAD_THRESHOLD>
	uint HashMap<DATA, HASH_FUNCTION, GROW_SIZE, LOAD_THRESHOLD>::Count() const
	{
		return m_entryCount;
	}

	template <typename DATA, uint(*HASH_FUNCTION)(const char*), uint GROW_SIZE, float LOAD_THRESHOLD>
	uint HashMap<DATA, HASH_FUNCTION, GROW_SIZE, LOAD_THRESHOLD>::Size() const
	{
		return m_maxArraySize;
	}

	template <typename DATA, uint(*HASH_FUNCTION)(const char*), uint GROW_SIZE, float LOAD_THRESHOLD>
	float HashMap<DATA, HASH_FUNCTION, GROW_SIZE, LOAD_THRESHOLD>::LoadFactor() const
	{
		return static_cast<float>(m_entryCount) / static_cast<float>(m_maxArraySize);
	}

	template <typename DATA, uint(*HASH_FUNCTION)(const char*), uint GROW_SIZE, float LOAD_THRESHOLD>
	DATA* HashMap<DATA, HASH_FUNCTION, GROW_SIZE, LOAD_THRESHOLD>::operator[](const char* _key)
	{
		// Calculates the array index this key would be stored in
		const uint index = HASH_FUNCTION(_key) % m_maxArraySize;
		assert(m_entries[index] != nullptr);

		// Get the first entry in this index
		HashEntry<DATA>* value = m_entries[index];
		// Whilst this entry is not the one with the correct key, move to the next one
		while (value != nullptr && strcmp(value->Key(), _key) != 0)
			value = value->next;

		// Validate that we did in fact find a valid entry and return its value
		assert(value != nullptr);
		return value->Value();
	}

	template <typename DATA, uint(*HASH_FUNCTION)(const char*), uint GROW_SIZE, float LOAD_THRESHOLD>
	const DATA* HashMap<DATA, HASH_FUNCTION, GROW_SIZE, LOAD_THRESHOLD>::operator[](const char* _key) const
	{
		// Calculates the array index this key would be stored in
		const uint index = HASH_FUNCTION(_key) % m_maxArraySize;
		assert(m_entries[index] != nullptr);

		// Get the first entry in this index
		HashEntry<DATA>* value = m_entries[index];
		// Whilst this entry is not the one with the correct key, move to the next one
		while (value != nullptr && strcmp(value->Key(), _key) != 0)
			value = value->next;

		// Validate that we did in fact find a valid entry and return its value
		assert(value != nullptr);
		return value->Value();
	}

	template <typename DATA, uint(*HASH_FUNCTION)(const char*), uint GROW_SIZE, float LOAD_THRESHOLD>
	void HashMap<DATA, HASH_FUNCTION, GROW_SIZE, LOAD_THRESHOLD>::Expand()
	{
		// Calculate new size and generate new array pointer
		const uint newSize = m_maxArraySize + GROW_SIZE;
		HashEntry<DATA>** newTable = new HashEntry<DATA>*[newSize];

		// Initialise new array to all nullptr
		for (uint i = 0; i < newSize; ++i)
			newTable[i] = nullptr;

		// Iterate over the old entry array
		for (uint i = 0; i < m_maxArraySize; ++i)
		{
			HashEntry<DATA>* entry = m_entries[i];

			// Iterate over all items in this entry
			while (entry != nullptr)
			{
				// Get the next entry and the new hash index
				HashEntry<DATA>* next = entry->next;
				const uint index = HASH_FUNCTION(entry->Key()) % newSize;

				// Set up the entry for this index and the next entry
				entry->next = newTable[index];
				newTable[index] = entry;

				entry = next;
			}
		}

		// Delete old array and override with new one
		delete[] m_entries;
		m_entries = newTable;
		m_maxArraySize = newSize;
	}
}
