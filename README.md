# CTF
CTFとはCapture The Flagの略で、特定の文字をプログラムから探すゲームです。<br>
ネットにあるCTFがむずすぎたので自分で自分が解けるくらいのCTFを作りました。<br>
 __windows__ 上でexeファイルを起動して、FLAG＿から始まる文字列を探す感じです。<br>
簡単なCTFで誘導付きで勉強ができるCTF欲しいぃ。<br>

1.overflow<br>
名前の通り。scanfの脆弱性を学べた。誘導付き。<br>

2.kakikae<br>
exeファイルの中身がどうなっているのかを学べた。誘導付き。<br>

3.CTF3<br>
拡張子とMZをいじって起動すると後はただのクイズ。<br>どっちかがWordを使っているためWordが入っていないならもう一方の方で。<br>
デッドプール見てないけどジャンプで読んで面白かった。<br>

4.CTF_APIHook<br>
mystrcmpをフックすれば解ける。mystrcmpはif文を回した自作関数ではなく、strcmpをIATを使わないでLoadLibraryで読みこんだもの。<br>
strcmpを参照するアドレスからたどれば書き換えられると思う。<br>
けれどデバッガを検出してfake関数に飛ばすように書き換えるようにしてある。<br>
あと静的解析で書き換えれば簡単に解けてしまう。<br>

5.CTF_MEMO<br>
windowsのメッセージとアンチデバッグを学べた。文字コードの扱いも大変だった。<br>
マルチスレッドでコードハッシュを常に確認している。<br>
メモ帳をもっといじりたかったけど文字の表示しかできなかった。<br>
親プロセス確認、strcmpのIAT確認、.textのコードハッシュ（SHA1）確認。<br>
なんかVisualStudioの例外処理のコードの部分がファイルを移動させたりコピーすると変わるから、ハッシュ値はDll1に初回だけ保存するようにした。<br>

6.CTFnet<br>
フラグをネットからダウンロードして比較するＣＴＦ。<br>
base64を理解するために自分で変換した。

学んだこと：<br>
ポインタは4バイト単位だからDWORDとかに直す！！<br>

フラグや文字はxorやビット反転で隠した。<br>マルチバイト文字はビット反転だと反転させた文字を一回画面に表示させて、それをコピーしたものを反転させれば元に戻るが、xorは全然戻らなかった。<br>


# CrackMeシリーズ<br>
CrackMeはパスワードを求める問題です。
プログラムが求めている文字をプログラムから読み取って解きます。

1.対策なし<br>
ただのif文です。そのまま読むだけです。

2.jumpを読む<br>
無駄なジャンプ、文字の足し引き計算があります。そこまで難しくはありません。
比較ルーチンの部分をインラインアセンブラを使わず、16進数の機械語で書いているので最初にめっちゃ代入している部分がありますが無視して良いです。

3.例外処理<br>
TLSからint3をnopに書き換えるスレッドを実行、int3の例外処理があります。<br>
時間がかかりすぎなければTLSの方は無視しても問題ないです。int3の例外処理はpushしているところを見れば解けます。
  
3.5.　例外処理＆コンパイラによる最適化<br>
SEHとVEHと、2つの例外処理があります。またCrackMe3はSEHの例外処理をアセンブラで書いているのに対して、こちらはコンパイラの機能を用いているため最適化されており非常に読みにくいです。

4. SelfDebugging & Heaven's Gate & MultiThread
SelfDebuggingはCreateProcessの引数の分岐やDebugActiveProcessStop。Heaven's GateはWinDbg64や64bitにコピー。MultiThreadは変数の参照から。
