# 第8章: 一般的なコレクション

## コレクションとは

**標準ライブラリの便利なデータ構造！**

| Rust | C++ | 用途 |
|------|-----|------|
| `Vec<T>` | `std::vector<T>` | 可変長配列 |
| `String` | `std::string` | 文字列 |
| `HashMap<K, V>` | `std::unordered_map<K, V>` | キーと値 |

---

## Vec（ベクタ）

### 作成

```rust
// 空のベクタ（型を明記！）
let v: Vec<i32> = Vec::new();

// vec! マクロ（型は推論される）
let v = vec![1, 2, 3];
```

### 要素の追加

```rust
let mut v = Vec::new();
v.push(1);
v.push(2);
```

### 要素の取得

```rust
let v = vec![1, 2, 3, 4, 5];

// 添字（範囲外でパニック）
let third = &v[2];

// get（Option を返す、安全）
match v.get(2) {
    Some(x) => println!("{}", x),
    None => println!("ない"),
}
```

---

## 借用規則と Vec

### ❌ ダメな例

```rust
let mut v = vec![1, 2, 3];
let first = &v[0];  // 不変借用
v.push(6);          // ❌ 可変借用できない！
println!("{}", first);
```

**なぜ？push で再割り当てが起きたら first が無効になるかも！**

### ✅ 解決策

```rust
let mut v = vec![1, 2, 3];
let first = &v[0];
println!("{}", first);  // 使い終わる
v.push(6);  // ✅ もう first は使ってない
```

---

## NLL（Non-Lexical Lifetimes）

**借用は「最後に使った場所」で終わる！**

```rust
let first = &v[0];  // 借用開始
println!("{}", first);  // ← 最後に使う = 借用終了
v.push(6);  // ✅ 借用は終わってる
```

**コンパイラは「この後使う？」を見てる！**

---

## for ループ

### 不変参照

```rust
let v = vec![1, 2, 3];
for i in &v {
    println!("{}", i);
}
```

### 可変参照

```rust
let mut v = vec![100, 32, 57];
for i in &mut v {
    *i += 50;  // * でデリファレンス
}
// v = [150, 82, 107]
```

**`*i` = 参照先の値にアクセス（C++ と同じ）**

### なぜ `println!` は * 不要？

```rust
for i in &v {
    println!("{}", i);  // ✅ * なしでOK
}

for i in &mut v {
    *i += 50;  // ❌ * 必要！
}
```

| 操作 | 自動デリファレンス |
|------|------------------|
| `println!` | ✅ する |
| `+=` `-=` など | ❌ しない（明示的に `*`）|

**Rust は「読み取り」は自動、「変更」は明示的！（めんどくせ！）**

---

## Enum で複数型を入れる

```rust
enum Cell {
    Int(i32),
    Float(f64),
    Text(String),
}

let row = vec![
    Cell::Int(3),
    Cell::Text(String::from("blue")),
    Cell::Float(10.12),
];
```

**Vec は1型だけど、Enum なら複数種類OK！**

---

## 💡 学んだこと（Vec）

- `Vec::new()` は型を明記、`vec![]` は推論
- `push()` で追加、`get()` は安全（Option）
- 借用中は push できない（再割り当ての危険）
- NLL: 「最後に使った場所」で借用終了
- `*i` でデリファレンス
- Enum で複数型を入れられる

---

## String（文字列）

### 命名規則

| 種類 | 命名 | 例 |
|------|------|-----|
| 型/構造体/Enum | PascalCase | `String`, `OsString` |
| 関数/変数 | snake_case | `to_string()`, `push_str()` |

### String vs &str

```rust
let s1: &str = "hello";                  // 文字列リテラル（参照）
let s2: String = String::from("hello");  // String（ヒープ）
let s3: String = "hello".to_string();    // これも同じ
```

| | `&str` | `String` |
|---|--------|----------|
| 場所 | 参照 | ヒープ |
| 可変 | ❌ | ✅ |
| 文字列リテラル | ✅ | ❌ |

**ダブルクォートで書いた文字列 = `&str`**

### UTF-8 vs Unicode

```
Unicode = 文字のカタログ（番号）
UTF-8 = Unicode を保存する方法（バイト列）

'A' → UTF-8: 1バイト
'あ' → UTF-8: 3バイト
'З' → UTF-8: 2バイト
```

**Rust の String は UTF-8 エンコーディング！**

### 文字列操作

```rust
let mut s = String::from("foo");

s.push_str("bar");  // 文字列追加
s.push('!');        // 1文字追加

// + 演算子（s1 は move される！）
let s1 = String::from("Hello");
let s2 = String::from("World");
let s3 = s1 + &s2;  // s1 は使えなくなる

// format! マクロ（所有権奪わない、読みやすい）
let s = format!("{}-{}", s2, s3);
```

### 参照外し型強制（Deref Coercion）

```rust
&String → &str  // 自動変換！
```

### 添字アクセスできない！

```rust
let s = String::from("Здравствуйте");
s[0];  // ❌ エラー！
```

**UTF-8 は可変長だから `[0]` が何を返すべきかわからない！**

```rust
// 代わりの方法
s.as_bytes()[0];   // バイト
s.chars().nth(0);  // 文字
&s[0..4];          // スライス（境界注意！）

// 文字を走査
for c in "नमस्ते".chars() {
    println!("{}", c);
}
```

### &str と String のメソッド共有

| メソッド | `&str` | `String` |
|---------|--------|----------|
| `.chars()` | ✅ | ✅ |
| `.len()` | ✅ | ✅ |
| `.push()` | ❌ | ✅ |

**変更系は `String` だけ！読み取り系は両方！**

---

## 💡 学んだこと（String）

- 文字列リテラル `"..."` は `&str`
- `to_string()` と `String::from()` は同じ
- UTF-8 エンコーディング（可変長）
- 添字アクセス禁止（`.chars()` を使う）
- `+` は左側の所有権を奪う、`format!` は奪わない
- `&String` → `&str` 自動変換（参照外し型強制）

