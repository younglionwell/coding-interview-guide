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
 * LeetCode: https://leetcode.com/problems/maximal-rectangle/description/
 *【题目】
 * 给定一个由 ‘0’，‘1’ 字符组成的矩阵，找出其中最大的全 ‘1’ 矩阵包含的 ‘1’ 的数量。
 *【解题思路】 
 * 详见：https://blog.csdn.net/yanglingwell/article/details/79480836
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// i 的左边最靠近它且比它小的值的下标 left-1, 右边最靠近它且比它小的值的下标 right
// 则：以 height[i] 为高的矩形宽为 (right-left)
int largestRectangleArea(const vector<int>& heights) 
{
    stack<int> stk;
    int ans = 0;
    
    for (int i = 0; i <= heights.size(); ++i)
    {
        if (i != heights.size() && (stk.empty() || heights[stk.top()] <= heights[i]))
        {
            stk.push(i);
        }
        else
        {
            while (!stk.empty() && (i == heights.size() || heights[stk.top()] > heights[i]))
            {
                int cur_idx = stk.top();
                stk.pop();
                
                // [left, right)
                int left = stk.empty() ? 0 : stk.top()+1;
                int right = i;
                
                ans = max(ans, heights[cur_idx]*(right-left));
            }
            
            if (i != heights.size()) stk.push(i);
        }
    }
    
    return ans;
}
    
    
int maximalRectangle(const vector<vector<char>>& matrix) 
{
    vector<vector<int>> heights(matrix.size(), vector<int>());
    
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            if (i == 0)
            {
                heights[i].push_back(matrix[i][j]-'0');
            }
            else if(matrix[i][j] == '1')
            {
                heights[i].push_back(heights[i-1][j]+1);
            }
            else
            {
                heights[i].push_back(0);
            }
        }
    }
    
    int ans = 0;
    for (int i = 0; i < matrix.size(); ++i)
    {
        ans = max(ans,  largestRectangleArea(heights[i]));
    }
    
    return ans;
}

int main()
{
    vector<vector<char>> matrix{{'1','1','1', '1', '1'},
                                {'0','1','1', '1', '1'},
                                {'0','1','1', '0', '1'},
                                {'1','1','0', '1', '1'},
                                {'1','1','1', '1', '0'}};
    
    cout << maximalRectangle(matrix) << endl;

    return 0;
}