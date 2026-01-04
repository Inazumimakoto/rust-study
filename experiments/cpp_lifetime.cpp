#include <cstring>
#include <iostream>
using namespace std;

// ポインタを返す関数（ライフタイム問題）
const char *longest(const char *x, const char *y) {
  return strlen(x) > strlen(y) ? x : y;
}

int main() {
  const char *s1 = "hello";
  const char *result;

  {
    // ローカル配列（スコープを抜けると無効）
    char s2[20] = "world!!!";
    result = longest(s1, s2);
    cout << "Inside: " << result << endl;

    // s2 を破壊
    memset(s2, 'X', 19);
    s2[19] = '\0';
  } // s2 が死ぬ

  // result は s2 を指してるかもしれない
  cout << "Outside: " << result << endl; // 💀

  return 0;
}
