#include<bits/stdc++.h>
using namespace std;

void heapify(int a[], int n, int i)
{
  int l = 2*i + 1;
  int r = 2*i + 2;
  int largest = i;
  if(l < n && a[l] > a[largest])
  {
    largest = l;
  }
    if(r < n && a[r] > a[largest])
  {
    largest = r;
  }
  if(largest != i){
    swap(a[i], a[largest]);
    heapify(a, n, largest);
  }
}
void heapSort(int a[],int n){
  for(int i = n / 2 - 1; i >= 0; i--){
    heapify(a,n,i);
  }
  for(int i = n - 1; i>= 0; i--)
  {
    swap(a[i], a[0]);
    heapify(a, i, 0);
  }
}
int main()
{
  srand(time(NULL));
  int n; cin >> n;
  int a[n];
  for(int i = 0; i < n; i++)
  {
    a[i] = rand() % 100;
  }
  heapSort(a, n);
  for(int x : a) cout << x << " ";
  return 0;
}