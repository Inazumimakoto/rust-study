#include <iostream>
#include <string>
using namespace std;

// C++ では何も警告しない！
string &longest(string &x, string &y) {
  return x.length() > y.length() ? x : y;
}

int main() {
  string s1 = "hello";
  string *result;

  {
    string s2 = "world!!!";
    result = &longest(s1, s2);
    cout << "Inside: " << *result << endl; // OK
  } // s2 が死ぬ

  // result は s2 を指してるかもしれない（未定義動作）
  cout << "Outside: " << *result << endl; // 💀 ダングリング参照

  return 0;
}
