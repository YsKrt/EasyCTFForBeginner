# EasyCTFForBeginner
CTFとはCapture The Flagの略で、特定の文字をプログラムから探すゲームです。<br>
ネットにあるCTFがむずすぎたので自分で自分が解けるくらいのCTFを作りました。<br>
windows上でexeファイルを起動すればできます。<br>
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


学んだこと。<br>
ポインタは4バイト単位だからDWORDとかに直さないと計算が狂っちまうよ！<br>

フラグや文字はxorやビット反転で隠した。<br>マルチバイト文字はビット反転だと反転させた文字を一回画面に表示させて、それをコピーしたものを反転させれば元に戻るが、xorは全然戻らなかった。<br>
