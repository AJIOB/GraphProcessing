#pragma once

#include <list>

#include "Graph.h"

template <typename T>
bool isGraphHaveCycles(std::list<std::pair<T, T>> edges)
{
	AJIOB::Graph<T> graph(edges);
	return graph.isHaveCycles();
}
