# 第11章: テスト

## テストとは

**コードが意図通りに動くか確認する仕組み！**

コンパイラは「メモリ安全」はチェックするけど、「ロジックが正しいか」はチェックしない。

---

## 基本構文

```rust
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}
```

### 実行

```bash
cargo test
```

---

## 3つのステップ

1. **セットアップ**: データや状態を準備
2. **実行**: 対象コードを動かす
3. **アサーション**: 結果が期待通りか確認

---

## よく使うマクロ

| マクロ | 用途 |
|--------|------|
| `assert!(条件)` | 条件が true か |
| `assert_eq!(a, b)` | a と b が等しいか |
| `assert_ne!(a, b)` | a と b が異なるか |

---

## 属性

```rust
#[test]
fn normal_test() { ... }

#[test]
#[should_panic]
fn test_that_should_panic() {
    panic!("expected panic");
}

#[test]
#[ignore]
fn expensive_test() { ... }  // cargo test -- --ignored で実行
```

---

## どんな時に使う？

1. **新機能追加時**: 既存機能が壊れてないか確認
2. **リファクタリング時**: 動作が変わってないか確認
3. **バグ修正時**: 同じバグが再発しないことを保証
4. **チーム開発**: CI で自動テスト

---

## 💡 学んだこと

- `#[test]` でテスト関数を定義
- `cargo test` で実行
- `assert!`, `assert_eq!`, `assert_ne!` でアサーション
- `#[should_panic]` でパニックをテスト
- 基本だけ覚えておけばOK！
