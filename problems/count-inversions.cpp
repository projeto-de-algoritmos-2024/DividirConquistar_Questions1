/**
 * Count Inversions
 *
 * Given an array of integers arr[]. Find the Inversion Count in the array.
 * Two elements arr[i] and arr[j] form an inversion if arr[i] > arr[j] and i < j.
 *
 * Inversion Count: For an array, inversion count indicates how far (or
 * close) the array is from being sorted. If the array is already sorted
 * then the inversion count is 0.
 * If an array is sorted in the reverse order then the inversion count is
 * the maximum.
 *
 * Difficulty Level: Medium
 *
 * link: https://www.geeksforgeeks.org/problems/inversion-of-array-1587115620/1?page=1&category=Divide%20and%20Conquer&sortBy=submissions
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int inversionsCount(vector<int> &arr)
    {

        auto merge = [&](vector<int> &arr, int lo, int mid, int hi, int &invCount)
        {
            int n1 = mid - lo + 1;
            int n2 = hi - mid;

            vector<int> L(n1), R(n2);

            for (int i = 0; i < n1; i++)
                L[i] = arr[lo + i];
            for (int i = 0; i < n2; i++)
                R[i] = arr[mid + 1 + i];

            int i = 0, j = 0, k = lo;

            while (i < n1 && j < n2)
            {
                if (L[i] <= R[j])
                    arr[k++] = L[i++];
                else
                {
                    arr[k++] = R[j++];
                    invCount += (n1 - i);
                }
            }

            while (i < n1)
                arr[k++] = L[i++];
            while (j < n2)
                arr[k++] = R[j++];
        };

        auto mergeSort = [&](auto &self, vector<int> &arr, int lo, int hi, int &invCount) -> void
        {
            if (lo < hi)
            {
                int mid = lo + (hi - lo) / 2;
                self(self, arr, lo, mid, invCount);
                self(self, arr, mid + 1, hi, invCount);
                merge(arr, lo, mid, hi, invCount);
            }
        };

        int invCount = 0;
        mergeSort(mergeSort, arr, 0, arr.size() - 1, invCount);
        return invCount;
    }
};

int main()
{
    vector<int> arr = {2, 4, 1, 3, 5};
    Solution sl;
    cout << sl.inversionsCount(arr) << endl;
    return 0;
}