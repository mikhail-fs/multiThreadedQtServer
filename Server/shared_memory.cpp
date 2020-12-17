#include "shared_memory.h"

SharedMemory::SharedMemory()
{
    m_segment = new managed_shared_memory(open_or_create, "MySharedMemory", (long long int)100*1024*1024*1024);

    void_allocator m_allocInst = m_segment->get_segment_manager();

    m_clientBase = m_segment->find_or_construct<MyHashMap>("MyHashMap")
       (3, boost::hash<char_string>(), std::equal_to<char_string>(), m_allocInst);
}

SharedMemory::~SharedMemory()
{
    shared_memory_object::remove("MySharedMemory");
}

bool SharedMemory::addRecord(std::string data)
{
    Account account(data);

    char_string username(account.getUserName().c_str(), m_segment->get_allocator<char_string>());
    char_string password(account.getUserPass().c_str(), m_segment->get_allocator<char_string>());

    auto find = m_clientBase->find(username);
    if(find == m_clientBase->end())
    {
        if(account.createAccount()){
            ++m_idRecord;
            m_clientBase->insert({username, {password, m_idRecord}});
            return true;
        }
        else
        {
            return false;
        }
//        for(auto& [key, pair] : *m_clientBase)
//        {
//            std::cout << key << "--" << pair.first << "==" << pair.second << std::endl;
//        }

    }
    else
    {
        return false;
    }
}

bool SharedMemory::delRecord(std::string data)
{
    Account account(data);

    char_string username(account.getUserName().c_str(), m_segment->get_allocator<char_string>());
    char_string password(account.getUserPass().c_str(), m_segment->get_allocator<char_string>());

    auto find = m_clientBase->find(username);
    if(find != m_clientBase->end())
    {
        if(find->second.first == password)
        {
            if(account.deleteAccount(find->second.second))
            {
                m_clientBase->erase(find);
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool SharedMemory::isRecord(std::string data)
{
    Account account(data);

    char_string username(account.getUserName().c_str(), m_segment->get_allocator<char_string>());
    char_string password(account.getUserPass().c_str(), m_segment->get_allocator<char_string>());

    auto find = m_clientBase->find(username);
    if(find != m_clientBase->end())
    {
        if(find->second.first == password)
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}

SharedMemory globalSharedMemory;
