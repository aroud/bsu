#include <bits/stdc++.h>

using namespace std;

int main()
{
   int n;
   cin>>n;
   int a[n];
   for(int i=0; i < n; i++)
   {
       cin >> a[i];
   }
   int k=0;
   int c=0;
   for (int i=0; i < n; i++)
   {
       if(k==0)
       {
           k=1;
           c=i+1;
           cout << "c= "<< c << endl;
       }
       else
       {
           if(a[c-1] == a[i])
           {
               k++;
              cout << "k= "<< k << endl;
           }
           else
           {
               k--;
               cout << "k= "<< k << endl;
           }
       }
   }
    cout << c;
    return 0;
}
