#include<bits/stdc++.h>
using namespace std;


void selectionSort(int a[], int n)
{
  for(int i = 0; i < n; i++){
    int min_pos = i;
    for(int j = i + 1; j < n; j++){
      if(a[min_pos] > a[j]) swap(a[min_pos], a[j]);
    }
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
  selectionSort(a, n);
  for(int x : a) cout << x << " ";
  return 0;
}