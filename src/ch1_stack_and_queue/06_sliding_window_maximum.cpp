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
 * LeetCode: https://leetcode.com/problems/sliding-window-maximum/
 *【题目】
 * 给定一个数组 nums 和一个大小为 k 的滑动窗口，其中滑动窗口从 nums 数组的最左边移动最右边。
 * 每次滑动窗口向右移动一个位置。求每个滑动窗口的最大值。
 *【例子】
 * Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
 * Output: [3,3,5,5,6,7] 
 * Explanation: 
 * 
 * Window position                Max
 * ---------------               -----
 *[1  3  -1] -3  5  3  6  7       3
 * 1 [3  -1  -3] 5  3  6  7       3
 * 1  3 [-1  -3  5] 3  6  7       5
 * 1  3  -1 [-3  5  3] 6  7       5
 * 1  3  -1  -3 [5  3  6] 7       6
 * 1  3  -1  -3  5 [3  6  7]      7
 * 
 *【解题思路】 
 * 从左到右移动滑动窗口，维护一个每个位置到当前滑动窗口结束的最大值的位置队列。
 * 根据维护的队列将每次的滑动窗口的最大值保存下来（维护方式见代码注释）。
 */

#include <string>
#include <iostream>
#include <deque>
#include <vector>

using namespace std;

vector<int> maxSlidingWindow(const vector<int>& nums, int k)
{
    // 每个滑动窗口的最大值
    vector<int> slide_win_max;
    // 记录当前 index 到滑动窗口结尾的最大值的位置
    deque<int> slide_win_max_buffer;

    for (int i = 0; i < nums.size(); ++i)
    {
        // 滑动
        if (i == 0)
        {
            slide_win_max_buffer.push_back(i);
        }
        else
        {
            // 更新当前滑动窗口在 i 之前的 index 到当前滑动窗口结尾的最大值的位置
            while (!slide_win_max_buffer.empty() && nums[slide_win_max_buffer.back()] <= nums[i])
            {
                slide_win_max_buffer.pop_back();
            }
            slide_win_max_buffer.push_back(i);
        }

        // 获取当前滑动窗口的最大值
        if (i >= k-1)
        {
            // slide_win_max_buffer 的队首记录的是从滑动窗口最左到滑动窗口结尾的最大值的位置
            slide_win_max.push_back(nums[slide_win_max_buffer.front()]);
            
            // 如果滑动窗口最左边的位置就是整个滑动窗口的最大值的位置，则更新滑动窗口的最大值
            if (slide_win_max_buffer.front() == i-k+1)
            {
                slide_win_max_buffer.pop_front();
            }
        }
    }

    return slide_win_max;
}

int main()
{
    auto slide_win_max = maxSlidingWindow({4, 3, 5, 4, 3, 3, 6, 7}, 3);
    for(auto var : slide_win_max)
    {
        cout << var << " ";
    }
    cout << endl;

    return 0;
}
