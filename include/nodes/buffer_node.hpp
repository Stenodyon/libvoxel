#ifndef BUFFER_NODE_HPP_
#define BUFFER_NODE_HPP_

#include <unordered_map>

#include "node.hpp"
#include "point.hpp"

class Buffer
{
    public:
        virtual void reset() = 0;
};

template <typename T>
class BufferNode : public Node<T>, Buffer
{
    private:
        Node<T> *input;
        std::unordered_map<Point, T> buffer;

    public:
        explicit BufferNode(Node<T> *input);

        T get_voxel(const Point &pos) override;

        void reset() override;
};

template <typename T>
BufferNode<T>::BufferNode(Node<T> *input)
    : input(input)
{
}

template <typename T>
T BufferNode<T>::get_voxel(const Point &pos)
{
    auto search = buffer.find(pos);
    if (search != buffer.end())
    {
        return search->second;
    }
    else
    {
        T value = input->get_voxel(pos);
        buffer.insert({pos, value});
        return value;
    }
}

template <typename T>
void BufferNode<T>::reset()
{
    this->buffer.clear();
}

#endif // BUFFER_NODE_HPP_
