#define _CRT_SECURE_NO_WARNINGS


#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>
#include <iostream>

using namespace std;

class Edge {
public:
    Edge(int u, int v, long long c, long long p) :u(u), v(v), c(c), p(p) {}
    Edge(const Edge& e, bool b) :u(e.v), v(e.u), c(0), p(-e.p) {}
    Edge(const Edge& e, bool b, bool b1) :u(e.u), v(e.v), c(e.c), p(e.p), f(0), rev(-1) {}
    int u, v;
    long long f = 0;
    long long c;
    long long p;
    int rev = -1;
};

int n, m, s, t;
vector <Edge> ve;
vector <int>* g;
long long* d;
long long* phi;
int* parent;

void fordBellman() {
    for (int i = 1; i <= n; i++)
        d[i] = INT_MAX;
    d[s] = 0;
    for (;;) 
    {
        bool any = false;
        for (int i = 0; i < m; i++) 
        {
            int u = ve[i].u;
            int v = ve[i].v;
            if (ve[i].f == ve[i].c)
                continue;
            if (d[u] < INT_MAX)
            {
                if (d[v] > d[u] + ve[i].p) 
                {
                    d[v] = d[u] + ve[i].p;
                    parent[v] = i;
                    any = true;
                }
            }
        }
        if (!any)
            break;
    }
}
void dijkstra()
{
    for (int i = 1; i <= n; ++i)
    {
        parent[i] = -1;
    }
    for (int i = 1; i <= n; ++i)
    {
        d[i] = INT_MAX;
    }
    d[s] = 0;
    vector<bool> used(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        int vertex = -1;
        for (int j = 1; j <= n; ++j)
        {
            if (!used[j] && (vertex == -1 || d[j] < d[vertex]))
            {
                vertex = j;
            }
        }
        if (d[vertex] == INT_MAX)
            break;
        used[vertex] = true;
        int e_num, to, w;
        for (int j = 0; j < g[vertex].size(); ++j)
        {
            e_num = g[vertex][j];
            if (ve[e_num].f == ve[e_num].c)
                continue;
            to = ve[e_num].v;
            w = ve[e_num].p + phi[vertex] - phi[to];
            if (d[vertex] + w < d[to])
            {
                d[to] = d[vertex] + w;
                parent[to] = e_num;
            }
        }
    }
}



long long minCost() 
{
    long long result = 0;

    fordBellman();
    for (int i = 1; i <= n; i++)
        phi[i] = d[i];
    int vertex, e_num;
    while (d[t] != INT_MAX) 
    {
        vertex = t;

        int min_upi = INT_MAX, upi;


        //найти минимум остаточных пропускных способностей на найденном пути

        while (vertex != s)
        {
            e_num = parent[vertex];
            Edge& temp = ve[e_num];
            int from = temp.u, upi = (temp.c - temp.f);
            min_upi = min(upi, min_upi);
            vertex = from;
        }

        vertex = t;

        while (vertex != s)
        {
            e_num = parent[vertex];
            Edge& temp = ve[e_num];
            Edge& temp_rev = ve[temp.rev];
            int from = temp.u;
            temp.f += min_upi;
            temp_rev.f -= min_upi;
            result += min_upi * temp.p;
            vertex = from;
        }

        dijkstra();

        for (int i = 1; i <= n; i++)
            phi[i] = min(phi[i] + d[i], (long long)INT_MAX);
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
  
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n >> m >> s >> t;
  
    g = new vector<int>[n + 1];
  

    int u, v, c, p;
    
    for (int i = 0; i < m; ++i)
    {
        cin >> u >> v >> c >> p;
        Edge e(u, v, c, p);
        Edge e_rev(v, u, 0, -p);
        e.rev = ve.size() + 1;
        e_rev.rev = ve.size();
        g[u].push_back(ve.size());
        g[v].push_back(ve.size() + 1);
        ve.push_back(e);
        ve.push_back(e_rev);
    }
    m = ve.size();
    d = new long long[n + 1];
    phi = new long long[n + 1];
    parent = new int[n + 1];


    long long min_cost = minCost();
    long long flow = 0;
    int e_num;
    for (int i = 0; i < g[s].size(); ++i)
    {
        e_num = g[s][i];
        flow += ve[e_num].f;
    }
  

    vector <int>* g_sugg;
    g_sugg = new vector<int>[n + 1];
    vector <Edge> ve_sugg;

    while (scanf("%d %d\n", &u, &v) != EOF) {
        for (int i = 0; i < g[u].size(); ++i)
        {
            e_num = g[u][i];
            Edge e (ve[e_num],true,true);
            
            if (e.v == v && e.c) //не искусственно добавленная дорога
            {
                Edge e_rev(e,true);
                e.rev = ve_sugg.size() + 1;
                e_rev.rev = ve_sugg.size();
                g_sugg[u].push_back(ve_sugg.size());
                g_sugg[v].push_back(ve_sugg.size() + 1);
                ve_sugg.push_back(e);
                ve_sugg.push_back(e_rev);
            }
        }
    }
    swap(ve, ve_sugg);
    swap(g, g_sugg);
    m = ve.size();

    long long min_cost_sugg = minCost();
    long long flow_sugg = 0;
    for (int i = 0; i < g[s].size(); ++i)
    {
        e_num = g[s][i];
        flow_sugg += ve[e_num].f;
    }
    if (flow == flow_sugg && min_cost == min_cost_sugg) 
    {
        printf("%s", "Yes\n");
        printf("%d\n", flow);
        printf("%d\n", min_cost);
    }
    else
    {
        printf("%s", "No\n");
        printf("%d\n", flow);
        printf("%d\n", min_cost);
        printf("%d\n", flow_sugg);
        printf("%d\n", min_cost_sugg);
    }

    delete[] g;
    delete[] g_sugg;
    delete[] phi;
    delete[] d;
    delete[] parent;
    return 0;
}