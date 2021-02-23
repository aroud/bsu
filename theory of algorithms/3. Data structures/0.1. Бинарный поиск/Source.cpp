#include <iostream>
using namespace std;
 
bool lowerBound(int* arr, int& l, int&r, int x)
{
    while (l < r)
    {
        int k = (l + r) / 2;

        if (x <= arr[k])
            r = k;
        else
            l = k + 1;
    }
    return arr[l]==x;
}
void upperBound(int* arr, int& l, int& r, int x)
{
    while (l < r)
    {
        int k = (l + r) / 2;

        if (x < arr[k])
            r = k;
        else
            l = k + 1;
    }
}
int main()
{
    int n;
    cin >> n;

    int* arr = new int[n];

    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    int k;
    cin >> k;

    int x;
    for (int i = 0; i < k; ++i)
    {
        cin >> x;
        int l = 0, r = n;
        cout << lowerBound(arr, l, r, x)<<" ";
        cout << l<<" ";
        l = 0, r = n;
        upperBound(arr, l, r, x);
        cout << l << "\n";
    }

    delete[] arr;
    return 0;
}