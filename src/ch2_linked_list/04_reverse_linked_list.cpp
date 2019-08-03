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
 * LeetCode(翻转单向链表): https://leetcode.com/problems/reverse-linked-list/
 *【题目】
 * 翻转双向链表和单向链表
 *【要求】
 * 如果链表长度为 N ，则时间复杂度为 O(N)，空间复杂度为 O(1)。
 *【解题思路】 
 * 解题方式比较多，这里分别用递归和非递归两种方式求解，抛砖引玉。
 * 非递归翻转单链表：依次遍历原链表，用头插法创建新链表。
 * 递归翻转双链表： 先将当前节点后面的所有节点翻转，然后再将当前节点翻转。
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

// 双向链表节点
struct DoubleListNode
{
    DoubleListNode* next;
    DoubleListNode* prev;
    int val;
    
    DoubleListNode(int v) : val(v), next(nullptr), prev(nullptr){}
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

// 递归翻转双向链表 head，返回其新的头结点
DoubleListNode* reverse_double_list(DoubleListNode* head)
{
    if (head == nullptr) return nullptr;

    if (head->next == nullptr)
    {
        head->prev = nullptr;
        return head;
    }

    // 翻转当前节点后面的节点
    DoubleListNode* new_head = reverse_double_list(head->next);

    // 翻转当前节点
    head->prev = head->next; 
    head->prev->next = head;
    head->next = nullptr;

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

// 打印双链表
void print_double_list(DoubleListNode* head)
{
    if (head == nullptr) return;

    cout << "正向打印双向链表： ";
    while (true)
    {
        cout << head->val << " ";

        if (head->next == nullptr)
        {
            break;
        }
        head = head->next;
    }
    cout << endl;

    cout << "逆向打印双向链表： ";
    while (head != nullptr)
    {
        cout << head->val << " ";
        head = head->prev;
    }
    cout << endl;
}

int main()
{
    // 翻转单向链表测试
    ListNode* singly_list = nullptr;

    create_singly_list(singly_list, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    cout << "翻转前的单向链表： ";
    print_singly_list(singly_list);
    singly_list = reverse_singly_list(singly_list);
    cout << "翻转后的单向链表： ";
    print_singly_list(singly_list);


    // 翻转双向链表测试
    DoubleListNode* double_list = nullptr;

    create_double_list(double_list, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    cout << endl << "翻转前的双向链表： " << endl;
    print_double_list(double_list);
    double_list = reverse_double_list(double_list);
    cout << endl << "翻转后的双向链表： " << endl;
    print_double_list(double_list);

    return 0;
}
