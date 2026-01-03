# 第5章: 構造体

C++でやったから大体わかる！（多分）

## 構造体とは

**雛形 = 構造体、実データ = インスタンス**

## 定義

```rust
struct User {
    username: String,
    email: String,
    sign_in_count: u64,
    active: bool,
}
```

### C++との違い

```cpp
// C++
struct User {
    string username;  // 型 フィールド名
};
```

```rust
// Rust
struct User {
    username: String,  // フィールド名: 型 ← 逆！
}
```

**型とフィールド名の順番が逆！**

---

## インスタンス作成

```rust
let user1 = User {
    email: String::from("someone@example.com"),
    username: String::from("someusername123"),
    active: true,
    sign_in_count: 1,
};
```

### フィールドアクセス

```rust
println!("{}", user1.email);  // ドットでアクセス
```

### 変更（全体が可変）

```rust
let mut user1 = User { ... };
user1.email = String::from("new@example.com");
```

**注意**: 一部フィールドだけ可変はできない！全体が `mut` か否か！

---

## 省略記法

### フィールド初期化省略

引数名とフィールド名が同じなら省略可能！

```rust
fn build_user(email: String, username: String) -> User {
    User {
        email,      // email: email の省略！
        username,   // username: username の省略！
        active: true,
        sign_in_count: 1,
    }
}
```

### 構造体更新記法

```rust
let user2 = User {
    email: String::from("another@example.com"),
    username: String::from("anotherusername567"),
    ..user1  // 残りは user1 から！
};
```

**注意**: `..user1` で String がムーブされたら `user1` 使えなくなる！

---

## タプル構造体

**C++にはない！Rust特有！**

```rust
struct Color(i32, i32, i32);
struct Point(i32, i32, i32);

let black = Color(0, 0, 0);
let origin = Point(0, 0, 0);
```

`black` は `Color` 型、`origin` は `Point` 型。
同じ `(i32, i32, i32)` でも**別の型**！

---

## ユニット様構造体

フィールドなし！トレイト実装用。

```rust
struct AlwaysEqual;
```

---

## ⚠️ 参照をフィールドに持つには？

```rust
struct User {
    username: &str,  // ❌ コンパイルエラー！
}
```

**エラー**: 「ライフタイム指定子が必要」

→ 第10章で解決！今は `String` を使おう！

---

## 💡 学んだこと

- 構造体 = 雛形、インスタンス = 実データ
- フィールド名: 型（C++と逆！）
- `mut` は全体、一部だけ可変は不可
- フィールド初期化省略記法
- `..` で構造体更新
- タプル構造体（C++にはない！）
- `&str` フィールドにはライフタイムが必要（第10章）
