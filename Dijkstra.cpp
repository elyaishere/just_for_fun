// Dijkstra’s shortest path algorithm from x to y


#include <iostream>
#include <limits>
#include <vector>
#include <map>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;  // n - number of vertices, m - number of edges
    map<int, vector<pair<int, int>>> w;
    for (int i = 1; i <= n; ++i) {
        w[i] = {};
    }
    // w[i] = { {j, w}.. } - edge(i, j) = w
    for (int i = 0; i < m; ++i) {
        int x, y, wi;
        cin >> x >> y >> wi;
        w[x].push_back({y, wi});
    }
    int x, y;  // x - starting vertex, y - destination vertex
    cin >> x >> y;
    vector<bool> visited(n + 1, false);
    vector<int> D(n + 1, numeric_limits<int>::max());
    D[x] = 0;
    visited[x] = true;
    for (auto i: w[x]) {
        D[i.first] = i.second;
    }
    int cnt = n - 1;  // in case y is not reachable
    while (!visited[y] && cnt) {
        int u;
        int min_d = D[0];
        for (int j = 1; j <=n; ++j)
            if (!visited[j] && D[j] < min_d) {
                u = j;
                min_d = D[j];
            }
        visited[u] = true;
        for (auto i: w[u])
            if (D[i.first] > D[u] + i.second)
                D[i.first] = D[u] + i.second;
        --cnt;
    }
    if (visited[y]) cout << D[y] << endl;
    else cout << -1 << endl;
    return 0;
}
