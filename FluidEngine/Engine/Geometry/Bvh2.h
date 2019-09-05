#pragma once

#include <vector>
#include <numeric>

#include "../Utils/MathUtils.h"
#include "../Utils/Constants.h"
#include "IntersectionQueryEngine2.h"
#include "NearestNeighborQueryEngine2.h"

namespace Engine
{
	//!
	//! \brief Bounding Volume Hierarchy (BVH) in 2D
	//!
	//! This class implements the classic bounding volume hierarchy structure in 2D.
	//! It implements IntersectionQueryEngine2 in order to support box/ray
	//! intersection tests. Also, NearestNeighborQueryEngine2 is implemented to
	//! provide nearest neighbor query.
	//!
	template <typename T>
	class Bvh2 final : public IntersectionQueryEngine2<T>,
					   public NearestNeighborQueryEngine2<T>
	{
	public:
		using ContainerType = std::vector<T>;
		using Iterator = typename ContainerType::iterator;
		using ConstIterator = typename ContainerType::const_iterator;

		//! Default constructor.
		Bvh2();

		//! Builds bounding volume hierarchy.
		void build(const std::vector<T>& items, const std::vector<BoundingBox2D>& itemsBounds);

		//! Clears all the contents of this instance.
		void clear();

		//! Returns the nearest neighbor for given point and distance measure
		//! function.
		NearestNeighborQueryResult2<T> nearest(
			const Vector2D& pt,
			const NearestNeighborDistanceFunc2<T>& distanceFunc) const override;

		//! Returns true if given \p box intersects with any of the stored items.
		bool intersects(const BoundingBox2D& box,
			const BoxIntersectionTestFunc2<T>& testFunc) const override;

		//! Returns true if given \p ray intersects with any of the stored items.
		bool intersects(const Ray2D& ray,
			const RayIntersectionTestFunc2<T>& testFunc) const override;

		//! Invokes \p visitorFunc for every intersecting items.
		void forEachIntersectingItem(
			const BoundingBox2D& box, const BoxIntersectionTestFunc2<T>& testFunc,
			const IntersectionVisitorFunc2<T>& visitorFunc) const override;

		//! Invokes \p visitorFunc for every intersecting items.
		void forEachIntersectingItem(
			const Ray2D& ray, const RayIntersectionTestFunc2<T>& testFunc,
			const IntersectionVisitorFunc2<T>& visitorFunc) const override;

		//! Returns the closest intersection for given \p ray.
		ClosestIntersectionQueryResult2<T> closestIntersection(
			const Ray2D& ray,
			const GetRayIntersectionFunc2<T>& testFunc) const override;

		//! Returns bounding box of every items.
		const BoundingBox2D& boundingBox() const;

		//! Returns the begin iterator of the item.
		Iterator begin();

		//! Returns the end iterator of the item.
		Iterator end();

		//! Returns the immutable begin iterator of the item.
		ConstIterator begin() const;

		//! Returns the immutable end iterator of the item.
		ConstIterator end() const;

		//! Returns the number of items.
		size_t numberOfItems() const;

		//! Returns the item at \p i.
		const T& item(size_t i) const;

		//! Returns the number of nodes.
		size_t numberOfNodes() const;

		//! Returns the children indices of \p i-th node.
		std::pair<size_t, size_t> children(size_t i) const;

		//! Returns true if \p i-th node is a leaf node.
		bool isLeaf(size_t i) const;

		//! Returns bounding box of \p i-th node.
		const BoundingBox2D& nodeBound(size_t i) const;

		//! Returns item of \p i-th node.
		Iterator itemOfNode(size_t i);

		//! Returns item of \p i-th node.
		ConstIterator itemOfNode(size_t i) const;

	private:
		struct Node 
		{
			char flags;
			union {
				size_t child;
				size_t item;
			};
			BoundingBox2D bound;

			Node();
			void initLeaf(size_t it, const BoundingBox2D& b);
			void initInternal(uint8_t axis, size_t c, const BoundingBox2D& b);
			bool isLeaf() const;
		};

		BoundingBox2D _bound;
		ContainerType _items;
		std::vector<BoundingBox2D> _itemBounds;
		std::vector<Node> _nodes;

		size_t build(size_t nodeIndex, size_t* itemIndices, size_t nItems, size_t currentDepth);

		size_t qsplit(size_t* itemIndices, size_t numItems, double pivot, uint8_t axis);


	};
	
