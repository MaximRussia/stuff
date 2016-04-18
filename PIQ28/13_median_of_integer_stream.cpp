/**
    Median of Integer Stream
    Given a stream of unsorted integers, find the median element in sorted order at any given time.
    So, we will be receiving a continuous stream of numbers in some random order and we don’t
    know  the  stream  length  in  advance.  Write  a  function  that  finds  the  median  of  the  already
    received numbers efficiently at any time. We will be asked to find the median multiple times.
    Just to recall, median is the middle element in an odd length sorted array, and in the even case
    it’s the average of the middle elements.
**/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
using namespace std;

int median1(vector<int> &nums) {
    if (nums.size() == 0) {
        return -1;
    }

    int median = nums[0];
    priority_queue<int> maxHeap, minHeap;

    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] < median) {
            maxHeap.push(nums[i]);
        } else {
            minHeap.push(-nums[i]);
        }

        if (maxHeap.size() > minHeap.size()) {
            minHeap.push(-median);
            median = maxHeap.top();
            maxHeap.pop();
        } else if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(median);
            median = -minHeap.top();
            minHeap.pop();
        }
    }

    return median;
}

int main() {

    vector<int> v;
    for(int i = 0; i < 12; i++) v.push_back(i);

    cout << median1(v) << endl;

    return 0;
}
