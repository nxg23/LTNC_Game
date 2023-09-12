#include<bits/stdc++.h>
using namespace std;

// Sắp xếp nhanh
// phan hach lumuto
int partition(int a[], int l, int r)
{
  int i = l - 1;
  int pivot = a[r];
  for(int j = l; j < r; j++) {
     if(a[j] <= pivot){
      i++;
      swap(a[i], a[j]);
     }
  }
  i++;
  swap(a[i],pivot);
  return i;
}

// phan hach hoare
int partition2(int a[], int l, int r)
{
  int pivot = a[l];
  int i = l - 1, j = r + 1;
  while(1){
    do{
      ++i;

    }while(a[i] < pivot);

    do{
      --j;
    }while(a[j] > pivot);
    if( i < j) swap(a[i], a[j]);
    else return j;
  }
}
void quickSort(int a[], int l, int r)
{
  if( l >= r) return;
  //int p = partition(a, l , r);
  //quickSort(a, l, p - 1);
  //quickSort(a, p + 1, r);
  int p = partition2(a, l , r);
  quickSort(a, l, p);
  quickSort(a, p + 1, r);
}



int main()
{
  int n; cin >> n ;
  int a[n];
  //heapSort(a, n);
  srand(time(NULL));
  for(int i = 0; i < n; i++)
  {
    a[i] = rand() % 100;
  }
  quickSort(a, 0, n - 1);
  for(int i = 0; i < n; i++) cout << a[i] << " ";
  return 0;
}