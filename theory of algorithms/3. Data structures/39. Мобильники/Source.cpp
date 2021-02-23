#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n;

struct yNode {
    int sum;
    yNode* left;
    yNode* right;
    yNode(int sum) : sum(sum), left(nullptr), right(nullptr) {}
};

struct xNode {
    yNode* yTree;
    xNode* left;
    xNode* right;
    xNode(int sum) : left(nullptr), right(nullptr)
    {
        yTree = new yNode(sum);
    }
};

void yInc(yNode* t, int l, int r, int y, int delta)
{
    if (l == r)
    {
        t->sum += delta;
        return;
    }
    int m = (l + r) / 2;
    if (y <= m) {
        if (!t->left) t->left = new yNode(0);
        yInc(t->left, l, m, y, delta);
    }
    else {
        if (!t->right) t->right = new yNode(0);
        yInc(t->right, m + 1, r, y, delta);
    }
   
    int s1 = t->left ? t->left->sum : 0;
    int s2 = t->right ? t->right->sum : 0;

    t->sum = s1 + s2;
}


void xInc(xNode* t, int l, int r, int x, int y, int delta)
{
    if (l == r) 
    {
        yInc(t->yTree, 0, n - 1, y, delta);
        return;
    }
    int m = (l + r) / 2;
    if (x <= m)
    {
        if (!t->left) 
            t->left = new xNode(0);
        xInc(t->left, l, m, x, y, delta);
    }
    else 
    {
        if (!t->right) 
            t->right = new xNode(0);
        xInc(t->right, m + 1, r, x, y, delta);
    }

    yInc(t->yTree, 0, n - 1, y, delta);
}


int ySum(yNode* t, int l, int r, int yl, int yr) {
    if (yl > yr) 
        return 0;
    if (l == yl && r == yr) 
        return t->sum;

    int ym = (l + r) / 2;

    int s1 = t->left ? ySum(t->left, l, ym, yl, min(yr, ym)) : 0;
    int s2 = t->right ? ySum(t->right, ym + 1, r, max(yl, ym + 1), yr) : 0;

    return s1 + s2;
}

int xSum(xNode* t, int l, int r, int xl, int xr, int yl, int yr) {
    if (xl > xr) 
        return 0;
    if (l == xl && r == xr)
        return ySum(t->yTree, 0, n - 1, yl, yr);

    int xm = (l + r) / 2;

    int s1 = t->left ? xSum(t->left, l, xm, xl, min(xr, xm), yl, yr) : 0;
    int s2 = t->right ? xSum(t->right, xm + 1, r, max(xl, xm + 1), xr, yl, yr) : 0;

    return s1 + s2;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t;
    cin>> t >> n;

    int x1, y1, x2, y2, delta;
    xNode* xyTree = new xNode(0);

    while (cin >> t)
    {
        if (t == 1) 
        {
            scanf("%d %d %d", &x1, &y1, &delta);
            xInc(xyTree, 0, n - 1, x1, y1, delta);
        }
        else
        {
            if (t == 2)
            {
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                printf("%d\n", xSum(xyTree, 0, n - 1, x1, x2, y1, y2));
            }
            else 
            {
                break;
            }
        }
    }

    return 0;
}