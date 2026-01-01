# 🔥 C++ ネガキャン（Rustが解決したこと）

C++でつらかったことを、Rustがどう解決したかまとめ。
Rustのありがたみを理解するためのファイル。

---

## 1. 参照渡しで変更されるかわからない問題

### C++（地獄）
```cpp
void process(string& s);      // 変更される？
void display(const string& s); // const なら変更されない

// 呼び出し側
process(text);   // ← textが変更されるか、ここだけ見てもわからん！
display(text);   // ← constかどうか、ここからは見えない
```

### Rust（天国）
```rust
fn process(s: &mut String);  // 変更する
fn display(s: &String);      // 変更しない

// 呼び出し側
process(&mut text);  // ← 「あ、変更されるんだな」一目瞭然！
display(&text);      // ← 変更されない、明確！
```

---

## 2. Null参照（Billion Dollar Mistake）

### C++（地獄）
```cpp
string* ptr = nullptr;
cout << *ptr;  // 💥 実行時クラッシュ！コンパイルは通る

// nullチェック忘れで死ぬ
if (ptr != nullptr) { ... }  // 毎回書くの？
```

### Rust（天国）
```rust
// Rustにはnullがない！代わりにOption
let value: Option<String> = None;

// 使う時は必ずチェックが必要（コンパイラが強制）
match value {
    Some(s) => println!("{}", s),
    None => println!("値がない"),
}
```

---

## 3. メモリ解放忘れ / 二重解放

### C++（地獄）
```cpp
int* ptr = new int(42);
delete ptr;
delete ptr;  // 💥 二重解放！未定義動作

// または
int* ptr = new int(42);
// deleteし忘れ → メモリリーク
```

### Rust（天国）
```rust
let s = String::from("hello");
// スコープ抜けたら自動で解放
// 二重解放？所有権システムが防ぐ！
```

---

## 4. データ競合（マルチスレッド）

### C++（地獄）
```cpp
// 複数スレッドから同じデータにアクセス
// → コンパイルは通るけど実行時にデータ競合で死ぬ
// → デバッグ地獄
```

### Rust（天国）
```rust
// コンパイル時に検出！実行する前にエラーになる
// 「Send」「Sync」トレイトで安全性を保証
```

---

## 5. switch文のbreak忘れ

### C++（地獄）
```cpp
switch (x) {
    case 1:
        doSomething();
        // break忘れた！→ 次のcaseに落ちる！
    case 2:
        doOther();  // ← 意図せず実行される
        break;
}
```

### Rust（天国）
```rust
match x {
    1 => do_something(),  // 自動で止まる
    2 => do_other(),
    _ => {},
}
```

---

## 6. 依存関係管理

### C++（地獄）
```bash
# ライブラリ追加したい？
# 1. ダウンロード
# 2. ビルド
# 3. パス設定
# 4. Makefile/CMake修正
# 5. 依存の依存も同じ手順...
# 6. バージョン違いで動かない
# 7. 泣く
```

### Rust（天国）
```toml
[dependencies]
rand = "0.8.3"
```
```bash
cargo build  # 終わり
```

---

## まとめ

| 問題 | C++ | Rust |
|------|-----|------|
| 参照の変更可否 | わからん | `&mut` で明確 |
| Null | 実行時💥 | コンパイル時に防止 |
| メモリ管理 | 手動🔥 | 自動（所有権） |
| データ競合 | 実行時💥 | コンパイル時に防止 |
| switch fall-through | 罠 | 安全 |
| 依存管理 | 地獄 | Cargo神 |

**C++で苦しんだ人たちが作った言語、それがRust** 🦀
