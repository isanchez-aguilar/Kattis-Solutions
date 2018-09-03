/*
*	User: Isanchez_Aguilar
*	Problem: Kattis Programming Tutors
*/
#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef pair<int, int> point;

vvi adj;
vi match;
vb visited;

inline int getDistance(point p1, point p2)
{
	return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

inline int getMaxFlow(int l)
{
	if (visited[l])
		return 0;
	
	visited[l] = true;

	for (int j = 0; j < adj[l].size(); ++j)
	{
		int v = adj[l][j];
	
		if (match[v] == -1 or getMaxFlow(match[v]))
		{
			match[v] = l;
			return 1;
		}
	}

	return 0;
}

int main(void)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	point tutors[n];
	point students[n];
	
	for (int i = 0; i < n; ++i)
		cin >> students[i].first >> students[i].second;
	
	for (int i = 0; i < n; ++i)
		cin >> tutors[i].first >> tutors[i].second;
	
	int l = 0;
	int r = 0;
	int distanceTable[n << 1][n << 1];
	
	adj.resize(n << 1);
	memset(distanceTable, INT_MAX, sizeof distanceTable);

	for (int i = 0; i < n; ++i)
	{
		for (int j = n; j < (n << 1); ++j)
		{
			distanceTable[i][j] = getDistance(students[i], tutors[j - n]);
			r = max(r, distanceTable[i][j]);
		}
	}

	while (l < r)
	{
		int flow = 0;
		int m = (l + r) >> 1;
		
		match.assign(n << 1, -1);
		
		for (int i = 0; i < n; ++i)
		{
			adj[i].clear();
			
			for (int j = n; j < (n << 1); ++j)
			{
				if (distanceTable[i][j] <= m)
				{
					adj[i].push_back(j);
					adj[j].push_back(i);
				}
			}
		}

		for (int i = 0; i < n; ++i)
		{
			visited.assign(n << 1, false);
			flow += getMaxFlow(i);
		}
		
		if (flow < n)
			l = m + 1;
		else
			r = m;
	}

	cout << l << "\n";

	return 0;
}