/*
 * @lc app=leetcode.cn id=876 lang=c
 * @lcpr version=30006
 *
 * [876] 链表的中间结点
 *
 * https://leetcode.cn/problems/middle-of-the-linked-list/description/
 *
 * algorithms
 * Easy (71.80%)
 * Likes:    1046
 * Dislikes: 0
 * Total Accepted:    494.2K
 * Total Submissions: 688.4K
 * Testcase Example:  '[1,2,3,4,5]'
 *
 * 给你单链表的头结点 head ，请你找出并返回链表的中间结点。
 * 
 * 如果有两个中间结点，则返回第二个中间结点。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：head = [1,2,3,4,5]
 * 输出：[3,4,5]
 * 解释：链表只有一个中间结点，值为 3 。
 * 
 * 
 * 示例 2：
 * 
 * 输入：head = [1,2,3,4,5,6]
 * 输出：[4,5,6]
 * 解释：该链表有两个中间结点，值分别为 3 和 4 ，返回第二个结点。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 链表的结点数范围是 [1, 100]
 * 1 <= Node.val <= 100
 * 
 * 
 */


// @lcpr-template-start

// @lcpr-template-end
// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* middleNode(struct ListNode* head) {
    struct ListNode *middle = head;
    int count = 0;
    int middle_index = 0;

    while (head)
    {
        count++;
        head = head->next;
    }

    middle_index = count / 2;
    while (middle_index-- > 0)
        middle = middle->next;
    
    return middle;
}
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4,5]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4,5,6]\n
// @lcpr case=end

 */

