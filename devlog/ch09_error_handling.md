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

TODO: panic! の詳細

---

## Result（回復可能なエラー）

TODO: Result の詳細
