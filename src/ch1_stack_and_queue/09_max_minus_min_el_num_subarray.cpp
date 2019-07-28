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
 *最大值减去最小值小于或等于 num 的连续子数组数量
 *【要求】
 *如果数组长度为 N，则时间复杂度为 O(N)。
 *【解题思路】 
 * 1. 利用最大值栈和最小值栈保存滑动窗口的最值情况
 * 2. 当滑动窗口的最大值和最小值之差大于 num 时，移动 left
 */

#include <iostream>
#include <vector>
#include <deque>
#include <cmath>

using namespace std;

int cal_subarray_num(const vector<int>& arr, int num)
{
    deque<int> que_max;
    deque<int> que_min;
    int count = 0;
    int left = 0;
    int right = -1;

    // [left, right] 的最大值的下标 que_max.front()
    // [left, right] 的最小值的下标 que_min.front()
    while (++right < arr.size())
    {
        while (!que_max.empty() && arr[que_max.back()] <= arr[right])
        {
            que_max.pop_back();
        }
        que_max.push_back(right);
        
        while (!que_min.empty() && arr[que_min.front()] >= arr[right])
        {
            que_min.pop_back();
        }
        que_min.push_back(right);

        while (!que_max.empty() && !que_min.empty() && arr[que_max.front()] - arr[que_min.front()] > num)
        {
            if (que_max.front() > que_min.front())
            {
                // 最小值离开区间
                count = count + (que_min.front() - left + 1) * right - (que_min.front() - left + 1) * (que_min.front() + left) / 2;
                left = que_min.front() + 1;
                que_min.pop_front();
            }
            else
            {
                // 最大值离开区间
                count = count + (que_max.front() - left + 1) * right - (que_max.front() - left + 1) * (que_max.front() + left) / 2;
                left = que_max.front() + 1;
                que_max.pop_front();
            }
        }

        // 后续没有更多数据
        if (left <= right && right == arr.size()-1)
        {
           count += (right - left + 2) * (right - left + 1) / 2;
        }
    } 

    return count;
}

// 暴力求解(DP)，用于测试
int cal_subarray_num_bf(const vector<int>& arr, int num)
{
    int min_range[100][100] = {0};
    int max_range[100][100] = {0};
    int cnt = 0;

    for (int i = 0; i < arr.size(); ++i)
    {
        for (int j = i; j < arr.size(); ++j)
        {
            min_range[i][j] = arr[j];
            max_range[i][j] = arr[j];

            if (i != j && min_range[i][j-1] < min_range[i][j])
            {
                min_range[i][j] = min_range[i][j-1];
            }
            if (i != j && max_range[i][j-1] > max_range[i][j])
            {
                max_range[i][j] = max_range[i][j-1];
            }

            if (abs(max_range[i][j] - min_range[i][j]) <= num)
            {
                ++cnt;
            }
            else
            {
                break;
            }
        }
    }

    return cnt;
}

int main()
{
    auto arr = { 10, 5, 3, 9, 6, 2, 7, 11, 19, 12, 1, 4, 18};

    for (int i = 0; i < 13; ++i)
    {
        cout << i << ": " << endl;
        cout << "cal_subarray_num_bf: " << cal_subarray_num_bf(arr, i) << endl;
        cout << "cal_subarray_num: " << cal_subarray_num(arr, i) << endl << endl;
    }
    return 0;
}
