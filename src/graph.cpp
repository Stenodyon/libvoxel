#include "graph.hpp"

Graph::Graph() : nodeArena(NODE_ARENA_SIZE)
{
}

void Graph::reset_buffers()
{
    for (auto& buffer : buffers)
        buffer->reset();
}

void Graph::clear()
{
    for (auto &node : nodes)
        delete node;
    nodes.clear();
    nodeArena.free();
}
