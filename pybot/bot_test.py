# ---------------------------------------------------------------------------------------------- 
# 
# プログラム概要 ： 麻雀AI：MJSakuraモジュール
# バージョン     ： 0.0.1.0.20(mjai.app向け実装)
# プログラム名   ： bot.py
# 処理概要       ： mjai.app通信用スクリプト
# Ver0.0.1作成日 ： 2024/06/23 10:53:04
# 最終更新日     ： 2024/07/20 07:56:44
# 
# Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
# 
# ---------------------------------------------------------------------------------------------- 

import sys
import mjsmodule as mjs

# プレーヤIDの定義
ply_id = int(sys.argv[1])
ret = mjs.init_mjs_module(ply_id)

# メイン処理
while True:
  # resは行末に改行が必要
  res = sys.stdin.readline().strip() + "\n"
  print("================")
  print("RES->:")
  print(res)
  snd = mjs.get_message(res)
  print("================")
  print("<-SND:")
  # sndに改行が含まれている
  sys.stdout.write(snd)
  sys.stdout.flush()
