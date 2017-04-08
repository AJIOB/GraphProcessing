#pragma once

#include <map>

#include "Namespace.h"
#include "Node.h"


NAMESPACE_BEGIN

template <typename T>
class Graph
{
	std::set<Node<T>*> nodes;
public:
	/**
	 * Build the non-oriented graph with edges.
	 * Key in multimap - starting node.
	 * Value in multimap - ending node.
	 */
	explicit Graph(std::multimap<T, T> edges);

	bool isHaveCycles() const;
};

template <typename T>
Graph<T>::Graph(std::multimap<T, T> edges)
{
	//todo: build graph
}

template <typename T>
bool Graph<T>::isHaveCycles() const
{
	return false;			//todo: fix
}

NAMESPACE_END