	//! ----------------------------------Definition---------------------------------

	template <typename T>
	Bvh2<T>::Node::Node() : flags(0) { child = kMaxSize; }

	template <typename T>
	void Bvh2<T>::Node::initLeaf(size_t it, const BoundingBox2D& b) 
	{
		flags = 2;
		item = it;
		bound = b;
	}

	template <typename T>
	void Bvh2<T>::Node::initInternal(uint8_t axis, size_t c, const BoundingBox2D& b) 
	{
		flags = axis;
		child = c;
		bound = b;
	}

	template <typename T>
	bool Bvh2<T>::Node::isLeaf() const { return flags == 2; }

	//

	template <typename T>
	Bvh2<T>::Bvh2() {}

	template <typename T>
	void Bvh2<T>::build(const std::vector<T>& items, const std::vector<BoundingBox2D>& itemsBounds) 
	{
		_items = items;
		_itemBounds = itemsBounds;

		if (_items.empty()) 
			return;

		_nodes.clear();

		for (size_t i = 0; i < _items.size(); ++i) 
			_bound.merge(_itemBounds[i]);

		std::vector<size_t> itemIndices(_items.size());
		std::iota(std::begin(itemIndices), std::end(itemIndices), 0);

		build(0, itemIndices.data(), _items.size(), 0);
	}

	template <typename T>
	void Bvh2<T>::clear() 
	{
		_bound = BoundingBox2D();
		_items.clear();
		_itemBounds.clear();
		_nodes.clear();
	}

	template <typename T>
	inline NearestNeighborQueryResult2<T> Bvh2<T>::nearest(
		const Vector2D& pt,
		const NearestNeighborDistanceFunc2<T>& distanceFunc) const 
	{
		NearestNeighborQueryResult2<T> best;
		best.distance = kMaxD;
		best.item = nullptr;

		// Prepare to traverse BVH
		static const int kMaxTreeDepth = 8 * sizeof(size_t);
		// dfs traverse stack.
		const Node* todo[kMaxTreeDepth];
		size_t todoPos = 0;

		// Traverse BVH nodes
		const Node* node = _nodes.data();
		while (node != nullptr) 
		{
			if (node->isLeaf()) 
			{
				double dist = distanceFunc(_items[node->item], pt);
				if (dist < best.distance) 
				{
					best.distance = dist;
					best.item = &_items[node->item];
				}

				// Grab next node to process from todo stack
				if (todoPos > 0) 
				{
					// Dequeue
					--todoPos;
					node = todo[todoPos];
				}
				else 
					break;
			}
			else 
			{
				const double bestDistSqr = best.distance * best.distance;

				// left subnode.
				const Node* left = node + 1;
				// right subnode.
				const Node* right = &_nodes[node->child];

				// If pt is inside the box, then the closestLeft and Right will be
				// identical to pt. This will make distMinLeftSqr and
				// distMinRightSqr zero, meaning that such a box will have higher
				// priority.
				Vector2D closestLeft = left->bound.clamp(pt);
				Vector2D closestRight = right->bound.clamp(pt);

				double distMinLeftSqr = closestLeft.distanceSquaredTo(pt);
				double distMinRightSqr = closestRight.distanceSquaredTo(pt);

				bool shouldVisitLeft = distMinLeftSqr < bestDistSqr;
				bool shouldVisitRight = distMinRightSqr < bestDistSqr;

				const Node* firstChild;
				const Node* secondChild;
				if (shouldVisitLeft && shouldVisitRight) 
				{
					if (distMinLeftSqr < distMinRightSqr) 
					{
						firstChild = left;
						secondChild = right;
					}
					else 
					{
						firstChild = right;
						secondChild = left;
					}

					// Enqueue secondChild in todo stack
					todo[todoPos] = secondChild;
					++todoPos;
					node = firstChild;
				}
				else if (shouldVisitLeft) 
				{
					node = left;
				}
				else if (shouldVisitRight) 
				{
					node = right;
				}
				else 
				{
					if (todoPos > 0) 
					{
						// Dequeue
						--todoPos;
						node = todo[todoPos];
					}
					else 
						break;
				}
			}
		}

		return best;
	}

