#include "graph.hpp"

void Graph::reset_buffers()
{
    for (auto& buffer : buffers)
        buffer->reset();
}

void Graph::clear()
{
    nodes.clear();
}
