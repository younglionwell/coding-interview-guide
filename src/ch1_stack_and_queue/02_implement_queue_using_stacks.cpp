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
 * LeetCode: https://leetcode.com/problems/implement-queue-using-stacks/
 *【题目】
 * 编写一个类，用两个栈实现队列，支持队列的基本操作（add, poll, peek）
 *【要求】 
 * add 添加一个元素到队列
 * poll 移除并返问队列头部的元素 如果队列为空，则返回默认值
 * peek 返回队列头部的元素 如果队列为空，则返回默认值
 *【解题思路】
 * 用两个栈实现，一个栈作为输入缓冲（逆序），一个栈作为输出缓冲（正序）。
 * add 的数据都存入输入缓冲中，peek 和 poll 的都是输出缓冲的数据。
 * 当输出缓冲为空时，将输入缓冲全部压入输出缓冲，从而恢复逆序数据的顺序。
 */
#include <iostream>
#include <stack>
#include <string.h>
using namespace std;

template<typename _Ty>
class QueueByStacks
{
public:
    bool empty() const
    {
        return (_stk_in.empty() && _stk_out.empty());
    }

    void add(const _Ty& val)
    {
        _stk_in.push(val);
    }

    _Ty peek()
    {
        if (_stk_out.empty() && _stk_in.empty())
        {
            return _Ty();
        }
        if (_stk_out.empty())
        {
            while(!_stk_in.empty())
            {
                _stk_out.push(_stk_in.top());
                _stk_in.pop();
            }
        }

        return _stk_out.top();
    }

    _Ty poll()
    {
        _Ty ret = this->peek();
        if (!_stk_out.empty())
        {
            _stk_out.pop();
        }

        return ret;
    }
private:
    stack<_Ty> _stk_in, _stk_out;
};

int main()
{   
    QueueByStacks<string> que;
 
    for (auto var : { "hello", "world" })
    {
        que.add(var);
    }
    cout << que.peek() << endl;
    for (auto var : { "This", "is", "a", "test"} )
    {
        que.add(var);
    }
    
    while(!que.empty())
    {
        cout << que.poll() << " ";
    }
    cout << endl;

    return 0;
}
