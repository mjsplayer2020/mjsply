import socket
import mjsmodule as mjs

host = "192.168.27.88"
port = 11600

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, port))
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

res = s.recv(1024).decode("utf-8")
print("=============")
print(res)
s.send(b"{\"type\":\"join\",\"name\":\"tampopo\",\"room\":\"default\"}\n")

while True:
  res = s.recv(1024).decode("utf-8")
  if len(res) <= 0:
    break
  print("================")
  print("RES->:")
  print(res)
  snd = mjs.get_message(res)
  print("================")
  print("<-SND:")
  print(snd)
  s.send(snd.encode('utf8'))
# s.send(b"{\"type\":\"none\"}\n")
