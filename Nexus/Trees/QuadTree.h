#pragma once

#include "QuadTreeNode.h"

namespace Nexus
{
	template<typename DATA>
	class QuadTree
	{
	public:
		explicit QuadTree(const Bounds2D& _bounds);
		~QuadTree();

		QuadTree(const QuadTree&) = delete;
		QuadTree(QuadTree&&) = delete;

	public:
		void Insert(QuadTreeData<DATA>* _data);
		void Remove(QuadTreeData<DATA>* _data);
		void Update(QuadTreeData<DATA>* _data);

		vector<QuadTreeData<DATA>*> Query(const Bounds2D& _area);

	public:
		QuadTree& operator=(const QuadTree&) = delete;
		QuadTree& operator=(QuadTree&&) = delete;

	private:
		QuadTreeNode<DATA>* m_root;

	};

	template<typename DATA>
	QuadTree<DATA>::QuadTree(const Bounds2D& _bounds)
	{
		m_root = new QuadTreeNode<DATA>(_bounds);
	}

	template<typename DATA>
	QuadTree<DATA>::~QuadTree()
	{
		if (m_root != nullptr)
		{
			delete m_root;
			m_root = nullptr;
		}
	}

	template<typename DATA>
	void QuadTree<DATA>::Insert(QuadTreeData<DATA>* _data)
	{
		if (m_root != nullptr)
			m_root->Insert(_data);
	}

	template<typename DATA>
	void QuadTree<DATA>::Remove(QuadTreeData<DATA>* _data)
	{
		if (m_root != nullptr)
			m_root->Remove(_data);
	}

	template<typename DATA>
	void QuadTree<DATA>::Update(QuadTreeData<DATA>* _data)
	{
		if (m_root != nullptr)
			m_root->Update(_data);
	}

	template<typename DATA>
	vector<QuadTreeData<DATA>*> QuadTree<DATA>::Query(const Bounds2D& _area)
	{
		vector<QuadTreeData<DATA>*> data;

		if (m_root != nullptr)
			data = m_root->Query(_area);

		return data;
	}
}
