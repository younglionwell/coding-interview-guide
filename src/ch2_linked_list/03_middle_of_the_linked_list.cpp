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
 * LeetCode(查找中间节点): https://leetcode.com/problems/middle-of-the-linked-list/
 *【题目】
 * 删除链表的中间节点
 *【要求】
 * 给定一个单向链表，删除该单链表正中间的链表
 *【解题思路】 
 * 快慢指针。快指针走两步，慢指针走一步。当快指针到达链表末尾时，慢指针到达链表的正中间。
 */

#include <list>
#include <iostream>

using namespace std;

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 删除单链表的中间节点
void del_middle_node(ListNode*& head) 
{
    ListNode* fast_iter = head;
    ListNode* slow_iter = head;
    // 慢指针的上一个节点
    ListNode* slow_iter_prev = nullptr;
    
    while (fast_iter != nullptr && fast_iter->next != nullptr)
    {
        // 快指针走两步
        fast_iter = fast_iter->next->next;
        // 慢指针走一步
        slow_iter_prev = slow_iter;
        slow_iter = slow_iter->next;
    }
    
    // 删除慢指针指向的节点
    if (slow_iter == head)
    {
        head = head->next;
        delete slow_iter;
    }
    else
    {
        slow_iter_prev->next = slow_iter->next;
        delete slow_iter;
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
    ListNode* head = nullptr;
    create_singly_list(head, {1, 2, 3, 4, 5});

    cout << "删除中间节点前： ";
    print_singly_list(head);

    del_middle_node(head);

    cout << "删除中间节点后： ";
    print_singly_list(head);

    return 0;
}
