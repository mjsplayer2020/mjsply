/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： mjsply：Mjaiクライアント
 * バージョン     ： 1.0.0.0.0(アーカイブFix版)
 * プログラム名   ： mjs
 * ファイル名     ： player.h
 * クラス名       ： MJSPlayerクラス
 * 処理概要       ： プレーヤークラス
 * Ver0.0.1作成日 ： 2024/06/01 16:03:43
 * Ver0.0.2作成日 ： 2025/01/02 15:34:38
 * Ver1.0.0作成日 ： 2026/09/23 13:38:14
 * 最終更新日     ： 2026/09/23 13:38:14
 * 
 * Copyright (c) 2010-2026 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#ifndef PLY_H_INCLUDED
#define PLY_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "score.h"

/* ---------------------------------------------------------------------------------------------- */
// 固定値
/* ---------------------------------------------------------------------------------------------- */

#define ERR_MES_MAX_SIZE      1024      // バッファサイズ
#define KARITBL_MAX_COUNT     8192      // 仮テーブルの最大値

/* ---------------------------------------------------------------------------------------------- */
// ラベル(各モード)
/* ---------------------------------------------------------------------------------------------- */

// プレーヤーキャラクター
typedef enum {

	PLYCHAR_NONAME = 0,                 // 00:プレーヤー状態なし
	PLYCHAR_TAMPOPO,                    // 01:プレーヤーキャラクター1
	PLYCHAR_HIMAWARI,                   // 02:プレーヤーキャラクター2
	PLYCHAR_HITOHA,                     // 03:プレーヤーキャラクター3
	PLYCHAR_FATABA,                     // 04:プレーヤーキャラクター4
	PLYCHAR_WAKABA,                     // 05:プレーヤーキャラクター5
	PLYCHAR_SHINBA,                     // 06:プレーヤーキャラクター6
	PLYCHAR_AOBA,                       // 07:プレーヤーキャラクター7
	PLYCHAR_AYAME,                      // 08:プレーヤーキャラクター8
	PLYCHAR_TSUBAKI,                    // 09:プレーヤーキャラクター9
	PLYCHAR_NADESHIKO,                  // 10:プレーヤーキャラクター10
	PLYCHAR_TSUBOMI,                    // 11:プレーヤーキャラクター11
	PLYCHAR_MOMIJI,                     // 12:プレーヤーキャラクター12
	PLYCHAR_KAREHA,                     // 13:プレーヤーキャラクター13
	PLYCHAR_OCHIBA,                     // 14:プレーヤーキャラクター14
	PLYCHAR_SAKURA,                     // 15:プレーヤーサクラ
	PLYCHAR_MJSPLY_TEST,                // 16:テスト用キャラクター

} LBPlyChar;

// プレーヤー手牌モード
typedef enum {

	PLY_TEHAI_NO_MODE = 0,              // 00:状態なし
	PLY_TEHAI_NORMAL,                   // 01:通常状態
	PLY_TEHAI_NAKI_WAIT,                // 02:鳴き待ち
	PLY_TEHAI_RIICHI_SUTEHAI,           // 03:リーチ時の捨牌選択
	PLY_TEHAI_RIICHI_YUKO,              // 04:リーチ有効状態

} LBPlyTehaiMode;

