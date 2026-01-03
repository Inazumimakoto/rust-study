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

## モジュール = コードのフォルダ分け！

**1ファイル1000行を避けるための整理術！**

### Before: 地獄（1ファイルに全部）

```rust
// main.rs に全部... 1000行...
fn create_user() {}
fn add_to_waitlist() {}
fn take_order() {}
// どこに何があるかわからない！
```

### After: ファイル分割

```
src/
├── main.rs         ← メイン処理だけ
├── user.rs         ← ユーザー関連
└── order.rs        ← 注文関連
```

```rust
// main.rs
mod user;   // user.rs を読み込む
mod order;  // order.rs を読み込む

fn main() {
    user::create("taro");
    order::take();
}
```

---

## モジュールの2つの書き方

### 1. インラインモジュール（1ファイル内で整理）

```rust
// lib.rs（1ファイルだけど論理的に分けてる）
mod front_of_house {
    pub mod hosting {
        pub fn add_to_waitlist() {}
    }
}
```

| 記法 | 意味 |
|------|------|
| `mod foo { ... }` | {} の中身がモジュール（インライン）|
| `mod foo;` | `foo.rs` ファイルを読み込む |

### 2. 別ファイルモジュール（物理的にファイル分け）

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

### ネストした use（まとめて書く）

```rust
// 長い
use std::io;
use std::io::Write;

// ネストで短く
use std::io::{self, Write};
//             ↑ io 自体
//                  ↑ io::Write
```

```rust
// まとめる例
use std::{cmp::Ordering, io};
```

### Glob（全部持ち込む）⚠️

```rust
use std::collections::*;  // 全部持ち込む
```

**⚠️ 非推奨！どこから来たかわからなくなる！**

**テストでは使う：`use super::*;`**

### as で別名

```rust
use std::io::Result as IoResult;
```

### use の慣例

| 持ち込むもの | 慣例 |
|-------------|------|
| 関数 | 親モジュールまで（`hosting::func()`）|
| 構造体/enum | フルパス（`use HashMap;`）|

### `::` と `.` の違い

```rust
rand::thread_rng().gen_range(1..100);
//   ↑ モジュール::関数
//                 ↑ .メソッド
```

| 記号 | 意味 |
|------|------|
| `::` | モジュール/型の中身にアクセス |
| `.` | オブジェクトのメソッド/フィールド |

### トレイトを use しないとメソッド使えない

```rust
use rand::Rng;  // トレイトを持ち込む

rand::thread_rng().gen_range(1..100);
//                 ↑ Rng トレイトのメソッド
```

**`gen_range()` は `rand::` じゃなくて、オブジェクトのメソッド！**

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

### プライバシールール

| 関係 | 見える？ | pub 必要？ |
|------|---------|-----------|
| 兄弟モジュール | ✅ | ❌ |
| 親 → 子の中身 | ❌ | ✅ |
| 子 → 親 | ✅ | ❌ |

### なぜ隠す？

```rust
// ライブラリを作るとき
pub fn random() -> i32 {    // 公開（ユーザーが使う）
    let seed = get_seed();
    generate(seed)
}

fn get_seed() -> u64 { ... }     // 非公開（内部実装）
fn generate(seed: u64) -> i32 { ... }  // 非公開
```

**隠す理由:**
1. **後で変更しやすい** - 内部実装変えても影響なし
2. **間違った使い方を防ぐ** - 正しいAPIだけ公開
3. **APIをシンプルに** - 使う人は公開関数だけ覚えればOK

**「使う人に見せるもの」だけ `pub`！**

### pub use で再エクスポート

```rust
pub use crate::front_of_house::hosting;
```

### struct と enum の pub の違い

| | pub つけたら |
|---|-------------|
| struct | 構造体だけ公開、**フィールドは個別に pub 必要** |
| enum | 全部公開（variant も自動で公開）|

```rust
// struct: フィールドごとに pub 必要
pub struct User {
    pub name: String,    // 公開
    password: String,    // 非公開（外から触れない）
}

// enum: variant は自動で公開
pub enum Status {
    Active,   // 自動で公開
    Inactive, // 自動で公開
}
```

**非公開フィールドがあると外から作れない → コンストラクタ関数必要！**

### いつ使う？

**→ ライブラリ作るとき！**

```
普通のアプリ開発: 全部 pub でOK
ライブラリ開発: 内部実装を隠す
```

---

## 💡 学んだこと

## モジュールを別ファイルに分割

**`mod foo { }` → `mod foo;` に変えて別ファイルへ！**

```rust
// src/lib.rs
mod front_of_house;  // ← セミコロン！front_of_house.rs を読む
```

```
src/
├── lib.rs              ← mod front_of_house;
├── front_of_house.rs   ← pub mod hosting;
└── front_of_house/
    └── hosting.rs      ← pub fn add_to_waitlist() {}
```

**use や呼び出しは変更不要！モジュールツリーは同じ！**

---

## 💡 学んだこと

- **パッケージ** = プロジェクト全体（Cargo.toml があるところ）
- **クレート** = バイナリ（main.rs）or ライブラリ（lib.rs）
- **クレートルート** = コンパイルの起点
- **モジュール** = コードのフォルダ分け（1000行地獄を避ける）
- **パス** = `std::io::stdin`、`::` は階層アクセス
- **use** = パスを短くする
- **pub** = 公開する（デフォルトは非公開）
- **struct/enum の pub 違い**: struct はフィールド個別、enum は全部公開
- **`::` vs `.`**: モジュール/型 vs メソッド
- **トレイト use 必要**: `.gen_range()` 使うには `use rand::Rng;`
- **ファイル分割**: `mod foo;` で foo.rs を読む

---

> **モジュール = フォルダ分け！整理術！** 🦀

