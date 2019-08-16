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
 * LeetCode(分为不小于 x 和小于 x 两部分): https://leetcode.com/problems/partition-list/
 *【题目】
 * 将单链表按照某值 x 分为左边小于 x、中间等于 x、右边大于 x 三部分
 *【要求】
 * 比 LeetCode 要求严格一些，需要分为 3 部分。
 * 链表长度为 N 时，要求时间复杂度 O(N), 空间复杂度 O(1)
 *【解题思路】 
 * 遍历一遍链表，将其分为小于、等于、大于 x 三条链表。最后，将它们按顺序连接起来。
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

ListNode* partition(ListNode* head, int x) 
{
    ListNode *less_head = nullptr, *less_tail = nullptr;
    ListNode *equal_head = nullptr, *equal_tail = nullptr;
    ListNode *greater_head = nullptr, *greater_tail = nullptr;

    while (head != nullptr)
    {
        ListNode* cur_node = head;
        head = head->next;
        cur_node->next = nullptr;

        if (cur_node->val > x)
        {
            if (greater_head == nullptr)
            {
                greater_head = greater_tail = cur_node;
            }
            else
            {
                greater_tail->next = cur_node;
                greater_tail = cur_node;
            }
        }
        else if (cur_node->val == x)
        {
            if (equal_head == nullptr)
            {
                equal_head = equal_tail = cur_node;
            }
            else
            {
                equal_tail->next = cur_node;
                equal_tail = cur_node;
            }
        }
        else
        {
            if (less_head == nullptr)
            {
                less_head = less_tail = cur_node;
            }
            else
            {
                less_tail->next = cur_node;
                less_tail = cur_node;
            }
        }
    }

    if (less_tail != nullptr && equal_head != nullptr)
    {
        less_tail->next = equal_head;
    }
    if (equal_tail != nullptr && greater_head != nullptr)
    {
        equal_tail->next = greater_head;
    }
    if (less_tail != nullptr && equal_head == nullptr && greater_head != nullptr)
    {
        less_tail->next = greater_head;
    }

    if (less_head != nullptr)
    {
        return less_head;
    }
    else if (equal_head != nullptr)
    {
        return equal_head;
    }
    else
    {
        return greater_head;
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
    ListNode* head1 = nullptr;
    ListNode* head2 = nullptr;

    create_singly_list(head1, {2, 9, 5, 1, 3, 0});
    cout << "head1: ";
    print_singly_list(head1);
    head1 = partition(head1, 4);
    cout << "after: ";
    print_singly_list(head1);

    create_singly_list(head2, {1, 6, 5, 8, 5, 4, 3, 5});
    cout << "head2: ";
    print_singly_list(head2);
    head1 = partition(head2, 5);
    cout << "after: ";
    print_singly_list(head2);

    return 0;
}
