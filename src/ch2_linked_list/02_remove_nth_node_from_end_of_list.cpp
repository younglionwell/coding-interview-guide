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
 * LeetCode: https://leetcode.com/problems/remove-nth-node-from-end-of-list/ (单链表)
 *【题目】
 * 分别实现两个函数：
 *（1）删除单向链表倒数第 k 个节点的函数
 *（2）删除双向链表倒数第 k 个节点的函数
 *【要求】
 * 链表长度为 N 时，时间复杂度为 O(N)
 *【解题思路】 
 * 单链表，双链表的解题方式类似，只是删除操作略有不同。 
 * 下面用递归的方式实现删除单链表节点的函数，用非递归实现删除双链表的函数，抛砖引玉。
 * 递归： 递归到链表结尾返回的时候，计算返回的层数就可以知道当前节点是倒数第几个节点了。
 * 非递归：让一根指针先走 k 步， 然后第二根指针再跟着第一根指针一起前进。
 *        当第一根指针指向链表结尾的 nullptr 时，第二根指针指向倒数第 k 个节点。
 */

#include <iostream>
#include <list>

using namespace std;

// 单向链表节点
struct ListNode
{
    ListNode* next;
    int val;
    
    ListNode(int v) : val(v), next(nullptr){}
};

// 双向链表节点
struct DoubleListNode
{
    DoubleListNode* next;
    DoubleListNode* prev;
    int val;
    
    DoubleListNode(int v) : val(v), next(nullptr), prev(nullptr){}
};

// 删除单链表的倒数第 k 个节点（返回 next 节点是倒数序号）
int del_singly_backward_kth_node(ListNode*& cur_node, int k)
{
    if (cur_node == nullptr) return 0;
    int cur_node_back_num = del_singly_backward_kth_node(cur_node->next, k) + 1;
    
    // 删除当前节点
    if (cur_node_back_num == k)
    {
        ListNode* del_node = cur_node;
        cur_node = cur_node->next;
        delete del_node;
    }
    
    return cur_node_back_num;
}

// 删除双链表的倒数第 k 个节点
void del_double_backward_kth_node(DoubleListNode*& cur_node, int k)
{
    int cnt = 0;
    DoubleListNode* prev = cur_node;
    DoubleListNode* rear = cur_node;
    
    while (prev != nullptr)
    {
        // 第一根指针先走 k 步
        prev = prev->next;

        // 第二根指针后走 k 步
        if (cnt < k)
        {
            ++cnt;
        }
        else 
        {
            rear = rear->next;
        }
    }
    
    // 删除第二根指针对应的节点
    if (cnt == k && rear != nullptr)
    {
        if (rear->prev != nullptr)
        {
            rear->prev->next = rear->next;
        }
        else // 待删除的节点是首节点
        {
            cur_node = rear->next;
        }
        
        if (rear->next != nullptr)
        {
            rear->next->prev = rear->prev;
        }
        
        delete rear;
    }
}

// 创建单链表
void create_singly_list(ListNode*& head, list<int> vals)
{
    if (vals.empty()) return;
    head = new ListNode(vals.front());
    vals.pop_front();
    
    create_singly_list(head->next, vals);
}

// 创建双链表
void create_double_list(DoubleListNode*& head, list<int> vals)
{
    if (vals.empty()) return;
    head = new DoubleListNode(vals.front());
    vals.pop_front();
    
    create_double_list(head->next, vals);
    if (head->next != nullptr)
    {
        head->next->prev = head;
    }
}

int main()
{
    ListNode *singlyList = nullptr;
    DoubleListNode *doubleList = nullptr;
    
    create_singly_list(singlyList, {10, 9, 8, 7, 6, 5, 4, 3, 2, 1});
    create_double_list(doubleList, {10, 9, 8, 7, 6, 5, 4, 3, 2, 1});
    
    // 删除双链表的 10，5，1 节点
    del_double_backward_kth_node(doubleList, 10);
    del_double_backward_kth_node(doubleList, 5);
    del_double_backward_kth_node(doubleList, 1);
    DoubleListNode* iter = doubleList;
    DoubleListNode* backIter = nullptr;
    cout << "删除后的双链表节点： ";
    while (iter != nullptr)
    {
        cout << iter->val << " ";
        backIter = iter;
        iter = iter->next;
    }
    cout << endl;
    cout << "删除后的双链表节点(逆向)： ";
    while (backIter != nullptr)
    {
        cout << backIter->val << " ";
        backIter = backIter->prev;
    }
    cout << endl;
    
    // 删除单链表的 10，5，1 节点
    del_singly_backward_kth_node(singlyList, 10);
    del_singly_backward_kth_node(singlyList, 5);
    del_singly_backward_kth_node(singlyList, 1);
    cout << "删除后的单链表节点： ";
    ListNode* iter1 = singlyList;
    while(iter1 != nullptr)
    {
        cout << iter1->val << " ";
        iter1 = iter1->next;
    }
    cout << endl;
    
    return 0;
}
