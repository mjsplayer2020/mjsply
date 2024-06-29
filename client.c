/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： 麻雀AI：MJSakuraモジュール
 * バージョン     ： 0.0.1.0.11(チーポン処理準備)
 * プログラム名   ： mjs
 * ファイル名     ： client.c
 * クラス名       ： MJSMjaiClient構造体
 * 処理概要       ： クライアント構造体
 * Ver0.0.1作成日 ： 2024/06/01 16:03:43
 * 最終更新日     ： 2024/06/29 15:53:39
 * 
 * Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "client.h"

/* ---------------------------------------------------------------------------------------------- */
// メイン処理
/* ---------------------------------------------------------------------------------------------- */
void set_ply_id(int tmp_ply_id){

	// 卓開始処理(Ply_id設定)
	ply_id = tmp_ply_id;
	PlyActTakuStart(tmp_ply_id);

}

/* ---------------------------------------------------------------------------------------------- */
// メイン処理
/* ---------------------------------------------------------------------------------------------- */
void set_taku_stat_main(struct MJSClient *cli, char* tmp_res_mes, char* tmp_snd_mes){

	// ----------------------------------------
	// 初期化処理
	// ----------------------------------------

	// 構造体定義
	struct MJSPlyInfo pinfo;

	// ----------------------------------------
	// メイン処理
	// ----------------------------------------

	// 解析
	read_logline(cli, tmp_res_mes);

	// MjaiのTYPEごとの処理確認
	chk_mjai_type_main(cli, &pinfo, tmp_snd_mes);

}

/* ---------------------------------------------------------------------------------------------- */
// 牌番号取得
/* ---------------------------------------------------------------------------------------------- */
int get_hainum(char hai_str[]){

	char tmp_str[8];
	int  hainum;

	// ----------------------------------------
	// 1文字目
	// ----------------------------------------

	tmp_str[0] = hai_str[0];
	tmp_str[1] = '\0';

	// 文字抽出(半角_前半分)
	if(      strcmp( tmp_str, "1" ) == 0){
		hainum = 1;
	}else if(strcmp( tmp_str, "2" ) == 0){
		hainum = 2;
	}else if(strcmp( tmp_str, "3" ) == 0){
		hainum = 3;
	}else if(strcmp( tmp_str, "4" ) == 0){
		hainum = 4;
	}else if(strcmp( tmp_str, "5" ) == 0){
		hainum = 5;
	}else if(strcmp( tmp_str, "6" ) == 0){
		hainum = 6;
	}else if(strcmp( tmp_str, "7" ) == 0){
		hainum = 7;
	}else if(strcmp( tmp_str, "8" ) == 0){
		hainum = 8;
	}else if(strcmp( tmp_str, "9" ) == 0){
		hainum = 9;
	}else if(strcmp( tmp_str, "E" ) == 0){
		hainum = 31;
	}else if(strcmp( tmp_str, "S" ) == 0){
		hainum = 32;
	}else if(strcmp( tmp_str, "W" ) == 0){
		hainum = 33;
	}else if(strcmp( tmp_str, "N" ) == 0){
		hainum = 34;
	}else if(strcmp( tmp_str, "P" ) == 0){
		hainum = 35;
	}else if(strcmp( tmp_str, "F" ) == 0){
		hainum = 36;
	}else if(strcmp( tmp_str, "C" ) == 0){
		hainum = 37;
	}else if(strcmp( tmp_str, "?" ) == 0){
		hainum = 0;
	}else{
		hainum = 0;
	}

	// ----------------------------------------
	// 2文字目
	// ----------------------------------------

	if( hai_str[1] != '\0'){

		tmp_str[0] = hai_str[1];
		tmp_str[1] = '\0';

		if(      strcmp( tmp_str, "m" ) == 0){

		}else if(strcmp( tmp_str, "p" ) == 0){
			hainum = hainum + 10;
		}else if(strcmp( tmp_str, "s" ) == 0){
			hainum = hainum + 20;
		}else{

		}

	}

	// ----------------------------------------
	// 3文字目
	// ----------------------------------------

	if(( hai_str[1] != '\0' ) && ( hai_str[2] != '\0' )){

		tmp_str[0] = hai_str[2];
		tmp_str[1] = '\0';

		if( strcmp( tmp_str, "r" ) == 0){
			hainum = hainum + 100;
		}else{

		}

	}

	// ----------------------------------------
	// 返り値
	// ----------------------------------------
	return hainum;

}

