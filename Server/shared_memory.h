#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <iostream>
#include "account.h"

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/functional/hash.hpp>
#include <boost/unordered_map.hpp>
#include <functional>

using namespace boost::interprocess;

typedef managed_shared_memory::segment_manager                                      segment_manager_t;
typedef allocator<void, segment_manager_t>                                          void_allocator;
typedef allocator<char, segment_manager_t>                                          char_allocator;
typedef basic_string<char, std::char_traits<char>, char_allocator>                  char_string;
typedef char_string                                                                 KeyType;
typedef std::pair<char_string, int>                                                 MappedType;
typedef allocator<std::pair<const char_string, MappedType>, segment_manager_t>      pair_allocator;
typedef boost::unordered_map<KeyType, MappedType, boost::hash<KeyType>,
        std::equal_to<KeyType>, pair_allocator>                                     MyHashMap;

class SharedMemory{
public:
    SharedMemory();
    ~SharedMemory();
    bool addRecord(std::string data);
    bool delRecord(std::string data);
    bool isRecord(std::string data);

private:
    MyHashMap * m_clientBase;
    managed_shared_memory * m_segment;
    int m_idRecord = 0;
};

extern SharedMemory globalSharedMemory;

#endif // SHARED_MEMORY_H
