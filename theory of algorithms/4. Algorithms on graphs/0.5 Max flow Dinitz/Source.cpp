#pragma comment(linker, "/STACK:16777216")
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <queue>
#include <cstring>
#include <iostream>
using namespace std;

class edge
{
public:
    edge(int _to, long long _cap, int _rev) : to(_to), cap(_cap), rev(_rev) {}
    int to;
    long long cap;
    int rev;
};
class dinic
{
private:
    long long INF;
    vector<edge> G[10000];
    int level[100000];
    int iter[100000];
public:
    dinic();
    void add_edge(int from, int to, long long cap);
    void bfs(int s);
    long long dfs(int v, int t, long long f);
    long long maximum_flow(int s, int t);
};
dinic::dinic()
{
    INF = LLONG_MAX;
    fill(level, level + 100000, 0);
    fill(iter, iter + 100000, 0);
}
void dinic::add_edge(int from, int to, long long cap)
{
    G[from].emplace_back( to, cap, (int)G[to].size() );
    G[to].emplace_back( from, 0, (int)G[from].size() - 1 );
}
void dinic::bfs(int s)
{
    std::memset(level, -1, sizeof(level));
    std::queue<int> que;
    level[s] = 0;
    que.push(s);
    while (!que.empty())
    {
        int v = que.front();
        que.pop();
        for (int i = 0; i < (int)G[v].size(); i++)
        {
            edge& e = G[v][i];
            if (e.cap > 0 && level[e.to] < 0)
            {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}
long long dinic::dfs(int v, int t, long long f)
{
    if (v == t)
        return f;
    for (int& i = iter[v]; i < (int)G[v].size(); i++)
    {
        edge& e = G[v][i];
        if (e.cap > 0 && level[v] < level[e.to])
        {
            long long d = dfs(e.to, t, std::min(f, e.cap));
            if (d > 0)
            {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}
long long dinic::maximum_flow(int s, int t)
{
    long long flow = 0;
    for (;;)
    {
        bfs(s);
        if (level[t] < 0)
            return flow;
        std::memset(iter, 0, sizeof(iter));
        long long f;
        while ((f = dfs(s, t, INF)) > 0)
            flow += f;
    }
}
int main() {
    int n, m, s, t;
   
    scanf("%d %d", &n, &m);

    s = 0; t = n-1;
    dinic din;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        din.add_edge(a-1, b-1, c);
    }


    cout << din.maximum_flow(s,t) << endl;

    return 0;
}