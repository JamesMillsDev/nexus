#pragma once

#include <cstring>

namespace Nexus
{
	template<typename DATA>
	class HashEntry
	{
	public:
		HashEntry* next;

	public:
		explicit HashEntry(const char* _key, DATA* _value);
		~HashEntry();

		HashEntry(const HashEntry&) = delete;
		HashEntry(HashEntry&&) = delete;

	public:
		[[nodiscard]] const char* Key() const;
		const DATA* Value() const;
		DATA* Value();

	public:
		HashEntry& operator=(const HashEntry&) = delete;
		HashEntry& operator=(HashEntry&&) = delete;

	private:
		char* m_key;
		DATA* m_value;

	};

	template <typename DATA>
	HashEntry<DATA>::HashEntry(const char* _key, DATA* _value)
		: next{ nullptr }, m_key{ new char[strlen(_key)] }, m_value{ _value }
	{
		strcpy_s(m_key, strlen(_key) + 1, _key);
	}

	template <typename DATA>
	HashEntry<DATA>::~HashEntry()
	{
		delete m_value;
		m_value = nullptr;

		delete[] m_key;
		m_key = nullptr;
	}

	template <typename DATA>
	const char* HashEntry<DATA>::Key() const
	{
		return m_key;
	}

	template <typename DATA>
	const DATA* HashEntry<DATA>::Value() const
	{
		return m_value;
	}

	template <typename DATA>
	DATA* HashEntry<DATA>::Value()
	{
		return m_value;
	}
}
