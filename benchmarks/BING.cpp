Technical problem: Please implement a method to get a point in a reversed pascal triangle.
= For error case return 0 as 0 is not a value of the triangle
= Used recursive approach without memorization
= Code concise and clean
= Lack of test cases. Able to fix bugs in his code quickly.
= Thought about integer overflow, first candidate to actually spot it. He tried to detect it poorly
= However he spotted the integer overflow problem, he had no solution to detect it from the input.

///////////////////////////////////////////////////////////////////////
-1 -3 -3 -1 (-3)
-1 -2 -1 (-2)
-1 -1 (-1)
 1 (0, 0)
 1  1 (1)
 1  2  1 (2)
 1  3  3  1 (3)
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// memorization
void PascalIter(vector<vector<int>> & cache, int row) {
    if(row <= 0) return;

    cache.push_back({{1}});

    for(int i = 1; i < row; i++) {
        cache.push_back({{1}});
        for(int j = 1; j < i; j++) {
            cache[i].push_back(cache[i-1][j-1] + cache[i-1][j]);
        }
        cache[i].push_back({1});
    }
}

int cache_size = 65535;
vector<vector<int>> cache;

PascalIter(cache, cache_size);

int GetPascalPoint(int row, int col) {
    if(col < 0) throw std::runtime_error("col smaller then zero");
    if(col > row) throw std::runtime_error("col bigger then rows");
    if(row > cache_size || row < -cache_size) throw std::runtime_error("try get not cached value");

    bool sign = 1;
    if(row < 0) {
        row = -row;
        sign = -1;
    }

    return sign*cache[row][col];
}


















