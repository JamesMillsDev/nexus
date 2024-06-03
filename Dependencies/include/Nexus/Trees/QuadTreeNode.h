#pragma once

#include <Nexus/Trees/QuadTreeData.h>

#include <vector>
#include <queue>

#include <typeinfo>

using std::vector;
using std::queue;

constexpr uint QUAD_TREE_LEAFS = 4;

namespace Nexus
{
	template<typename DATA>
	class QuadTreeNode
	{
	public:
		static int maxDepth;
		static int maxObjectsPerNode;

		vector<QuadTreeNode<DATA>*> children;
		vector<QuadTreeData<DATA>*> contents;
		int currentDepth;
		Bounds2D bounds;

	public:
		explicit QuadTreeNode(Bounds2D _bounds);
		~QuadTreeNode();

		QuadTreeNode(const QuadTreeNode&) = delete;
		QuadTreeNode(QuadTreeNode&&) = delete;

	public:
		bool IsLeaf();
		int NumObjects();

		void Insert(QuadTreeData<DATA>* _data);
		void Remove(QuadTreeData<DATA>* _data);
		void Update(QuadTreeData<DATA>* _data);

		vector<QuadTreeData<DATA>*> Query(const Bounds2D& _area);

	public:
		QuadTreeNode& operator=(const QuadTreeNode&) = delete;
		QuadTreeNode& operator=(QuadTreeNode&&) = delete;

	private:
		static Point2D GetMin(const Bounds2D& _rect);
		static Point2D GetMax(const Bounds2D& _rect);
		static Bounds2D FromMinMax(const Point2D& _min, const Point2D& _max);

	private:
		void Shake();
		void Split();
		void Reset();
	};

	template<typename DATA>
	int QuadTreeNode<DATA>::maxDepth = 5;
	template<typename DATA>
	int QuadTreeNode<DATA>::maxObjectsPerNode = 15;

	template <typename DATA>
	QuadTreeNode<DATA>::QuadTreeNode(Bounds2D _bounds)
		: currentDepth{ 0 }, bounds{ std::move(_bounds) }
	{

	}

	template <typename DATA>
	QuadTreeNode<DATA>::~QuadTreeNode()
	{
		for (auto& child : children)
			delete child;

		for (auto& data : contents)
			delete data;

		children.clear();
		contents.clear();
	}

	template <typename DATA>
	bool QuadTreeNode<DATA>::IsLeaf()
	{
		return children.size() == 0;
	}

	template <typename DATA>
	int QuadTreeNode<DATA>::NumObjects()
	{
		Reset();

		int objectCount = contents.size();

		for (int i = 0; i < contents.size(); ++i)
			contents[i]->visited = false;

		queue<QuadTreeNode<DATA>*> process;
		process.push(this);

		while (process.size() > 0)
		{
			QuadTreeNode* processing = process.back();

			if (!processing->IsLeaf())
			{
				for (int i = 0; i < processing->children.size(); ++i)
					process.push(processing->children[i]);
			}
			else
			{
				for (int i = 0; i < processing->contents.size(); ++i)
				{
					if (!processing->contents[i]->visited)
					{
						++objectCount;
						processing->contents[i]->visited = true;
					}
				}
			}

			process.pop();
		}

		Reset();
		return objectCount;
	}

	template <typename DATA>
	void QuadTreeNode<DATA>::Insert(QuadTreeData<DATA>* _data)
	{
		if (!_data->bounds.Overlaps(bounds))
			return;

		if (IsLeaf() && contents.size() + 1 > maxObjectsPerNode)
			Split();

		if (IsLeaf())
		{
			contents.push_back(_data);
		}
		else
		{
			for (auto& child : children)
				child->Insert(_data);
		}
	}

	template <typename DATA>
	void QuadTreeNode<DATA>::Remove(QuadTreeData<DATA>* _data)
	{
		if (IsLeaf())
		{
			int removeIndex = -1;

			for (int i = 0; i < contents.size(); ++i)
			{
				if (contents[i]->data == _data->data)
				{
					removeIndex = i;
					break;
				}
			}

			if (removeIndex != -1)
				contents.erase(contents.begin() + removeIndex);
		}
		else
		{
			for (int i = 0; i < contents.size(); ++i)
				children[i]->Remove(_data);
		}

		Shake();
	}

