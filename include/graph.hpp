#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <memory>
#include <vector>
#include <string>

#include "graph_node.hpp"
//#include "buffer_node.hpp"

class Graph
{
    private:
        std::vector<std::unique_ptr<GraphNode>> nodes;
        //std::vector<BufferNode*> buffers;

    public:
        Graph() {}

        template <typename NodeType, typename Args...>
        NodeType * add(Args ... && args);

        void reset_buffers();
        void clear(); // What's that supposed to do again?

        static Graph FromFile(std::string filename);
};

#endif // GRAPH_HPP_
