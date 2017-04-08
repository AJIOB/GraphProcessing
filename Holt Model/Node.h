#pragma once

#include <set>

#include "Namespace.h"

NAMESPACE_BEGIN

template<typename T>
class Node
{
	T id;
	std::set<Node<T>*> connections;

public:
	explicit Node(const T& id);

	void addConnection(Node<T>* toAdd);

	/**
	 * Function finds cycles by Holt method.
	 * Will change currentCheckedNodes and noCycleElements variables (add or remove itself address)
	 */
	bool isInCycle(std::set<Node<T>*>& currentCheckedNodes, std::set<Node<T>*>& noCycleElements);
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

template <typename T>
bool Node<T>::isInCycle(std::set<Node<T>*>& currentCheckedNodes, std::set<Node<T>*>& noCycleElements)
{
	//if not insert => we have that element => we have cycle
	if (!currentCheckedNodes.insert(this).second)
	{
		return true;
	}

	for (auto it = connections.begin(); it != connections.end(); ++it)
	{
		if ((*it)->isInCycle(currentCheckedNodes, noCycleElements))
		{
			return true;
		}
	}

	noCycleElements.insert(this);
	return false;
}

NAMESPACE_END
