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
 * 给定两个有序链表，输出他们的公共部分
 *【要求】
 * 输出两个链表中值相等的节点的值
 *【解题思路】 
 * 同时遍历两个链表：
 * 若其中一个链表的节点的值小于另一个节点的值，则较小节点对应的链表移动到下一个节点。
 * 若两个链表当前节点的值相等，则输出该值，并将两个链表都移动到下一个节点。
 */

#include <iostream>
#include <list>
#include <vector>

using namespace std;

typedef struct LinkNode
{
    int val;
    LinkNode* next;

    LinkNode(int v) : val(v), next(nullptr){}
}*LinkNodePtr;

// 获取两个链表一样的数据
void get_common_part(LinkNodePtr list1, LinkNodePtr list2, vector<int>& compart)
{
    if (list1 == nullptr || list2 == nullptr)
    {
        return;
    }
    else if (list1->val < list2->val)
    {
        return get_common_part(list1->next, list2, compart);
    }
    else if (list1->val > list2->val)
    {
        return get_common_part(list1, list2->next, compart);
    }
    else
    {
        compart.push_back(list1->val);
        return get_common_part(list1->next, list2->next, compart);
    }
}

// 创建链表
void create_linked_list(LinkNodePtr* l, list<int> v)
{
    if (v.empty()) return;

    (*l) = new LinkNode(v.front());
    v.pop_front();

    create_linked_list(&(*l)->next, v);
}

int main()
{
    LinkNodePtr list1 = nullptr, list2 = nullptr;

    create_linked_list(&list1, {1, 3, 4, 5, 6, 8, 10});
    create_linked_list(&list2, {0, 1, 4, 7, 10, 11, 13});

    vector<int> v;
    get_common_part(list1, list2, v);

    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    return 0;
}
