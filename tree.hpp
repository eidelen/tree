#include <memory>
#include <functional>

template<class T>
class Node: public std::enable_shared_from_this<Node<T>>
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

        ~Node()
        {
            std::cout << data() << ",";
            deleteRightChild();
            deleteLeftChild();
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
         * Set the left child. Existing tree beneath goes lost.
         * @param data Data of the new left child node.
         * @return New created node.
         */
        NodePtr setLeftChild(const T& data)
        {
            m_leftChild.reset(new Node<T>(data));
            return m_leftChild;
        }

        /**
         * Set the right child. Existing tree beneath goes lost.
         * @param data Data of the new right child node.
         * @return New created node.
         */
        NodePtr setRightChild(const T& data)
        {
            m_rightChild.reset(new Node<T>(data));
            return m_rightChild;
        }

        /**
         * Deletes the left child node and all its children.
         */
        void deleteLeftChild()
        {
            m_leftChild.reset();
        }

        /**
         * Deletes the right child node and all its children.
         */
        void deleteRightChild()
        {
            m_rightChild.reset();
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

        // Traversals

        /**
         * This function visits the tree nodes in the depth first search order. The
         * exact visit strategy is pre-order (current, left, right).
         * @param  nodeFunction A custom function which is called at every node
         */
        void doDFS(std::function<void(NodePtr)> nodeFunction)
        {
            nodeFunction(this->shared_from_this());
            if(hasLeftChild())
            {
                leftChild()->doDFS(nodeFunction);
            }
            if(hasRightChild())
            {
                rightChild()->doDFS(nodeFunction);
            }
        }

        /**
         * Counts the number of elements in the tree.
         * @return Number of elements.
         */
        size_t count()
        {
            size_t s = 0;
            std::function<void(NodePtr)> countFunc = [&s](NodePtr n)
            {
                s += 1;
            };

            doDFS(countFunc);

            return s;
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


template<class T>
class BTNode: public Node<T>
{

};

