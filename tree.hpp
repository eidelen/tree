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
         * Set the data of this node.
         * @param data The new data of this node.
         */
        void setData(const T& data)
        {
            m_data = data;
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
         * exact visit strategy is pre-order (current, left, right). At each node the
         * passed function is called. The current node's depth is known and passend 
         * to the custom function too.
         * @param  nodeFunction A custom function which is called at every node
         * @param  depth Current depth within the tree traversal. 
         */
        void doDFS(std::function<void(NodePtr, size_t)> nodeFunction, size_t depth = 0)
        {
            nodeFunction(this->shared_from_this(), depth);
            if(hasLeftChild())
            {
                leftChild()->doDFS(nodeFunction, depth+1);
            }
            if(hasRightChild())
            {
                rightChild()->doDFS(nodeFunction, depth+1);
            }
        }

        /**
         * Search the tree for nodes which fullfill statement.
         * Note: This function traverses through the wohle tree (slow)!!
         * @param Comparison function.
         * @return returns vector with nodes.
         */
        std::vector<NodePtr> findNodes(std::function<bool(T)> cmpFunction) 
        {
            std::vector<NodePtr> nodes;
            std::function<void(NodePtr, size_t)> findFunc = [&nodes, cmpFunction](NodePtr n, size_t)
            {
                if(cmpFunction(n->data()))
                {
                    nodes.push_back(n);
                }
            };

            doDFS(findFunc);
            return nodes;
        }


        /**
         * Counts the number of elements in the tree.
         * @return Number of elements.
         */
        size_t count()
        {
            size_t s = 0;
            std::function<void(NodePtr, size_t)> countFunc = [&s](NodePtr n, size_t)
            {
                s += 1;
            };

            doDFS(countFunc);
            return s;
        }

        
        /**
         * Compute the maximum depth of the tree.
         * @return Max depth of the tree.
         */
        size_t getDepth()
        {
            size_t maxDepth = 0;
            std::function<void(NodePtr, size_t)> maxDepthFunc = [&maxDepth](NodePtr, size_t currentDepth)
            {
                maxDepth = std::max(maxDepth, currentDepth);
            };

            doDFS(maxDepthFunc);
            return maxDepth;
        }


        /**
         * Prints tree horicontally
         */
        void print()
        {
            print("", false);
        }

        /**
         * Recursive helper function for print()
         */
        void print(const std::string& prefix, bool isLeft)
        {
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──" );

            // print the value of the node
            std::cout << data() << std::endl;

            // enter the next tree level - left and right branch
            if(hasLeftChild())
            {
                leftChild()->print( prefix + (isLeft ? "│   " : "    "), true);
            }
            if(hasRightChild())
            {
                rightChild()->print(prefix + (isLeft ? "│   " : "    "), false);
            }
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
