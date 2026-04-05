#include <iostream>
#include <vector>
using namespace std;

#define MAX 100

struct Node {
	int level;     // index of last considered item
	int profit;    // current profit
	int weight;    // current weight
	float ub;      // upper bound (profit)
	int taken[MAX]; // track included/excluded items
};

struct Item {
	int wt;
	int val;
	float ratio;
};

float uBound(const Node &u, int n, int W, int wt[], int val[]) {
	if (u.weight >= W) return 0.0f;

	float profit_bound = u.profit;
	int j = u.level + 1;
	int totweight = u.weight;

	// take items while there is capacity
	while (j < n && totweight + wt[j] <= W) {
		totweight += wt[j];
		profit_bound += val[j];
		j++;
	}

	// take fraction of the next item
	if (j < n) {
		profit_bound += (W - totweight) * ((float)val[j] / wt[j]);
	}

	return profit_bound;
}

// Select index of node with maximum UB in queue Q of given size
int selectMaxUB(Node Q[], int size) {
	int index = 0;
	float maxUB = Q[0].ub;
	for (int i = 1; i < size; i++) {
		if (Q[i].ub > maxUB) {
			maxUB = Q[i].ub;
			index = i;
		}
	}
	return index;
}

int main() {
	int n, W;
    cout << "Enter number of items and knapsack capacity: ";
	cin >> n >> W;
    if (n <= 0 || W <= 0) {
        cout << "Invalid input. Number of items and capacity must be positive." << endl;
        return 1;
    }

	vector<Item> items;
	int wt[MAX], val[MAX];

	for (int i = 0; i < n; i++) {
		cin >> wt[i] >> val[i];
		float ratio = (float)val[i] / wt[i];
		items.push_back({wt[i], val[i], ratio});
	}

	sort(items.begin(), items.end(), [](const Item &a, const Item &b){
		return a.ratio > b.ratio;
	});

	for (int i = 0; i < n; i++) {
		wt[i] = items[i].wt;
		val[i] = items[i].val;
	}
    // now wt and val are sorted and ready for branch and bound

	Node Q[1000];
	int size = 0;

	// initial node
	Node u;
	u.level = -1;
	u.profit = 0;
	u.weight = 0;
	for (int i = 0; i < MAX; i++) u.taken[i] = 0;
	u.ub = uBound(u, n, W, wt, val);

	Q[size++] = u;
	int maxProfit = 0;
	int bestTaken[MAX] = {0};

	while (size > 0) {
		int idx = selectMaxUB(Q, size);
		u = Q[idx];

		// remove selected node from queue
		Q[idx] = Q[size - 1];
		size--;

		if (u.ub <= maxProfit) continue; // prune

		// next item index
		int lvl = u.level + 1;
		if (lvl >= n) continue;

		// INCLUDE next item
		Node v = u;
		v.level = lvl;
		v.weight += wt[lvl];
		v.profit += val[lvl];
		v.taken[lvl] = 1;

		if (v.weight <= W && v.profit > maxProfit) {
			maxProfit = v.profit;
			for (int i = 0; i < n; i++) bestTaken[i] = v.taken[i];
		}

		v.ub = uBound(v, n, W, wt, val);
		if (v.ub > maxProfit) {
			Q[size++] = v;
		}

		// EXCLUDE next item
		Node w = u;
		w.level = lvl;
		w.taken[lvl] = 0;
		w.ub = uBound(w, n, W, wt, val);
		if (w.ub > maxProfit) {
			Q[size++] = w;
		}
	}

	cout << maxProfit << '\n';
	return 0;
}