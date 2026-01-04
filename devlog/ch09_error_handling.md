# 第9章: エラー処理

## Rust のエラー処理

**Rust には例外がない！エラーは型で表現！**

| エラー種類 | 処理方法 | 例 |
|-----------|---------|-----|
| 回復不能 | `panic!` | 配列範囲外、バグ |
| 回復可能 | `Result<T, E>` | ファイルなし、ネットワーク |

---

## 他の言語との比較

### Python / Java / C++ の例外

```python
# Python
try:
    file = open("hello.txt")
except FileNotFoundError:
    print("ファイルがない")
```

### 例外の問題点

1. **どこで例外が投げられるかわからない** 💀
2. **catch 忘れるとクラッシュ**
3. **エラー処理が「別の場所」に飛ぶ**

### Rust

**例外なし！`Result` で明示的にエラーを扱う！**

---

## panic!（回復不能なエラー）

### 基本

```rust
fn main() {
    panic!("crash and burn");  // クラッシュして炎上
}
```

### 範囲外アクセス

```rust
let v = vec![1, 2, 3];
v[99];  // panic!
```

### Rust vs C++

| 言語 | 範囲外アクセス |
|------|---------------|
| C/C++ | 未定義動作💀（何が返るかわからない）|
| Rust | panic!（安全に停止）|

**C++ は「メモリ上のナニカ」を返す = 脆弱性祭り！**
**Rust は panic で安全に止まる！**

### バックトレース

```bash
RUST_BACKTRACE=1 cargo run
```

**どこで panic したか詳細がわかる！**

### panic = 'abort' 設定

```toml
[profile.release]
panic = 'abort'
```

| 設定 | 動作 | バイナリサイズ |
|------|------|---------------|
| `unwind`（デフォルト）| スタック巻き戻し | 大きい |
| `abort` | 即座に終了 | 小さい |

---

## Result（回復可能なエラー）

### 定義

```rust
enum Result<T, E> {
    Ok(T),   // 成功
    Err(E),  // 失敗
}
```

### 基本的な使い方

```rust
use std::fs::File;

fn main() {
    let f = File::open("hello.txt");

    let f = match f {
        Ok(file) => file,
        Err(error) => panic!("ファイルを開けませんでした: {:?}", error),
    };
}
```

### エラーの種類で分岐

```rust
use std::io::ErrorKind;

let f = match File::open("hello.txt") {
    Ok(file) => file,
    Err(ref error) if error.kind() == ErrorKind::NotFound => {
        // ファイルがなかったら作成
        File::create("hello.txt").unwrap()
    },
    Err(error) => panic!("{:?}", error),
};
```

### unwrap と expect

```rust
// unwrap: 成功なら中身、失敗なら panic
let f = File::open("hello.txt").unwrap();

// expect: unwrap + エラーメッセージ
let f = File::open("hello.txt").expect("ファイルを開けませんでした");
```

---

## ? 演算子（エラー伝播）

### Before（長い）

```rust
fn read_username() -> Result<String, io::Error> {
    let f = File::open("hello.txt");
    let mut f = match f {
        Ok(file) => file,
        Err(e) => return Err(e),
    };
    let mut s = String::new();
    match f.read_to_string(&mut s) {
        Ok(_) => Ok(s),
        Err(e) => Err(e),
    }
}
```

### After（? で短く！）

```rust
fn read_username() -> Result<String, io::Error> {
    let mut f = File::open("hello.txt")?;
    let mut s = String::new();
    f.read_to_string(&mut s)?;
    Ok(s)
}
```

**`?` = 「Ok なら中身、Err なら即 return Err」！**

### さらに短く（チェーン）

```rust
fn read_username() -> Result<String, io::Error> {
    let mut s = String::new();
    File::open("hello.txt")?.read_to_string(&mut s)?;
    Ok(s)
}
```

---

## 💡 学んだこと

| 方法 | 用途 |
|------|------|
| `match` | 詳細なエラー処理 |
| `unwrap()` | 絶対成功する時 |
| `expect("msg")` | unwrap + メッセージ |
| `?` | エラーを呼び出し元に伝播 |

- Rust には例外がない！`Result` で明示的にエラー処理
- `?` は関数が `Result` を返す場合のみ使える
- C++ の例外より安全で分かりやすい！

