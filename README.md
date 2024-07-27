# mjsply

## ツール情報
麻雀AI対戦サーバ「Mjai」向けのクライアントツール

## 実行手順：ruby用Mjaiサーバの場合

```
$ python mjscli.py
```

## 履歴
 * プログラム概要 ： mjsply：Mjaiクライアント
 * バージョン     ： 0.0.1.0.28(mjai.app配布版)
 * 最終更新日     ： 2024/07/27 12:34:20

## 実装予定
 * 期待値の実装
 * ドラ捨の優先順位検討(どのタイミングでドラを捨てるのか？)

## 実装済
 * 済：2024/07/14：オリの実装

## 不具合情報
 * (動作検証中)

## 不具合修正済
 * 済：2024/07/27：ラス牌で鳴いてしまう
 * 済：2024/07/27：1000点未満の時にリーチを掛けてしまう
 * 済：2024/07/07：Mjaiツール側の不具合でアンカンアクションを無効化
 * 済：2024/07/06：フリテンの確認を行っていない
 * 済：2024/07/06：次の自摸番がない場合(自摸牌が3枚以下)でリーチを宣言する

## リンク集
 * [Mjai麻雀AI対戦サーバ](https://gimite.net/pukiwiki/index.php?Mjai%20%E9%BA%BB%E9%9B%80AI%E5%AF%BE%E6%88%A6%E3%82%B5%E3%83%BC%E3%83%90)  
 * [mjai/github](https://github.com/gimite/mjai)
 * [mjai.app](https://mjai.app/)  
 * [mjai.app/github](https://github.com/smly/mjai.app)  
