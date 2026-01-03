# 第7章: パッケージ・クレート・モジュール

プログラム整理術！

## 用語整理

```
📦 パッケージ（Package）= プロジェクト全体
├── 📄 Cargo.toml
│
├── 📚 クレート（Crate）= 実行ファイル or ライブラリ
│   ├── 🚀 バイナリクレート → 実行できる（main.rs）
│   └── 📖 ライブラリクレート → 使われる側（lib.rs）
│
└── 📁 モジュール（Module）= ファイル/フォルダ分け
    └── 関数、構造体など
```

---

## 用語の意味

| 用語 | 意味 | 例 |
|------|------|-----|
| パッケージ | プロジェクト全体 | `cargo new my_project` |
| バイナリクレート | 実行ファイル | `main.rs` |
| ライブラリクレート | ライブラリ | `lib.rs`, `rand` |
| モジュール | ファイル/フォルダ分け | `mod utils;` |
| パス | 場所を指定 | `std::io::stdin` |
| use | パスを短くする | `use std::io;` |

---

## 現実世界で例えると

```
📦 パッケージ = 本棚（プロジェクト全体）
│
├── 🚀 バイナリクレート = 実行できる本
│   └── 例: guessing_game（cargo runで動く）
│
├── 📖 ライブラリクレート = 参考書（他から使われる）
│   └── 例: rand（乱数生成に使った！）
│
└── 📁 モジュール = 本の章
    └── 例: std::io（std の中の io 章）
```

---

## フォルダ構造

```
my_project/          ← 📦 パッケージ
├── Cargo.toml
├── src/
│   ├── main.rs      ← 🚀 バイナリクレート
│   ├── lib.rs       ← 📖 ライブラリクレート（オプション）
│   └── utils/       ← 📁 モジュール
│       └── mod.rs
```

---

## クレートルート（Crate Root）

**コンパイラが最初に読むファイル！木構造の根っこ！**

| ファイル | 意味 |
|---------|------|
| `src/main.rs` | バイナリクレートのルート |
| `src/lib.rs` | ライブラリクレートのルート |

---

## Cargo の慣習（Convention）

**`Cargo.toml` に書かなくても、Cargo は暗黙で理解する！**

```
my_project/
├── Cargo.toml  ← main.rs や lib.rs の記述なし！
├── src/
│   ├── main.rs ← 自動的にバイナリクレート
│   └── lib.rs  ← 自動的にライブラリクレート
```

---

## パッケージのルール

```
1パッケージ = 
  ├── ライブラリクレート: 0個 or 1個（2個以上ダメ！）
  └── バイナリクレート:   何個でもOK！
```

### 複数バイナリを作るには？

```
my_project/
├── src/
│   ├── main.rs       ← バイナリ①
│   └── bin/          ← 複数バイナリ用フォルダ
│       ├── tool1.rs  ← バイナリ②
│       └── tool2.rs  ← バイナリ③
```

```bash
cargo run              # main.rs
cargo run --bin tool1  # tool1.rs
```

---

## 外部依存と自分のライブラリ

### 「1パッケージに1ライブラリ」は自分のパッケージの話！

```
my_project/
├── src/lib.rs  ← 自分のライブラリ（0〜1個）
│
└── Cargo.toml
    [dependencies]
    rand = "0.8"   ← 外部ライブラリ（何個でもOK！）
    serde = "1.0"
    tokio = "1.0"
```

**`rand` は crates.io からダウンロードした「他人のライブラリクレート」！**

---

## モジュールの定義

### インラインで定義

```rust
mod front_of_house {
    pub mod hosting {
        pub fn add_to_waitlist() {}
    }
}
```

### 別ファイルで定義

```
src/
├── main.rs
└── front_of_house.rs  ← モジュール
```

```rust
// main.rs
mod front_of_house;  // front_of_house.rs を読み込む
```

---

## パスの書き方

### 絶対パス（crate から）

```rust
crate::front_of_house::hosting::add_to_waitlist();
```

### 相対パス（現在位置から）

```rust
front_of_house::hosting::add_to_waitlist();
```

### super（親モジュール）

```rust
super::some_function();  // 親モジュールの関数
```

---

## use でパスを短縮

```rust
// 長い
std::io::stdin().read_line(&mut input);

// use で短く
use std::io;
io::stdin().read_line(&mut input);

// もっと短く
use std::io::stdin;
stdin().read_line(&mut input);
```

### 複数インポート

```rust
use std::io::{self, Write};  // io と io::Write
use std::collections::*;      // 全部（非推奨）
```

### as で別名

```rust
use std::io::Result as IoResult;
```

---

## pub: 公開/非公開

### デフォルトは非公開！

```rust
mod my_module {
    fn private_fn() {}      // 非公開
    pub fn public_fn() {}   // 公開
    
    pub struct MyStruct {
        pub field1: i32,    // 公開フィールド
        field2: i32,        // 非公開フィールド
    }
}
```

### pub use で再エクスポート

```rust
pub use crate::front_of_house::hosting;
```

---

## 💡 学んだこと

- **パッケージ** = プロジェクト全体（Cargo.toml があるところ）
- **クレート** = バイナリ（main.rs）or ライブラリ（lib.rs）
- **モジュール** = コードの整理（ファイル/フォルダ分け）
- **パス** = `std::io::stdin` みたいな場所指定
- **use** = パスを短くする
- **pub** = 公開する（デフォルトは非公開）
