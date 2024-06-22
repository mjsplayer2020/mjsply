import mjsmodule as mjs

# print(get_message("{\"type\":\"hello\",\"protocol\":\"mjsonp\",\"protocol_version\":3}\n"));
res_list=["{\"type\":\"start_game\",\"id\":1,\"names\":[\"ply1\",\"himawari\",\"ply3\",\"ply4\"]}\n"
    ,"{\"type\":\"start_kyoku\",\"bakaze\":\"E\",\"kyoku\":1,\"honba\":0,\"kyotaku\":0,\"oya\":0,\"dora_marker\":\"7s\",\"tehais\":[[\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\"],[\"1s\",\"2s\",\"3s\",\"4s\",\"5sr\",\"6s\",\"7s\",\"8s\",\"9s,\"1s\",\"1s\",\"9s\",\"9s\"],[\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\"],[\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\"]]}\n"
    ,"{\"type\":\"tsumo\",\"actor\":1,\"pai\":\"5mr\"}\n"
    ,"{\"type\":\"reach\",\"actor\":1}\n"
    ,"{\"type\":\"dahai\",\"actor\":1,\"pai\":\"5mr\",\"tsumogiri\":false}\n"
    ,"{\"type\":\"tsumo\",\"actor\":2,\"pai\":\"?\"}\n"
    ,"{\"type\":\"dahai\",\"actor\":2,\"pai\":\"5sr\",\"tsumogiri\":false}\n"
#    ,"{\"type\":\"tsumo\",\"actor\":1,\"pai\":\"3p\"}\n"
#    ,"{\"type\":\"reach\",\"actor\":1}\n"
#    ,"{\"type\":\"dahai\",\"actor\":1,\"pai\":\"C\",\"tsumogiri\":false}\n"
#    ,"{\"type\":\"tsumo\",\"actor\":1,\"pai\":\"5sr\"}\n"
    ]

#print(res_list)
for res in res_list:
  print("================")
  print("RES->:")
  print(res)
  snd = mjs.get_message(res)
  print("================")
  print("<-SND:")
  print(snd)