/* ---------------------------------------------------------------------------------------------- */
// Mjai向け牌文字取得
/* ---------------------------------------------------------------------------------------------- */
void Get_haichr(int hai_num, bool hai_aka, char hai_str[]){

	// 字牌処理
	if(hai_num > 30){

		if(hai_num == 31){
			sprintf(hai_str, "E");
		}else if(hai_num == 32){
			sprintf(hai_str, "S");
		}else if(hai_num == 33){
			sprintf(hai_str, "W");
		}else if(hai_num == 34){
			sprintf(hai_str, "N");
		}else if(hai_num == 35){
			sprintf(hai_str, "P");
		}else if(hai_num == 36){
			sprintf(hai_str, "F");
		}else if(hai_num == 37){
			sprintf(hai_str, "C");
		}else{
			sprintf(hai_str, "-");
		}

	}else if (hai_num > 0 && hai_num < 10){
		if(hai_aka==true){
			sprintf(hai_str, "%dmr", hai_num%10);
		}else{
			sprintf(hai_str, "%dm" , hai_num%10);
		}
	}else if (hai_num > 10 && hai_num < 20){
		if(hai_aka==true){
			sprintf(hai_str, "%dpr", hai_num%10);
		}else{
			sprintf(hai_str, "%dp" , hai_num%10);
		}
	}else if (hai_num > 20 && hai_num < 30){
		if(hai_aka==true){
			sprintf(hai_str, "%dsr", hai_num%10);
		}else{
			sprintf(hai_str, "%ds" , hai_num%10);
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// MjaiJSONの読み込み
/* ---------------------------------------------------------------------------------------------- */
void read_logline(struct MJSClient *cli, char *line_buf){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------

	// wkインデックスの初期化
	cli->wk_str_count = 0;

	// 読み込み文字定義用
	int  line_buf_point;                //  fgetのバッファの位置取り
	char tmp_wk_str[1024];              //  1ワードのバッファ用
	char tmp_buf[3];                    //  分割処理用

	// 空白確認フラグ
	int space_flg;                      // 0：文字なし(空白スペースのみ) 1：空白以外の文字列

	// 値の初期化
	line_buf_point = 0;
	space_flg = 0;                      // 「空白」「改行」以外の半角文字を読込んだ場合は、「space_flg = 1」とする。

	// バッファクリア
	memset(tmp_wk_str, 0, sizeof(tmp_wk_str));
	// sprintf(tmp_wk_str, "");

	/* ---------------------------------------- */
	// fgetで取得した文字列を行末まで確認する
	/* ---------------------------------------- */
    while( line_buf[line_buf_point] != '\0' ){

		/* ---------------------------------------- */
		// 半角文字の格納
		/* ---------------------------------------- */
		tmp_buf[0] = line_buf[line_buf_point];
		tmp_buf[1] = '\0';
		line_buf_point++;

		/* ---------------------------------------- */
		// 文字抽出(空白)
		/* ---------------------------------------- */
		if ( strcmp(tmp_buf, ":" ) == 0 || strcmp(tmp_buf, "," ) == 0 ){

				// 「空白区切り」で文字を追記
				if(space_flg == 1){
					space_flg = 0;

					// wk構造体に一時データを格納、その後tmp_wk_strは初期化
					set_wk_param(cli, tmp_wk_str);
					memset(tmp_wk_str, 0, sizeof(tmp_wk_str));
					// sprintf(tmp_wk_str, "");

				}

		/* ---------------------------------------- */
		// 無視文字
		/* ---------------------------------------- */
		}else if( strcmp(tmp_buf, "{")  == 0 || 
		          strcmp(tmp_buf, "}")  == 0 || 
		          strcmp(tmp_buf, "\"") == 0 || 
		          strcmp(tmp_buf, "[")  == 0 || 
		          strcmp(tmp_buf, "]")  == 0 ){

		/* ---------------------------------------- */
		// 文字抽出(改行)
		/* ---------------------------------------- */
		}else if(strcmp(tmp_buf, "\n") == 0){

				// 「空白区切り」で文字を追記
				if(space_flg == 1){
					space_flg = 0;

					// wk構造体に一時データを格納、その後tmp_wk_strは初期化
					set_wk_param(cli, tmp_wk_str);
					// sprintf(tmp_wk_str, "");
					memset(tmp_wk_str, 0, sizeof(tmp_wk_str));

				}

				// 「改行区切り」処理の場合は、間に「+」文字を挿入する
				sprintf(tmp_wk_str, "+");
				set_wk_param(cli, tmp_wk_str);

				// 値の初期化
				// sprintf(tmp_wk_str, "");
				memset(tmp_wk_str, 0, sizeof(tmp_wk_str));

		/* ---------------------------------------- */
		// その他の文字抽出
		/* ---------------------------------------- */
		}else{

				// 「空白」「改行」以外の半角文字処理
				space_flg = 1;
				// sprintf(tmp_wk_str, "%s%s", tmp_wk_str, tmp_buf);
			 	strcat(tmp_wk_str, tmp_buf);	

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// wk構造体に一時データを格納
/* ---------------------------------------------------------------------------------------------- */
void set_wk_param(struct MJSClient *cli, char* str){

	sprintf(cli->wk_str[cli->wk_str_count], "%s", str);
	cli->wk_str_count++;

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとの処理確認(メイン処理)
/* ---------------------------------------------------------------------------------------------- */
void chk_mjai_type_main(struct MJSClient *cli, struct MJSPlyInfo *pinfo, char *tmp_snd_mes){

	// ----------------------------------------
	// 変数定義
	// ----------------------------------------
	bool possible_mode = false;

	// ----------------------------------------
	// 受信メッセージの解析
	// ----------------------------------------
	for( int tmp_i = 0; tmp_i < cli->wk_str_count; tmp_i++ ) {

		// ----------------------------------------
		// possible_actionsモード
		// ----------------------------------------
		if( possible_mode == true ){

			// 何もしない

		// ----------------------------------------
		// 通常モード
		// ----------------------------------------
		}else{

			// -----------------------
			// 改行
			// -----------------------
			if(strcmp(cli->wk_str[tmp_i], "+" ) == 0 ){

				// 改行の場合は何もしない

			// -----------------------
			// possible_actionsの有効化
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "possible_actions" ) == 0 ){

				// 初期化
				possible_mode = true;

			// -----------------------
			// HELLOメッセージ
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type" ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "hello" ) == 0 ){

				// type_noneメッセージの設定
				set_snd_none_mes(tmp_snd_mes);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 卓開始
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type" ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "start_game" ) == 0 ){

				// アクション設定
				set_type_startgame(cli, tmp_i);

				// 卓開始処理
				PlyActTakuStart(ply_id);

				// type_noneメッセージの設定
				set_snd_none_mes(tmp_snd_mes);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 局開始
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type" ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "start_kyoku" ) == 0 ){

				// アクション設定
				set_type_startkyoku(cli, tmp_i);

				// type_noneメッセージの設定
				set_snd_none_mes(tmp_snd_mes);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 自摸アクション
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "tsumo" ) == 0 ){

				// アクション設定
				set_type_tsumo(cli, pinfo, tmp_snd_mes, tmp_i);

				// possible_actionsの値を確認するためにbreakで抜けない
				// → メッセージ確定のために処理抜け
				break;

			// -----------------------
			// リーチアクション
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "reach" ) == 0 ){

				// アクション設定：リーチ後の捨牌処理
				set_type_riichi(cli, pinfo, tmp_snd_mes, tmp_i);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 暗槓アクション
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "ankan" ) == 0 ){

				// アクション設定：リーチ後の捨牌処理
				// Set_type_ankan(tk,gui, tmp_i);

				// type_noneメッセージの設定
				set_snd_none_mes(tmp_snd_mes);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 加槓アクション
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "kakan" ) == 0 ){

				// アクション設定：リーチ後の捨牌処理
				// Set_type_kakan(tk,gui, tmp_i);

				// type_noneメッセージの設定
				set_snd_none_mes(tmp_snd_mes);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 捨牌処理
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "dahai" ) == 0 ){

				// アクション設定
				set_type_dahai(cli, pinfo, tmp_snd_mes, tmp_i);

				// possible_actionsの値を確認するためにbreakで抜けない
				// break;

			// -----------------------
			// ポン処理
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "pon" ) == 0 ){

				// アクション設定
				set_type_pon(cli, pinfo, tmp_snd_mes, tmp_i);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// チー処理
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "chi" ) == 0 ){

				// アクション設定
				set_type_chi(cli, pinfo, tmp_snd_mes, tmp_i);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// ミンカン処理
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "daiminkan" ) == 0 ){

				// アクション設定
				// Set_type_minkan(tk,gui, tmp_i);

				// type_noneメッセージの設定
				set_snd_none_mes(tmp_snd_mes);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// リーチ宣言受け入れ
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "reach_accepted" ) == 0 ){

				// アクション設定
				// Set_type_reach_accepted(tk,gui, tmp_i);

				// type_noneメッセージの設定
				set_snd_none_mes(tmp_snd_mes);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 和了確認
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "hora" ) == 0 ){

				// アクション設定
				// Set_type_hora(tk,gui, tmp_i);

				// type_noneメッセージの設定
				set_snd_none_mes(tmp_snd_mes);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 流局
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "ryukyoku" ) == 0 ){

				// アクション設定
				// Set_type_ryukyoku(tk,gui, tmp_i);

				// type_noneメッセージの設定
				set_snd_none_mes(tmp_snd_mes);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 終局
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "end_kyoku" ) == 0 ){

				// アクション設定
				// Set_type_endkyoku(tk, gui, tmp_i);

				// type_noneメッセージの設定
				set_snd_none_mes(tmp_snd_mes);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// 卓終了
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "end_game" ) == 0 ){

				// アクション設定
				// Set_type_endgame(tk, gui, tmp_i);

				// type_noneメッセージの設定
				set_snd_none_mes(tmp_snd_mes);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// エラー処理
			// -----------------------
			}else if(strcmp(cli->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(cli->wk_str[tmp_i+1], "error" ) == 0 ){

				// エラー処理
				// tk->stat = TAKUERR;

				// type_noneメッセージの設定
				set_snd_none_mes(tmp_snd_mes);

				// メッセージ確定のために処理抜け
				break;

			// -----------------------
			// その他のアクション
			// -----------------------
			}else{

				// wk_str_countでforループで回している間は何もしない

			}

			// -----------------------
			// アクション確認はここまで
			// -----------------------

		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 卓ゲーム開始処理
/* ---------------------------------------------------------------------------------------------- */
void set_type_startgame(struct MJSClient *cli, int tmp_wk_num){


	// ----------------------------------------
	// 前処理
	// ----------------------------------------

	// HUMプレーヤーのPly_id設定
	ply_id = atoi(cli->wk_str[tmp_wk_num+3]);

}

/* ---------------------------------------------------------------------------------------------- */
// 局開始処理
/* ---------------------------------------------------------------------------------------------- */
void set_type_startkyoku(struct MJSClient *cli, int tmp_wk_num){

	// ----------------------------------------
	// 前処理
	// ----------------------------------------

	// 初期化
	int  tmp_ply_oya;
	int  tmp_ply_ie;
	int  tmp_kyoku;
	int  tmp_kaze;
	int  tmp_dora_hai;
	bool tmp_dora_aka;

	// 配牌
	int  haipai_point=0;
	int  now_tsumo_hai;
	bool now_tsumo_aka = false;

	// ----------------------------------------
	// 局の算出
	// ----------------------------------------

	// 風
	tmp_kaze = get_hainum(cli->wk_str[tmp_wk_num+3] );

	// 局
/*	tmp_kyoku = get_hainum(cli->wk_str[tmp_wk_num+3] ) - 31 +         // E(東場)かS(南場)の文字列確認
	            atoi(cli->wk_str[tmp_wk_num+5]) - 1;                  // 局情報取得
*/

	// ----------------------------------------
	// 局情報定義
	// ----------------------------------------

	// 本場
	// tk->kyoku[tk->kyoku_index].tsumibo = atoi(cli->wk_str[tmp_wk_num+7]);

	// リーチ棒
	// tk->kyoku[tk->kyoku_index].riichbo = atoi(cli->wk_str[tmp_wk_num+9]);

	// ----------------------------------------
	// ドラ定義
	// ----------------------------------------
/*
	// ドラ表示牌
	tmp_dora_hai = get_hainum(cli->wk_str[tmp_wk_num+13]);

	// 赤牌確認
	if (tmp_dora_hai > 100){
		tmp_dora_hai = tmp_dora_hai - 100;
		tmp_dora_aka = true;
	}else{
		tmp_dora_aka = false;
	}
*/
	// ----------------------------------------
	// 手番設定(親の席番号指定)
	// ----------------------------------------
	tmp_ply_oya = atoi(cli->wk_str[tmp_wk_num+11]);

	// 家算出
	tmp_ply_ie = ( 4 + ply_id - tmp_ply_oya) % 4;

	// 結果表示
/*	printf("================\n");
	printf("tmp_kyoku = %d\n", tmp_kyoku);
	printf("tmp_ply_oya = %d\n", tmp_ply_oya);*/

	// ----------------------------------------
	// pinfo設定(局開始)
	// ----------------------------------------
	PlyActKyokuStart(tmp_kaze, tmp_ply_ie);

	// ----------------------------------------
	// 配牌設定
	// ----------------------------------------
	// 配牌ポインター設定
	haipai_point=tmp_wk_num + 15 + TEHAI_MAX * ply_id;

	// 配牌設定
	for(int tmp_i=0; tmp_i < TEHAI_MAX; tmp_i++){

		// 配牌確認
		now_tsumo_hai = get_hainum(cli->wk_str[haipai_point+tmp_i]);

		// 赤牌確認
		if (now_tsumo_hai > 100){
			now_tsumo_hai = now_tsumo_hai - 100;
			now_tsumo_aka = true;
		}else{
			now_tsumo_aka = false;
		}

		// plyクラス配牌
		PlyActHaipai(now_tsumo_hai, now_tsumo_aka);

	}

	// ----------------------------------------
	// 配牌後処理
	// ----------------------------------------

	// 配牌後の確認処理
	PlyActPostHaipai();

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(tsumo)
/* ---------------------------------------------------------------------------------------------- */
void set_type_tsumo(struct MJSClient *cli, struct MJSPlyInfo *pinfo, char *tmp_snd_mes, int tmp_wk_num){

	// アクション定義
	// https://gimite.net/pukiwiki/index.php?Mjai%20%E9%BA%BB%E9%9B%80AI%E5%AF%BE%E6%88%A6%E3%82%B5%E3%83%BC%E3%83%90

	// 初期化
	int tmp_ply_id;

	// 手番設定
	tmp_ply_id = atoi(cli->wk_str[tmp_wk_num+3]);

	// ----------------------------------------
	// 自摸プレーヤが自分ならば
	// ----------------------------------------
	if( ply_id == tmp_ply_id ){

		// ----------------------------------------
		// 牌情報設定
		// ----------------------------------------

		// 自摸牌確認
		cli_tsumo_hai = get_hainum(cli->wk_str[tmp_wk_num+5]);

		// 赤牌確認
		if (cli_tsumo_hai > 100){
			cli_tsumo_hai = cli_tsumo_hai  - 100;
			cli_tsumo_aka = true;
		}else{
			cli_tsumo_aka = false;
		}

		// ----------------------------------------
		// ply関数処理
		// ----------------------------------------
		PlyActTsumo(pinfo, cli_tsumo_hai, cli_tsumo_aka);

		// ----------------------------------------
		// pinfo結果表示
		// ----------------------------------------
		print_pinfo_act(pinfo);

		// ----------------------------------------
		// メッセージ定義
		// ----------------------------------------
		set_tsumo_act_mes(pinfo, tmp_snd_mes);

		// ----------------------------------------
		// ply関数処理(自摸後アクション)
		// ----------------------------------------
		set_post_tsumo_act(pinfo);

	// ----------------------------------------
	// 自摸プレーヤがCOMならば
	// ----------------------------------------
	}else{

		// type_noneメッセージの設定
		set_snd_none_mes(tmp_snd_mes);

	}
}

/* ---------------------------------------------------------------------------------------------- */
// 自摸後アクション(ply関数向け)
/* ---------------------------------------------------------------------------------------------- */
void set_post_tsumo_act(struct MJSPlyInfo *pinfo){

		// 暗槓
		if(pinfo->ply_act == ACTANKAN){
			PlyActAnkan(pinfo->act_idx);
		// 加槓
		}else if(pinfo->ply_act == ACTKAKAN){
			PlyActKakan(pinfo->act_idx, pinfo->act_aka_count);
		// 捨牌
		}else if(pinfo->ply_act == ACTSUTE){
			PlyActTsumoSute();
		// 自摸切り
		}else if(pinfo->ply_act == ACTTSUMOGIRI){
			PlyActTsumoSute();
		}

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(riichi)
/* ---------------------------------------------------------------------------------------------- */
void set_type_riichi(struct MJSClient *cli, struct MJSPlyInfo *pinfo, char *tmp_snd_mes, int tmp_wk_num){

	// 初期化
	int tmp_ply_id;

	// 手番設定
	tmp_ply_id = atoi(cli->wk_str[tmp_wk_num+3]);

	// ----------------------------------------
	// 自摸プレーヤが自分ならば
	// ----------------------------------------
	if( ply_id == tmp_ply_id ){

		// ----------------------------------------
		// ply関数処理
		// ----------------------------------------
		PlyActTsumo(pinfo, cli_tsumo_hai, cli_tsumo_aka);

		// ----------------------------------------
		// pinfo結果表示
		// ----------------------------------------
		print_pinfo_act(pinfo);

		// ----------------------------------------
		// メッセージ定義
		// ----------------------------------------
		set_tsumo_act_mes(pinfo, tmp_snd_mes);

		// ----------------------------------------
		// ply関数処理(自摸後アクション)
		// ----------------------------------------

		// 捨牌
		if(pinfo->ply_act == ACTSUTE){
			PlyActTsumoSute();
		// 自摸切り
		}else if(pinfo->ply_act == ACTTSUMOGIRI){
			PlyActTsumoSute();
		}

	// ----------------------------------------
	// 自摸プレーヤがCOMならば
	// ----------------------------------------
	}else{

		// type_noneメッセージの設定
		set_snd_none_mes(tmp_snd_mes);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(dahai)
/* ---------------------------------------------------------------------------------------------- */
void set_type_dahai(struct MJSClient *cli, struct MJSPlyInfo *pinfo, char *tmp_snd_mes, int tmp_wk_num){

	// 初期化
	int tmp_ply_sute_id;

	// 手番設定
	tmp_ply_sute_id = atoi(cli->wk_str[tmp_wk_num+3]);

	// ----------------------------------------
	// 自摸プレーヤが自分ならば
	// ----------------------------------------
	if( ply_id == tmp_ply_sute_id ){

		// メッセージ定義：処理なし
		set_snd_none_mes(tmp_snd_mes);

	// ----------------------------------------
	// 自摸プレーヤがCOMならば
	// ----------------------------------------
	}else{

		// ----------------------------------------
		// 牌情報設定
		// ----------------------------------------

		// 自摸牌確認
		cli_sute_hai = get_hainum(cli->wk_str[tmp_wk_num+5]);

		// 赤牌確認
		if (cli_sute_hai > 100){
			cli_sute_hai = cli_sute_hai  - 100;
			cli_sute_aka = true;
		}else{
			cli_sute_aka = false;
		}

		// ----------------------------------------
		// ply関数処理(鳴き確認)
		// ----------------------------------------
		PlyChkNaki(pinfo, tmp_ply_sute_id, cli_sute_hai);

		// ----------------------------------------
		// pinfo結果表示
		// ----------------------------------------
		print_pinfo_act(pinfo);

		// ----------------------------------------
		// メッセージ定義：鳴き確認(捨牌確認)
		// ----------------------------------------
		set_naki_act_mes(pinfo, tmp_snd_mes, tmp_ply_sute_id);

	}
}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(pon)
/* ---------------------------------------------------------------------------------------------- */
void set_type_pon(struct MJSClient *cli, struct MJSPlyInfo *pinfo, char *tmp_snd_mes, int tmp_wk_num){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------

	int tmp_naki_ply_id;
	// int tmp_target_ply_id;

	int  tmp_naki_hai  = 0;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// REACTプレーヤー(targetプレーヤー)の特定
	// ----------------------------------------

	// プレーヤーID確認
	tmp_naki_ply_id  = atoi(cli->wk_str[tmp_wk_num+3]);
	// tmp_target_ply_id = atoi(cli->wk_str[tmp_wk_num+5]);

	// ----------------------------------------
	// 鳴きプレーヤが自分ならば
	// ----------------------------------------
	if( ply_id == tmp_naki_ply_id ){

		// ----------------------------------------
		// ポン牌確認(捨牌)
		// ----------------------------------------

		// 手牌読込
		tmp_naki_hai = get_hainum(cli->wk_str[tmp_wk_num+7]);
		// 赤牌確認
		if (tmp_naki_hai > 100){
			tmp_naki_hai = tmp_naki_hai - 100;
			tmp_aka_count++;
		}

		// ----------------------------------------
		// 手牌確認(1枚目)
		// ----------------------------------------

		// 手牌読込
		tmp_naki_hai = get_hainum(cli->wk_str[tmp_wk_num+9]);
		// 赤牌確認
		if (tmp_naki_hai > 100){
			tmp_naki_hai = tmp_naki_hai - 100;
			tmp_aka_count++;
		}

		// ----------------------------------------
		// 手牌確認(2枚目)
		// ----------------------------------------

		// 手牌読込
		tmp_naki_hai = get_hainum(cli->wk_str[tmp_wk_num+10]);
		// 赤牌確認
		if (tmp_naki_hai > 100){
			tmp_naki_hai = tmp_naki_hai - 100;
			tmp_aka_count++;
		}

		// ----------------------------------------
		// ply関数処理(ポン処理)
		// ----------------------------------------

		// 鳴きアクション処理
		PlyActNaki( pinfo,                        // 捨て牌アクション定義
	                tmp_naki_ply_id,              // 鳴きプレーヤ
	                ACTPON,                       // 鳴きアクション種別
	                tmp_naki_hai,                 // 鳴き牌
	                tmp_naki_hai,                 // 鳴き面子(チー面子)の頭牌
	                tmp_aka_count);               // 鳴き面子の赤牌枚数

		// ----------------------------------------
		// pinfo結果表示
		// ----------------------------------------
		print_pinfo_act(pinfo);

		// ----------------------------------------
		// 鳴き捨牌アクション
		// ----------------------------------------
		PlyActNakiSute();

		// ----------------------------------------
		// 捨牌メッセージの定義
		// ----------------------------------------

		// メッセージ定義：鳴き捨牌
		if( pinfo->act_aka_count > 0){
			set_snd_dahai_mes(tmp_snd_mes, pinfo->act_hai, true, false); 
		}else{
			set_snd_dahai_mes(tmp_snd_mes, pinfo->act_hai, false, false); 
		}

	// ----------------------------------------
	// 自摸プレーヤがCOMならば
	// ----------------------------------------
	}else{

		// メッセージ定義：処理なし
		set_snd_none_mes(tmp_snd_mes);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// typeごとでの値設定(chi)
/* ---------------------------------------------------------------------------------------------- */
void set_type_chi(struct MJSClient *cli, struct MJSPlyInfo *pinfo, char *tmp_snd_mes, int tmp_wk_num){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------

	int tmp_naki_ply_id;
	// int tmp_target_ply_id;

	int  tmp_naki_hai = 0;
	// bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	int tmp_naki_tehai_hai1 = 0;
	int tmp_naki_tehai_hai2 = 0;
	int tmp_hai = 0;
	int tmp_chi_idx = 0;

	// ----------------------------------------
	// REACTプレーヤー(targetプレーヤー)の特定
	// ----------------------------------------

	// プレーヤーID確認
	tmp_naki_ply_id  = atoi(cli->wk_str[tmp_wk_num+3]);
	// tmp_target_ply_id = atoi(cli->wk_str[tmp_wk_num+5]);

	// ----------------------------------------
	// 鳴きプレーヤが自分ならば
	// ----------------------------------------
	if( ply_id == tmp_naki_ply_id ){

		// ----------------------------------------
		// チー牌確認(捨牌)
		// ----------------------------------------
		tmp_naki_hai = get_hainum(cli->wk_str[tmp_wk_num+7]);
		if (tmp_naki_hai > 100){
			tmp_naki_hai = tmp_naki_hai - 100;
			// tmp_naki_aka = true ;
			tmp_aka_count++;
		}

		// ----------------------------------------
		// チー構成牌(1枚目)
		// ----------------------------------------
		tmp_naki_tehai_hai1 = get_hainum(cli->wk_str[tmp_wk_num+9]);
		if (tmp_naki_tehai_hai1 > 100){
			tmp_naki_tehai_hai1 = tmp_naki_tehai_hai1 - 100;
			tmp_aka_count++;
		}

		// ----------------------------------------
		// チー構成牌(2枚目)
		// ----------------------------------------
		tmp_naki_tehai_hai2 = get_hainum(cli->wk_str[tmp_wk_num+10]);
		if (tmp_naki_tehai_hai2 > 100){
			tmp_naki_tehai_hai2 = tmp_naki_tehai_hai2 - 100;
			tmp_aka_count++;
		}

		// ----------------------------------------
		// チーINDEX牌算出
		// ----------------------------------------

		// 1枚目2枚目の大小比較・交換
		if(tmp_naki_tehai_hai1 > tmp_naki_tehai_hai2){
			tmp_hai = tmp_naki_tehai_hai1;
			tmp_naki_tehai_hai1 = tmp_naki_tehai_hai2;
			tmp_naki_tehai_hai2 = tmp_hai;
		}

		// チーINDEX牌を算出
		if (tmp_naki_tehai_hai1 == tmp_naki_hai - 2 ){
			tmp_chi_idx = tmp_naki_tehai_hai1;
		}else if (tmp_naki_tehai_hai1 == tmp_naki_hai - 1 ){
			tmp_chi_idx = tmp_naki_tehai_hai1;
		}else if (tmp_naki_tehai_hai1 == tmp_naki_hai + 1 ){
			tmp_chi_idx = tmp_naki_hai;
		}else {
			tmp_chi_idx = 0;
		}

		// ----------------------------------------
		// ply関数処理(チー処理)
		// ----------------------------------------

		// 鳴きアクション処理
		PlyActNaki( pinfo,                        // 捨て牌アクション定義
	                tmp_naki_ply_id,              // 鳴きプレーヤ
	                ACTCHI,                       // 鳴きアクション種別
	                tmp_naki_hai,                 // 鳴き牌
	                tmp_chi_idx,                  // 鳴き面子(チー面子)の頭牌
	                tmp_aka_count);               // 鳴き面子の赤牌枚数

		// ----------------------------------------
		// pinfo結果表示
		// ----------------------------------------
		print_pinfo_act(pinfo);

		// ----------------------------------------
		// 鳴き捨牌アクション
		// ----------------------------------------
		PlyActNakiSute();

		// ----------------------------------------
		// 捨牌メッセージの定義
		// ----------------------------------------

		// メッセージ定義：鳴き捨牌
		if( pinfo->act_aka_count > 0){
			set_snd_dahai_mes(tmp_snd_mes, pinfo->act_hai, true, false); 
		}else{
			set_snd_dahai_mes(tmp_snd_mes, pinfo->act_hai, false, false); 
		}

	// ----------------------------------------
	// 自摸プレーヤがCOMならば
	// ----------------------------------------
	}else{

		// メッセージ定義：処理なし
		set_snd_none_mes(tmp_snd_mes);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// メッセージ定義(メイン処理：自摸時)
/* ---------------------------------------------------------------------------------------------- */
void set_tsumo_act_mes(struct MJSPlyInfo *pinfo, char *tmp_snd_mes){

	// ----------------------------------------
	// 赤定義
	// ----------------------------------------
	bool tmp_aka_flg;

	// ----------------------------------------
	// 自摸和了
	// ----------------------------------------
	if(pinfo->ply_act == ACTTSUMOAGARI){

		if(pinfo->act_aka_count > 0){
			tmp_aka_flg = true;
		}else{
			tmp_aka_flg = false;
		}

		// メッセージ定義：自摸和了
		set_snd_hora_mes(tmp_snd_mes, ply_id, pinfo->act_hai, tmp_aka_flg); 

	// ----------------------------------------
	// 捨牌
	// ----------------------------------------
	}else if(pinfo->ply_act == ACTSUTE){

		if(pinfo->act_aka_count > 0){
			tmp_aka_flg = true;
		}else{
			tmp_aka_flg = false;
		}

		// メッセージ定義：捨牌
		set_snd_dahai_mes(tmp_snd_mes, pinfo->act_hai, tmp_aka_flg, false); 

	// ----------------------------------------
	// 自摸切り
	// ----------------------------------------
	}else if(pinfo->ply_act == ACTTSUMOGIRI){

		if(pinfo->act_aka_count > 0){
			tmp_aka_flg = true;
		}else{
			tmp_aka_flg = false;
		}

		// メッセージ定義：自摸切り
		// set_snd_dahai_mes(tmp_snd_mes, pinfo->act_hai, tmp_aka_flg, true); 
		set_snd_dahai_mes(tmp_snd_mes, cli_tsumo_hai, cli_tsumo_aka, true); 

	// ----------------------------------------
	// リーチアクション
	// ----------------------------------------
	}else if(pinfo->ply_act == ACTRIICH){

		// メッセージ定義：リーチ宣言
		set_snd_riichi_mes(tmp_snd_mes);

	// ----------------------------------------
	// 暗槓アクション
	// ----------------------------------------
	}else if(pinfo->ply_act == ACTANKAN){

		// メッセージ定義：暗槓
		set_snd_ankan_mes(tmp_snd_mes, pinfo->act_idx, pinfo->act_aka_count);

	// ----------------------------------------
	// 加槓アクション
	// ----------------------------------------
	}else if(pinfo->ply_act == ACTKAKAN){

		// メッセージ定義：加槓
		if(pinfo->act_aka_count > 0){
			set_snd_kakan_mes(tmp_snd_mes, pinfo->act_idx, true, 0);
		}else{
			set_snd_kakan_mes(tmp_snd_mes, pinfo->act_idx, false, 1);
		}

	// ----------------------------------------
	// 例外処理
	// ----------------------------------------
	}else{

		// メッセージ定義：処理なし
		set_snd_none_mes(tmp_snd_mes);

	}
}

/* ---------------------------------------------------------------------------------------------- */
// メッセージ定義(メイン処理：鳴き確認時)
/* ---------------------------------------------------------------------------------------------- */
void set_naki_act_mes(struct MJSPlyInfo *pinfo, char *tmp_snd_mes, int tmp_ply_sute_id){

	// ----------------------------------------
	// 自摸和了
	// ----------------------------------------
	if(pinfo->ply_act == ACTRON){

		// ロン和了
		set_snd_hora_mes(tmp_snd_mes, tmp_ply_sute_id, cli_sute_hai, cli_sute_aka);

	// ----------------------------------------
	// 例外処理
	// ----------------------------------------
	}else if(pinfo->ply_act == ACTPON){

		// ポン
		set_snd_pon_mes(tmp_snd_mes, tmp_ply_sute_id, cli_sute_hai, cli_sute_aka, pinfo->act_aka_count);

	// ----------------------------------------
	// 例外処理
	// ----------------------------------------
	}else if(pinfo->ply_act == ACTCHI){

		// チー
		set_snd_chi_mes(tmp_snd_mes, tmp_ply_sute_id, cli_sute_hai, cli_sute_aka, pinfo->act_idx, pinfo->act_aka_count);

	// ----------------------------------------
	// 例外処理
	// ----------------------------------------
	}else{

		// 何もしない
		set_snd_none_mes(tmp_snd_mes);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 捨牌(打牌)メッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void set_snd_dahai_mes(char *tmp_snd_mes, int hai, bool aka_flg, bool tsumogiri_flg){

	// 変数定義
	char tmp_hai_chr[5];

	// Mes取得準備：文字取得
	Get_haichr(hai, aka_flg, tmp_hai_chr);

	// バッファクリア
	memset(tmp_snd_mes, 0, sizeof(*tmp_snd_mes));

	// sendメッセージ設定
	if( tsumogiri_flg == true ){
		// アクション：自摸切り
		sprintf(tmp_snd_mes, "{\"type\":\"dahai\",\"actor\":%d,\"pai\":\"%s\",\"tsumogiri\":true}\n", ply_id, tmp_hai_chr);
	}else{
		// アクション：捨牌処理
		sprintf(tmp_snd_mes, "{\"type\":\"dahai\",\"actor\":%d,\"pai\":\"%s\",\"tsumogiri\":false}\n", ply_id, tmp_hai_chr);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// リーチメッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void set_snd_riichi_mes(char *tmp_snd_mes){

	// バッファクリア
	memset(tmp_snd_mes, 0, sizeof(*tmp_snd_mes));

	// sendメッセージ設定
	sprintf(tmp_snd_mes, "{\"type\":\"reach\",\"actor\":%d}\n", ply_id);

}

/* ---------------------------------------------------------------------------------------------- */
// 暗槓メッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void set_snd_ankan_mes(char *tmp_snd_mes, int ankan_hai, int tehai_aka_count){

	// 変数定義
	char tmp_ankan_hai_chr[5];

	// Mes取得準備：文字取得(鳴き牌)
	Get_haichr(ankan_hai, false, tmp_ankan_hai_chr);

	// sendメッセージ設定
	if( tehai_aka_count == 0 ){
		// 赤牌なし
		sprintf(tmp_snd_mes, "{\"type\":\"ankan\",\"actor\":%d,\"consumed\":[\"%s\",\"%s\",\"%s\",\"%s\"]}\n",     ply_id, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr);
	}else if( tehai_aka_count == 1 ){
		// 赤牌1枚
		sprintf(tmp_snd_mes, "{\"type\":\"ankan\",\"actor\":%d,\"consumed\":[\"%s\",\"%s\",\"%s\",\"%sr\"]}\n",    ply_id, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr);
	}else if( tehai_aka_count == 2 ){
		// 赤牌2枚
		sprintf(tmp_snd_mes, "{\"type\":\"ankan\",\"actor\":%d,\"consumed\":[\"%s\",\"%s\",\"%sr\",\"%sr\"]}\n",   ply_id, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr);
	}else if( tehai_aka_count == 3 ){
		// 赤牌3枚
		sprintf(tmp_snd_mes, "{\"type\":\"ankan\",\"actor\":%d,\"consumed\":[\"%s\",\"%sr\",\"%sr\",\"%sr\"]}\n",  ply_id, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr);
	}else if( tehai_aka_count == 4 ){
		// 赤牌4枚
		sprintf(tmp_snd_mes, "{\"type\":\"ankan\",\"actor\":%d,\"consumed\":[\"%sr\",\"%sr\",\"%sr\",\"%sr\"]}\n", ply_id, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 加槓メッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void set_snd_kakan_mes(char *tmp_snd_mes, int nakl_hai_num, bool naki_aka, int tehai_aka_count){

	// 変数定義
	char tmp_kakan_hai_chr[5];

	// Mes取得準備：文字取得(鳴き牌)
	Get_haichr(nakl_hai_num, false, tmp_kakan_hai_chr);

	// sendメッセージ設定
	if( naki_aka == true ){

		// Act牌が赤牌
		if( tehai_aka_count == 0 ){
			// 赤牌なし
			sprintf(tmp_snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%sr\",\"consumed\":[\"%s\",\"%s\",\"%s\"]}\n",    ply_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 1 ){
			// 赤牌3枚
			sprintf(tmp_snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%sr\",\"consumed\":[\"%s\",\"%s\",\"%sr\"]}\n",   ply_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 2 ){
			// 赤牌3枚
			sprintf(tmp_snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%sr\",\"consumed\":[\"%s\",\"%sr\",\"%sr\"]}\n",  ply_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 3 ){
			// 赤牌3枚
			sprintf(tmp_snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%sr\",\"consumed\":[\"%sr\",\"%sr\",\"%sr\"]}\n", ply_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}

	}else{

		// Act牌が黒牌
		if( tehai_aka_count == 0 ){
			// 赤牌なし
			sprintf(tmp_snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%s\",\"%s\"]}\n",     ply_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 1 ){
			// 赤牌3枚
			sprintf(tmp_snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%s\",\"%sr\"]}\n",    ply_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 2 ){
			// 赤牌3枚
			sprintf(tmp_snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%sr\",\"%sr\"]}\n",   ply_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 3 ){
			// 赤牌3枚
			sprintf(tmp_snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%s\",\"consumed\":[\"%sr\",\"%sr\",\"%sr\"]}\n",  ply_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ポンメッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void set_snd_pon_mes(char *tmp_snd_mes, int ply_target, int nakl_hai, bool nakl_aka, int tehai_aka_count){

	// 変数定義
	char tmp_naki_hai_chr[5];
	char tmp_tehai_chr[5];

	// Mes取得準備：文字取得(鳴き牌)
	Get_haichr(nakl_hai, nakl_aka, tmp_naki_hai_chr);

	// Mes取得準備：文字取得(手牌)
	Get_haichr(nakl_hai, false, tmp_tehai_chr);

	// sendメッセージ設定
	if( tehai_aka_count == 0 ){
		// 赤牌なし
		sprintf(tmp_snd_mes, "{\"type\":\"pon\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%s\"]}\n",   ply_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}else if( tehai_aka_count == 1 ){
		// 赤牌1枚
		sprintf(tmp_snd_mes, "{\"type\":\"pon\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%sr\"]}\n",  ply_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}else if( tehai_aka_count == 2 ){
		// 赤牌2枚
		sprintf(tmp_snd_mes, "{\"type\":\"pon\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%sr\",\"%sr\"]}\n", ply_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// チーメッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void set_snd_chi_mes(char *tmp_snd_mes, int ply_target, int nakl_hai, bool nakl_aka, int naki_idx, int tehai_aka_count){

	// 変数定義
	char tmp_hai_chr[5];
	int tmp_chi_count = 0;

	// Mes取得準備：文字取得(鳴き牌)
	Get_haichr(nakl_hai, nakl_aka, tmp_hai_chr);

	// メッセージ設定(ヘッダー)
	sprintf(tmp_snd_mes, "{\"type\":\"chi\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[", ply_id, ply_target, tmp_hai_chr);

	// チー牌設定
	for(int tmp_i=0; tmp_i < 3; tmp_i++){

		// 鳴き牌でないなら
		if( nakl_hai != naki_idx + tmp_i ){
			// チーの仮枚数
			tmp_chi_count++;
			// Mes取得準備：文字取得(赤牌確認)
			if(( naki_idx + tmp_i == 5 || naki_idx + tmp_i == 15 || naki_idx + tmp_i == 25) && (tehai_aka_count > 0)){
				Get_haichr(naki_idx + tmp_i, true, tmp_hai_chr);
			}else{
				Get_haichr(naki_idx + tmp_i, false, tmp_hai_chr);
			}
			// 鳴きメッセージ作成
			sprintf(tmp_snd_mes, "%s\"%s\"", tmp_snd_mes, tmp_hai_chr);
			// 最後でないなら、カンマ追加
			if(tmp_chi_count != 2){
				sprintf(tmp_snd_mes, "%s,", tmp_snd_mes);
			}
		}
	}

	// メッセージ設定(フッター)
	sprintf(tmp_snd_mes, "%s]}\n", tmp_snd_mes);

}

/* ---------------------------------------------------------------------------------------------- */
// 和了(ロン・ツモ)メッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void set_snd_hora_mes(char *tmp_snd_mes, int ply_target, int agari_hai, bool agari_aka){

	// 変数定義
	char tmp_hai_chr[5];

	// Mes取得準備：文字取得
	Get_haichr(agari_hai, agari_aka, tmp_hai_chr);

	// バッファクリア
	memset(tmp_snd_mes, 0, sizeof(*tmp_snd_mes));

	// sendメッセージ設定
	sprintf(tmp_snd_mes, "{\"type\":\"hora\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\"}\n", ply_id, ply_target, tmp_hai_chr);

}

/* ---------------------------------------------------------------------------------------------- */
// 処理なしメッセージ定義
/* ---------------------------------------------------------------------------------------------- */
void set_snd_none_mes(char *tmp_snd_mes){

	// バッファクリア
	memset(tmp_snd_mes, 0, sizeof(*tmp_snd_mes));

	// sendメッセージ設定
	sprintf(tmp_snd_mes, "{\"type\":\"none\"}\n");

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：pinfoアクション
/* ---------------------------------------------------------------------------------------------- */
void print_pinfo_act(struct MJSPlyInfo *pinfo){

	// アクション表示
	printf("================\n");
	if(pinfo->ply_act == ACTTSUMOAGARI){
		printf("アクション：自摸和了\n");
	}else if(pinfo->ply_act == ACTSUTE){
		printf("アクション：捨牌　　\n");
	}else if(pinfo->ply_act == ACTTSUMOGIRI){
		printf("アクション：自摸切り\n");
	}else if(pinfo->ply_act == ACTNAKISUTE){
		printf("アクション：鳴き捨牌\n");
	}else if(pinfo->ply_act == ACTRIICH){
		printf("アクション：リーチ　\n");
	}else if(pinfo->ply_act == ACTANKAN){
		printf("アクション：暗槓　　\n");
	}else if(pinfo->ply_act == ACTKAKAN){
		printf("アクション：加槓　　\n");
	}else if(pinfo->ply_act == ACTNONAKI){
		printf("アクション：鳴き無し\n");
	}else if(pinfo->ply_act == ACTRON){
		printf("アクション：ロン和了\n");
	}else if(pinfo->ply_act == ACTPON){
		printf("アクション：ポン\n");
	}else if(pinfo->ply_act == ACTCHI){
		printf("アクション：チー\n");
	}else{
		printf("アクション：不明　　\n");
	}

	// 牌情報
	printf("pinfo->act_hai = %d\n", pinfo->act_hai);
	printf("pinfo->act_idx = %d\n", pinfo->act_idx);
	printf("pinfo->act_aka_count = %d\n", pinfo->act_aka_count);

}

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
