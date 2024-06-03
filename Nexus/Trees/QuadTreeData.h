#pragma once

#include <algorithm>
#include <Nexus/Utility/Bounds2D.h>

namespace Nexus
{
	/**
	 * A container for data that is held inside each QuadTreeNode.
	 * @tparam DATA The raw data type that is held within this container
	 */
	template<typename DATA>
	struct QuadTreeData
	{
	public:
		/* The flag used to detect if this data has been looked at during Counting operations. */
		bool visited;
		/* The raw data contained in this object. */
		DATA* data;
		/* The bounding box of this quad tree data. */
		Bounds2D bounds;

	public:
		/**
		 * The main constructor to store the data.
		 * @param _data The data to be stored in the node.
		 * @param _bounds The bounding box of this node.
		 */
		explicit QuadTreeData(DATA* _data, Bounds2D _bounds);
		~QuadTreeData();

		QuadTreeData() = delete;
		QuadTreeData(const QuadTreeData&) = delete;
		QuadTreeData(QuadTreeData&&) = delete;

	public:
		QuadTreeData& operator=(const QuadTreeData&) = delete;
		QuadTreeData& operator=(QuadTreeData&&) = delete;

	};

	template <typename DATA>
	QuadTreeData<DATA>::QuadTreeData(DATA* _data, Bounds2D _bounds)
		: visited{ false }, data{ _data }, bounds{ std::move(_bounds) }
	{
	}

	template <typename DATA>
	QuadTreeData<DATA>::~QuadTreeData() = default;
}
