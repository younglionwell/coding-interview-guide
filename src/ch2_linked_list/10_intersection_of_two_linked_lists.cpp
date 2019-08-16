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
 * 1. LeetCode(判断是否有环): https://leetcode.com/problems/linked-list-cycle-ii/
 * 2. LeetCode(判断两个无环链表是否相交): https://leetcode.com/problems/intersection-of-two-linked-lists/
 *【题目】
 * 实现以下函数：
 * 1. 判断一个链表是否有环，如果有环，则返回第一个进入环的节点，没有则返回 nullptr
 * 2. 如何判断两个无环链表是否相交，相交则返回第一个相交节点，不相交则返回 nullptr
 * 3. 如何判断两个有环链表是否相交，相交则返回第一个相交的节点(如果在环内相交，随便返回一个环内的一个节点即可)，不想交则返回 nullptr
 *【要求】
 *【解题思路】
 * 1. 利用快慢指针求解， 详见：https://blog.csdn.net/yanglingwell/article/details/80952805
 * 2. 先计算出长度差，然后让长度较长的链表先走长度差那么多步。最后同时步进，直到遇到相同的节点。
 *    详见： https://blog.csdn.net/yanglingwell/article/details/81177842 (下面的实现略微有优化)
 * 3. 利用 1 算出两个链表进入环的位置。如果入口相同，说明相交与非环状部分，则直接用 2 比较。
 *    否则表示相相交于环或者不想交，在这种情况下只需要从一个入口开始遍历环，如果遇到另一个入口则表示在环内相交。
 */

#include <list>
#include <iostream>

using namespace std;

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 快慢指针找到环的入口
ListNode *detect_cycle(ListNode *head) 
{
    if (head == nullptr || head->next == nullptr)
    {
        return nullptr;
    }
    
    ListNode* fast = head->next;
    ListNode* slow = head;
    
    while (fast != slow && fast != nullptr && fast->next != nullptr)
    {
        // 快指针的步长为 2
        fast = fast->next->next;
        // 慢指针的步长为 1
        slow = slow->next;
    }
    
    if (fast == nullptr || fast != slow)
    {
        return nullptr;
    }
    
    slow = head;
    fast = fast->next;
    while (fast != slow)
    {
        fast = fast->next;
        slow = slow->next;
    }
    
    return fast;
}

// 两根非环链表相交的第一个节点
ListNode *get_intersection_node(ListNode *headA, ListNode *headB) 
{
    ListNode* iterA = headA;
    ListNode* iterB = headB;
    int cnt = 0; // |A|-|B|
    
    // 求两链表的长度差
    while(iterA != nullptr || iterB != nullptr)
    {
        if (iterA != nullptr)
        {
            iterA = iterA->next;
            ++cnt;
        }
        
        if (iterB != nullptr)
        {
            iterB = iterB->next;
            --cnt;
        }
    }
    
    // 求相交节点(长链表先走 ||A|-|B|| 步)
    iterA = headA;
    iterB = headB;
    while (cnt > 0 && iterA != nullptr)
    {
        iterA = iterA->next;
        --cnt;
    }
    while (cnt < 0 && iterB != nullptr)
    {
        iterB = iterB->next;
        ++cnt;
    }
    
    while(iterA != nullptr && iterB != nullptr && iterA != iterB)
    {
        iterA = iterA->next;
        iterB = iterB->next;
    }
    
    return iterA;
}

// 两根带环链表相交的第一个节点
ListNode *get_intersection_node_cycle(ListNode *headA, ListNode *headB) 
{
    ListNode* intersection_node = nullptr;
    ListNode* cycleA = detect_cycle(headA);
    ListNode* cycleB = detect_cycle(headB);
    
    if (cycleA == nullptr || cycleB == nullptr) // 有链表没有环？ 输入有问题？
    {
        intersection_node = nullptr;
    }
    else if (cycleA == cycleB) // 在进入环之前相遇
    {
        // 存环的入口
        ListNode* tail = cycleA->next;
       
        // 求进入环之前的两根无环链表的交点
        cycleA->next = nullptr;
        intersection_node = get_intersection_node(headA, headB);
        
        // 恢复环的入口
        cycleA->next = tail;
    }
    else // 在环内相交
    {
        // 如果在环内相交，随便返回一个环内的一个节点即可
        intersection_node = cycleA;
        while (true)
        {
            if (cycleA != cycleB)
            {
                cycleA = cycleA->next;
            }
            else
            {
                // 相交
                break;
            }
            
            // 不想交
            if (cycleA == intersection_node)
            {
                intersection_node = nullptr;
            }
        }
    }
    
    return intersection_node;
}

