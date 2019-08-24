/****************************************************************************
**
** Copyright 2019 yanglingwell@sina.com
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation the
** rights to use, copy, modify, merge, publish, distribute, sublicens-e, and/or
** sell copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*
 *【题目】
 * 将搜索二叉树转化为有序的双向链表(树木的 left, right 指针分别表示双向链表的 prev, next 指针)
 *【要求】
 * 时间复杂度 O(N)
 *【解题思路】 
 * 递归中序遍历原树，并按照遍历顺序改造成双向链表。
 */
 
#include <list>
#include <iostream>
 
using namespace std;

// 双向链表/树的节点
struct Node
{
    Node* left;
    Node* right;
    int val;
    
    Node(int v) : val(v), left(nullptr), right(nullptr){}
};

// 返回链表的头结点和尾节点
pair<Node*, Node*> convert_bst_to_doubly_linked_list(Node* root)
{
    if (root == nullptr) return {nullptr, nullptr};
    
    pair<Node*, Node*> new_list = { root, root };
    pair<Node*, Node*> left_list = convert_bst_to_doubly_linked_list(root->left);
    pair<Node*, Node*> right_list = convert_bst_to_doubly_linked_list(root->right);
    
    if (left_list.first != nullptr)
    {
        left_list.second->right = new_list.first;
        new_list.first->left = left_list.second;
        
        new_list.first = left_list.first;
    }
    if (right_list.first != nullptr)
    {
        right_list.first->left = new_list.second;
        new_list.second->right = right_list.first;
        
        new_list.second = right_list.second;
    }
    
    return new_list;
}

// 创建搜索二叉树
Node* create_binary_search_tree(const list<int>& vals)
{
    if (vals.empty()) return nullptr;
    
    Node* root = nullptr;
    Node* iter = nullptr;
    
    for (auto val : vals)
    {
        if (root == nullptr)
        {
            iter = root = new Node(val);
        }
        else
        {
            iter = root;
            while (true)
            {

                if (iter->val <= val)
                {
                    if (iter->right == nullptr) 
                    {
                        iter->right = new Node(val);
                        break;
                    }
                    else
                    {
                        iter = iter->right;
                    }
                }
                else
                {
                    if (iter->left == nullptr) 
                    {
                        iter->left = new Node(val);
                        break;
                    }
                    else
                    {
                        iter = iter->left;
                    }
                }
            }
        }
    }
    
    return root;
}

// 中序遍历二叉树
void print_binary_search_tree(Node* node, bool init = true)
{
    if (node == nullptr) 
    {
        return;
    }
    print_binary_search_tree(node->left, false);
    cout << node->val << " ";
    print_binary_search_tree(node->right, false);
    
    if (init == true) cout << endl;
}

void print_doubly_linked_list(Node* dlist)
{
    while (dlist != nullptr)
    {
        cout << dlist->val << " ";
        dlist = dlist->right;
    }
    cout << endl;
}

void print_doubly_linked_list_reverse(Node* dlist)
{
    while (dlist != nullptr)
    {
        cout << dlist->val << " ";
        dlist = dlist->left;
    }
    cout << endl;
}

int main()
{
    Node* tree = create_binary_search_tree({4, 5, 9, 3, 0, 2, 1, 6, 7, 8});
    cout << "binary search tree: ";
    print_binary_search_tree(tree);
    
    auto dlist = convert_bst_to_doubly_linked_list(tree);
    cout << "doubly linked list(normal): ";
    print_doubly_linked_list(dlist.first);
    cout  << "doubly linked list(reverse): ";
    print_doubly_linked_list_reverse(dlist.second);
    
    return 0;
}
