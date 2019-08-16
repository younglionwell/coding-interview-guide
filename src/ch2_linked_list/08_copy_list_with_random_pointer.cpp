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
 * LeetCode: https://leetcode.com/problems/copy-list-with-random-pointer/
 *【题目】
 * 复制一个含有随机指针节点的链表，随机指针指向链表中的节点或者为 nullptr。
 *【要求】
 * 链表长度为 N 时，时间复杂度 O(N), 空间复杂度 O(1)
 *【解题思路】 
 * 1. 将原始链表的每一个节点复制作为其 next 节点
 * 2. 复制节点的 random 节点，即使原节点的 random 节点的 next 节点
 * 3. 生成复制链表，恢复原链表
 * 4. 详细题解见链接： https://blog.csdn.net/yanglingwell/article/details/80893091
 */

#include <list>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;


struct RandomListNode
{
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};
 
class Solution 
{
private:
    // 拷贝 Random List(不包括 random 属性)， 并将拷贝的内容插入原节点之后
    void copy_random_list_without_random(RandomListNode *head)
    {
        if(head == nullptr) return ;

        auto iter = head;

        // 拷贝 head 节点
        RandomListNode * headCopy = new RandomListNode(head->label);
        // 将 headCopy 插入 head 后面
        headCopy->next = head->next;
        head->next = headCopy;

        // 处理后面的节点
        copy_random_list_without_random(head->next->next);
    }

    // 拷贝 random 属性
    void copy_random_list_random(RandomListNode *head)
    {
        if(head == nullptr) return;

        // NOTE: 原节点的 next 指针指向的是拷贝的节点
        if(head->random != nullptr)
        {
            head->next->random = head->random->next;
        }
        // 处理后面的节点
        copy_random_list_random(head->next->next);
    }

    // 生成拷贝链表，恢复原链表
    RandomListNode* copy_random_list_generator(RandomListNode *head)
    {
        if(head == nullptr) return nullptr;

        // NOTE: 原节点的 next 指针指向的是拷贝的节点
        RandomListNode* headCopy = head->next;
        head->next = headCopy->next;

        // 继续处理后面的节点
        headCopy->next = copy_random_list_generator(head->next);

        return headCopy;
    }
public:
    RandomListNode *copy_random_list(RandomListNode *head) 
    {
        // 拷贝 Random List(不包括 random 属性)， 并将拷贝的内容插入原节点之后
        copy_random_list_without_random(head);

        // 拷贝 random 属性
        copy_random_list_random(head);

        // 生成拷贝链表，恢复原链表
        return copy_random_list_generator(head);
    }
};

// 创建单链表
void create_singly_list(RandomListNode*& head, const list<int>& vals)
{
    if (vals.empty()) return;

    vector<RandomListNode*> nodes;
    RandomListNode* tail = nullptr;
    
    for (int x : vals)
    {
        if (tail == nullptr)
        {
            head = tail = new RandomListNode(x);
        }
        else
        {
            tail->next = new RandomListNode(x);
            tail = tail->next;
        }

        nodes.push_back(tail);
    }

    RandomListNode* iter = head;

    while (iter != nullptr)
    {
        int rd = rand() % (nodes.size() + 1);

        if (rd == 0)
        {
            iter->random = nullptr;
        }
        else
        {
            iter->random = nodes[rd-1];
        }

        iter = iter->next;
    }
}

// 打印单链表
void print_singly_list(RandomListNode* head)
{
    if(head == nullptr)
    {
        cout << endl;
        return;
    }

    cout << head->label << "(";
    if (head-> random != nullptr)
    {
        cout << head->random->label << ") ";
    }
    else
    {
        cout << "nullptr) ";
    }

    print_singly_list(head->next);
}

int main()
{
    srand(time(nullptr));

    RandomListNode* head = nullptr;
    RandomListNode* head_cpy = nullptr;

    create_singly_list(head, {1, 2, 3, 4, 5, 6, 7});
    cout << "head: ";
    print_singly_list(head);

    Solution s;
    head_cpy = s.copy_random_list(head);
    cout << "head_cpy: ";
    print_singly_list(head_cpy);
    return 0;
}
