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
 * LeetCode: https://leetcode.com/problems/remove-linked-list-elements/
 *【题目】
 * 移除单链表中的所有值为 val 的节点
 *【要求】
 * 如果链表长度为 N ，则时间复杂度为 O(N)，空间复杂度为 O(1)。
 *【解题思路】 
 * 1、如果当前节点是待删除元素，则删除当前节点。
 * 2、对当前节点的后续节点做同样的处理
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

 // 移除 head 后的所有值为 val 的节点
ListNode* remove_elements(ListNode* head, int val) 
{
    if (head == nullptr) return nullptr;
    
    if (head->val == val)
    {
        ListNode* cur_node = head;
        head = remove_elements(head->next, val);
        delete cur_node;
    }
    else
    {
        head->next = remove_elements(head->next, val);
    }
    
    return head;
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
    ListNode* singly_list = nullptr;

    create_singly_list(singly_list, {10, 2, 2, 2, 5, 2, 7, 2, 5, 10});
    cout << "原单向链表： ";
    print_singly_list(singly_list);
    singly_list = remove_elements(singly_list, 5);
    cout << "删除 5 素后的单向链表： ";
    print_singly_list(singly_list);
}