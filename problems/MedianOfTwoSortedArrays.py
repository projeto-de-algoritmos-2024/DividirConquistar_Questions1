import math
from typing import List

# 4. Median of Two Sorted Arrays (https://leetcode.com/problems/median-of-two-sorted-arrays/description/)
#
# Hard
#
# Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
# The overall run time complexity should be O(log (m+n)).
# 
# Example 1
# Input: nums1 = [1,3], nums2 = [2]
# Output: 2.00000

class Solution(object):
    def divideIntoGroups(self, vector):
        groups = [vector[i:i+5] for i in range(0, len(vector), 5)]
        return groups

    def sortGroups(self, groups):
        for group in groups:
            group.sort()
        return groups

    def knownMedian(self, length):
        match length:
            case 1:
                return 0
            case 2:
                return 0
            case 3:
                return 1
            case 4:
                return 1
            case 5:
                return 2

    def medianOfGroup(self, groups):
        medians = [group[self.knownMedian(len(group))] for group in groups]
        return medians

    def medianOfMedians(self, vector, k):
        if len(vector) <= 5:
            vector.sort()
            return vector[k]

        groups = self.divideIntoGroups(vector)
        groups = self.sortGroups(groups)
        medians = self.medianOfGroup(groups)

        pivot = self.medianOfMedians(medians, len(medians) // 2)

        minors = [x for x in vector if x < pivot]
        equal = [x for x in vector if x == pivot]
        majors = [x for x in vector if x > pivot]

        if k < len(minors):
            return self.medianOfMedians(minors, k)
        elif k < len(minors) + len(equal):
            return pivot
        else:
            return self.medianOfMedians(majors, k - len(minors) - len(equal))

    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        vector = nums1 + nums2

        n = len(vector)

        if n % 2 == 1:
            return float(self.medianOfMedians(vector, n // 2))
        else:
            left = self.medianOfMedians(vector, n // 2 - 1)
            right = self.medianOfMedians(vector, n // 2)
            return (left + right) / 2.0
