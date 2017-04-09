#pragma once

#include <map>
#include <set>

#include "Namespace.h"
#include "Node.h"


NAMESPACE_BEGIN

template <typename T>
class Graph
{
	std::set<Node<T>*> nodes;

	Node<T>* findOrCreateNode(const T& nodeID);
public:
	/**
	 * Build the non-oriented graph with edges.
	 * Key in multimap - starting node.
	 * Value in multimap - ending node.
	 */
	explicit Graph(const std::multimap<T, T>& edges);

	bool isHaveCycles() const;
};


template <typename T>
Node<T>* Graph<T>::findOrCreateNode(const T& nodeID)
{
	auto it = std::find_if(nodes.begin(), nodes.end(),
		[&nodeID](Node<T>* elem)
		{
			return (nodeID == elem->getId());
		});
	if (it != nodes.end())
	{
		return *it;
	}

	Node<T>* res = new Node<T>(nodeID);
	nodes.insert(res);
	return res;
}

template <typename T>
Graph<T>::Graph(const std::multimap<T, T>& edges)
{
	for (auto it = edges.begin(); it != edges.end(); ++it)
	{
		findOrCreateNode(it->first)->addConnection(findOrCreateNode(it->second));
	}
}

template <typename T>
bool Graph<T>::isHaveCycles() const
{
	std::set<Node<T>*> nodesToCheck = nodes;

	while (!nodesToCheck.empty())
	{
		std::set<Node<T>*> noCycleElements;

		if ((*nodesToCheck.begin())->isInCycle(std::set<Node<T>*>(), noCycleElements))
		{
			return true;
		}

		//remove all elements, that not in cycles
		for (auto it = noCycleElements.begin(); it != noCycleElements.end(); ++it)
		{
			nodesToCheck.erase(*it);
		}
	}

	return false;
}

NAMESPACE_END
