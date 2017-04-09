#include <gtest/gtest.h>

#include "../Holt Model/HoltModel.h"

TEST(Node_tests, connection_to_itSelf )
{
	typedef int T;
	AJIOB::Node<T> node(1);
	node.addConnection(&node);

	EXPECT_TRUE(node.isInCycle(std::set<AJIOB::Node<T>*>(), std::set<AJIOB::Node<T>*>()));
}

TEST(Node_tests, noConnections)
{
	typedef std::string T;
	AJIOB::Node<T> node("1");

	EXPECT_FALSE(node.isInCycle(std::set<AJIOB::Node<T>*>(), std::set<AJIOB::Node<T>*>()));
}

TEST(Node_tests, simple_cycle)
{
	typedef std::string T;
	AJIOB::Node<T> node1("1"), node2("q"), node3("w"), node4("r");
	node1.addConnection(&node2);
	node2.addConnection(&node3);
	node3.addConnection(&node1);

	node1.addConnection(&node4);
	node2.addConnection(&node4);

	EXPECT_TRUE(node1.isInCycle(std::set<AJIOB::Node<T>*>(), std::set<AJIOB::Node<T>*>()));
	EXPECT_FALSE(node4.isInCycle(std::set<AJIOB::Node<T>*>(), std::set<AJIOB::Node<T>*>()));
}

TEST(Graph_tests, empty_graph)
{
	typedef std::string T;
	std::multimap<T, T> edges;

	AJIOB::Graph<T> graph(edges);
	EXPECT_FALSE(graph.isHaveCycles());
}

TEST(Graph_tests, connection_to_itSelf)
{
	typedef int T;
	std::multimap<T, T> edges;

	edges.insert(std::make_pair(1, 1));

	AJIOB::Graph<T> graph(edges);
	EXPECT_TRUE(graph.isHaveCycles());
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