/* ---------------------------------------------------------------------------------------------- */
// static変数定義
/* ---------------------------------------------------------------------------------------------- */

	// -----------------------------
	// 役情報定義
	// -----------------------------

	// 役情報受け渡し構造体
	static struct MJSYakuinfo yk;

	// -----------------------------
	// 処理時間計測
	// -----------------------------

	static int action_timestamp1;
	static int action_timestamp2;

	// -----------------------------
	// 卓情報
	// -----------------------------

	// プレーヤのキャラクタータイプ
	static LBPlyChar ply_type;

	// プレーヤ席ID
	static int ply_id;                            // 自分のプレーヤ番号
	static int ply_id_shimo;                      // 下家のプレーヤ番号

	// プレーヤの家情報
	static int kyoku_index;                       // 局INDEX(内部処理用)
	static int kyoku;                             // 局
	static int honba;                             // ツミ棒
	static int riichibo;                          // リー棒
	static int ie[PLAYER_MAX];                    // 家情報 東家：0、南家：1、ie[ply_id]=2でプレーヤが西家
	static int ply_bakaze;                        // プレーヤの場風牌の牌番号(東場 = 31、南場 = 32)
	static int ply_zikaze;                        // プレーヤの自風牌の牌番号

	// プレーヤの得点情報
	static int ply_kyoku_score[PLAYER_MAX];       // 局開始時の得点(1000点以下の場合はリーチを掛けない)

	// ドラ情報
	static int  dora_count;
	static int  dora_marker[DORA_MAX];            // ドラ牌表示牌
	static int  dora_marker_aka[DORA_MAX];        // ドラ牌表示牌赤
	static int  dora_hai[DORA_MAX];               // 実際のドラ牌

	// 赤牌情報
	static int max_aka_count[AKA_TYPE_MAX_COUNT]; // 最大赤牌枚数

	// 局の自摸回数
	static int kyoku_tsumo_count;                 // 局の自摸回数(最大70まで)
	static int open_haiparts_count[PAI_MAX];      // 手牌、捨牌、鳴き牌、ドラ牌で既に表示された牌枚数(4から引くと残り枚数)

	// -----------------------------
	// 手牌情報
	// -----------------------------

	// 手牌情報
	static int tehai[PAI_MAX];                    // 手牌ヒストグラム
	static int tehai_count;                       // 手牌枚数
	static int aka_count[AKA_TYPE_MAX_COUNT];     // 赤牌枚数

	// 手牌テーブル
	static int  tehaitbl[TEHAI_MAX];              // 牌テーブル
	static bool tehaitbl_aka[TEHAI_MAX];          // 牌テーブル(赤牌)

	// リーチ状態
	static int ply_riichi_mode;                   // リーチ状態(0：リーチかけてない、1：リーチ宣言時捨牌前、2：リーチ捨牌後、3：リーチ受入状態)

	// -----------------------------
	// 晒し牌情報
	// -----------------------------

	static int naki_count;                        // 鳴き合計面子数
	static int ankan_count;                       // 暗槓合計面子数
	static int kakan_count;                       // 加槓合計面子数

	static LBMen naki_stat[MEN_MAX];              // 鳴き状態
	static int naki_hai[MEN_MAX];                 // 鳴き牌
	static int naki_idx[MEN_MAX];                 // チー時の頭牌
	static int naki_aka[MEN_MAX];                 // 赤牌の数

	// -----------------------------
	// 河情報
	// -----------------------------

	// 河情報
	static int  ply_kawa_count[PLAYER_MAX];            // 河の枚数
	static int  kawa[PLAYER_MAX][KAWA_HAI_MAX];        // 河(捨牌情報)
	static bool kawa_aka[PLAYER_MAX][KAWA_HAI_MAX];    // 河の赤牌有無

	// プレーヤのリーチ状態
	static int  ply_riichi_stat_count;                          // リーチプレーヤ人数
	static bool ply_riichi_stat[PLAYER_MAX];                    // プレーヤごとのリーチ状態
	static int  ply_riichi_junban[PLAYER_MAX];                  // リーチしたプレーヤ番号ply_riichi_junban[ply_id]=何番目
	static int  postriichi_turn_count[PLAYER_MAX][PLAYER_MAX];  // 他プレーヤリーチ開始時の捨牌巡目
	                                                            // postriichi_turn_count[リーチしたply_id][各ply_id] = 順目[各ply_id]

	// -----------------------------
	// プレーヤーアクション情報
	// -----------------------------

	// アクションステータス
	static LBPAct ply_act;                        // プレーヤーのアクションステータス

	// ツモアクション
	static int  ply_tsumo_hai;                    // ツモ牌
	static bool ply_tsumo_aka;                    // 自摸牌の赤牌有無

	// 捨牌アクション
	static int  ply_sute_hai;                     // 捨牌
	static bool ply_sute_aka;                     // 捨牌の赤牌有無

	// 鳴きアクション
	static int ply_naki_idx;                      // 鳴いた時の牌INDEX(カン宣言も含む)
	static int ply_naki_aka_count;                // 鳴いた時の赤牌枚数

	// -----------------------------
	// 向聴数定義
	// -----------------------------

	static int shanten_normal;                    // 通常向聴数
	static int shanten_kokushi;                   // 国士向聴数
	static int shanten_chitoi;                    // 七対向聴数

	// -----------------------------
	// 向聴数計算(通常パータン)
	// -----------------------------

	static int atama_count;                       // 雀頭の枚数(値は0又は1)
	static int atama_hai;                         // 雀頭の牌番号

	static int mentsu_count;                      // 面子数
	static LBMen mentsu_stat[MEN_MAX];            // 面子状態
	static int mentsu_hai[MEN_MAX];               // 面子牌

	static int taatsu_count;                      // 塔子数
	static LBMen taatsu_stat[MEN_MAX];            // 塔子状態
	static int taatsu_hai[MEN_MAX];               // 塔子牌

	// -----------------------------
	// 向聴数計算(通常パータン：作業用)
	// -----------------------------

	static int wrk_shanten;                                           // (作業用)通常シャンテン

	static int wrk_atama_count;                                       // 雀頭の枚数(値は0又は1)
	static int wrk_atama_hai;                                         // 雀頭の牌番号

	static int wrk_all_mentsu_count;                                  // 全色合計面子数
	static int wrk_all_taatsu_count;                                  // 全色合計塔子数

	static int wrk_color_tehai[COLOR_MAX_COUNT][10];                  // 手牌ヒストグラム(色ごと0から9まで)
	static int wrk_color_shanten[COLOR_MAX_COUNT];                    // 通常シャンテン(色ごと)

	static int   wrk_max_mentsu_count[COLOR_MAX_COUNT];           // 最大面子数(色ごと)
	static LBMen wrk_max_mentsu_stat[COLOR_MAX_COUNT][MEN_MAX];   // 最大面子状態(色ごと)
	static int   wrk_max_mentsu_hai[COLOR_MAX_COUNT][MEN_MAX];    // 最大面子牌(色ごと)

	static int   wrk_mentsu_count[COLOR_MAX_COUNT];               // 面子数(色ごと)
	static LBMen wrk_mentsu_stat[COLOR_MAX_COUNT][MEN_MAX];       // 面子状態(色ごと)
	static int   wrk_mentsu_hai[COLOR_MAX_COUNT][MEN_MAX];        // 面子牌(色ごと)

	static int   wrk_max_taatsu_count[COLOR_MAX_COUNT];           // 最大塔子数(色ごと)
	static LBMen wrk_max_taatsu_stat[COLOR_MAX_COUNT][MEN_MAX];   // 最大塔子状態(色ごと)
	static int   wrk_max_taatsu_hai[COLOR_MAX_COUNT][MEN_MAX];    // 最大塔子牌(色ごと)

	static int   wrk_taatsu_count[COLOR_MAX_COUNT];               // 塔子数(色ごと)
	static LBMen wrk_taatsu_stat[COLOR_MAX_COUNT][MEN_MAX];       // 塔子状態(色ごと)
	static int   wrk_taatsu_hai[COLOR_MAX_COUNT][MEN_MAX];        // 塔子牌(色ごと)

	// -----------------------------
	// 捨牌候補・捨牌候補ごとの有効牌
	// -----------------------------

	static int sutekoho_count;                                        // 捨牌候補の総数
	static int sutekoho_hai[SUTE_KOHO_MAX_COUNT];                     // 捨牌候補の牌番号
	static int sutekoho_shanten[SUTE_KOHO_MAX_COUNT];                 // 捨牌候補の向聴数
	static int sutekoho_priority[SUTE_KOHO_MAX_COUNT];                // 捨牌候補の距離
	static int sutekoho_nearby_hai_count[SUTE_KOHO_MAX_COUNT];        // 捨牌候補のくっつき牌(nearby_hai)枚数
	static int sutekoho_dora_length[SUTE_KOHO_MAX_COUNT];             // 捨牌候補のドラ距離

	// 有効牌
	static bool yuko_hai[SUTE_KOHO_MAX_COUNT][PAI_MAX];               // 有効牌
	static int  yuko_haishu_count[SUTE_KOHO_MAX_COUNT];               // 有効牌の牌種別数
	static int  yuko_hai_count[SUTE_KOHO_MAX_COUNT];                  // 有効牌となる種別の総数
	static int  yuko_hai_count_open_haiparts[SUTE_KOHO_MAX_COUNT];    // 有効牌枚数(表示牌(open_haiparts)から算出)
	static int  yuko_max_count_open_haiparts[SUTE_KOHO_MAX_COUNT];    // 有効牌の最大数(表示牌(open_haiparts)から算出)

	// 捨牌候補ごとの可能鳴き枚数

	// 期待値
	static double sutekoho_ev_score[SUTE_KOHO_MAX_COUNT];             // 捨牌候補の期待値
	static int    sutekoho_ev_count[SUTE_KOHO_MAX_COUNT];             // 期待値候補数 

	// 最終捨牌候補
	static int yuko_max_count;                                        // 有効牌の最大数
	static int prefix_sutekoho_count;                                 // 決定前の捨牌数(有効牌と牌プライオリティから算出)
	static int prefix_sutekoho_num[SUTE_KOHO_MAX_COUNT];              // 決定前の捨牌候補
	static int fixed_sutekoho_num;                                    // 最終決定した捨牌番号

	// -----------------------------
	// プレーヤステータス
	// -----------------------------

	// 和了処理関連
	static bool ply_tehai_yaku_stat;              // 手牌役の有無
	static bool ply_furiten_stat;                 // フリテン状態

	// 鳴き処理関連
	static bool ply_tehai_naki_stat;              // 鳴き許可
	static bool ply_yakuhai_stat;                 // 役牌の保持有無

	// オリステータス
	static bool ply_tehai_ori_stat;               // オリ状態
	static int  ply_ori_algo_num;                 // オリアルゴリズム番号
	static int  ply_ori_hai;                      // オリ状態の候補オリ牌
	static bool ply_ori_aka;                      // オリ状態の候補オリ牌の赤牌有無
	static int  fixed_riichi_ply;                 // オリを定義するプレーヤ

	// オリ牌ランクテーブル(オリ候補牌定義)
	static int orihai_count;                           // オリ牌枚数
	static int orihai_num[SUTE_KOHO_MAX_COUNT];        // 手牌番号
	static int orihai_ranknum[SUTE_KOHO_MAX_COUNT];    // 手牌内のランク順位

	// スジ壁ステータス
	static bool suzi[PLAYER_MAX][3][7];           // スジ(1-7×3色)
	static bool urasuzi[PLAYER_MAX][3][7];        // 裏スジ(1-7×3色)
	static bool kabe[PLAYER_MAX][3][4];           // 壁情報(2,3,7,8)
	static bool aidayonken[PLAYER_MAX][3][6];     // 間四軒情報(1-6×3色)

	// -----------------------------
	// 鳴き候補(和了牌候補)テーブル
	// -----------------------------

	// 有効牌
	static bool yuko_hai_13mai[PAI_MAX];                                   // 13枚時の有効牌

	// 鳴き候補テーブル
	static int  nakikoho_tbl_count;                                        // 鳴き候補テーブルの枚数
	static LBPAct nakikoho_tbl_act[NAKI_KOHO_MAX_COUNT];                   // 鳴き候補_アクションテーブル
	static int  nakikoho_tbl_hai[NAKI_KOHO_MAX_COUNT];                     // 鳴き候補_牌テーブル
	static int  nakikoho_tbl_idx[NAKI_KOHO_MAX_COUNT];                     // 鳴き候補_牌INDEXテーブル
	static bool nakikoho_tbl_yesno[NAKI_KOHO_MAX_COUNT];                   // 鳴き候補_アクション実行可否

	// 期待値計算(聴牌)
	static int    nakikoho_tbl_score[NAKI_KOHO_MAX_COUNT];                 // 鳴き候補_得点
	static double nakikoho_tbl_agari_rate[NAKI_KOHO_MAX_COUNT];            // 鳴き候補_和了率
	static double nakikoho_tbl_parts_ev_score[NAKI_KOHO_MAX_COUNT];        // 鳴き候補_期待値
	static double nakikoho_tbl_total_ev_score;                             // テンパイ時の期待値合計

	// 期待値計算(一向聴)
	static int ev_1shanten_yukohai_count;
	static int ev_1shanten_yukohai[PAI_MAX];                        
	static int ev_1shanten_sutehai_count[PAI_MAX];                         // 有効牌ごと
	static int ev_1shanten_sutehai[PAI_MAX][TSUMOARI_TEHAI_MAX];    
	static double ev_1shanten_evscore[PAI_MAX][TSUMOARI_TEHAI_MAX]; 
	static int ev_1shanten_maxev_sutehai_num[PAI_MAX];              
	static double ev_1shanten_maxevscore[PAI_MAX];                         // 有効牌ごとの最大期待値
	static double ev_1shanten_totalscore;                                  // イーシャンテン時の期待値合計

	// 向聴情報仮置きテーブル
	static int karitbl_count;                                              // 仮向聴テーブル総数
	static int kari_shanten[KARITBL_MAX_COUNT];
	static int kari_tehai[KARITBL_MAX_COUNT][PAI_MAX];
	static int karitbl_calc_count;                                         // 計算対象の総数

	// 残り合計枚数
	static double unkown_resthai_count;                                    // 計算対象の総数

	// -----------------------------
	// pinfo構造体(Plyアクション情報を定義)
	// -----------------------------

	// 情報共有用構造体(pinfo)
	struct MJSPlyInfo{
		LBPAct ply_act;                           // プレーヤーのアクションステータス
		int act_hai;                              // アクション時に指定した牌
		int act_idx;                              // 牌INDEX
		int act_aka_count;                        // 赤牌枚数
	};

	// -----------------------------
	// 表示処理
	// -----------------------------

	// メッセージ表示バッファ
	static char mes_buf[ERR_MES_MAX_SIZE];

	// 表示モード
	static int print_ply_mode;                    // ply関数の表示モード(0:何も表示しない、1:plyの設定値を表示する)

