---
layout: post
title: "Interesting interview algorithm problems"
date: 2019-05-03 15:00:00
categories: Interview
---

# Interview algorithm problems

Doing practise to explain the ideas behind the solutions. Only problems I feel interesting.


# Leetcode

## Interesting problem list

[My interesting problem list](https://leetcode.com/list/xecf1gge)

[My solutions](https://github.com/FiveEyes/ProblemSet/tree/master/LeetCode)


**11. Container With Most Water**

Solution: two pointers from two sides, greedy check the smaller one and remove it.


**375. Guess Number Higher or Lower II**

The goal is buidling a balanced tree which balances two sides' cost.

Solution: DP, set dp[i][j] as the minimum cost to build a tree from i to j.

The naive solution is O(n^3), and it can be optimized to O(n^2), because dp[i][0:n] is monotonic.


**546. Remove Boxes**

Solution: DP.

dp[i][j][k] -> the max score for removing boxes from i to j and leaving k boxes if boxes[i] == boxes[j].

if boxes[i] != boxes[j]: only dp[i][j][0] is valid.


**658. Find K Closest Elements**

Solution: Binary search

Very interesting binary search, it's the same to find the k smallest element in two sorted lists.


**843. Guess the Word**

An interactive problem

Solution: design a score for each word according to preivous queries, and query the word of top score.


**992. Subarrays with K Different Integers**

Solution: two pointers, hard to explain in one sentence. The basic idea is fixing right side of the subarray, and maintaining the valid range for the left side.


**1000. Minimum Cost to Merge Stones**

variant of merge stones problem: only adjacent stones can be merged.

Solution: DP. 
dp[i][j] is the minimum cost to merge i to j.
  * dp[i][j] =  min(dp[i][k] + dp[k+1][j])
  * if (j - i + 1) % (K - 1) == 1 or K == 2: dp[i][j] += sum(stones[i:j+1])
  
## Recommend problems

Good problems to practise.

[Recommend problem list](https://leetcode.com/list/xoqd52n1)


**410. Split Array Largest Sum**

DP soltion is O(n^2). Binary search can reach O(nlogn).

