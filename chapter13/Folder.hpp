#ifndef FOLDER_HPP
#define FOLDER_HPP

#include <set>
#include "Message.hpp"

// 对于Folder来说，拷贝控制成员是控制更新message，添加新的folder还是删除folder
class Folder {
public:
    Folder() = default;

    Folder(const Folder &rhs)   { add_to_msgset();    }
    Folder &operator=(const Folder &rhs);

    // 对于Folder来说，没有必要去定义移动操作，没有资源需要移动的，只是登记和删除而已，没有赋值双方的资源交换
    // 准确来说，set<Message *>不是移动的，而是通过addMsg() and removeMsg()添加和删除得到的
    // Folder(Folder &&);
    // Folder &operator=(Folder &&rhs);

    ~Folder()   { remove_from_msgset();   }

    void addMsg(Message *pm);       // 将新保存的message添加到文件夹中
    void removeMeg(Message *pm);    // 将所选择的Message从文件夹中删除

private:
    void add_to_msgset(const Folder &rhs);
    void remove_from_msgset();

    std::set<Message *> _msgset;
};


#endif