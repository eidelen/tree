#include <memory>

template<class T>
class Node
{
    private:
        using NodePtr = std::shared_ptr<Node<T>>;

    public:

        Node(){}

        Node(const T& data): m_data(data)
        {
        }

        NodePtr rightChild()
        {
            return m_rightChild;
        }

        NodePtr leftChild()
        {
            return m_leftChild;
        }

        T data()
        {
            return m_data;
        }


    private:
        NodePtr m_rightChild;
        NodePtr m_leftChild;
        T m_data;       
};

