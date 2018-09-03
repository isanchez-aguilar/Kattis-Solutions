/*
*	User: Isanchez_Aguilar
*	Problem: Kattis Charles in Charge
*/
#include <bits/stdc++.h>

using namespace std;

typedef double Double;
typedef pair<int, Double> iD;
typedef pair<Double, int> Di;
typedef vector<int> vi;
typedef vector<iD> viD;
typedef vector<viD> vviD;
typedef vector<Double> vD;

int n;
vD dist;
vviD adj;
vi parent;
Double limitJunction = 1e20;

inline Double dijkstra()
{
	fill(dist.begin(), dist.end(), 1e20);
	fill(parent.begin(), parent.end(), -1);
	priority_queue< Di, vector<Di>, greater<Di> > node;
	
	dist[0] = 0;
	node.push(Di(0.0, 0));

	while (not node.empty())
	{
		Double d = node.top().first;
		int u = node.top().second;
		node.pop();
		
		if (dist[u] < d)
			continue;
		
		for (int i = 0; i < adj[u].size(); ++i)
		{
			int v = adj[u][i].first;
			Double k = adj[u][i].second;

			if (k < limitJunction and dist[u] + k < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + k;
				node.push(Di(dist[v], v));
			}
		}
	}

	return dist[n - 1];
}

int main(void)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int m;
	Double x;
	cin >> n >> m >> x;

	adj.resize(n);
	dist.resize(n);
	parent.resize(n);

	for (int i = 0; i < m; ++i)
	{
		int u;
		int v;
		Double k;
		cin >> u >> v >> k;

		adj[--u].push_back(iD(--v, k));
		adj[v].push_back(iD(u, k));
	}

	Double d;
	Double longestJunction;
	Double maxDistance = dijkstra() * (1.0 + x / 100.0);

	do
	{
		int u = n - 1;
		longestJunction = -1.0;
		Double currentDistance = dist[u];

		while (parent[u] != -1)
		{
			u = parent[u];
			longestJunction = max(longestJunction, currentDistance - dist[u]);
			currentDistance = dist[u];
		}

		d = dijkstra();
		limitJunction = longestJunction;
		
	}while (d <= maxDistance);
	
	cout << (int)longestJunction << "\n";

	return 0;
}