	template <typename T>
	inline bool Bvh2<T>::intersects(
		const BoundingBox2D& box,
		const BoxIntersectionTestFunc2<T>& testFunc) const 
	{
		if (!_bound.overlaps(box)) 
			return false;

		// prepare to traverse BVH for box
		static const int kMaxTreeDepth = 8 * sizeof(size_t);
		const Node* todo[kMaxTreeDepth];
		size_t todoPos = 0;

		// traverse BVH nodes for box
		const Node* node = _nodes.data();

		while (node != nullptr) 
		{
			if (node->isLeaf()) 
			{
				if (testFunc(_items[node->item], box)) 
					return true;

				// grab next node to process from todo stack
				if (todoPos > 0) 
				{
					// Dequeue
					--todoPos;
					node = todo[todoPos];
				}
				else 
					break;
			}
			else 
			{
				// get node children pointers for box
				const Node* firstChild = node + 1;
				const Node* secondChild = (Node*)&_nodes[node->child];

				// advance to next child node, possibly enqueue other child
				if (!firstChild->bound.overlaps(box)) 
					node = secondChild;
				else if (!secondChild->bound.overlaps(box)) 
					node = firstChild;
				else 
				{
					// enqueue secondChild in todo stack
					todo[todoPos] = secondChild;
					++todoPos;
					node = firstChild;
				}
			}
		}

		return false;
	}

	template <typename T>
	inline bool Bvh2<T>::intersects(
		const Ray2D& ray, const RayIntersectionTestFunc2<T>& testFunc) const 
	{
		if (!_bound.intersects(ray)) 
			return false;

		// prepare to traverse BVH for ray
		static const int kMaxTreeDepth = 8 * sizeof(size_t);
		const Node* todo[kMaxTreeDepth];
		size_t todoPos = 0;

		// traverse BVH nodes for ray
		const Node* node = _nodes.data();

		while (node != nullptr) 
		{
			if (node->isLeaf()) 
			{
				if (testFunc(_items[node->item], ray)) 
					return true;

				// grab next node to process from todo stack
				if (todoPos > 0) 
				{
					// Dequeue
					--todoPos;
					node = todo[todoPos];
				}
				else 
					break;
			}
			else 
			{
				// get node children pointers for ray
				const Node* firstChild;
				const Node* secondChild;
				if (ray.direction[node->flags] > 0.0) 
				{
					firstChild = node + 1;
					secondChild = (Node*)&_nodes[node->child];
				}
				else 
				{
					firstChild = (Node*)&_nodes[node->child];
					secondChild = node + 1;
				}

				// advance to next child node, possibly enqueue other child
				if (!firstChild->bound.intersects(ray)) 
					node = secondChild;
				else if (!secondChild->bound.intersects(ray)) 
					node = firstChild;
				else 
				{
					// enqueue secondChild in todo stack
					todo[todoPos] = secondChild;
					++todoPos;
					node = firstChild;
				}
			}
		}

		return false;
	}

	template <typename T>
	inline void Bvh2<T>::forEachIntersectingItem(
		const BoundingBox2D& box, const BoxIntersectionTestFunc2<T>& testFunc,
		const IntersectionVisitorFunc2<T>& visitorFunc) const 
	{
		if (!_bound.overlaps(box)) 
			return;

		// prepare to traverse BVH for box
		static const int kMaxTreeDepth = 8 * sizeof(size_t);
		const Node* todo[kMaxTreeDepth];
		size_t todoPos = 0;

		// traverse BVH nodes for box
		const Node* node = _nodes.data();

		while (node != nullptr) {
			if (node->isLeaf()) 
			{
				if (testFunc(_items[node->item], box)) 
					visitorFunc(_items[node->item]);

				// grab next node to process from todo stack
				if (todoPos > 0) 
				{
					// Dequeue
					--todoPos;
					node = todo[todoPos];
				}
				else 
					break;
			}
			else 
			{
				// get node children pointers for box
				const Node* firstChild = node + 1;
				const Node* secondChild = (Node*)&_nodes[node->child];

				// advance to next child node, possibly enqueue other child
				if (!firstChild->bound.overlaps(box)) 
					node = secondChild;
				else if (!secondChild->bound.overlaps(box)) 
					node = firstChild;
				else 
				{
					// enqueue secondChild in todo stack
					todo[todoPos] = secondChild;
					++todoPos;
					node = firstChild;
				}
			}
		}
	}

