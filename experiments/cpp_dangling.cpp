#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    cout << "=== C++ Iterator Invalidation Demo ===" << endl;
    
    // ベクタの再配置によるダングリング参照
    vector<int> v = {1, 2, 3};
    
    cout << "Before: v = {1, 2, 3}" << endl;
    cout << "v.capacity() = " << v.capacity() << endl;
    
    int& first = v[0];  // 最初の要素への参照
    cout << "first (参照) = " << first << endl;
    cout << "first のアドレス = " << &first << endl;
    
    // 大量に追加して再配置を強制
    cout << "\n--- 大量に push_back... ---\n" << endl;
    for (int i = 0; i < 100; i++) {
        v.push_back(i);
    }
    
    cout << "After: v.capacity() = " << v.capacity() << endl;
    cout << "v[0] のアドレス = " << &v[0] << endl;
    
    cout << "\n=== ダングリング参照を使用 ===" << endl;
    cout << "first (ダングリング!) = " << first << endl;  // 未定義動作！
    
    // アドレスが変わってることを確認
    if (&first != &v[0]) {
        cout << "\n💀 アドレスが変わった！first はゴミを指してる！" << endl;
    }
    
    return 0;
}
