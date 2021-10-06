#include <gtest/gtest.h>

#include <tree.hpp>

// test helpers
using NodeInt = std::shared_ptr<Node<int>>;
NodeInt createIntNode(int data) {return NodeInt(new Node<int>(data));}


TEST(Memory, DefaultCtor)
{
    Node<int>* n = new Node<int>();
    ASSERT_FALSE(n == nullptr);
    ASSERT_TRUE(n->leftChild().get() == nullptr);
    ASSERT_TRUE(n->rightChild().get() == nullptr);

    delete n;
}

TEST(Memory, CtorNoChild)
{
    for(int i = -100; i < 100; i++)
    {
        NodeInt n = createIntNode(i);
        ASSERT_FALSE(n.get() == nullptr);
        ASSERT_EQ(n->data(), i);
        ASSERT_TRUE(n->leftChild().get() == nullptr);
        ASSERT_TRUE(n->rightChild().get() == nullptr);
    }
}

TEST(Child, HasNoChildAtInit)
{
    NodeInt n = createIntNode(5);
    ASSERT_FALSE(n->hasLeftChild());
    ASSERT_FALSE(n->hasRightChild());
}
