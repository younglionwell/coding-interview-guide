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
 * LeetCode: https://leetcode.com/problems/palindrome-linked-list/
 *【题目】
 * 求给定链表是否为回文结构
 *【要求】
 * 如果链表长度为 N，则空间复杂度: O(1), 时间复杂度: O(N)
 *【解题思路】 
 * 递归求解，递归在深入时，遍历该链表的节点，进一层递归，遍历一步则当递归到最底层时，此时的节点为尾结点。
 * 在递归最深处重新遍历链表，出一层递归，遍历一步。然后跟之前深入的遍历相比较，判断是否回文。
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

bool is_palindrome(ListNode* forward, ListNode*& backward) 
{
    if (forward == nullptr) return true;

    bool bret = false;

    // 递归深入时， forward 遍历链表
    if (is_palindrome(forward->next, backward) == true)
    {
        // 对称节点是否相等?
        if (forward->val == backward->val)
        {
            bret = true;
        }

        // 递归返回时， backward 遍历链表
        backward = backward->next;
    }

    return bret;
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
    ListNode* head3 = nullptr;

    create_singly_list(head1, {1, 2, 3, 4, 5, 6, 5, 3, 2, 1});
    print_singly_list(head1);
    cout << "is_palindrome: " << is_palindrome(head1, head1) << endl << endl;

    create_singly_list(head2, {1, 2, 3, 5, 6, 5, 3, 2, 1});
    print_singly_list(head2);
    cout << "is_palindrome: " << is_palindrome(head2, head2) << endl << endl;

    create_singly_list(head3, {1, 2, 3, 4, 5, 6});
    print_singly_list(head3);
    cout << "is_palindrome: " << is_palindrome(head3, head3) << endl << endl;

    return 0;
}
