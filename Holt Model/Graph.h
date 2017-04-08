#pragma once

#include <map>

#include "Namespace.h"
#include "Node.h"


NAMESPACE_BEGIN

template <typename T>
class Graph<T>
{
	std::set<Node<T>*> nodes;
public:
	explicit Graph(std::multimap<T, T> edges);

	bool isHaveCycles() const;
};

template <typename T>
Graph<T>::Graph(std::multimap<T, T> edges)
{
	//todo
}

template <typename T>
bool Graph<T>::isHaveCycles() const
{
	return false;			//todo: fix
}

NAMESPACE_END
