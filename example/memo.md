# memo

## recieve.cpp

### output
```cpp
for (int i = 0; i < ETH_ALEN; i++)
    std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)eth->h_dest[i] << (i < ETH_ALEN - 1 ? ":" : "");
```

#### ループ構造
```cpp
for (int i = 0; i < ETH_ALEN; i++)
```
- `for`ループは、イーサネットアドレスの各バイトを順に処理します。
- `ETH_ALEN`は、イーサネットアドレスの長さ（通常6バイト）を示す定数です。
- `i`はインデックス変数で、0から5までの値を取ります。

#### ループ内の出力操作
```cpp
std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)eth->h_dest[i] << (i < ETH_ALEN - 1 ? ":" : "");
```
この部分は、MACアドレスの各バイトを適切にフォーマットして表示するためのものです。

1. **`std::cout <<`**:
   - 標準出力ストリームにデータを送ります。

2. **`std::hex`**:
   - 以降の数値出力を16進数形式に変更します。

3. **`std::setw(2)`**:
   - 次に出力する数値の幅を2桁に設定します。例えば、数値`1`は`01`として表示されます。

4. **`std::setfill('0')`**:
   - 幅が足りない場合、空白ではなく`0`で埋めます。

5. **`(int)eth->h_dest[i]`**:
   - `eth->h_dest[i]`は、イーサネットアドレスの`i`番目のバイトです。
   - `unsigned char`型の値を`int`にキャストしてから出力します。これは、出力を適切に行うためです。

6. **`(i < ETH_ALEN - 1 ? ":" : "")`**:
   - 条件演算子（三項演算子）を使って、現在のバイトが最後のバイトでない場合はコロン（`:`）を出力し、最後のバイトの場合は何も出力しません。
   - これにより、MACアドレスの各バイトの間にコロンを挿入します。