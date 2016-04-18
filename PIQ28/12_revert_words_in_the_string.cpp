/**
Reverse Words in a String
Given an input string, reverse all the words. To clarify, input: “Interviews are awesome!” output:
“awesome!  are  Interviews”.  Consider  all  consecutive  non­whitespace  characters  as  individual
words.  If  there  are  multiple  spaces  between  words  reduce  them  to  a  single  white  space.  Also
remove all leading and trailing whitespaces. So, the output for ”   CS degree”, “CS    degree”, “CS
degree   “, or ”   CS   degree   ” are all the same: “degree CS”.

**/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

string revert_substring(string &str, int first, int last) {
    for(int i = first, j = last; i < j; i++, j--) {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }

    return str;
}

string revert_words_1(string str) {
    revert_substring(str, 0, str.size()-1);

    int first = 0;
    int last = 0;
    for(int i = 0; i < str.size(); i++) {
        if(str[i] != ' ') {
            first = i;
            while(str[i] != ' ') {
                i++;
                if(i == str.size()-1) break;
            }

            last = i;

            revert_substring(str, first, last);
        }
    }

    return str;
}

int main() {

    cout << revert_words_1("123 456 789") << endl;

    return 0;
}
