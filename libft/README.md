*This project has been created as part of the 42 curriculum by ttakemur.*

# libft

## Description

libft は、C 標準ライブラリの主要な関数を自前で再実装したライブラリです。42 School のカリキュラムにおける最初のプロジェクトであり、以降のすべてのプロジェクトで共通して使用するユーティリティ関数群を構築することを目的としています。

実装した関数は以下のカテゴリに分類されます：

- **文字判定・変換**：`ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`, `ft_toupper`, `ft_tolower`
- **文字列操作**：`ft_strlen`, `ft_strchr`, `ft_strrchr`, `ft_strncmp`, `ft_strlcpy`, `ft_strlcat`, `ft_strnstr`, `ft_strdup`, `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_split`
- **メモリ操作**：`ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp`, `ft_calloc`
- **数値変換**：`ft_atoi`, `ft_itoa`
- **文字列・数値の出力**：`ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`
- **高階関数**：`ft_strmapi`, `ft_striteri`
- **連結リスト操作**：`ft_lstnew`, `ft_lstadd_front`, `ft_lstadd_back`, `ft_lstsize`, `ft_lstlast`, `ft_lstdelone`, `ft_lstclear`, `ft_lstiter`, `ft_lstmap`

すべての実装は 42 Norm（v3）に準拠しています。

## Instructions

### ビルド

```sh
make        # libft.a をビルド
make re     # フルリビルド
make clean  # オブジェクトファイルを削除
make fclean # オブジェクトファイルと libft.a を削除
```

### 使い方

自分のプロジェクトで使用する場合は、`libft.a` をリンクしてください。

```sh
cc -Wall -Wextra -Werror main.c -L. -lft
```

## Resources

- [Libft — 42 Cursus Notion](https://42-cursus.notion.site/Libft-3d8c19e472544799abf12bb235797e0e) — プロジェクト解説・参考資料
- [42 Norm v3](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf) — コーディング規約

### AI の使用について

本プロジェクトでは以下の用途に AI（Claude）を使用しました：

- 42 Norm に準拠したコードへの自動フォーマット（`c_formatter_42` の実行と 42 Header の挿入）
- C 言語特有の言語仕様（メモリ配置、スタックとヒープの違いなど）に関する質問
- 関数の実装方針の相談
