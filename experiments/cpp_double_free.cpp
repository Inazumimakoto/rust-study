#include <cstring>
#include <iostream>
using namespace std;

class MyString {
  char *data;
  int id;
  static int counter;

public:
  MyString(const char *s) {
    id = ++counter;
    data = new char[strlen(s) + 1];
    strcpy(data, s);
    cout << "📦 [" << id << "] コンストラクタ: data=" << (void *)data
         << " 内容=\"" << data << "\"" << endl;
  }

  // コピーコンストラクタをあえて定義しない！
  // → デフォルトの「シャローコピー」が使われる

  ~MyString() {
    cout << "💀 [" << id << "] デストラクタ: data=" << (void *)data
         << " を解放..." << endl;
    delete[] data; // ここで二重解放が起きる！
    cout << "   [" << id << "] 解放完了！" << endl;
  }

  void print() { cout << "📖 [" << id << "] 内容: \"" << data << "\"" << endl; }
};

int MyString::counter = 0;

int main() {
  cout << "=== C++ 二重解放（Double Free）デモ ===" << endl << endl;

  {
    cout << "--- s1 を作成 ---" << endl;
    MyString s1("hello");

    cout << "\n--- s2 = s1 でコピー（シャローコピー！）---" << endl;
    MyString s2 = s1; // デフォルトコピー = ポインタだけコピー

    cout << "\n--- 両方の内容を表示 ---" << endl;
    s1.print();
    s2.print();

    cout << "\n--- スコープ終わり、デストラクタが呼ばれる ---" << endl;
  }
  // ↑ ここで s2 → s1 の順でデストラクタ
  // 同じメモリを2回 delete → クラッシュ or 未定義動作！

  cout << "\nここに到達できたら奇跡（多分クラッシュ）" << endl;

  return 0;
}
