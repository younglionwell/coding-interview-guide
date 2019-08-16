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
 * LeetCode: https://leetcode.com/problems/09_add_two_numbers-ii/
 *【题目】
 * 将两个单链表求和，返回相加后的单链表
 *【要求】
 * 如：1 -> 4 -> 9 和 1 -> 1 结果为 1 -> 6 -> 0 (149 + 11 = 160)
 *【解题思路】 
 * 先将两个加数链表翻转，然后再相加
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

// 非递归翻转单向链表 head， 返回其新的头节点
ListNode* reverse_singly_list(ListNode* head)
{
    ListNode* reverse_head = nullptr;
    ListNode* cur_node = nullptr;
    
    while (head != nullptr)
    {
        // 遍历 head 链表
        cur_node = head;
        head = head->next;
        
        // 头插法将 head 链表的节点插入 reverse_head 链表中
        cur_node->next = reverse_head;
        reverse_head = cur_node;
    }
    
    return reverse_head;
}

ListNode* add_two_numbers(ListNode* l1, ListNode* l2)
{
    l1 = reverse_singly_list(l1);
    l2 = reverse_singly_list(l2);

    ListNode* result_head = nullptr;
    ListNode* result_tail = nullptr;
    int carry = 0;

    while (l1 != nullptr || l2 != nullptr)
    {
        if (l1 != nullptr)
        {
            carry += l1->val;
            l1 = l1->next;
        }
        if (l2 != nullptr)
        {
            carry += l2->val;
            l2 = l2->next;
        }

        do
        {
            if (result_head == nullptr)
            {
                result_head = result_tail = new ListNode(carry % 10);
            }
            else 
            {
                result_tail->next = new ListNode(carry % 10);
                result_tail = result_tail->next;
            }
            carry /= 10;
        } while (l1 == nullptr && l2 == nullptr && carry != 0);
        
    }

    result_head = reverse_singly_list(result_head);
    return result_head;
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
    ListNode* lhv = nullptr;
    ListNode* rhv = nullptr;
    ListNode* res = nullptr;
    create_singly_list(lhv, {1, 2, 9, 4});
    create_singly_list(rhv, {1, 2, 6});
    print_singly_list(lhv);
    print_singly_list(rhv);
    res = add_two_numbers(lhv, rhv);

    print_singly_list(res);
    return 0;
}
