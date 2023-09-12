#include<bits/stdc++.h>
using namespace std;

void bubleSort(int a[], int n)
{
  for(int i = 0; i < n - 1; i++){
    for(int j = 0; j < n - i - 1; j++){
      if(a[j] > a[j+1]) {
        swap(a[j+1], a[j]);   
      } 
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
  bubleSort(a, n);
  for(int x : a) cout << x << " ";
  return 0;
}