# 第1章: 入門

## 📅 学習日
2026-01-01

## 🛠 やったこと

### 1.1 インストール

```bash
curl --proto '=https' --tlsv1.2 https://sh.rustup.rs -sSf | sh
```

- `rustup`: Rustのバージョン管理ツール
- `rustc`: Rustコンパイラ
- `cargo`: パッケージマネージャ＆ビルドツール

### 1.2 Hello, World!

```rust
fn main() {
    println!("Hello, world!");
}
```

- `fn` で関数定義
- `main()` はエントリーポイント
- `println!` はマクロ（`!`がついてるのがマクロの印）

### 1.3 Cargo

依存関係とか諸々管理してくれるビルドツール！今は単純だけど便利そう！

#### プロジェクト作成

```bash
cargo new プロジェクト名
```

- `Cargo.toml` と `src/` ができる
- ソースコードは `src/` に書いていく
- `cargo new` しなくても、手動で `src/` にソースを移動して `Cargo.toml` 置けばOK

![cargo new](../images/ch01_cargo_new.png)

#### コマンドまとめ

| コマンド | 説明 |
|----------|------|
| `cargo build` | バイナリを `target/debug/` に作成 |
| `cargo run` | ビルド＋実行（変更なければコンパイルスキップ！賢い！） |
| `cargo check` | コンパイルチェックのみ（バイナリ作らないから高速！） |
| `cargo build --release` | 最適化ビルド → `target/release/` に出力 |

- `--release` は Xcode のアーカイブみたいなもの（多分）
- 最適化される分コンパイルは遅くなる

![cargo build & run](../images/ch01_cargo_build_run.png)

## ❓ 疑問点

- `!`がマクロ呼び出しらしいけど、見た目は関数じゃん！
  - → マクロは関数と同じルールには必ずしも従わないらしい
  - → 第19章で詳しくやるらしい（先すぎる...）

## 💡 学んだこと

- Rustのインストールは `rustup` を使う
- `println!` は関数じゃなくてマクロ（`!`がついてる）
- コンパイルしてから実行する（`rustc main.rs` → `./main`）
- 構文がC++っぽい！
  - セミコロン `;` で文が終わる
  - `{}` で囲む

## 🖥 実行結果

![Hello World 実行成功！](../images/ch01_hello_world.png)
