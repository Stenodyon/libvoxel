#ifndef MEMORY_ARENA_HPP_
#define MEMORY_ARENA_HPP_

#include <utility> // std::forward
#include <vector>

class MemoryArena
{
    private:
        size_t size;
        size_t capacity;
        char *data;

    public:
        MemoryArena(size_t capacity);
        ~MemoryArena();

        void * alloc(size_t count);
        void free();
};

#endif // MEMORY_ARENA_HPP_
