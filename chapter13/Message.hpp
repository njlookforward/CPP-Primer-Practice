#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <set>
#include "Folder.hpp"

// 自定义类进行资源管理需要定义拷贝控制成员，除此之外，进行簿记操作也需要拷贝控制成员
// 只要涉及到改变资源的操作，就需要定义拷贝控制成员
// 对于Message来说，拷贝控制操作针对的就是更新Folders，添加新的还是删除旧的，脑袋一定要清醒
class Message {
    friend void swap(Message &lhs, Message &rhs);
public:
    explicit Message(const std::string &msg = std::string()): _msg(msg) {}  // default constructor

    Message(const Message &rhs):_msg(rhs._msg), _folders(rhs._folders)
    {   add_to_folders(rhs);    }

    // need to judge add noexcept or not,因为有向set添加元素的操作，需要分配内存，可能抛出bad_alloc异常
    Message(Message &&rhs):_msg(std::move(rhs._msg))
    {
        rhs.remove_from_folders();
        add_to_folders(rhs);
        _folders = std::move(rhs._folders);
        rhs._folders.clear();
    }

    Message &operator=(const Message &rhs);
    Message &operator=(Message &&rhs);

    ~Message()  {   remove_from_folders();  }

    void save(Folder &fd);      // 将邮件添加到某个文件夹中，因此需要实参传址
    void remove(Folder &fd);    // 需要调用对象删除对象保存的Message指针

    // 只是添加或者删除folder指针，不更新folder中的message指针  exercise_13_37
    void addFold(Folder *pfd);
    void remFold(Folder *pfd);

private:
    void add_to_folders(const Message &m);
    void remove_from_folders();

    std::string         _msg;   // 多个文件只有一份内容副本
    std::set<Folder *>  _folders;    // 文件保存到的路径的集合
};

void swap(Message &lhs, Message &rhs);

#endif