	template <typename T>
	inline void Bvh2<T>::forEachIntersectingItem(
		const Ray2D& ray, const RayIntersectionTestFunc2<T>& testFunc,
		const IntersectionVisitorFunc2<T>& visitorFunc) const 
	{
		if (!_bound.intersects(ray)) 
			return;

		// prepare to traverse BVH for ray
		static const int kMaxTreeDepth = 8 * sizeof(size_t);
		const Node* todo[kMaxTreeDepth];
		size_t todoPos = 0;

		// traverse BVH nodes for ray
		const Node* node = _nodes.data();

		while (node != nullptr) 
		{
			if (node->isLeaf()) 
			{
				if (testFunc(_items[node->item], ray)) 
					visitorFunc(_items[node->item]);

				// grab next node to process from todo stack
				if (todoPos > 0) 
				{
					// Dequeue
					--todoPos;
					node = todo[todoPos];
				}
				else 
					break;
			}
			else 
			{
				// get node children pointers for ray
				const Node* firstChild;
				const Node* secondChild;
				if (ray.direction[node->flags] > 0.0) 
				{
					firstChild = node + 1;
					secondChild = (Node*)&_nodes[node->child];
				}
				else 
				{
					firstChild = (Node*)&_nodes[node->child];
					secondChild = node + 1;
				}

				// advance to next child node, possibly enqueue other child
				if (!firstChild->bound.intersects(ray)) 
					node = secondChild;
				else if (!secondChild->bound.intersects(ray)) 
					node = firstChild;
				else 
				{
					// enqueue secondChild in todo stack
					todo[todoPos] = secondChild;
					++todoPos;
					node = firstChild;
				}
			}
		}
	}

	template <typename T>
	inline ClosestIntersectionQueryResult2<T> Bvh2<T>::closestIntersection(
		const Ray2D& ray, const GetRayIntersectionFunc2<T>& testFunc) const 
	{
		ClosestIntersectionQueryResult2<T> best;
		best.distance = kMaxD;
		best.item = nullptr;

		if (!_bound.intersects(ray)) 
			return best;

		// prepare to traverse BVH for ray
		static const int kMaxTreeDepth = 8 * sizeof(size_t);
		const Node* todo[kMaxTreeDepth];
		size_t todoPos = 0;

		// traverse BVH nodes for ray
		const Node* node = _nodes.data();

		while (node != nullptr) 
		{
			if (node->isLeaf()) 
			{
				double dist = testFunc(_items[node->item], ray);
				if (dist < best.distance) 
				{
					best.distance = dist;
					best.item = _items.data() + node->item;
				}

				// grab next node to process from todo stack
				if (todoPos > 0) 
				{
					// Dequeue
					--todoPos;
					node = todo[todoPos];
				}
				else 
					break;
			}
			else 
			{
				// get node children pointers for ray
				const Node* firstChild;
				const Node* secondChild;
				if (ray.direction[node->flags] > 0.0) 
				{
					firstChild = node + 1;
					secondChild = (Node*)&_nodes[node->child];
				}
				else 
				{
					firstChild = (Node*)&_nodes[node->child];
					secondChild = node + 1;
				}

				// advance to next child node, possibly enqueue other child
				if (!firstChild->bound.intersects(ray)) 
					node = secondChild;
				else if (!secondChild->bound.intersects(ray)) 
					node = firstChild;
				else 
				{
					// enqueue secondChild in todo stack
					todo[todoPos] = secondChild;
					++todoPos;
					node = firstChild;
				}
			}
		}

		return best;
	}

