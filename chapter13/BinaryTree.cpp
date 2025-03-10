#include "BinaryTree.hpp"
using namespace std;

void TreeNode::addNode(const std::string &val)
{
    if(_val == val)
        ++_cnt;
    else if(_val < val)
    {
        if(!_rchild)
            _rchild = new TreeNode(val);
        else
            _rchild->addNode(val);
    }
    else
    {
        if(!_lchild)
            _lchild = new TreeNode(val);
        else
            _lchild->addNode(val);
    }
}

void TreeNode::addNode(TreeNode *&pt)
{
    if(this != pt)
    {
        // 要考虑全面，抛出自插入
        if(_val == pt->_val)
        {
            _cnt += pt->_cnt;
            delete pt;
            pt = nullptr;
        }
        else if(_val > pt->_val)
        {
            if(!_lchild)
                _lchild = pt;
            else
                _lchild->addNode(pt);
        }
        else
        {
            if(!_rchild)
                _rchild = pt;
            else
                _rchild->addNode(pt);
        }
    }
}

void TreeNode::copysubTree(TreeNode *&newBT)
{
    if(!newBT)
    {
        // 说明复制目标的新树是一颗空树，针对的是新树的根节点
        newBT = new TreeNode(*this);
        // error: infinite resursion, 又是一个无限递归的例子，需要返回条件的，要考虑细致
        if(_lchild)
            _lchild->copysubTree(newBT);
        if(_rchild)
            _rchild->copysubTree(newBT);
    }
    else
    {
        // 这就是偷懒的下场，不要偷懒不写else，这次同一个节点被添加两次，就是逻辑发生问题，不要偷懒
        TreeNode *pn = new TreeNode(*this);
        newBT->addNode(pn);
        if(_lchild)
            _lchild->copysubTree(newBT);
        if(_rchild)
            _rchild->copysubTree(newBT);
    }
}

void TreeNode::destroy()
{
    if(_lchild)
    {
        _lchild->destroy();
        delete _lchild;
        _lchild = nullptr;
    }
    if(_rchild)
    {
        _rchild->destroy();
        delete _rchild;
        _rchild = nullptr;
    }
}

void TreeNode::inorder()
{
    cout << _val << "(" << _cnt << ") ";
    // error: infinite recursion, because don't set return condition
    if(_lchild)
        _lchild->inorder();
    if(_rchild)
        _rchild->inorder();
}

BinStrTree::BinStrTree(const BinStrTree &bt) : _root(nullptr)
{
    // 要想实现递归，必须找到进行递归的对象，二叉树中递归的对象都是节点TreeNode
    bt._root->copysubTree(_root);
}

BinStrTree &BinStrTree::operator=(const BinStrTree &bt)
{
    if(this != &bt)
    {
        clear();
        bt._root->copysubTree(_root);
    }
    return *this;
}

void BinStrTree::insert(const string &val)
{
    if(!_root)
    {
        _root = new TreeNode(val);
        return;
    }
    _root->addNode(val);
}

void BinStrTree::clear()
{
    _root->destroy();
    delete _root;
    _root = nullptr;
}

void BinStrTree::inorderTraversal()
{
    _root->inorder();
}
