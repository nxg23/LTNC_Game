#include<bits/stdc++.h>
using namespace std;

// size
// push_front : đẩy vào đầu 
// push_back : đẩy vaò cuối 
// pop_front : xóa đầu 
// pop_back : xóa cuối 
// empty() 
// front() : lấy phần tử đầu 
// back() : lấy phần tử cuối 

// sliding window maximum
// c1
void maximum(int n, int k)
{
  int a[n];
  for(int &x : a) cin >> x ;
  for(int i = 0; i < n - k; i++){
  int temp = INT_MIN ;
   for(int j = 0; j < k; j++){
    temp = max(temp, a[i + j]);
   }
   cout << temp <<" ";
  }
}
// c2 

int main()
{
  deque<int> dq;
  maximum(9,3);

  return 0;
}