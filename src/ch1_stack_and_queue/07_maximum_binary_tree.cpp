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
 * LeetCode: https://leetcode.com/problems/maximum-binary-tree/
 *【题目】
 *根据给定的 TreeNode 的定义，已经给定的数组，求出其最大二叉树。
 *【要求】
 *（1）给定数组没有重复元素
 *（2）最大二叉树是指其任意子树值最大的节点是该子树根节点的二叉树
 *（3）左子树的元素在数组中出现的位置在根节点的左边，右子树的元素出现在数组中的位置在根节点的右边。
 *【解题思路】 
 *维护一个栈，然后依次遍历数组元素：
 *（1）如果栈中没有数据，则将数组中的当前元素压入栈中
 *（2）如果栈顶元素大于当前元素，则将当前元素压入栈中（当前元素一定是栈底元素的右子树）
 *（3）如果栈顶元素小于当前元素，则依次取出栈顶元素作为当前元素的左子树（栈顶所有小于当前元素的元素一定是当前元素的左子树）。
 */

#include <vector>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* constructMaximumBinaryTree(const vector<int>& nums)
{
    stack<TreeNode*> stk;
    if (nums.empty()) return nullptr; 
    
    for (int i = 0; i < nums.size(); ++i)
    {
        TreeNode* cur_node = new TreeNode(nums[i]);
        
        if (i == 0)
        {
            stk.push(cur_node);
            continue;
        }

        if (stk.top()->val < nums[i])
        {
            cur_node->left = stk.top();
            stk.pop();
            
            // 取出当前元素的左子树
            while (!stk.empty() && stk.top()->val < nums[i])
            {
                stk.top()->right = cur_node->left;
                cur_node->left = stk.top();
                stk.pop();
            }
        }
        stk.push(cur_node);
    }
    
    TreeNode* cur_node = stk.top();
    stk.pop();
    while (!stk.empty())
    {
        stk.top()->right = cur_node;
        cur_node = stk.top();
        stk.pop();
    }
    return cur_node;
}

int main()
{
    TreeNode* root = constructMaximumBinaryTree({3, 2, 1, 6, 0, 5});

    // 层次遍历树
    queue<TreeNode*> que;
    que.push(root);

    while (!que.empty())
    {
        TreeNode* cur_node = que.front();
        que.pop();
        if (cur_node == nullptr)
        {
            cout << "nullptr ";
        }
        else
        {
            cout << cur_node->val << " ";
            que.push(cur_node->left);
            que.push(cur_node->right);
        }
    }
    cout << endl;

    return 0;
}
