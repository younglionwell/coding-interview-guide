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
 * 按照左右半区间的方式重新组合单链表
 * 给定一个单链表的头部节点 head，链表长度为 N，如果 N 是偶数，那么前 N / 2 个节点算作左半区，后 N / 2 个节点算作右半区；
 * 如果 N 为奇数，那么前 N / 2 个节点算作左半区，后 N / 2 + 1 个节点算作右半区。左半区从左到右依次记为 L1->L2->...，
 * 右半区从左到右依次记为 R1->R2->...，请将单链表调整成 L1->R1->L2->R2->... 的形式。
 *【要求】
 * 假设链表长度为 N, 则空间复杂度：O(1), 时间复杂度：O(N)
 *【解题思路】 
 * 1. 根据 03_middle_of_the_linked_list.cpp 的快慢指针方法找到中间节点的指针，拆成左右两个区间的链表。
 * 2. 根据要求组合成一个交叉的链表
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


// 1. 找到链表的中间节点
ListNode* mid_list(ListNode* head)
{
    ListNode* fast = head;
    ListNode* slow = nullptr;
    
    while (fast != nullptr && fast->next != nullptr)
    {
        // slow 移动一步
        if (slow == nullptr) slow = head;
        else slow = slow->next;
        
        // fast 移动两步
        fast = fast->next->next;
    }
    
    if (slow != nullptr)
    {
        ListNode* right = slow->next;
        slow->next = nullptr;
        return right;
    }
    
    return slow;
}

// 2. 根据要求组合成一个交叉的链表
ListNode * relocate(ListNode * head)
{
    ListNode* right = mid_list(head);
    ListNode* left = head;
    
    while(left->next != nullptr)
    {
        ListNode* temp = right;
        right = right->next;
        
        temp->next = left->next;
        left->next = temp;
        left = left->next->next;
    }
    left->next = right;
    
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

    create_singly_list(singly_list, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    cout << "原单向链表： ";
    print_singly_list(singly_list);
    singly_list = relocate(singly_list);
    cout << "重新排列的单向链表： ";
    print_singly_list(singly_list);
}