	template <typename DATA>
	void QuadTreeNode<DATA>::Update(QuadTreeData<DATA>* _data)
	{
		Remove(_data);
		Insert(_data);
	}

	template <typename DATA>
	vector<QuadTreeData<DATA>*> QuadTreeNode<DATA>::Query(const Bounds2D& _area)
	{
		vector<QuadTreeData*> result;

		if (!_area.Overlaps(bounds))
			return result;

		if (IsLeaf())
		{
			for (int i = 0, size = contents.size(); i < size; ++i)
			{
				if (contents[i]->bounds.Overlaps(_area))
					result.push_back(contents[i]);
			}
		}
		else
		{
			for (int i = 0, size = children.size(); i < size; ++i)
			{
				vector<QuadTreeData*> recurse = children[i]->Query(_area);
				if (recurse.size() > 0)
					result.insert(result.end(), recurse.begin(), recurse.end());
			}
		}
		return result;
	}

	template <typename DATA>
	Point2D QuadTreeNode<DATA>::GetMin(const Bounds2D& _rect)
	{
		return _rect.pos;
	}

	template <typename DATA>
	Point2D QuadTreeNode<DATA>::GetMax(const Bounds2D& _rect)
	{
		return _rect.pos + _rect.size;
	}

	template <typename DATA>
	Bounds2D QuadTreeNode<DATA>::FromMinMax(const Point2D& _min, const Point2D& _max)
	{
		return { _min.x, _min.y, _max.x - _min.x, _max.y - _min.y };
	}

	template <typename DATA>
	void QuadTreeNode<DATA>::Shake()
	{
		if (!IsLeaf())
		{
			const int numObjects = NumObjects();
			if (numObjects == 0)
			{
				children.clear();
			}
			else if (numObjects < maxObjectsPerNode)
			{
				queue<QuadTreeNode<DATA>*> process;
				process.push(this);
				while (process.size() > 0)
				{
					QuadTreeNode<DATA>* processing = process.back();
					if (!processing->IsLeaf())
					{
						for (int i = 0; i < processing->children.size(); ++i)
							process.push(processing->children[i]);
					}
					else
					{
						contents.insert(contents.end(), processing->contents.begin(), processing->contents.end());
					}
					process.pop();
				}

				children.clear();
			}
		}
	}

	template <typename DATA>
	void QuadTreeNode<DATA>::Split()
	{
		if (currentDepth + 1 >= maxDepth)
			return;

		const Point2D min = GetMin(bounds);
		const Point2D max = GetMax(bounds);

		const Point2D center = min + (max - min) * .5f;

		Bounds2D childBounds[] =
		{
			FromMinMax({ min.x, min.y }, { center.x, center.y }),
			FromMinMax({ center.x, min.y }, { max.x, center.y }),
			FromMinMax({ center.x, center.y }, { max.x, max.y }),
			FromMinMax({ min.x, center.y }, { center.x, max.y })
		};

		for (int i = 0; i < QUAD_TREE_LEAFS; ++i)
		{
			children.push_back(new QuadTreeNode<DATA>(childBounds[i]));
			children[i]->currentDepth = currentDepth + 1;
		}

		vector<QuadTreeData<DATA>*> data = contents;

		while (data.size() > 0)
		{
			for (int i = 0; i < children.size(); i++)
			{
				if (CheckCollisionRecs(children[i]->bounds, data[0]->bounds))
				{
					children[i]->Insert(data[0]);
					break;
				}
			}

			data.erase(data.begin());
		}

		contents.clear();
	}

	template <typename DATA>
	void QuadTreeNode<DATA>::Reset()
	{
		if (IsLeaf())
		{
			for (int i = 0; i < contents.size(); ++i)
				contents[i]->visited = false;
		}
		else
		{
			for (int i = 0; i < children.size(); ++i)
				children[i]->Reset();
		}
	}
}
