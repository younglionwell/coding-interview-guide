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
 * LeetCode：https://leetcode.com/problems/reverse-nodes-in-k-group/
 *【题目】
 * 将单链表的每 K 个节点之间逆序：给定一个单链表的头结点 head，一个整数 k。实现让每 k 个节点之间逆序，
 * 如果最后不够 k 个节点，则不调整最后几个节点。如：
 * head: 1->2->3->4->5->6->7->8, k = 3 调整后为 3->2->1->6->5->4->7->8
 *【要求】
 * 如果链表长度为 N ，则时间复杂度为 O(N)，空间复杂度为 O(1)。
 *【解题思路】 
 * 利用依次遍历节点，每 k 个节点调用改自 04_reverse_linked_list.cpp 的 reverse_singly_list 函数翻转链表。
 */

#include<list>
#include<iostream>

using namespace std;

// 单向链表节点
struct ListNode
{
    ListNode* next;
    int val;
    
    ListNode(int v) : val(v), next(nullptr){}
};

// 非递归翻转单向链表 [head, tail)， 返回其新的头节点
ListNode* reverse_singly_list(ListNode* head, ListNode* tail)
{
    ListNode* reverse_head = tail;
    ListNode* cur_node = nullptr;
    
    while (head != tail)
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

ListNode* reverse_k_group(ListNode* head, int k) 
{
    // 返回的链表的首尾节点
    ListNode* new_head = head;
    ListNode* new_tail = nullptr;
    
    int cnt = 1;
    ListNode* front_iter = head;
    ListNode* back_iter = head;
    
    while (front_iter != nullptr)
    {
        if (cnt < k)
        {
            ++cnt;
            front_iter = front_iter->next;
        }
        else if (cnt == k) // 逆转刚才数过的 k 个节点
        {   
            if (new_tail == nullptr)
            {
                new_head = reverse_singly_list(back_iter, front_iter->next);
                new_tail = back_iter;
            }
            else
            {
                new_tail->next = reverse_singly_list(back_iter, front_iter->next);
                new_tail = back_iter;
            }
            
            cnt = 1;
            back_iter = front_iter = new_tail->next;
        }
    }
    
    return new_head;
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
    // 翻转单向链表测试
    ListNode* singly_list = nullptr;

    create_singly_list(singly_list, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    cout << "翻转前的单向链表： ";
    print_singly_list(singly_list);
    singly_list = reverse_k_group(singly_list, 4);
    cout << "翻转后的单向链表： ";
    print_singly_list(singly_list);
}
