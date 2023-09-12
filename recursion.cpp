#include<bits/stdc++.h>
using namespace std;

int baitap1(int n)
{
  if(n == 0) return 0;
  else if(n == 1) return 1;
  else return baitap1(n-1) * pow(n, n);
}
int fibonaci(int n)
{
  if(n == 0) return 0;
  if(n == 1) return 1;
  else return fibonaci(n -1) + fibonaci(n-2);
}
int giaithua(int n)
{
  if(n < 0) return -1 ;
  if(n == 0 || n == 1) return n;
  else return n * giaithua(n-1);
}

int UCLN(int a, int b)
{
  if(b == 0) return a;
  else return UCLN(b, a % b);
}
int BCNN(int a, int b)
{
  return (a * b) / UCLN(a, b);
}
int sum(int n)
{
  if(n == 0 || n == 1) return n;
  else return n + sum(n - 1);
}
int main()
{
  //cout << baitap1(4);
  int n; cin >> n;
  //cout << fibonaci(n) << " ";
  //cout << giaithua(n);
  //cout << UCLN(3,4) << " " << BCNN(3,4);
  cout << sum(n);
  return 0;
}