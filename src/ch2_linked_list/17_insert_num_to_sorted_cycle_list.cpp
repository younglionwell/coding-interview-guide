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
 * 想排好序的循环链表中插入一个节点，要求插入后依然有序。
 *【要求】
 * 如果链表长度为 N，空间复杂度为 O(1)，时间复杂度 O(N)
 *【解题思路】 
 * 遍历循环链表，找到新插入的数据应该在的位置，然后插入。
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

// 插入数据 num， 返回新的头结点
ListNode* insert_num(ListNode* head, int num)
{
    if (head == nullptr) return new ListNode(num);
    ListNode* iter = head;
    
    // 找到尾节点
    while (iter->next != head) iter = iter->next;
    
    // 找到应该插入的位置
    while (true)
    {
        if (iter->next->val < num)
        {
            iter = iter->next;
        }
        else
        {
            break;
        }
        
        if (iter->next == head)
        {
            break;
        }
    };
    
    // 插入新节点
    ListNode* new_node = new ListNode(num);
    new_node->next = iter->next;
    iter->next = new_node;
    
    // 新节点是否为头结点
    if (new_node->next == head && new_node->val <= head->val)
    {
        return new_node;
    }
    else 
    {
        return head;
    }
}

// 创建单链表
ListNode* create_singly_list(ListNode*& head, list<int> vals)
{
    if (vals.empty()) return nullptr;
    head = new ListNode(vals.front());
    vals.pop_front();
    
    if (vals.empty())
    {
        head->next = head;
        return head;
    }
    
    ListNode* tail = create_singly_list(head->next, vals);
    tail->next = head;
    return tail;
}

// 打印单链表
void print_singly_list(ListNode* head, ListNode* iter)
{
    if(iter == nullptr)
    {
        return;
    }
    if (iter->next == head)
    {
        cout << iter->val << endl;
        return;
    }

    cout << iter->val << " ";
    print_singly_list(head, iter->next);
}

int main()
{
    ListNode* singly_list = nullptr;

    create_singly_list(singly_list, {1, 2, 3, 4, 6, 7, 8, 9, 10});
    cout << "原单向链表： ";
    print_singly_list(singly_list, singly_list);
    singly_list = insert_num(singly_list, 11);
    singly_list = insert_num(singly_list, 5);
    singly_list = insert_num(singly_list, 0);
    cout << "插入 {0, 5, 11} 后的单向链表： ";
    print_singly_list(singly_list, singly_list);
}