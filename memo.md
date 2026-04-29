# ft_printf 実装メモ

## 対応するフォーマット指定子

| 指定子 | 意味 |
|--------|------|
| `%c`        | 文字 |
| `%s`        | 文字列 |
| `%d` / `%i` | 符号付き整数（出力は同じ） |
| `%u`        | 符号なし整数 |
| `%x` / `%X` | 16進数（小文字/大文字） |
| `%p`        | ポインタアドレス |
| `%%`        | `%` 文字そのもの |

## ボーナスパート

### Bonus 1: `-`, `0`, `.` とフィールド幅

| 記法 | 意味 |
|------|------|
| `%10d`  | 幅10で右寄せ（デフォルト） |
| `%-10d` | `-` = 左寄せ |
| `%010d` | `0` = 0埋め |
| `%.5d`  | `.` = 精度（整数なら最小桁数） |

### Bonus 2: `#`, ` `（スペース）, `+`

| フラグ | 意味 |
|--------|------|
| `%#x`  | `#` = プレフィックス付加（`0x` / `0X`） |
| `% d`  | スペース = 正数の前にスペース |
| `%+d`  | `+` = 正数にも符号を付ける |

## 設計方針

### アクセス制御

- ヘルパー関数（`ft_putchar` 等）は**公開ヘッダーにプロトタイプを書かない**
- `static` はノルムの5関数制限によりファイルを分ける必要があるため使えない
- 内部用ヘッダー（`ft_printf_private.h`）で管理する方法もあるが、ヘッダーに書かないで十分

### フォーマット情報の管理（t_format 構造体）

ボーナスを見据えて、フォーマット指定子の情報を構造体で管理する。

```c
# define FLAG_MINUS   (1 << 0)  // -
# define FLAG_ZERO    (1 << 1)  // 0
# define FLAG_HASH    (1 << 2)  // #
# define FLAG_SPACE   (1 << 3)  //   (space)
# define FLAG_PLUS    (1 << 4)  // +

typedef struct s_format
{
    int     flags;      // 上記ビットフラグの組み合わせ
    int     width;      // フィールド幅（例: %10d → 10）
    int     precision;  // 精度（未指定は -1）
    char    spec;       // 変換指定子 (c, s, d, ...)
}   t_format;
```

フラグの操作：
```c
f.flags |= FLAG_MINUS;       // セット
if (f.flags & FLAG_MINUS)    // 確認
```

必須パートは `flags=0, width=0, precision=-1` で動作するので、後からボーナスを足しやすい。

### ファイル構成（ボーナス）

42のルール上、ボーナスはファイルを分ける必要がある（`_bonus.c` / `_bonus.h` サフィックス必須）。
共通ロジックは必須側に実装し、ボーナス側は `t_format` を拡張する形で最小限のコピーに抑える。

```
Makefile
ft_printf.h             ← 公開API（ft_printf のみ宣言）
ft_printf.c             ← エントリーポイント
ft_utils.c              ← ft_putchar, ft_putstr, ft_putnbr 等
ft_utils2.c             ← ft_putunsigned, ft_puthex, ft_putptr 等
ft_printf_bonus.c       ← ボーナス版エントリーポイント
ft_utils_bonus.c        ← ボーナス版ヘルパー
...
```

## 必要な関数一覧

### コア

| 関数 | 役割 |
|------|------|
| `ft_printf(const char *fmt, ...)` | エントリーポイント。フォーマット文字列を走査し `%` を検出したら振り分け |
| `ft_parse_format(const char *fmt, t_format *f)` | `%` 以降を解析して `t_format` に詰める |
| `ft_handle_specifier(va_list ap, t_format *f)` | `t_format` を見て各出力関数を呼び出し、書いた文字数を返す |

### 出力ヘルパー（各自 書いた文字数を返す）

| 関数 | 対応指定子 | 注意点 |
|------|-----------|--------|
| `ft_putchar(char c)` | `%c`, `%%` | `write(1, &c, 1)` で 1 を返す |
| `ft_putstr(char *s)` | `%s` | NULL のとき `"(null)"` を出力 |
| `ft_putnbr(int n)` | `%d`, `%i` | `INT_MIN` は `-n` でオーバーフローするのでハードコードで逃がす |
| `ft_putunsigned(unsigned int n)` | `%u` | 符号なしで再帰出力 |
| `ft_puthex(unsigned long n, int upper)` | `%x`, `%X` | `upper` で大文字/小文字を切り替え |
| `ft_putptr(void *ptr)` | `%p` | `"0x"` プレフィックスを付けて `ft_puthex` を呼ぶ。`unsigned long` にキャストすること |

## 呼び出し関係

```
ft_printf
  └─ (ループ) 普通の文字 → ft_putchar
              '%' 検出   → ft_parse_format → t_format
                         → ft_handle_specifier(ap, &f)
                              ├─ 'c'      → ft_putchar
                              ├─ 's'      → ft_putstr
                              ├─ 'd'/'i'  → ft_putnbr
                              ├─ 'u'      → ft_putunsigned
                              ├─ 'x'/'X'  → ft_puthex
                              ├─ 'p'      → ft_putptr → ft_puthex
                              └─ '%'      → ft_putchar('%')
```

## 実装メモ

- `ft_printf` の戻り値は**出力した総文字数**。各ヘルパーの戻り値を必ず積算する
- `%d` と `%i` は出力において完全に同じ動作（`scanf` では異なるが `printf` では同じ）
- `%f`（小数）は 42 ft_printf の必須パートに含まれないので実装不要
