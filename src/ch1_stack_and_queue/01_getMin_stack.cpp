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
 * LeetCode: https://leetcode.com/problems/min-stack/
 * 【题目】
 * 设计一个有 getMin 功能的栈：在实现栈的基本功能的基础上，实现返回栈中最小元素的操作。
 * 【要求】
 * 1. pop, push, getMin 操作的复杂度都是 O(1)。
 * 2. 设计的栈类型可以使用现成的栈结构
 */
#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

template<typename _Ty>
class MinStack
{
public:
    bool empty() const
    {
        return _stk.empty();
    }

    _Ty pop()
    {
        if (_stk.empty())
        {
            return _Ty();
        }

        _Ty ret = _stk.top();
        _stk.pop();
        _min.pop();

        return ret;
    }
    
    void push(_Ty item)
    {
        if (_min.empty() || _min.top() > item)
        {
            _min.push(item);
        }
        else
        {
           _min.push(_min.top());
        }
        _stk.push(item);
    }
    
    _Ty getMin() const
    {
        if(_min.empty()) 
        {
            return _Ty();
        }
        return _min.top();
    }
private:
    stack<_Ty> _stk; // 保存入栈数据
    stack<_Ty> _min; // 栈顶元素表示 _stk 栈内的最小值
};

int main()
{ 
    MinStack<int> minstk;

    cout << "push order: ";
    for(int val : { 10, 5, 3, 6, 2, 1 })
    {
        cout << val << " ";
        minstk.push(val);
    }
    cout << endl;

    while(!minstk.empty()) 
    {
        cout << minstk.getMin() << " ";
        minstk.pop();
    }
    cout << endl;

    return 0;
}
