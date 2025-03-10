#include "Message.hpp"

Message &Message::operator=(const Message &rhs)
{
    remove_from_folders();
    add_to_folders(rhs);
    _msg = rhs._msg;
    _folders = rhs._folders;

    return *this;
}

Message &Message::operator=(Message &&rhs)
{
    // 注意移动操作假设右值即将被销毁
    if(this != &rhs)
    {
        remove_from_folders();
        add_to_folders(rhs);
        rhs.remove_from_folders();
        _msg = std::move(rhs._msg);
        _folders = std::move(rhs._folders);
        rhs._folders.clear();
    }

    return *this;
}

void Message::save(Folder &fd)
{
    _folders.insert(&fd);
    fd.addMsg(this);
}

void Message::remove(Folder &fd)
{
    _folders.erase(&fd);
    fd.removeMeg(this);
}

void Message::addFold(Folder *pfd)
{
    _folders.insert(pfd);
}

void Message::remFold(Folder *pfd)
{
    _folders.erase(pfd);
}

void Message::add_to_folders(const Message &m)
{
    for (auto &pf : m._folders)
    {
        pf->addMsg(this);
    }
}

void Message::remove_from_folders()
{
    for (auto &pf : _folders)
    {
        pf->removeMeg(this);
    }
}

void swap(Message &lhs, Message &rhs)
{
    using std::swap;
    lhs.remove_from_folders();
    rhs.remove_from_folders();
    swap(lhs._msg, rhs._msg);
    swap(lhs._folders, rhs._folders);
    lhs.add_to_folders(lhs);
    rhs.add_to_folders(rhs);
}
