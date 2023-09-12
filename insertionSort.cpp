#include<bits/stdc++.h>
using namespace std;


void insertionSort(int a[], int n)
{
  for(int i = 1; i < n; i++){
    int x = a[i], pos = i - 1;
    while (pos >= 0 && x < a[pos])
    {
      a[pos + 1] = a[pos];
      --pos;
    } 
    a[pos + 1] = x ;
  }
}

int main()
{
  int n; cin >> n;
  int a[n];
  srand(time(NULL));
  for(int i = 0; i < n; i++){
    a[i] = rand() % 100;
  }
  insertionSort(a, n);
  for(int x : a) cout << x << " ";
  return 0;
}