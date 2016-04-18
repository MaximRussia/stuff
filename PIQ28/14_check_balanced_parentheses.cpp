/**
    14. Check Balanced Parentheses
    Given a string of opening and closing parentheses, check whether it’s balanced. We have 3 types
    of parentheses: round brackets: (), square brackets: [], and curly brackets: {}. Assume that the
    string  doesn’t  contain  any  other  character  than  these,  no  spaces  words  or  numbers.  Just  to
    remind, balanced parentheses require every opening parenthesis to be closed in the reverse order
    opened. For example ‘([])’ is balanced but ‘([)]‘ is not.
**/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <cstring>
using namespace std;

bool brackets_balance(string str) {
    int b = 0;
    for(int i = 0; i < str.size(); i++) {
        if(strchr("]})", str[i])) b--;
        else if(strchr("[{(", str[i])) b++;
    }

    return b == 0;
}

int main() {

    cout << brackets_balance("()()){}{}[][]()()") << endl;
    cout << brackets_balance("()(){}{}[][]()()") << endl;

    return 0;
}
