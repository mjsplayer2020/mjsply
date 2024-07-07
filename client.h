/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： 麻雀AI：MJSakuraモジュール
 * バージョン     ： 0.0.1.0.15(相手プレーヤの捨牌実装)
 * プログラム名   ： mjs
 * ファイル名     ： client.h
 * クラス名       ： MJSMjaiClient構造体
 * 処理概要       ： クライアント構造体
 * Ver0.0.1作成日 ： 2024/06/01 16:03:43
 * 最終更新日     ： 2024/07/07 15:53:02
 * 
 * Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include "player.h"

/* ---------------------------------------------------------------------------------------------- */
// 変数定義
/* ---------------------------------------------------------------------------------------------- */

	// 手牌情報
	static int  cli_ply_id;          // プレーヤ番号
	static int  cli_tsumo_hai;       // 自摸牌
	static bool cli_tsumo_aka;       // 自摸赤
	static int  cli_sute_hai;        // 捨牌
	static bool cli_sute_aka;        // 捨牌赤

	// 赤牌情報
	static int cli_max_aka_count[AKA_SHUBETSU_MAX];     // 最大赤牌枚数


// 構造体定義
struct MJSClient{

	// MJAIメッセージ解析用バッファ
	int  wk_str_count;        // 作業用文字配列の総数
	char wk_str[128][64];     // 作業用文字配列

};

/* ---------------------------------------------------------------------------------------------- */
// 関数定義
/* ---------------------------------------------------------------------------------------------- */

	// -----------------------------
	// クライアントクラス初期化・終了処理
	// -----------------------------
	void mjs_client_init();        // Mjaiクライアントの処理開始
	void mjs_client_post();        // Mjaiクライアントの処理終了

	// -----------------------------
	// メイン処理
	// -----------------------------

	// メイン関数
	void set_ply_id(int tmp_ply_id);
	void set_taku_stat_main(char* tmp_res_mes, char* tmp_snd_mes);

	// JSON解析
	void read_logline(struct MJSClient *cli, char *line_buf);
	void set_wk_param(struct MJSClient *cli, char* str);

	// -----------------------------
	// typeごとの処理確認
	// -----------------------------

	// typeごとの処理確認(メイン処理)
	void chk_mjai_type_main(struct MJSClient *cli, struct MJSPlyInfo *pinfo, char *tmp_snd_mes);

	// typeごとの処理確認(サブ処理)
	void set_type_hello(struct MJSClient *cli, int tmp_wk_num);                                                   // helloメッセージ確認
	void set_type_startgame(struct MJSClient *cli, int tmp_wk_num);                                               // 卓ゲーム開始処理
	void set_type_startkyoku(struct MJSClient *cli, int tmp_wk_num);                                              // 局開始処理
	void set_type_tsumo(struct MJSClient *cli, struct MJSPlyInfo *pinfo, char *tmp_snd_mes, int tmp_wk_num);      // 自摸時処理
	void set_type_riichi(struct MJSClient *cli, struct MJSPlyInfo *pinfo, char *tmp_snd_mes, int tmp_wk_num);     // リーチ時処理
	void set_type_dahai(struct MJSClient *cli, struct MJSPlyInfo *pinfo, char *tmp_snd_mes, int tmp_wk_num);      // 捨牌時処理
	void set_type_pon(struct MJSClient *cli, struct MJSPlyInfo *pinfo, char *tmp_snd_mes, int tmp_wk_num);        // ポン処理
	void set_type_chi(struct MJSClient *cli, struct MJSPlyInfo *pinfo, char *tmp_snd_mes, int tmp_wk_num);        // チー処理

	// 自摸後アクション(ply関数向け)
	void set_post_tsumo_act(struct MJSPlyInfo *pinfo);

	// -----------------------------
	// メッセージ定義
	// -----------------------------

	// メッセージ定義(メイン処理)
	void set_tsumo_act_mes(struct MJSPlyInfo *pinfo, char *tmp_snd_mes);                                                          // 自摸時メッセージ定義(メイン)
	void set_naki_act_mes(struct MJSPlyInfo *pinfo, char *tmp_snd_mes, int tmp_sute_ply_id);                                      // 鳴き確認時メッセージ定義(メイン)

	// メッセージ定義(サブ処理)
	void set_snd_joinmes(char *tmp_snd_mes);                                                                                      // ジョインメッセージ
	void set_snd_dahai_mes(char *tmp_snd_mes, int hai, bool aka_flg, bool tsumogiri_flg);                                         // 捨牌メッセージ
	void set_snd_riichi_mes(char *tmp_snd_mes);                                                                                   // リーチメッセージ
	void set_snd_ankan_mes(char *tmp_snd_mes, int ankan_hai, int tehai_aka_count);                                                // 暗槓メッセージ
	void set_snd_kakan_mes(char *tmp_snd_mes, int nakl_hai_num, bool naki_aka, int tehai_aka_count);                              // 加槓メッセージ
	void set_snd_pon_mes(char *tmp_snd_mes, int ply_target, int nakl_hai, bool nakl_aka, int tehai_aka_count);                    // ポンメッセージ
	void set_snd_chi_mes(char *tmp_snd_mes, int ply_target, int nakl_hai, bool nakl_aka, int naki_idx, int tehai_aka_count);      // チーメッセージ
	void set_snd_minkan_mes(char *tmp_snd_mes, int ply_target, int nakl_hai, bool nakl_aka, int tehai_aka_count);                 // 明槓メッセージ
	void set_snd_hora_mes(char *tmp_snd_mes, int ply_target, int agari_hai, bool agari_aka);                                      // 和了(ロン・ツモ)メッセージ                                                                                                  // 無効メッセージ
	void set_snd_none_mes(char *tmp_snd_mes);                                                                                     // noneメッセージ

	// -----------------------------
	// サブ関数
	// -----------------------------
	int  get_hainum(char hai_str[]);                                  // 牌番号取得
	void Get_haichr(int hai_num, bool hai_aka, char hai_str[]);       // Mjai向け牌文字取得

#endif /* CLIENT_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */

