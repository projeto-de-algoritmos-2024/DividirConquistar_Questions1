/**
 * Candy
 *
 * There are N children standing in a line. Each child is assigned a rating value
 * given in the integer array ratings.
 *
 * You are giving candies to these children subjected to the following requirements:
 *
 * - Each child must have atleast one candy.
 * - Children with a higher rating than its neighbors get more candies than their
 * neighbors.
 *
 * Return the minimum number of candies you need to have to distribute.
 *
 * Difficulty: Hard
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int minCandy(int N, vector<int> &ratings)
    {
        int left = 0, right = N - 1;
        vector<int> candies(N, 1);

        auto distributeCandies = [&](auto self, vector<int> &ratings, vector<int> &candies, int left, int right) -> int
        {
            if (left == right)
            {
                candies[left] = 1;
                return candies[left];
            }
            int mid = left + (right - left) / 2;

            self(self, ratings, candies, left, mid);
            self(self, ratings, candies, mid + 1, right);

            for (int i = mid; i < right; i++)
            {
                if (ratings[i + 1] > ratings[i])
                {
                    candies[i + 1] = max(candies[i + 1], candies[i] + 1);
                }
            }

            for (int i = mid; i > left; i--)
            {
                if (ratings[i - 1] > ratings[i])
                {
                    candies[i - 1] = max(candies[i - 1], candies[i] + 1);
                }
            }

            int sum = 0;
            for (int c : candies)
            {
                sum += c;
            }
            return sum;
        };

        return distributeCandies(distributeCandies, ratings, candies, left, right);
    }
};