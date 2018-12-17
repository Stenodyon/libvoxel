#include <cstdlib>

#include "memory_arena.hpp"

MemoryArena::MemoryArena(size_t capacity)
    : size(0),
    capacity(capacity)
{
    data = (char*)malloc(this->capacity);
}

MemoryArena::~MemoryArena()
{
    ::free(data);
}

void * MemoryArena::alloc(size_t count)
{
    if (size + count > capacity)
        return nullptr;

    auto ptr = (void*)(data + size);
    size += count;
    return ptr;
}

void MemoryArena::free()
{
    size = 0;
}
