
/**
	Transform Word
	Given a source word, target word and an English dictionary, transform the source word to target
	by  changing/adding/removing  1  character  at  a  time,  while  all  intermediate  words  being  valid
	English words. Return the transformation chain which has the smallest number of intermediate
	words.
	**/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

/// 'A'..'z' implementation
map<string, vector<string>> generateGraph(vector<string> &dictionary) {
	map<string, vector<string>> graph;

	set<char> cached; /// cache characters
	for (auto word : dictionary) {
		for (auto ch : word) {
			cached.insert(ch);
		}
	}

	cout << "cached size : " << cached.size() << endl;

	for (auto word : dictionary) {
		for (int j = 0; j < word.size(); j++) {

			/// remove 1 character
			string remove = word.substr(0, j) + word.substr(j + 1, word.size() - 1);
			if (find(dictionary.begin(), dictionary.end(), remove) != dictionary.end()) {
				graph[word].push_back(remove);
			}

			/// change 1 character
			for (auto ch : cached) {
				string change = word.substr(0, j) + string(1, ch) + word.substr(j + 1, word.size() - 1);
				if (find(dictionary.begin(), dictionary.end(), change) != dictionary.end() && change != word) {
					graph[word].push_back(change);
				}
			}

			/// add 1 character
			for (auto ch : cached) {
				string add = word.substr(0, j) + string(1, ch) + word.substr(j, word.size() - 1);
				if (find(dictionary.begin(), dictionary.end(), add) != dictionary.end()) {
					graph[word].push_back(add);
				}
			}
		}
	}

	return graph;
}

vector<string> transformWord(map<string, vector<string>> &graph, string start, string goal) {
	vector<vector<string>> paths(1);
	paths[0].push_back(start);
	vector<string> extended;

	/// Breadth First Search
	while (!paths.empty()) {
		vector<string> currentPath = paths.back();
		paths.pop_back();

		string currentWord = currentPath[currentPath.size() - 1];
		if (currentWord == goal) {
			return currentPath;
		}
		else if (find(extended.begin(), extended.end(), currentWord) != extended.end()) {
			continue;
		}

		extended.push_back(currentWord);
		vector<string> transforms = graph[currentWord];
		for (auto word : transforms) {
			if (find(currentPath.begin(), currentPath.end(), word) == currentPath.end()) {
				currentPath.push_back(word);
				paths.push_back(currentPath);
			}
		}
	}

	cout << "path is empty" << endl;
	return vector<string>();
}

int main() {

	vector<string> dict = { "cat", "bat", "bet", "bed", "at", "ad", "ed" };

	map<string, vector<string>> graph = generateGraph(dict);

	for (auto x : graph) {
		std::cout << x.first << " : ";
		for (auto v : x.second) cout << v << " ";
		cout << std::endl;
	}

	auto res = transformWord(graph, "cat", "bed");

	for (auto v : res) cout << v << endl;

	return 0;
}
