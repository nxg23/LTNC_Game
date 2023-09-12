#include<bits/stdc++.h>
using namespace std;

// first in first out 
// push()
// pop()
// size()
// empty()
// front()
// số nhị phân từ 1 -> n
 vector<string> res ;
void init()
{
  queue<string> que;
  que.push("1");
  res.push_back("1");
  while(res.size() < 10000)
  {
    string top = que.front();
    que.pop();
    res.push_back(top + "0");
    res.push_back(top + "1");
    que.push(top + "0");
    que.push(top +"1");
  }

}
int main()
{
 init();
 int t; cin >> t ;
 while(t--)
 {
  int n; cin >> n;
  for(int i = 0; i < n; i++) cout << res[i] << " " ;
  cout << endl ;
 }



  return 0;
}