	template <typename T>
	const BoundingBox2D& Bvh2<T>::boundingBox() const { return _bound; }

	template <typename T>
	typename Bvh2<T>::Iterator Bvh2<T>::begin() { return _items.begin(); }

	template <typename T>
	typename Bvh2<T>::Iterator Bvh2<T>::end() { return _items.end(); }

	template <typename T>
	typename Bvh2<T>::ConstIterator Bvh2<T>::begin() const { return _items.begin(); }

	template <typename T>
	typename Bvh2<T>::ConstIterator Bvh2<T>::end() const { return _items.end(); }

	template <typename T>
	size_t Bvh2<T>::numberOfItems() const { return _items.size(); }

	template <typename T>
	const T& Bvh2<T>::item(size_t i) const { return _items[i]; }

	template <typename T>
	size_t Bvh2<T>::numberOfNodes() const { return _nodes.size(); }

	template <typename T>
	std::pair<size_t, size_t> Bvh2<T>::children(size_t i) const 
	{
		if (isLeaf(i)) 
			return std::make_pair(kMaxSize, kMaxSize);
		else 
			return std::make_pair(i + 1, _nodes[i].child);
	}

	template <typename T>
	bool Bvh2<T>::isLeaf(size_t i) const { return _nodes[i].isLeaf(); }

	template <typename T>
	const BoundingBox2D& Bvh2<T>::nodeBound(size_t i) const { return _nodes[i].bound; }

	template <typename T>
	typename Bvh2<T>::Iterator Bvh2<T>::itemOfNode(size_t i) 
	{
		if (isLeaf(i)) 
			return _nodes[i].item + begin();
		else 
			return end();
	}

	template <typename T>
	typename Bvh2<T>::ConstIterator Bvh2<T>::itemOfNode(size_t i) const 
	{
		if (isLeaf(i)) 
			return _nodes[i].item + begin();
		else 
			return end();
	}

	template <typename T>
	size_t Bvh2<T>::build(size_t nodeIndex, size_t* itemIndices, size_t nItems, size_t currentDepth) 
	{
		// add a node
		_nodes.push_back(Node());

		// initialize leaf node if termination criteria met
		if (nItems == 1) 
		{
			_nodes[nodeIndex].initLeaf(itemIndices[0], _itemBounds[itemIndices[0]]);
			return currentDepth + 1;
		}

		// find the mid-point of the bounding box to use as a qsplit pivot
		BoundingBox2D nodeBound;
		for (size_t i = 0; i < nItems; ++i) 
		{
			nodeBound.merge(_itemBounds[itemIndices[i]]);
		}

		Vector2D d = nodeBound.upperCorner - nodeBound.lowerCorner;

		// choose which axis to split along
		uint8_t axis;
		if (d.x > d.y) 
			axis = 0;
		else 
			axis = 1;

		double pivot =
			0.5 * (nodeBound.upperCorner[axis] + nodeBound.lowerCorner[axis]);

		// classify primitives with respect to split
		size_t midPoint = qsplit(itemIndices, nItems, pivot, axis);

		// recursively initialize children _nodes
		// build left subtree.
		size_t d0 = build(nodeIndex + 1, itemIndices, midPoint, currentDepth + 1);
		_nodes[nodeIndex].initInternal(axis, _nodes.size(), nodeBound);
		// build right subtree.
		size_t d1 = build(_nodes[nodeIndex].child, itemIndices + midPoint,
			nItems - midPoint, currentDepth + 1);

		return std::max(d0, d1);
	}

	template <typename T>
	size_t Bvh2<T>::qsplit(size_t* itemIndices, size_t numItems, double pivot, uint8_t axis) 
	{
		double centroid;
		size_t ret = 0;
		for (size_t i = 0; i < numItems; ++i) 
		{
			BoundingBox2D b = _itemBounds[itemIndices[i]];
			centroid = 0.5f * (b.lowerCorner[axis] + b.upperCorner[axis]);
			if (centroid < pivot) 
			{
				std::swap(itemIndices[i], itemIndices[ret]);
				ret++;
			}
		}
		if (ret == 0 || ret == numItems) 
			ret = numItems >> 1;
		return ret;
	}
	
}