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
	void removeConnection(Node<T>* toRemove);

	/**
	 * Function finds cycles by Holt method.
	 * Will change currentCheckedNodes and noCycleElements variables (add or remove itself address)
	 */
	bool isInCycle(std::set<Node<T>*>& currentCheckedNodes, std::set<Node<T>*>& noCycleElements);

	T getId() const;
	std::set<T> getConnectedIDs() const;
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
void Node<T>::removeConnection(Node<T>* toRemove)
{
	connections.erase(toRemove);
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
	currentCheckedNodes.erase(this);
	return false;
}

template <typename T>
T Node<T>::getId() const
{
	return id;
}

template <typename T>
std::set<T> Node<T>::getConnectedIDs() const
{
	std::set<T> res;
	for (auto node : connections)
	{
		res.insert(node->id);
	}

	return res;
}

NAMESPACE_END
