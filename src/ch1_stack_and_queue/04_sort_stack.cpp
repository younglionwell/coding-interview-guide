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
 * 一个栈中的元素类型为整形，请将该栈从栈顶到栈底按照从大到小排序。
 *【要求】
 * 只允许申请额外的一个栈。
 *【解题思路】 
 * 依次取出原栈的元素，移入新栈。当该元素大于新栈栈顶时，将新栈顶元素移入原栈。
 * 最后获得的新栈是从栈顶到栈底按照从小到大排序的。依次取出元素压入原栈即可。
 */

#include<stack>
#include<iostream>

using namespace std;

void sort_stack(stack<int>& stk)
{
    stack<int> stk_ref;

    while (!stk.empty())
    {
        int sort_elem = stk.top(); // 当前待排序元素
        stk.pop();

        // 将当前待排序元素移入新栈的对应位置
        while (!stk_ref.empty() && stk_ref.top() < sort_elem)
        {
            stk.push(stk_ref.top());
            stk_ref.pop();
        }
        stk_ref.push(sort_elem);
    }

    while (!stk_ref.empty())
    {
        stk.push(stk_ref.top());
        stk_ref.pop();
    }
}

int main()
{
    stack<int> stk;
    for(auto var : { 1, 2, 3, 10, 9, 8, 7, 11, 2, 3, 20, 6 })
    {
        stk.push(var);
    }
    
    sort_stack(stk);

    while(!stk.empty())
    {
        cout << stk.top() << " ";
        stk.pop();
    }
    cout << endl;

    return 0;
}
