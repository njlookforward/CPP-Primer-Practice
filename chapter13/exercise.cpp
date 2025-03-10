#include "exercise.hpp"
using namespace std;

void fcn1_copy(X x1) {}

X fcn2_right_val()
{   
    // return X(); 
    X ret;
    return ret;
}

X &fcn3_left_val(X &x1)
{
    return x1;
}

numbered::numbered()
{
    srand(static_cast<unsigned int>(time(NULL)));
    mysn = rand() % 1000;
}

numbered::numbered(const numbered &rhs)
{
    mysn = rhs.mysn + 1;
}


/***********Employee Definition***********/
size_t Employee::_cnt = 0;

// void TreeNode::addNode(const string &val)
// {
//     if(_val == val)
//         ++_cnt;
//     else if(_val > val)
//     {
//         if(!_lchild)
//             _lchild = new TreeNode(val);
//         else
//             _lchild->addNode(val);
//     }
//     else
//     {
//         if(!_rchild)
//             _rchild = new TreeNode(val);
//         else
//             _rchild->addNode(val);
//     }
// }

// void TreeNode::destroy()
// {
//     if(_lchild)
//     {
//         _lchild->destroy();
//         delete _lchild;
//         _lchild = nullptr;
//     }
//     if(_rchild)
//     {
//         _rchild->destroy();
//         delete _rchild;
//         _rchild = nullptr;
//     }
// }

// void TreeNode::inorder()
// {
//     cout << _val << "(" << _cnt << ") ";
//     if(_lchild)
//         _lchild->inorder();
//     if(_rchild)
//         _rchild->inorder();
// }

// BinStrTree &BinStrTree::operator=(const BinStrTree &rhs)
// {
//     ascendCnt(rhs);
//     descendCnt();
//     _root = rhs._root;
//     _use = rhs._use;

//     return *this;
// }

// void BinStrTree::insert(const std::string &val)
// {
//     if(!_root)  // 此时是空树
//     {
//         _root = new TreeNode(val);
//         return;
//     }

//     _root->addNode(val);
// }

// void BinStrTree::clear()
// {
//     // 谁申请资源就由谁释放资源，根节点申请了左子树和右子树，那么只需要用来释放子树，BinStrTree申请了根节点，那么由BInStrTree释放根节点，没有delete this的设计，太难看了
//     _root->destroy();
//     delete _root;
//     _root = nullptr;
// }

// void BinStrTree::inorderTraversal()
// {
//     _root->inorder();
// }

// void BinStrTree::descendCnt()
// {
//     if(--*_use == 0)
//     {
//         delete _use;
//         clear();
//     }
// }
