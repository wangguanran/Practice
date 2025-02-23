/*
 * @lc app=leetcode.cn id=86 lang=c
 * @lcpr version=30006
 *
 * [86] 分隔链表
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
struct ListNode* partition(struct ListNode* head, int x) {
    struct ListNode* small = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* larger = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* smallHead = small;
    struct ListNode* largerHead = larger;

    small->next = NULL;
    larger->next = NULL;

    while (head != NULL)
    {
        if (head->val < x)
        {
            small->next = head;
            small = small->next;
        }
        else
        {
            larger->next = head;
            larger = larger->next;
        }
        head = head->next;
    }
    small->next = largerHead->next;
    larger->next = NULL;

    head = smallHead->next;
    free(smallHead);
    free(largerHead);

    return head;
}
// @lc code=end



/*
// @lcpr case=start
// [1,4,3,2,5,2]\n3\n
// @lcpr case=end

// @lcpr case=start
// [2,1]\n2\n
// @lcpr case=end

 */

