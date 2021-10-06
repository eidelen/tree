#include <memory>

template<class T>
class Node
{
    private:
        using NodePtr = std::shared_ptr<Node<T>>;

    public:

        Node(){}

        
        /**
         * Create a node with data.
         * @param Passed data.
         * @return Pointer to node.
         */
        Node(const T& data): m_data(data)
        {
        }

        /**
         * Get right child node. If leaf node, sp 
         * points to null.
         * @return Right child node 
         */
        NodePtr rightChild()
        {
            return m_rightChild;
        }

        /**
         * Get left child node. If leaf node, sp 
         * points to null.
         * @return Left child node 
         */
        NodePtr leftChild()
        {
            return m_leftChild;
        }

        /**
         * Return stored node data.
         * @return Node data
         */
        T data()
        {
            return m_data;
        }

        /**
         * Has node a left child.
         * @return True if node has left child node. Otherwise false.
         */
        bool hasLeftChild() const
        {
            return !isLeafNode(m_leftChild);
        }

        /**
         * Has node a right child.
         * @return True if node has right child node. Otherwise false.
         */
        bool hasRightChild() const
        {
            return !isLeafNode(m_rightChild);
        }

    private:

        bool isLeafNode(const NodePtr& node) const
        {
            return node.get() == nullptr;
        }

        NodePtr m_rightChild;
        NodePtr m_leftChild;
        T m_data;       
};

