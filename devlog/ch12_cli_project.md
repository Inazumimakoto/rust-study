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
