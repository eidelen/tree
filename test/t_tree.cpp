#include <gtest/gtest.h>

#include <vector>

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

TEST(Child, CreateChildren)
{
    NodeInt n = createIntNode(5);
    ASSERT_FALSE(n->hasLeftChild());
    ASSERT_FALSE(n->hasRightChild());

    NodeInt lc = n->setLeftChild(2);
    ASSERT_TRUE(n->hasLeftChild());
    ASSERT_EQ(lc.get(), n->leftChild().get());
    ASSERT_EQ(lc->data(), 2);

    NodeInt rc = n->setRightChild(3);
    ASSERT_TRUE(n->hasRightChild());
    ASSERT_EQ(rc.get(), n->rightChild().get());
    ASSERT_EQ(rc->data(), 3);
}

void setDepthAsContent(NodeInt n, int depth, int maxDepth)
{
    if(depth < maxDepth)
    {
        setDepthAsContent( n->setLeftChild(depth+1), depth+1, maxDepth );
        setDepthAsContent( n->setRightChild(depth+1), depth+1, maxDepth );
    }
}

TEST(Tree, Connect)
{
    // Node content is its depth. Filled tree till level 2.
    NodeInt r = createIntNode(0);
    setDepthAsContent( r, 0, 2 );

    ASSERT_EQ(r->data(), 0);
    ASSERT_EQ(r->rightChild()->data(), 1);
    ASSERT_EQ(r->leftChild()->data(), 1);
    ASSERT_EQ(r->rightChild()->rightChild()->data(), 2);
    ASSERT_EQ(r->rightChild()->leftChild()->data(), 2);
    ASSERT_EQ(r->leftChild()->rightChild()->data(), 2);
    ASSERT_EQ(r->leftChild()->leftChild()->data(), 2);

    ASSERT_FALSE(r->rightChild()->rightChild()->hasRightChild());
    ASSERT_FALSE(r->rightChild()->leftChild()->hasLeftChild());
    ASSERT_FALSE(r->leftChild()->rightChild()->hasRightChild());
    ASSERT_FALSE(r->leftChild()->leftChild()->hasLeftChild());
}

// Example Tree: 5 (3 (2, 4),  7 (6, 8))
// Depth = 2; Nbr Elements = 7
NodeInt getExampleTree()
{
    NodeInt r = createIntNode(5);

    NodeInt l1 = r->setLeftChild(3);
    l1->setLeftChild(2);
    l1->setRightChild(4);

    NodeInt r1 = r->setRightChild(7);
    r1->setLeftChild(6);
    r1->setRightChild(8);

    return r;
}

TEST(Tree, DFS)
{
    // Node content is its depth. Filled tree till level 2.
    NodeInt r = getExampleTree();

    std::vector<int> dataCollectionVec;
    std::function<void(NodeInt)> nodeFunction = [&dataCollectionVec](NodeInt n) {
        dataCollectionVec.push_back(n->data());
    };
    
    r->doDFS(nodeFunction);

    // DFS Traversal should finish nodes in this order
    std::vector<int> resShould = {5, 3, 2, 4, 7, 6, 8} ;
    ASSERT_TRUE(dataCollectionVec == resShould);
}
