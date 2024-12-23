import math
class Solution(object):
    def divideIntoGroup(self, vector):
            groups = []
            for i in range(math.ceil(len(vector)/5)):
                group = []
                for j in range(5):
                    if i*5+j < len(vector):
                        group.append(vector[i*5+j])
                groups.append(group)
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
        medians = []
        for group in groups:
            median = group[self.knownMedian(len(group))]
            medians.append(median)
        return medians
    def medianOfMedians(self, vector, k):
        if (len(vector) <= 5):
            vector.sort()
            return vector[k]
        groups = self.divideIntoGroup(vector)
        groups = self.sortGroups(groups)
        medians = self.medianOfGroup(groups)
        while (len(medians) > 5):
            groups = self.divideIntoGroup(medians)
            groups = self.sortGroups(groups)
            medians = self.medianOfGroup(groups)
        median = medians[self.knownMedian(len(medians))]
        minors = [element for element in vector if element < median]
        equal = [element for element in vector if element == median]
        majors = [element for element in vector if element > median]
        minors = minors + equal
        minors.pop()
        
        if len(minors) == k-1:
            return median
        elif len(minors) > k-1:
            return self.medianOfMedians(minors, k)
        else:
            return self.medianOfMedians(majors, k-len(minors)-1)

    def findMedianSortedArrays(self, nums1, nums2):
        vector = nums1+nums2
        result = self.medianOfMedians(vector, len(vector)//2)
        if len(vector) % 2 == 0:
            result += self.medianOfMedians(vector, len(vector)//2-1)
            result = float(result / 2)
        return float(result)
