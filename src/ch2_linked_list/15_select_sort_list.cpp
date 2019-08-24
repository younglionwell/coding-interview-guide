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
 * LeetCode: https://leetcode.com/problems/sort-list/
 *【题目】
 * 单链表的选择排序: 从小到大排序
 *【要求】
 * 如果链表长度为 N，空间复杂度为 O(1)。
 *【解题思路】 
 * 1. 按照选择排序的思路，遍历链表排序, 依次选择排序
 * 2. 扩展一个插入排序
 * 3. 快速排序：https://blog.csdn.net/yanglingwell/article/details/81043009
 */
 
#include <list>
#include <iostream>
#include <algorithm>
 
 using namespace std;
 
 // 单向链表节点
struct ListNode
{
    ListNode* next;
    int val;
    
    ListNode(int v) : val(v), next(nullptr){}
};

// 选择排序
ListNode* select_sort_list(ListNode* head)
{
    // 头结点的前一个节点
    ListNode pre_head(-1);
    pre_head.next = head;

    ListNode* iter = nullptr;         // 正在遍历的节点
    ListNode* pre_min_node = nullptr; // 最小值节点的前一个节点
    ListNode* cur_node = &pre_head;   // 当前正在计算节点的前一个节点

    while (cur_node->next != nullptr)
    {
        iter = cur_node;
        pre_min_node = cur_node;

        // 选择最小的节点的上一个节点
        while (iter->next != nullptr)
        {
            if (iter->next->val <= pre_min_node->next->val)
            {
                pre_min_node = iter;
            }
            iter = iter->next;
        }

        // 交换 pre_min_node->next 和 cur_node->next 的位置
        if (pre_min_node != cur_node)
        {
            swap(cur_node->next, pre_min_node->next);
            swap(cur_node->next->next, pre_min_node->next->next);
        }

        cur_node = cur_node->next;
    }
    
    return pre_head.next;
}

// 递归插入排序
ListNode* insert_sort_list(ListNode* head)
{
    if (head == nullptr) return nullptr;
    
    ListNode* sorted_list_head = insert_sort_list(head->next);
    ListNode* iter = sorted_list_head;
    
    // 选择 head 的位置插入
    while (true)
    {
        if (sorted_list_head == nullptr || (iter == sorted_list_head && head->val <= iter->val))
        {
            head->next = sorted_list_head;
            sorted_list_head = head;
            break;
        }
        if (iter->next == nullptr || head->val <= iter->next->val)
        {
            head->next = iter->next;
            iter->next = head;
            break;
        }
        
        iter = iter->next;
    }
    
    return sorted_list_head;
}

// 对链表进行快速排序
ListNode* quick_sort_list(ListNode* head)
{
    if(head == nullptr || head->next == nullptr) return head;

    ListNode* anchorNode = head;
    ListNode *lowerNodeBeg = nullptr;
    ListNode *higherNodeBeg = nullptr;
    
    // partion 操作
    head = head->next;
    while (head != nullptr)
    {
        ListNode* curNode = head;
        head = head->next;
        
        if (anchorNode->val >= curNode->val)
        {
            curNode->next = lowerNodeBeg;
            lowerNodeBeg = curNode;
        }
        else
        {
            curNode->next = higherNodeBeg;
            higherNodeBeg = curNode;
        }
    }
    
    // 分别对左右边两边数据进行处理
    lowerNodeBeg = quick_sort_list(lowerNodeBeg);
    higherNodeBeg = quick_sort_list(higherNodeBeg);
    
    // 将大于 anchorNode 的数，anchorNode 的数 和 小于 anchorNode 的数连接起来
    ListNode *lowerNodeEnd = lowerNodeBeg;
    
    while (lowerNodeEnd != nullptr && lowerNodeEnd->next != nullptr)
    {
        lowerNodeEnd = lowerNodeEnd->next;
    }
    
    if (lowerNodeEnd == nullptr)
    {
        lowerNodeBeg = anchorNode;
    }
    else
    {
        lowerNodeEnd->next = anchorNode;
    }
    
    anchorNode->next = higherNodeBeg;
    
    return lowerNodeBeg;
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

    create_singly_list(singly_list, {10, 2, 1, 9, 3, 4, 7, 6, 5, 0});
    cout << "原单向链表： ";
    print_singly_list(singly_list);
    singly_list = select_sort_list(singly_list);
    cout << "选择排序后的单向链表： ";
    print_singly_list(singly_list);

    ListNode* singly_list2 = nullptr;

    create_singly_list(singly_list2, {10, 2, 1, 9, 3, 4, 7, 6, 5, 0});
    cout << "原单向链表： ";
    print_singly_list(singly_list2);
    singly_list2 = select_sort_list(singly_list2);
    cout << "插入排序后的单向链表： ";
    print_singly_list(singly_list2);

    ListNode* singly_list3 = nullptr;

    create_singly_list(singly_list3, {10, 2, 1, 9, 3, 4, 7, 6, 5, 0});
    cout << "原单向链表： ";
    print_singly_list(singly_list3);
    singly_list3 = quick_sort_list(singly_list3);
    cout << "快速排序后的单向链表： ";
    print_singly_list(singly_list3);
}