/* ---------------------------------------------------------------------------------------------- */
// 関数定義
/* ---------------------------------------------------------------------------------------------- */

	// -----------------------------
	// 初期定義
	// -----------------------------

	// クラス初期化・後処理
	void PlyInit();
	void PlyPost();

	// 1-1.卓開始・終了
	void PlyActTakuStart(int tmp_ply_id,          // ply_idの決定
	                     int tmp_init_score,      // 卓開始時点での持ち得点
	                     int tmp_aka_man_max,     // 萬子の赤牌枚数
	                     int tmp_aka_pin_max,     // 筒子の赤牌枚数
	                     int tmp_aka_sou_max);    // 索子の赤牌枚数

	void PlyActTakuEnd();                         // 卓終了処理

	// 1-2.局開始・終了
	void PlyActKyokuStart(int  tmp_kaze,          // 局番号
	                      int  tmp_kyoku,         // 場風の牌番号
	                      int  tmp_honba,         // 本場
	                      int  tmp_riichibo,      // リーチ棒の本数
	                      int  tmp_ie,            // プレーヤの家番号
	                      bool tmp_score_flg,     // 得点変更有り無し
	                      int  tmp_score[],       // 得点情報
	                      int  tmp_dora_marker);  // ドラ表示牌

	void PlyActKyokuEnd();                        // 局終了処理

	// 2-1.配牌処理
	void PlyActHaipai(int tmp_tsumo_hai, bool tmp_tsumo_aka);

	// 2-2.配牌後処理
	void PlyActPostHaipai();

	// 3-1.(メイン関数)自摸処理
	void PlyActTsumo(struct MJSPlyInfo *pinfo, int tmp_tsumo_hai, bool tmp_tsumo_aka);   // 自摸時捨牌決定(メイン)
	void PlyChkAISutehai();                                                              // (サブ)戦略を含めた捨牌設定

	// 3-1.(サブ処理)オリ確認
	void PlyChkTehaiOri();              // 手牌オリ確認
	void set_ori_stat();                // オリ条件確認
	void set_ori_info();                // オリ情報定義(オリランク牌、スジ壁情報)
	void set_ori_hai();                 // オリ牌設定

	// 3-1.(サブ処理)アクション確認
	void PlyChkAnkan(int tmp_tsumo_hai, bool tmp_tsumo_aka);          // 暗槓確認
	void PlyChkKakan(int tmp_tsumo_hai, bool tmp_tsumo_aka);          // 加槓確認
	void PlyChkTsumoSute();                                           // 自摸時のアクションと捨牌決定
	void PlyChk9shu9hai();                                            // 九種九牌確認

	// 3-2.リーチ宣言時処理
	void PlyChkRiichiSute(struct MJSPlyInfo *pinfo);                  // リーチ時の捨牌決定(メイン)

	// 3-3.捨牌後アクション処理
	void PlyActTsumoSute();                                           // 自摸捨牌アクション(自摸捨牌、自摸切り、リーチ時捨牌)

	// 3-3.(サブ処理)捨牌後アクション処理
	void PlySetTsumoSuteTehaiHist();                                  // 1.自摸捨牌時の手牌ヒストグラム処理
	void PlyChkPlyStat();                                             // 2.プレーヤ手牌の状態確認(メイン処理)
	void PlyChkYaku();                                                // 3.役有り確認
	void PlyChkFuriten();                                             // 4.フリテン確認
	void PlyChkNakitbl();                                             // 5.鳴きテーブルの状態確認
	void PlySetKawa(int tmp_ply_id, int tmp_hai, int tmp_aka);        // (汎用処理)河情報の設定

	// 3-4.捨牌時アクション処理(自摸捨てアクション以外)
	void PlyActAnkan(int tmp_naki_hai);                               // 暗槓アクション
	void PlyActKakan(int tmp_naki_hai, int tmp_naki_aka_count);       // 加槓アクション

	// 4-1.他プレーヤの確認処理
	void PlyChkOthPlyTsumo();                                                       // 他プレーヤの自摸
	void PlyChkOthPlyRiichi(int tmp_ply_id);                                        // 他プレーヤのリーチ宣言
	void PlyChkOthPlyNaki(int naki_ply_id, LBPAct naki_ply_act, int tmp_naki_hai, int tmp_naki_idx, int tmp_aka_count); // 他プレーヤの鳴き処理

	// 4-2.鳴きアクション処理
	void PlyChkNaki(struct MJSPlyInfo *pinfo, int suteply, int hai, bool tmp_aka);  // 鳴き確認(相手プレーヤ捨牌確認)
	void PlyActNaki(struct MJSPlyInfo *pinfo,                         // 捨て牌アクション定義
	                int naki_ply_id,                                  // 鳴きプレーヤ
	                LBPAct naki_ply_act,                              // 鳴きアクション種別
	                int tmp_hai,                                      // 鳴き牌
	                int tmp_chi_hai_idx,                              // 鳴き面子(チー面子)の頭牌
	                int tmp_naki_aka_count);                          // 鳴き面子の赤牌枚数
	void PlyChkNakiSute(struct MJSPlyInfo *pinfo);                    // 鳴き後の捨牌確認

	// 4-3.鳴き捨牌後アクション処理
	void PlyActNakiSute();                                            // 鳴き捨牌後アクション

	// 5-1.和了終了処理
	void PlyAgari(bool tmp_score_flg, int tmp_score[]);

	// 5-2.流局終了処理
	void PlyRyuKyoku(bool tmp_score_flg, int tmp_score[]);

	// -----------------------------
	// 向聴数確認(メイン処理)
	// -----------------------------

	// 自摸有り/無し向聴数確認
	void ChkTsumoAriShanten();                         // 自摸有り(自摸後、捨牌前)状態の向聴数確認：捨牌候補算出
	void ChkTsumoNashiShanten();                       // 自摸無し(捨牌後、自摸前)状態の向聴数確認：鳴きテーブル情報格納

	// シャンテン計算/サブ処理
	void SetSutekohoPriority();                        // 捨牌候補の優先順位算出
	void SetFixedSutekoho();                           // 最終捨牌候補の算出

	// 期待値計算
	void set_tsumoari_kitaichi();                      // 自摸有り時の期待値
	void set_tenpai_kitaichi(int yuko_hai_num);        // 自摸無し時のテンパイ期待値
	void set_1shanten_kitaichi();                      // 自摸無し時の1シャンテン期待値

	// -----------------------------
	// 向聴数確認(改訂版)
	// -----------------------------

	void set_normal_shanten();                         // 通常向聴数確認
	void set_mentsu_taatsu_count();                    // 面子数・塔子数カウント処理
	void set_mentsu_count(int color, int hai);         // 面子数カウント処理
	void set_taatsu_count(int color, int hai);         // 塔子数カウント処理

	// -----------------------------
	// 向聴数確認(その他)
	// -----------------------------

	void KokushiShanten();              // 向聴数確認(国士無双)
	void ChitoiShanten();               // 向聴数確認(七対子)

	// -----------------------------
	// 汎用確認
	// -----------------------------

	void init_param();                            // パラメータ初期化
	void set_pinfo(struct MJSPlyInfo *pinfo,      // pinfo定義
	               LBPAct tmp_ply_act, 
	               int tmp_act_hai, 
	               int tmp_act_idx, 
	               int tmp_act_aka_count);

	// -----------------------------
	// 表示関数
	// -----------------------------

	// 汎用関数(卓情報)
	void print_version_info();          // バージョン情報
	void print_taku_start();            // 卓開始情報
	void print_kyoku_start();           // 局開始情報
	void print_haipai(int tmp_tsumo_hai, bool tmp_tsumo_aka);    // 配牌情報

	// 汎用関数(手牌)
	void print_tehai_line();            // ライン手牌情報表示
	void print_tehai_hist();            // 手牌ヒストグラム表示
	void print_tehai_aka();             // 手牌の赤牌枚数
	void print_tsumo_hai();             // 自摸牌情報
	void print_kawa_line();             // 河情報
	void print_ori_info();              // オリ情報

	// 手牌詳細情報
	void print_tsumoari_tehai_info();   // 自摸有り手牌の詳細銃砲
	void print_tsumonashi_tehai_info(); // 自摸無し手牌の詳細銃砲
	void print_sutekoho(int sutenum);   // 手牌ごとの詳細銃砲

	// 汎用関数(一般処理)
	void print_mes(char* tmp_mes);      // メッセージ表示
	void print_separator();             // 区切り線表示
	void print_cr();                    // 改行表示

	// 汎用関数(パーツ)
	void print_char_info();             // プレーヤーキャラクター情報
	void print_pinfo_act(struct MJSPlyInfo *pinfo);         // pinfoアクション詳細表示
	void print_mentsu(LBMen men_stat,   // 面子情報
	                 int men_hai, 
	                 int men_idx, 
	                 int aka_count);

#endif/* PLY_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */

