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
 * 用环形链表解决约瑟夫问题
 *【要求】
 * 1. 用环形链表解决约瑟夫问题
 * 2. 进阶： O(n) 的复杂度解决约瑟夫问题
 *【解题思路】 
 * 1. 环形链表： 直接模拟，当链表只剩下一个节点时，就是答案。
 * 2. 动态规划的思想，
 *    令 josephus(n, m) 表示 n 个人连续的序号的人组成的环形(从 0 到 n-1)，每隔 m 个杀一个人，最后活下来的人的号数。
 *    当第一次杀人之后，要然新的局面成为 josephus(n, m) 的子问题，只需要对其重新排号，让下一个开始计数的人为新的 0 号。
 *    易知，子问题为 josephus(n-1, m)。 新的局面中的编号 N_new 和之前的编号 N_old 的关系是 (N_new + m) % n = N_old。
 *    因此，约瑟夫问题的状态转移函数为： josephus(n, m) = (josephus(n-1, m) + m) % n
 */
#include <iostream>

using namespace std;

// 环形链表的节点
struct CycleListNode
{
    CycleListNode* next;
    int val;

    CycleListNode(int v) : next(nullptr), val(v) {}
};

// 创建 n 个节点的环形链表(0 到 n-1)
// 返回链表尾（头结点的上一个节点）
CycleListNode*  create_cycle_list(int n)
{
    CycleListNode* head = nullptr;
    CycleListNode* tail = nullptr;
    int i = 0;

    while (i < n)
    {
        CycleListNode* cur_node = new CycleListNode(i++);

        if (head == nullptr)
        {
            tail = head = cur_node;
        }
        else
        {
            tail->next = cur_node;
            tail = tail->next;
        }
    }

    if (tail != nullptr)
    {
        tail->next = head;
    }

    return tail;
}

// 用环形链表解决约瑟夫问题
int josephus_by_cycle_list(int n, int m)
{
    if(n == 0 || m == 0) return -1;

    int cnt = 0;
    CycleListNode* iter = create_cycle_list(n);
    
    while (iter != nullptr && iter != iter->next)
    {
        // 在被移除节点的前一个节点进行移除操作
        if (cnt + 1 == m)
        {
            // 移除下一个节点
            CycleListNode* next_node = iter->next;
            iter->next = next_node->next;
            delete next_node;

            cnt = 0; // 重新开始计算
            continue;
        }

        iter = iter->next;
        ++cnt;
    }

    int ans = iter->val;
    delete iter;

    return ans;
}

// 递归实现约瑟夫问题
int josephus_by_recursion(int n, int m)
{
    if (n == 0 || m == 0) return -1;
    if (n == 1) return 0;

    return (josephus_by_recursion(n-1, m) + m) % n;
}

int main()
{
    for (auto param : { pair<int, int>{78, 3}, {18, 7}, {0, 1}, {23, 11}, {9, 5}})
    {
        cout << "josephus_by_cycle_list: " << josephus_by_cycle_list(param.first, param.second) << endl;
        cout << "josephus_by_recursion: " << josephus_by_recursion(param.first, param.second) << endl;
    }

    return 0;
}
