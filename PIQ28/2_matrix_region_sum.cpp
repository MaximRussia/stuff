
/**
    Given a matrix of integers and coordinates of a rectangular region within the matrix, find the
    sum of numbers falling inside the rectangle. Our program will be called multiple times with
    different rectangular regions from the same matrix.
**/

/*
    We should precompute and cache some data in order to reduce the complexity to O(1).
    The precomputation complexity is not that important since it will be performed just
    once in the beginning, and the cached data will be used to speed up the subsequent
    calls to the function. Let’s see what we can precompute. To achieve an O(1) solution,
    we can precompute the sum of every possible rectangular region inside the matrix, and
    store it in a hashtable for later use. Afterwards, when we are asked the sum of a rectangular
    region, we will just return the precomputed value in constant time. However, the space
    complexity of this approach would be O(M^2N^2) which is too much. Because there are MN
    different candidates for both top left and bottom right coordinates of the rectangle.
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
using namespace std;

void cacheSumm(vector<vector<int>> &v, vector<vector<int>> &cache) {
    for(int i = 0; i < v.size(); i++) cache[i][0] = v[i][0];
    for(int i = 0; i < v[0].size(); i++) cache[0][i] = v[0][i];

    int i = 1;
    while(i < v.size()) {
        for(int j = 1; j < v[i].size(); j++) {
            cache[i][j] = v[i][j] + v[i-1][j-1] + v[i-1][j] + v[i][j-1];
        }
        i++;
    }
}


int getSum(vector<vector<int>> &cache, int a, int b, int c, int d) {
    if(a == 0 && b == 0) return cache[c][d];
    return cache[c][d] - cache[a-1][b-1];
}

int main() {

    vector<vector<int>> v = {{1,2,3,4,5},
                             {1,2,3,4,5},
                             {1,2,3,4,5},
                             {1,2,3,4,5},
                             {1,2,3,4,5}};
    vector<vector<int>> cache;
    cache.resize(v.size());
    for(int i = 0; i < v.size(); i++) cache[i].resize(v[i].size());

    cacheSumm(v, cache);

    cout << getSum(cache, 2, 2, 4, 4) << endl;

    return 0;
}
