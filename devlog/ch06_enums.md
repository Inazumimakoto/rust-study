# 第6章: Enum とパターンマッチ

## Enum とは

**「これ OR これ のどれか1つ」を表す型！**

### 構造体との違い

```
構造体 = AND（全部持つ）
  User { name AND email AND age }
  
Enum = OR（どれか1つ）
  IpAddr { V4 OR V6 }
```

---

## 基本的な Enum

```rust
enum IpAddrKind {
    V4,
    V6,
}

let four = IpAddrKind::V4;
let six = IpAddrKind::V6;
```

### データ付き Enum

```rust
enum IpAddr {
    V4(u8, u8, u8, u8),  // 各 variant で違う型！
    V6(String),
}

let home = IpAddr::V4(127, 0, 0, 1);
let loopback = IpAddr::V6(String::from("::1"));
```

### 複雑な Enum

```rust
enum Message {
    Quit,                       // データなし
    Move { x: i32, y: i32 },   // 構造体的
    Write(String),              // データ付き
    ChangeColor(i32, i32, i32), // タプル的
}
```

### Enum にもメソッド定義可能！

```rust
impl Message {
    fn call(&self) { }
}
```

---

## C++ の enum との違い

| | C++ enum | Rust enum |
|---|----------|-----------|
| データ | ただの数字 | **各 variant にデータ持てる！** |
| 柔軟性 | 低い | 高い |

---

## Option: NULL の代わり

**Rust には NULL がない！代わりに Option！**

### C++ の NULL の問題

```cpp
int* ptr = nullptr;
*ptr;  // 💀 クラッシュ！コンパイラは警告しない
```

### Rust の Option

```rust
enum Option<T> {
    Some(T),  // 値がある
    None,     // 値がない
}
```

### 使い方

```rust
let some_number = Some(5);        // 値「5」がある
let some_string = Some("hello");  // 値「hello」がある
let absent: Option<i32> = None;   // 値がない
```

**`Some(値)` = 箱に値が入ってる 📦**
**`None` = 箱が空っぽ 📭**

### なぜ安全？

```rust
let x: i8 = 5;
let y: Option<i8> = Some(5);

let sum = x + y;  // ❌ エラー！型が違う！
```

**`i8` と `Option<i8>` は別の型！**
**中身を取り出さないと使えない！ = チェック強制！**

### 中身を取り出す方法

```rust
match y {
    Some(value) => x + value,
    None => 0,  // None の場合の処理
}

y.unwrap()      // None だとパニック
y.unwrap_or(0)  // None のときは 0
```

### Option の実用例

```rust
// 1. 割り算（0で割れない）
fn divide(a: i32, b: i32) -> Option<i32> {
    if b == 0 { None } else { Some(a / b) }
}

divide(10, 2);  // Some(5)
divide(10, 0);  // None

// 2. 配列の安全なアクセス
let nums = vec![1, 2, 3];
nums.get(0);   // Some(&1)
nums.get(10);  // None（C++ならクラッシュ💀）

// 3. 検索
let names = vec!["Alice", "Bob"];
names.iter().find(|&x| *x == "Bob");  // Some(&"Bob")
names.iter().find(|&x| *x == "Dave"); // None
```

### なぜ `-> User` じゃダメ？

```rust
fn find_user(id: i32) -> User {
    // 見つからなかったら...何を返す？
    // Rust に NULL ないから返せない！
}

// だから Option を使う
fn find_user(id: i32) -> Option<User> {
    // 見つかった → Some(user)
    // 見つからない → None
}
```

**`-> User` = 必ずある**
**`-> Option<User>` = あるかも、ないかも**

---

## match: C++ の switch の完全上位互換

### C++ の switch（ゴミ）

```cpp
switch (value) {
    case 1:
        cout << "One";
        break;  // 忘れたらフォールスルー💀
    case 2:
        cout << "Two";
        break;
}
```

### Rust の match（神）

```rust
match value {
    1 => println!("One"),  // break 不要！
    2 => println!("Two"),
    _ => println!("Other"),
}
```

### match の利点

1. **フォールスルーなし**
2. **あらゆる型で使える**
3. **パターンマッチできる**
4. **値を返せる（式！）**
5. **網羅性チェック（全パターン必須）**

### パターンマッチの例

```rust
// Option のマッチ
match option_value {
    Some(5) => println!("5だ！"),
    Some(x) => println!("{}だ！", x),
    None => println!("なし"),
}

// 範囲マッチ
match age {
    0..=17 => "未成年",
    18..=64 => "成人",
    _ => "シニア",
}
```

### 比較表

| | C++ switch | Rust match |
|---|-----------|------------|
| break | 必要（忘れる💀）| 不要！ |
| 使える型 | 整数、enum | **全部！** |
| パターン | ❌ | ✅ |
| 式として使える | ❌ | ✅ |
| 網羅性チェック | ❌ | ✅ |

---

## if let: 簡単な match の代替

```rust
// match だと冗長
match some_value {
    Some(x) => println!("{}", x),
    _ => (),
}

// if let で簡潔に
if let Some(x) = some_value {
    println!("{}", x);
}
```

---

## 💡 学んだこと

- Enum = 「どれか1つ」を表す型（構造体は AND、Enum は OR）
- Rust の Enum は各 variant にデータを持てる（C++ は持てない）
- **Option**: NULL の代わり（`Some(値)` or `None`）
- Option は型が違うから中身を取り出さないと使えない = 安全
- **match**: switch の完全上位互換（パターンマッチ、式、網羅性チェック）
- `if let`: 1パターンだけなら簡潔に書ける
