/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： 麻雀AI：MJSakuraモジュール
 * バージョン     ： 0.0.1.0.5(自摸和了Mes定義)
 * プログラム名   ： mjs
 * ファイル名     ： main.c
 * クラス名       ： main
 * 処理概要       ： メイン関数
 * Ver0.0.1作成日 ： 2024/06/01 16:03:43
 * 最終更新日     ： 2024/06/10 16:20:03
 * 
 * Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "mjs.h"

/* ---------------------------------------------------------------------------------------------- */
// 構造体定義
/* ---------------------------------------------------------------------------------------------- */
int main(){

	// 変数定義
	int  rcv_mes_count;
	char rcv_mes[256][1024];
	char snd_mes[1024];

	// 文字列定義
	rcv_mes_count = 7;

	// アクション定義
	// https://gimite.net/pukiwiki/index.php?Mjai%20%E9%BA%BB%E9%9B%80AI%E5%AF%BE%E6%88%A6%E3%82%B5%E3%83%BC%E3%83%90

	// 文字列定義
	sprintf(rcv_mes[0], "{\"type\":\"hello\",\"protocol\":\"mjsonp\",\"protocol_version\":3}\n");
	sprintf(rcv_mes[1], "{\"type\":\"start_game\",\"id\":1,\"names\":[\"ply1\",\"himawari\",\"ply3\",\"ply4\"]}\n");
	// sprintf(rcv_mes[2], "{\"type\":\"start_kyoku\",\"bakaze\":\"E\",\"kyoku\":1,\"honba\":0,\"kyotaku\":0,\"oya\":0,\"dora_marker\":\"7s\",\"tehais\":[[\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\"],[\"3s\",\"4s\",\"5sr\",\"5s\",\"5s\" ,\"6s\",\"7s\",\"8s\",\"E\",\"N\" ,\"N\" ,\"C\",\"C\"],[\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\"],[\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\"]]}\n");
	   sprintf(rcv_mes[2], "{\"type\":\"start_kyoku\",\"bakaze\":\"E\",\"kyoku\":1,\"honba\":0,\"kyotaku\":0,\"oya\":0,\"dora_marker\":\"7s\",\"tehais\":[[\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\"],[\"1s\",\"2s\",\"3s\" ,\"4s\",\"5pr\",\"6s\",\"7s\",\"8s\",\"9s ,\"1s\",\"1s\",\"9s\",\"9s\"],[\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\"],[\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\",\"?\"]]}\n");
	// sprintf(rcv_mes[3], "{\"type\":\"tsumo\",\"actor\":0,\"pai\":\"?\"}\n");
	sprintf(rcv_mes[3], "{\"type\":\"tsumo\",\"actor\":1,\"pai\":\"5sr\"}\n");
	sprintf(rcv_mes[4], "{\"type\":\"reach\",\"actor\":1}\n");
	sprintf(rcv_mes[5], "{\"type\":\"dahai\",\"actor\":1,\"pai\":\"5pr\",\"tsumogiri\":false}\n");
	sprintf(rcv_mes[6], "{\"type\":\"tsumo\",\"actor\":1,\"pai\":\"5sr\"}\n");

	// 解析処理
	for(int tmp_i = 0; tmp_i < rcv_mes_count; tmp_i++){
		get_message(rcv_mes[tmp_i], snd_mes);
	}

	// 処理終了
	return 0;

}

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */