#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

int cycleStart, cycleEnd;
vector<vector<int>> graph;
vector<int> father;
vector<int> color;
vector<int> cycle;

bool DFS (int vertex) {
	color[vertex] = 1;
	int length = graph[vertex].size();
	for (int i=0; i<length; ++i) {
		int child = graph[vertex][i];
		if (child == father[vertex]) continue;
		if (color[child] == 0) {
			father[child] = vertex;
			if (DFS(child)) return true;
		}
		else if (color[child] == 1) {
			cycleStart = child;
			cycleEnd = vertex;
			return true;
		}
	}
	color[vertex] = 2;
	return false;
}

int main() {

	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);

	int n;
	scanf("%d", &n);
	graph.resize(n);
	for (int i=0; i<n; ++i) {
		for (int j=0; j<n; ++j) {
			int h;
			scanf("%d", &h);
			if (h) graph[i].push_back(j);
		}
	}

	father.resize(n, -1);
	color.resize(n, 0);
	cycleStart = -1;
	for (int i=0; i<n; ++i)
		if (color[i] == 0 && DFS(i))
			break;

	if (cycleStart == -1)
		printf("A");
	else {
		printf("N");
		for (int vertex = cycleEnd; vertex != cycleStart; vertex = father[vertex])
			cycle.push_back(vertex);
		cycle.push_back(cycleStart);
		reverse(cycle.begin(), cycle.end());
		int length = cycle.size();
		for (int i=0; i<length; ++i)
			printf(" %d", cycle[i]+1);
	}

	return 0;

}