#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <map>
using namespace std;

// Simple node stored in a vector. children are indices into the vector.
struct Node {
	char ch;    // character for leaf nodes, '\0' otherwise
	int freq;   // frequency
	int left;   // index of left child (-1 if none)
	int right;  // index of right child (-1 if none)
	Node(char c, int f) : ch(c), freq(f), left(-1), right(-1) {}
	Node(int f, int l, int r) : ch('\0'), freq(f), left(l), right(r) {}
};

// Build codes from tree using node indices
void buildCodes(const vector<Node> &tree, int idx, const string &prefix, map<char,string> &codes) {
	if (idx < 0) return;
	const Node &node = tree[idx];
	if (node.left == -1 && node.right == -1) {
		// leaf
		codes[node.ch] = prefix.empty() ? "0" : prefix;
		return;
	}
	buildCodes(tree, node.left, prefix + '0', codes);
	buildCodes(tree, node.right, prefix + '1', codes);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string input;
	if (!getline(cin, input)) return 0;

	if (input.empty()) {
		cout << "No input provided.\n";
		return 0;
	}

	// frequency count
	map<char,int> freq;
	for (char c : input) freq[c]++;

	// nodes vector and min-heap of (freq, index)
	vector<Node> tree;
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

	// create leaf nodes
	for (auto &p : freq) {
		tree.emplace_back(p.first, p.second);
		int idx = (int)tree.size() - 1;
		pq.push({p.second, idx});
	}

	// special case: single unique character
	if (pq.size() == 1) {
		int rootIdx = pq.top().second;
		map<char,string> codes;
		buildCodes(tree, rootIdx, "", codes);
		cout << "Huffman Codes:\n";
		for (auto &kv : codes) cout << "'" << (kv.first==' ' ? string("space") : string(1,kv.first)) << "': " << kv.second << '\n';
		string encoded;
		for (char c : input) encoded += codes[c];
		cout << "\nEncoded string:\n" << encoded << '\n';
		return 0;
	}

	// build tree
	while (pq.size() > 1) {
		auto a = pq.top(); pq.pop();
		auto b = pq.top(); pq.pop();
		int freqSum = a.first + b.first;
		// new parent node with children indices a.second and b.second
		tree.emplace_back(freqSum, a.second, b.second);
		int parentIdx = (int)tree.size() - 1;
		pq.push({freqSum, parentIdx});
	}

	int rootIdx = pq.top().second;

	map<char,string> codes;
	buildCodes(tree, rootIdx, "", codes);

	cout << "Huffman Codes:\n";
	for (auto &kv : codes) {
		char c = kv.first;
		cout << "'";
		if (c == ' ') cout << "space";
		else cout << c;
		cout << "': " << kv.second << '\n';
	}

	string encoded;
	for (char c : input) encoded += codes[c];
	cout << "\nEncoded string:\n" << encoded << '\n';

	return 0;
}
