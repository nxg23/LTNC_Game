#include<bits/stdc++.h>
using namespace std;

int cnt[10000001];
void countingSort(int a[], int n)
{
    int m = INT_MIN;
  for (int i = 0; i < n; i++){
    cnt[a[i]]++ ;
    m = max(m , a[i]);
  }
  
  for(int i = 0; i <= m; i++) {
    if(cnt[i] != 0){
     for(int j =0; j < cnt[i];j++ ){
      cout << i << " ";
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
 countingSort(a, n);
  //for(int x : a) cout << x << " ";
  return 0;
}