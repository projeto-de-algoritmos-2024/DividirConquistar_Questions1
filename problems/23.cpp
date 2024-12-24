/**
 * 23. Merge k Sorted Lists
 *
 * ou are given an array of k linked-lists lists, each linked-list is sorted in
 * ascending order.
 *
 * Merge all the linked-lists into one sorted linked-list and return it.
 *
 * Difficulty: Hard
 * https://leetcode.com/problems/merge-k-sorted-lists/description/
 */

#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        if (!l1) return l2;
        if (!l2) return l1;

        if (l1->val < l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        } else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }


    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        if (lists.empty()) return nullptr;

        int n = lists.size();
        while (n > 1)
        {
            for (int i = 0; i < n / 2; i++)
            {
                lists[i] = mergeTwoLists(lists[i], lists[n - i - 1]);
            }
            n = (n + 1) / 2;
        }

        return lists.front();
    }
};