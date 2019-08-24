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
 * LeetCode: https://leetcode.com/problems/merge-two-sorted-lists/
 *【题目】
 * 合并两个有序链表，要求合并后的链表依旧有序。
 *【要求】
 * 如果链表长度为 N ，则时间复杂度为 O(N)，空间复杂度为 O(1)。
 *【解题思路】 
 * 递归求解：每次将两个链表较小的头结点作为合并后的链表的头结点
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

// 合并两个有序链表
ListNode* merge_two_lists(ListNode* l1, ListNode* l2) 
{
    if (l1 == nullptr)
    {
        return l2;
    }
    if (l2 == nullptr)
    {
        return l1;
    }
    
    if (l1->val < l2->val)
    {
        l1->next = merge_two_lists(l1->next, l2);
        return l1;
    }
    else
    {
        l2->next = merge_two_lists(l1, l2->next);
        return l2;
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

    create_singly_list(head1, {2, 3, 5, 7, 8, 10});
    create_singly_list(head2, {1, 4, 6, 9, 11, 12});
    
    cout << "原单向链表(l1)： ";
    print_singly_list(head1);
    cout << "原单向链表(l2)： ";
    print_singly_list(head2);
    ListNode* merge_list = merge_two_lists(head1, head2);
    cout << "合并后的链表： ";
    print_singly_list(merge_list);
}