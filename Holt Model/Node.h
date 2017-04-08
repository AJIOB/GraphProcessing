#pragma once

#include <set>

#include "Namespace.h"

NAMESPACE_BEGIN

template<typename T>
class Node<T>
{
	T id;
	std::set<Node<T>*> connections;

public:
	explicit Node(const T& id);

	void addConnection(Node<T>* toAdd);
};

template <typename T>
Node<T>::Node(const T& id)
{
	this->id = id;
}

template <typename T>
void Node<T>::addConnection(Node<T>* toAdd)
{
	connections.insert(toAdd);
}

NAMESPACE_END
