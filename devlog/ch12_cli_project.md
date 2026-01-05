# 第12章: コマンドラインプログラムの構築 (`minigrep`)

## 1. プロジェクトのセットアップと基本実装

### 実装したコード (`src/main.rs`)

```rust
use std::env;
use std::fs::File;
use std::io::prelude::*;

fn main() {
    // 1. コマンドライン引数の取得
    let args: Vec<String> = env::args().collect();

    // 2. 引数の保存（参照を使用）
    let query = &args[1];
    let filename = &args[2];

    println!("Searching for {}", query);
    println!("In file {}", filename);

    // 3. ファイルを開く
    let mut f = File::open(filename).expect("file not found");

    // 4. ファイルの中身を読み込む
    let mut contents = String::new();
    f.read_to_string(&mut contents).expect("something went wrong reading the file");

    println!("With text:\n{}", contents);
}
```

## 💡 学んだこと・解説

### `use` と `#include`
*   `use` は Rust の名前空間を持ち込む機能。C++ の `using namespace` に近い。
*   `std::io::prelude::*` は I/O 処理に必要なトレイト（`Read`, `Write` など）を一括でインポートするために使う。これがないと `read_to_string` が使えない。

### コマンドライン引数 (`env::args()`)
*   `env::args()` はイテレータを返す。
*   `.collect()` でイテレータを消費して、ベクタ (`Vec<String>`) に変換する。
*   Python の `sys.argv` に近いが、Rust では明示的にコレクションに変換する必要がある。

### ファイル操作 (`File::open`)
*   **`File`**: 構造体名なので CamelCase（大文字始まり）。
*   **`mut f`**: `read_to_string` はファイルカーソルを進めるため、**ファイルオブジェクトの内部状態を変更する**。そのため、読み込みだけでも `mut` が必要。ここが重要！
*   **Rust の安全性**: ファイルが開けなかったり読み込めなかった場合は `expect` でパニックさせ、エラーを見逃さないようにしている。

### 所有権と参照
*   `query` や `filename` は `args` のデータを借用（参照 `&`）している。
*   データをコピー（`clone`）したり移動（`move`）させたりせず、参照を使うのがメモリ効率が良いベストプラクティス。

---

## 2. リファクタリング: 引数解析の抽出

`main` 関数が大きくなってきたので、引数解析のロジックを別の関数 `parse_config` に切り出す。

### 実装 (`src/main.rs`)

```rust
fn main() {
    let args: Vec<String> = env::args().collect();

    let (query, filename) = parse_config(&args);

    // ...
}

fn parse_config(args: &[String]) -> (&str, &str) {
    let query = &args[1];
    let filename = &args[2];

    (query, filename)
}
```

### 💡 なぜ `args: &[String]` なの？

`args` は `Vec<String>` なのに、なぜ関数の引数は `&[String]` （文字列スライス）にするのか？

#### 比較

| 書き方 | 意味 | メリット・デメリット |
|--------|------|----------------------|
| `args: Vec<String>` | 所有権をもらう | 元の場所で `args` が使えなくなる（move）。 |
| `args: &Vec<String>` | `Vec` の参照をもらう | `Vec` しか受け取れない。 |
| **`args: &[String]`** | **スライスをもらう** | **最も柔軟！** `Vec` 全体も、配列も、その一部も受け取れる。 |

#### ポイント
*   Rust では、コレクションへの参照を引数にする場合、**スライス (`&[T]`) を使うのが慣習（Idiom）**。
*   `&args` と書くだけで、Rust コンパイラが自動的に `&Vec<String>` を `&[String]` に変換してくれる（**Deref Coercion**）。
*   これにより、関数は「データの入れ物が何であれ、連続したデータの並びであれば何でもOK」という広い心を持つことができる。

---

#### ⚠️ 混乱ポイント: `&str` と `&[T]` は別物！

「スライス」という言葉には2種類あるので注意！

1.  **文字列スライス (`&str`)**
    *   **中身**: 文字列データ（UTF-8 bytes）の一部を指す。
    *   **例**: `"Hello"` のうち `"He"` だけを切り出す。
    *   **型**: `&str`

2.  **ベクタのスライス (`&[T]`)**
    *   **中身**: ベクタの**要素**の一部を指す。
    *   **例**: `["aaa", "bbb", "ccc"]` のうち `["aaa", "bbb"]` だけを切り出す。
    *   **型**: `&[String]` （もし中身が `i32` なら `&[i32]`）

今回 `parse_config(args: &[String])` で使っているのは **2. ベクタのスライス**。
`args` 変数（`Vec<String>`）は「文字列という箱」が並んだ棚みたいなもので、その「棚の一部（または全部）」を指し示しているのが `&[String]`。文字列の中身を切り刻んでいるわけではない！

---

## 3. リファクタリング: 構造体 `Config` の導入

引数の意味を明確にするため、タプルではなく専用の構造体 `Config` を使う。

### 実装 (`src/main.rs`)

```rust
struct Config {
    query: String,
    filename: String,
}

fn parse_config(args: &[String]) -> Config {
    // args は借用しているので、所有権を奪うことはできない。
    // Config はデータを所有したい (String) なので、データをコピー (clone) する必要がある。
    let query = args[1].clone();
    let filename = args[2].clone();

    Config { query, filename }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let config = parse_config(&args); // 呼び出し側もスッキリ！
    
    // ...
}
```

### 💡 なぜ `clone()` が必要なの？

**所有権の問題を回避するため！**

1.  **`Config` の定義**: `query: String` となっている。これは `Config` がデータの **所有権** を持ちたいということ。
2.  **`args` の状態**: `parse_config` は `&[String]` (参照) を受け取っている。つまり、データの所有者は `main` 関数の `args` 変数。
3.  **移動 (Move) 不可**: 借りているもの (`&args`) から、中身 (`String`) を勝手に持ち出して、自分のもの (`Config`) にすることはできない（所有権の移動禁止）。

#### 解決策
*   **A案: `clone()` する** (今回採用)
    *   データをまるっとコピーして新しい `String` を作る。
    *   **メリット**: 実装が単純、所有権の問題が消える。
    *   **デメリット**: メモリと時間を少し余分に使う（今回の規模なら無視できる）。
*   **B案: ライフタイムを使う** (今の段階では難しい)
    *   `struct Config<'a> { query: &'a str, ... }` のように参照を持つ。
    *   **メリット**: コピーしないので高速。
    *   **デメリット**: ライフタイム指定が必要になり、コードが複雑になる。

今回は**シンプルさ優先**で `clone()` を採用している。Rust 初学者はまず `clone` で動くものを作り、後で必要なら最適化するのが良い戦略！

---

