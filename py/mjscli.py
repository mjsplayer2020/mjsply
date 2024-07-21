# ---------------------------------------------------------------------------------------------- 
# 
# プログラム概要 ： 麻雀AI：MJSakuraモジュール
# バージョン     ： 0.0.1.0.21(start_kyoku値読み込み処理の見直し)
# プログラム名   ： mjscli.py
# 処理概要       ： Mjai送信処理ツール
# Ver0.0.1作成日 ： 2024/06/22 20:30:48
# 最終更新日     ： 2024/07/20 17:00:20
# 
# Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
# 
# ---------------------------------------------------------------------------------------------- 

import socket
import mjsmodule as mjs

# 接続先サーバ定義
host = "192.168.27.88"
port = 11600

# socket初期化
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, port))
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

# joinメッセージ送信
res = s.recv(1024).decode("utf-8")
print("=============")
print(res)
s.send(b"{\"type\":\"join\",\"name\":\"mjsply\",\"room\":\"default\"}\n")

# メッセージ送受信
while True:
  res = s.recv(1024).decode("utf-8")
  if len(res) <= 0:
    break
#  print("================")
#  print("RES->:")
#  print(res)
  snd = mjs.get_message(res)
#  print("================")
#  print("<-SND:")
#  print(snd)
  s.send(snd.encode('utf8'))
