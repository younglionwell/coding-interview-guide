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
 * 求当塔有 N 层时，最优的移动过程及最优移动步数。
 *【要求】
 *（1）不能从最左边的塔直接到最右边的塔移动
 *（2）不能从最右边的塔直接到最左边的塔移动
 *（3）分别用递归和用栈来模拟塔两种方式实现
 *【解题思路】 
 * 递归：由于不能直接让塔在左右间移动，因此只能将借助中间的柱子。（具体操作见代码注释）
 * 栈实现：由于有（1）（2）两条限制，要实现最优移动步数，每次只能有一种移动方法。
 *        使用栈来模拟三个塔，然后找出唯一的最优解法。
 */

#include <string>
#include <iostream>
#include <stack>

using namespace std;

int move_left_2_mid(int idx)
{
    cout << "Move " << idx << " from left to middle..." << endl;
    return 1;
}
int move_mid_2_right(int idx)
{
    cout << "Move " << idx << " from middle to right..." << endl;
    return 1;
}
int move_right_2_mid(int idx)
{
    cout << "Move " << idx << " from right to middle..." << endl;
    return 1;
}
int move_mid_2_left(int idx)
{
    cout << "Move " << idx << " from middle to left..." << endl;
    return 1;
}

// 将右边柱子上的 N 个塔移到左边的柱子
int move_left(int N);

// 将左边柱子的 N 个塔移动到右边的柱子 
int move_right(int N)
{
    int step_count = 0;
    if (N == 0) return step_count;

    step_count += move_right(N-1);           // 将左边的上层 N-1 个塔移到最右边的柱子（递归）
    step_count += move_left_2_mid(N);        // 将左边的第 N 个塔移到中间的柱子
    step_count += move_left(N-1);            // 将右边柱子的 N-1 个塔移到左边柱子（为最下层的第 N 个塔让位）
    step_count += move_mid_2_right(N);       // 将中间的第 N 个塔移到右边的柱子（第 N 个塔归位）
    step_count += move_right(N-1);           // 将剩下的 N-1 个塔也一移到右边去

    return step_count;
}
int move_left(int N)
{
    int step_count = 0;
    if (N == 0) return step_count;

    // 下面的操作与 move_right 类似
    // 将右边柱子上的 N 个塔借助中间的柱子移到左边的柱子
    step_count += move_left(N-1);
    step_count += move_right_2_mid(N);
    step_count += move_right(N-1);
    step_count += move_mid_2_left(N);
    step_count += move_left(N-1);
 
    return step_count;
}

void hanoi_with_recursive(int N)
{
    int step_count = move_right(N);
    cout << "It will move " << step_count << " steps." << endl;
}

void hanoi_with_stack(int N)
{
    int step_count = 0;
    stack<int> left, middle, right;
    for (int i = 0; i < N; ++i)
    {
        left.push(N-i);
    }

    // 0 : none
    // 1 : left   --> middle
    // 2 : middle --> right
    // 3 : right  --> middle
    // 4 : middle --> left
    int moves[] = { 0, 1, 2, 3, 4 };
    int last_move = 0;

    while (!left.empty() || !middle.empty())
    {
        ++step_count;

        // 1 : left --> middle ?
        if(last_move != 4 && !left.empty() && (middle.empty() || left.top() < middle.top()))
        {
            middle.push(left.top());
            left.pop();
            last_move = 1;

            move_left_2_mid(middle.top());
            continue;
        }

        // 2 : middle --> right ?
        if(last_move != 3 && !middle.empty() && (right.empty() || middle.top() < right.top()))
        {
            right.push(middle.top());
            middle.pop();
            last_move = 2;

            move_mid_2_right(right.top());
            continue;
        }

        // 3 : right --> middle ?
        if(last_move != 2 && !right.empty() && (middle.empty() || right.top() < middle.top()))
        {
            middle.push(right.top());
            right.pop();
            last_move = 3;

            move_right_2_mid(middle.top());
            continue;
        }

        // 4 : middle --> left ?
        if(last_move != 1 && !middle.empty() && (left.empty() || middle.top() < left.top()))
        {
            left.push(middle.top());
            middle.pop();
            last_move = 4;

            move_mid_2_left(left.top());
            continue;
        }
    }

    cout << "It will move " << step_count << " steps." << endl;
}

int main()
{
    int N;
    while (cin >> N)
    {
        hanoi_with_recursive(N);
        hanoi_with_stack(N);
    }
    return 0;
}