// 创建带环链表
void create_cycle_list(ListNode*& head)
{
    int n = 9;
    ListNode* tail = nullptr;
    tail = head = new ListNode(n);
    
    while (n--)
    {
        tail->next = new ListNode(n);
        tail = tail->next;
    }
    
    tail->next = head;
    cout << "cycle_enter: " << head << endl;
}

// 创建两个相交链表(返回尾节点)
ListNode* create_intersection_list(ListNode*& headA, ListNode*& headB)
{
    int n = 3;
    ListNode* tailA = nullptr;
    tailA = headA = new ListNode(n);
    while (n--)
    {
        tailA->next = new ListNode(n);
        tailA = tailA->next;
    }     

    n = 5;
    ListNode* tailB = nullptr;
    tailB = headB = new ListNode(n);
    while (n--)
    {
        tailB->next = new ListNode(n);
        tailB = tailB->next;
    }
    
    // 相交的节点
    n = 4;
    ListNode* inter_node = new ListNode(n);
    cout << "inter_node: " << inter_node << endl;
    tailA->next = tailB->next = inter_node;
    while (n--)
    {
        inter_node->next = new ListNode(n);
        inter_node = inter_node->next;
    }
    
    return inter_node;
}

// 创建两个带环链表(交于非环部分)
void create_intersection_list_cycle1(ListNode*& headA, ListNode*& headB)
{
    ListNode* cycle = nullptr;
    create_cycle_list(cycle);
    
    ListNode* tail = create_intersection_list(headA, headB);
    tail->next = cycle;
}

// 创建两个带环链表(交于环形部分)
void create_intersection_list_cycle2(ListNode*& headA, ListNode*& headB)
{
    int n = 3;
    ListNode* tailA = nullptr;
    tailA = headA = new ListNode(n);
    while (n--)
    {
        tailA->next = new ListNode(n);
        tailA = tailA->next;
    }     

    n = 5;
    ListNode* tailB = nullptr;
    tailB = headB = new ListNode(n);
    while (n--)
    {
        tailB->next = new ListNode(n);
        tailB = tailB->next;
    }
    
    ListNode* cycle = nullptr;
    create_cycle_list(cycle);
    
    tailA->next = cycle;
    cout << "cycle_enter1: " << cycle << endl;
    cycle = cycle->next->next;
    tailB->next = cycle;
    cout << "cycle_enter2: " << cycle << endl;
}

int main()
{
    // 测试获取链表中环的入口
    ListNode* cycle_list = nullptr;
    create_cycle_list(cycle_list);
    cout << "cycle_list's cycle_enter: " << detect_cycle(cycle_list) << endl << endl;
    
    // 测试两根链表的交点
    ListNode* inter_list1 = nullptr;
    ListNode* inter_list2 = nullptr;
    create_intersection_list(inter_list1, inter_list2);
    cout << "get_intersection_node(inter_list1, inter_list2): " 
        << get_intersection_node(inter_list1, inter_list2) << endl << endl;
    
    // 测试两根带环链表(相交于非环部分)的交点
    ListNode *l1 = nullptr, *l2 = nullptr;
    create_intersection_list_cycle1(l1, l2);
    cout << "get_intersection_node_cycle(l1, l2): " << get_intersection_node_cycle(l1, l2) << endl << endl;
    
    // 测试两根带环链表(相交于环形部分)的交点
    ListNode *l3 = nullptr, *l4 = nullptr;
    create_intersection_list_cycle2(l3, l4);
    cout << "get_intersection_node_cycle(l3, l4): " << get_intersection_node_cycle(l3, l4) << endl << endl;
    return 0;
}
