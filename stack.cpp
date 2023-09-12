#include<stack>
#include<bits/stdc++.h>

using namespace std;

// khai bao : stack<kieu du lieu> tên-> stack<int> st;
//push: st.push(value);
//pop: st.pop();
//top: st.top();
//size: st.size();
//emty: st.emty();

// ứng dụng bài toán số nhị phân 
void nhiPhan(int n)
{
  stack <int> st;
  while(n != 0)
  {
    st.push(n%2);
    n=n/2;
  }
  while(!st.empty())
  {
    cout << st.top() ;
    st.pop();
  }

}

// kiểm tra dấu hợp lệ
void check()
{
  string s; cin >> s;
  stack<char> st;
  for(char x : s)
  {
    if(x == '(')
    {
     st.push(x);
    }
    else 
    {
      if(st.empty()) break;
      else st.pop();
    }
  }
  if(st.empty()) cout << "valid" << endl;
  else cout <<"invalid" << endl;
}

// phần tử lớn hơn từ bên phải 
void max(int n)
{
  int a[n], b[n];
  for(int &x : a) cin >> x;
  stack<int> st;
  for(int i = 0; i < n; i++)
  {
    if(st.empty()) 
    {
      st.push(i);
    }
    else
    {
      while(!st.empty() && a[st.top()] < a[i])
      {
        b[st.top()] = a[i];
        st.pop();
      }
    st.push(i);
    }
  }
    while(!st.empty())
    {
      b[st.top()] = -1;
      st.pop();
    }
  
  for(int x : b) cout << x << " ";
}
//diện tích cột trên biểu đồ

int main()

{
  //nhiPhan(37);
  max(7);
  return 0;
}