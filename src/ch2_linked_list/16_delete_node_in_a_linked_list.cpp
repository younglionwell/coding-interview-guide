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
 * LeetCode: https://leetcode.com/problems/delete-node-in-a-linked-list/
 *【题目】
 * 给定一个链表中的节点 node，但不给定整个链表的头节点。要求删除该节点。
 *【要求】
 * 1. 给定节点不是链表的尾节点，也不是空节点。
 * 2. 时间复杂度：O(1)
 *【解题思路】 
 * 将下一个节点的值复制到当前节点，然后删除下一个节点。
 */

#include <list>
#include <iostream>

using namespace std;

// 单向链表节点
struct ListNode
{
    ListNode* next;
    int val;
    
    ListNode(int v) : val(v), next(nullptr){}
};

void delete_node(ListNode* node) 
{
    if (node == nullptr || node->next == nullptr)
    {
        // 不符合题意
        return;
    }   

    // 复制 next 节点到当前节点
    node->val = node->next->val;

    // 删除 next 节点
    ListNode* temp = node->next;
    node->next = temp->next;
    delete temp;
}

// 创建单链表
void create_singly_list(ListNode*& head, list<int> vals)
{
    if (vals.empty()) return;
    head = new ListNode(vals.front());
    vals.pop_front();
    
    create_singly_list(head->next, vals);
}

// 打印单链表
void print_singly_list(ListNode* head)
{
    if(head == nullptr)
    {
        cout << endl;
        return;
    }

    cout << head->val << " ";
    print_singly_list(head->next);
}


int main()
{
    ListNode* head1 = nullptr;

    create_singly_list(head1, {2, 9, 5, 1, 3, 0});
    cout << "head1: ";
    print_singly_list(head1);
    delete_node(head1->next->next);
    cout << "after delete: ";
    print_singly_list(head1);

    return 0;
}
