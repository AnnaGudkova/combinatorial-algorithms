#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct point {
	int x, y;
	point() {}
	point(const int &x, const int &y) {
		this->x = x;
		this->y = y;
	}
	const bool operator == (const point &p) {
		return (x == p.x) && (y == p.y);
	}
	const bool operator != (const point &p) {
		return !(*this==p);
	}
} startPoint, endPoint;

vector<vector<int>> graph;
vector<vector<point>> father;
queue<point> list;
int n, m;

bool checkPush(const point &cell, const int &x, const int &y) {
	point next = point(cell.x+x, cell.y+y);
	if (next.x > -1 && next.x < n && next.y > -1 && next.y < m && !graph[next.x][next.y]) {
		list.push(next);
		graph[next.x][next.y] = 2;
		father[next.x][next.y] = cell;
		if (next == endPoint) return true;
	}
	return false;
}

int main() {

	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	scanf("%d%d", &n, &m);
	graph.resize(n);
	father.resize(n);
	for (int i=0; i<n; ++i) {
		graph[i].resize(m);
		father[i].resize(m);
		for (int j=0; j<m; ++j) {
			scanf("%d", &graph[i][j]);
		}	
	}
	scanf("%d%d%d%d", &startPoint.x, &startPoint.y, &endPoint.x, &endPoint.y);
	startPoint.x -= 1;
	startPoint.y -= 1;
	endPoint.x -= 1;
	endPoint.y -= 1;

	if (graph[startPoint.x][startPoint.y] || graph[endPoint.x][endPoint.y]) {
		printf("N");
		return 0;
	}

	list.push(startPoint);
	graph[startPoint.x][startPoint.y] = 2;
	while (!list.empty()) {
		point cell = list.front();
		list.pop();
		bool flag = false;
		flag = flag || checkPush(cell, 0, 1);
		flag = flag || checkPush(cell, 0, -1);
		flag = flag || checkPush(cell, 1, 0);
		flag = flag || checkPush(cell, -1, 0);
		if (flag) break;
	}

	if (list.empty()) {
		printf("N");
	}
	else {
		printf("Y");
		vector<point> way;
		point x;
		for (x=endPoint; x!=startPoint; x=father[x.x][x.y])
			way.push_back(x);
		way.push_back(x);
		reverse(way.begin(), way.end());
		int length = way.size();
		for (int i=0; i<length; ++i)
			printf("\n%d %d", way[i].x+1, way[i].y+1);
	}

	return 0;

}