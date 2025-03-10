#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>
#include <string>

class BinStrTree;
class TreeNode {
    friend class BinStrTree;
public:
    TreeNode(): _val(), _cnt(0), _lchild(nullptr), _rchild(nullptr) {}
    TreeNode(const std::string &val):_val(val), _cnt(1), _lchild(nullptr), _rchild(nullptr) {}
    
    // 因为TreeNode属于二叉树申请的资源，因此指针变量要独立，不能直接覆盖
    TreeNode(const TreeNode &bt)
    : _val(bt._val), _cnt(bt._cnt), _lchild(nullptr), _rchild(nullptr) {}
    // TreeNode &operator=(const TreeNode &) = default; 我认为TreeNode不需要拷贝赋值运算符
    // 因为对于二叉树来说，用一个二叉树赋值另一个二叉树，只会先释放资源，在新建资源，而不是直接赋值
    ~TreeNode() {   destroy();  }

    void addNode(const std::string &val);
    void addNode(TreeNode *&pt);
    void copysubTree(TreeNode *&newBT);
    void destroy();
    void inorder();

private:
    std::string _val;
    std::size_t _cnt;
    TreeNode *_lchild;
    TreeNode *_rchild;
};

// 现在设计的主体是BinStrTree，因此enroll BinStrTree design
// 类值拷贝设计
class BinStrTree {
public:
    BinStrTree():_root(nullptr) {}
    // 传值不太好弄啊，可恶
    BinStrTree(const BinStrTree &bt);
    BinStrTree &operator=(const BinStrTree &bt);
    ~BinStrTree() { clear();    };

    void insert(const std::string &val);
    void inorderTraversal();

private:
    void clear();   // 工具函数，放在私有成员这里

    TreeNode *_root;
};

#endif