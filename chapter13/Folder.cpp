#include "Folder.hpp"

// Folder::Folder(Folder &&rhs)
// {
//     add_to_msgset(rhs);
//     rhs.remove_from_msgset();
// }

Folder &Folder::operator=(const Folder &rhs)
{
    if(this != &rhs)
    {
        remove_from_msgset();
        add_to_msgset(rhs);
    }

    return *this;
}

// Folder &Folder::operator=(Folder &&rhs)
// {
//     if(this != &rhs)
//     {
//         remove_from_msgset();
//         add_to_msgset(rhs);
//         rhs.remove_from_msgset();
//     }

//     return *this;
// }

void Folder::addMsg(Message *pm)
{
    _msgset.insert(pm);
    // 绝对不可以再次调用Message.save，否则会形成调用死循环
}

void Folder::removeMeg(Message *pm)
{
    _msgset.erase(pm);
}

void Folder::add_to_msgset(const Folder &rhs)
{
    for (auto &pm : rhs._msgset)
    {
        pm->save(*this);
    }   
}

void Folder::remove_from_msgset()
{
    for (auto &pm : _msgset)
    {
        pm->remove(*this);
    }
}

