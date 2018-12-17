#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <memory>
#include <vector>
#include <string>

#include "graph_node.hpp"
#include "nodes/buffer_node.hpp"
#include "memory_arena.hpp"

#define NODE_ARENA_SIZE 65536

class Graph
{
    private:
        MemoryArena nodeArena;
        std::vector<GraphNode*> nodes;
        std::vector<Buffer*> buffers;

    public:
        Graph();

        template <typename NodeType, typename ...Args>
        NodeType * add(Args && ...args);

        void reset_buffers(); // clear buffers
        void clear(); // Clear all nodes

        static Graph FromFile(std::string filename);
};

template <typename NodeType, typename ...Args>
NodeType * Graph::add(Args && ...args)
{
    auto location = nodeArena.alloc(sizeof(NodeType));
    auto node = new(location) NodeType(std::forward<Args>(args)...);
    nodes.push_back(node);
    if (auto buffer = dynamic_cast<Buffer*>(node); buffer != nullptr)
        buffers.push_back(buffer);
    return node;
}

#endif // GRAPH_HPP_
