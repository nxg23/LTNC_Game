#include<bits/stdc++.h>
using namespace std;

string reverse(string st)
{
   reverse(st.begin(), st.end());
    return st;
}
int main()
{
   string st;
   cout << "Nhap chuoi : ";
   cin.ignore();
   getline(cin, st);
   cout << "Chuoi sau khi dao :" << reverse(st);
    return 0;
}
