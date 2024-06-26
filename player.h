/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： 麻雀AI：MJSakuraモジュール
 * バージョン     ： 0.0.1.0.12(ログ表示レベルの実装)
 * プログラム名   ： mjs
 * ファイル名     ： player.h
 * クラス名       ： MJSPlayerクラス
 * 処理概要       ： プレーヤークラス
 * Ver0.0.1作成日 ： 2024/06/01 16:03:43
 * 最終更新日     ： 2024/06/29 22:21:40
 * 
 * Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#ifndef PLY_H_INCLUDED
#define PLY_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/* ---------------------------------------------------------------------------------------------- */
// ラベル(各モード)
/* ---------------------------------------------------------------------------------------------- */

// プレーヤーキャラクター
typedef enum {

	PLYCHAR_NONAME = 0,                 // 00:プレーヤー状態なし
	PLYCHAR_TAMPOPO,                    // 01:プレーヤーキャラクター1
	PLYCHAR_HIMAWARI,                   // 02:プレーヤーキャラクター2
	PLYCHAR_KOBUSHI,                    // 03:プレーヤーキャラクター3
	PLYCHAR_TSUBAKI,                    // 04:プレーヤーキャラクター4
	PLYCHAR_AYAME,                      // 05:プレーヤーキャラクター5
	PLYCHAR_TSUBOMI,                    // 06:プレーヤーキャラクター6
	PLYCHAR_SAKURA,                     // 07:プレーヤーサクラ

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
	// 卓情報
	// -----------------------------

	// プレーヤのタイプ
	static LBPlyChar ply_type;

	// プレーヤ席番号
	static int ply_num;                             // 自分のプレーヤ番号
	static int ply_num_shimo;                       // 下家のプレーヤ番号

	// プレーヤの家
	static int ie;                                  // 家情報 東家：0、南家：1、ie=2でプレーヤが西家
	static int ply_bakaze;                          // プレーヤの場風牌の牌番号(東家 = 0、南家 = 1)
	static int ply_zikaze;                          // プレーヤの自風牌の牌番号

	// 赤牌情報
	static int max_aka_count[AKA_SHUBETSU_MAX];     // 最大赤牌枚数

	// 局の自摸回数
	static int kyoku_tsumo_count;                   // 局の自摸回数(最大70まで)

	// -----------------------------
	// 手牌情報
	// -----------------------------

	// 手牌情報
	static int tehai[PAI_MAX];                      // 手牌ヒストグラム
	static int tehai_count;                         // 手牌枚数
	static int aka_count[AKA_SHUBETSU_MAX];         // 赤牌枚数

	// 手牌テーブル
	static int  tehaitbl[TEHAI_MAX];                // 牌テーブル
	static bool tehaitbl_aka[TEHAI_MAX];            // 牌テーブル(赤牌)

	// リーチ状態
	static int ply_riichi_mode;                     // リーチ状態(0：リーチかけてない、1：リーチ宣言後・捨牌前、2：リーチ確定状態)

	// -----------------------------
	// 晒し牌情報
	// -----------------------------

	static int naki_count;                          // 鳴き合計面子数
	static int ankan_count;                         // 暗槓合計面子数
	static int kakan_count;                         // 加槓合計面子数

	static LBMen naki_stat[MEN_MAX];                // 鳴き状態
	static int naki_hai[MEN_MAX];                   // 鳴き牌
	static int naki_idx[MEN_MAX];                   // チー時の頭牌
	static int naki_aka[MEN_MAX];                   // 赤牌の数

	// -----------------------------
	// 河情報
	// -----------------------------

	static int kawa[30];                            // 河(捨牌情報)

	// -----------------------------
	// プレーヤーアクション情報
	// -----------------------------

	// アクションステータス
	static LBPAct ply_act;                     // プレーヤーのアクションステータス

	// ツモアクション
	static int  ply_tsumo_hai;                 // ツモ牌
	static bool ply_tsumo_aka;                 // 自摸牌の赤牌有無

	// 捨牌アクション
	static int  ply_sute_hai;                  // 捨牌
	static bool ply_sute_aka;                  // 捨牌の赤牌有無

	// 鳴きアクション
	static int ply_naki_idx;                   // 鳴いた時の牌INDEX(カン宣言も含む)
	static int ply_naki_aka_count;             // 鳴いた時の赤牌枚数

	// -----------------------------
	// 向聴数定義
	// -----------------------------

	static int shanten_normal;                 // 通常向聴数
	static int shanten_kokushi;                // 国士向聴数
	static int shanten_chitoi;                 // 七対向聴数

	// -----------------------------
	// 通常シャンテン計算
	// -----------------------------

	static int atama_count;                    // 雀頭の枚数(値は0又は1)
	static int atama_hai;                      // 雀頭の牌番号

	static int mentu_count;                    // 面子数
	static LBMen mentu_stat[MEN_MAX];          // 面子状態
	static int mentu_hai[MEN_MAX];             // 面子牌

	static int taatu_count;                    // 塔子数
	static LBMen taatsu_stat[MEN_MAX];         // 塔子状態
	static int taatsu_hai[MEN_MAX];            // 塔子牌

	// -----------------------------
	// 通常シャンテン計算・作業用
	// -----------------------------

	static int tmp_shanten;                    // (作業用)通常シャンテン

	static int tmp_atama_count;                // 雀頭の枚数(値は0又は1)
	static int tmp_atama_hai;                  // 雀頭の牌番号

	static int tmp_mentu_count;                // 面子数
	static LBMen tmp_mentu_stat[MEN_MAX];      // 面子状態
	static int tmp_mentu_hai[MEN_MAX];         // 面子牌

	static int tmp_taatu_count;                // 塔子数
	static LBMen tmp_taatsu_stat[MEN_MAX];     // 塔子状態
	static int tmp_taatsu_hai[MEN_MAX];        // 塔子牌

	// -----------------------------
	// 捨牌候補・捨牌候補ごとの有効牌
	// -----------------------------

	static int sutekoho_count;                 // 捨牌候補の総数
	static int sutekoho_hai[14];               // 捨牌候補の牌番号
	static int sutekoho_shanten[14];           // 捨牌候補の向聴数
	static int sutekoho_priority[14];          // 捨牌候補の優先順位

	static bool yuko_hai[14][40];              // 有効牌
	static int  yuko_haishu_count[14];         // 有効牌の牌種別数
	static int  yuko_hai_count[14];            // 有効牌となる種別の総数
	static int  yuko_max_count;                   // 有効牌の最大数

	static int fixed_sutekoho_num;                // 最終決定した捨牌番号

	// -----------------------------
	// 鳴き候補テーブル
	// -----------------------------

	// プレーヤ状態
	static bool ply_tehai_naki_stat;              // 鳴き許可
	static bool ply_yakuhai_stat;                 // 役牌の保持状態

	// 有効牌
	static bool yuko_hai_13mai[40];               // 13枚時の有効牌

	// 鳴き候補テーブル
	static int  nakikoho_tbl_count;               // 鳴き候補テーブルの枚数
	static LBPAct nakikoho_tbl_act[20];           // 鳴き候補テーブル
	static int  nakikoho_tbl_hai[20];             // 鳴き候補_牌テーブル
	static int  nakikoho_tbl_idx[20];             // 鳴き候補_チーテーブル
	static bool nakikoho_tbl_yesno[20];           // 鳴き候補_実行有無

	// -----------------------------
	// 構造体
	// -----------------------------

	// 情報共有用構造体(pinfo)
	struct MJSPlyInfo{
		LBPAct ply_act;                           // プレーヤーのアクションステータス
		int act_hai;                              // アクション時に指定した牌
		int act_idx;                              // 牌INDEX
		int act_aka_count;                        // 赤牌枚数
	};

	// -----------------------------
	// 表示モード
	// -----------------------------

	static int print_ply_mode;                   // ply関数の表示モード(0:何も表示しない、1:plyの設定値を表示する)


/* ---------------------------------------------------------------------------------------------- */
// 関数定義
/* ---------------------------------------------------------------------------------------------- */

	// -----------------------------
	// 初期定義
	// -----------------------------

	// クラス初期化・後処理
	void PlyInit();
	void PlyPost();

	// 汎用確認
	void set_pinfo(struct MJSPlyInfo *pinfo, LBPAct tmp_ply_act, int tmp_act_hai, int tmp_act_idx, int tmp_act_aka_count);

	// 1-1.卓開始・終了
	void PlyActTakuStart(int tmp_ply_num);
	void PlyActTakuEnd();

	// 1-2.局開始・終了
	void PlyActKyokuStart(int tmp_kaze, int tmp_ie);
	void PlyActKyokuEnd();

	// 1-3.河設定
	void PlySetKawa(int suteply, int hai);

	// 2-1.配牌処理
	void PlyActHaipai(int tmp_tsumo_hai, bool tmp_tsumo_aka);

	// 2-2.配牌後処理
	void PlyActPostHaipai();

	// 3-1.自摸処理
	void PlyActTsumo(struct MJSPlyInfo *pinfo, int tmp_tsumo_hai, bool tmp_tsumo_aka);// 自摸時捨牌決定(メイン)
	void PlyChk9shu9hai();                                            // 九種九牌確認
	void PlyChkAnkan(int tmp_tsumo_hai, bool tmp_tsumo_aka);          // 暗槓確認
	void PlyChkKakan(int tmp_tsumo_hai, bool tmp_tsumo_aka);          // 加槓確認
	void PlyChkTsumoSute();                                           // 自摸時のアクションと捨牌決定(サブ)
	void PlyCountTsumo();                                             // 自摸枚数をカウント

	// 3-2.リーチ宣言時処理
	void PlyChkRiichiSute(struct MJSPlyInfo *pinfo);                  // リーチ時の捨牌決定(メイン)

	// 3-3.捨牌時アクション処理
	void PlyActTsumoSute();                                           // 自摸捨牌アクション(自摸捨牌、自摸切り、リーチ時捨牌)

	// 3-4.捨牌時アクション処理(サブ処理)
	void PlySetTsumoSuteTehaiHist();                                  // 3-2-1.自摸捨牌時の手牌ヒストグラム処理
	void PlyChkPlyStat();                                             // 3-2-2.(10-2.)プレーヤ手牌の状態確認
	void PlyChkNakitbl();                                             // 3-2-3.(10-3.)鳴きテーブルの状態確認

	// 3-5.捨牌時アクション処理(自摸捨てアクション以外)
	void PlyActAnkan(int tmp_naki_hai);                               // 暗槓アクション
	void PlyActKakan(int tmp_naki_hai, int tmp_naki_aka_count);       // 加槓アクション

	// 4-1.鳴き確認処理
	void PlyChkNaki(struct MJSPlyInfo *pinfo, int suteply, int hai);  // 鳴き確認

	// 4-2.鳴きアクション処理
	void PlyActNaki(struct MJSPlyInfo *pinfo,                         // 捨て牌アクション定義
	                int naki_ply_num,                                 // 鳴きプレーヤ
	                LBPAct naki_ply_act,                              // 鳴きアクション種別
	                int hai,                                          // 鳴き牌
	                int chi_hai_idx,                                  // 鳴き面子(チー面子)の頭牌
	                int naki_aka_count);                              // 鳴き面子の赤牌枚数

	// 4-3.鳴きアクション処理(サブ処理)
	void PlyChkNakiSute(struct MJSPlyInfo *pinfo);                    // 鳴き後の捨牌確認

	// 4-4.鳴き捨牌アクション
	void PlyActNakiSute();                                            // 鳴き後の捨牌処理

	// 5-1.和了終了処理
	void PlyAgari();
	bool PlyChkYaku();
	bool PlyChkFuriten();

	// 5-2.流局終了処理
	void PlyRyuKyoku();

	/* ----------------------------- */
	// 向聴数確認(メイン処理)
	/* ----------------------------- */

	void ChkTsumoAriShanten();          // 自摸有り(自摸後。捨牌前)状態の向聴数確認：捨牌候補算出
	void ChkTsumoNashiShanten();        // 自摸無し(捨牌後、自摸前)状態の向聴数確認：鳴きテーブル情報格納
	void SetSutekohoPriority();         // 捨牌候補の優先順位算出
	void SetFixedSutekoho();            // 最終捨牌候補の算出

	/* ----------------------------- */
	// 向聴数確認(サブ処理)
	/* ----------------------------- */

	void NormalShanten();               // 向聴数確認(通常)
	void mentu_cut(int hai);            // 面子削除処理
	void taatu_cut(int hai);            // 塔子削除処理

	void NormalShanten_detail();        // 向聴数確認(通常_面子情報付与版)
	void mentu_cut_detail(int hai);     // 面子削除処理(面子情報付与版)
	void taatu_cut_detail(int hai);     // 塔子削除処理(塔子情報付与版)

	void KokushiShanten();              // 向聴数確認(国士無双)
	void ChitoiShanten();               // 向聴数確認(七対子)

	/* ----------------------------- */
	// 表示処理
	/* ----------------------------- */

	// 汎用関数
	void print_tehai_line();                 // ライン手牌情報表示
	void print_tehai_hist();                 // 手牌ヒストグラム表示
	void print_tehai_aka();                            // 手牌の赤牌枚数
	void print_pinfo_act(struct MJSPlyInfo *pinfo);    // アクション表示

	// 手牌詳細情報
	void print_tsumoari_tehai_info();        // 自摸有り手牌の詳細銃砲
	void print_tsumonashi_tehai_info();      // 自摸無し手牌の詳細銃砲
	void print_sutekoho(int sutenum);        // 手牌ごとの詳細銃砲




#endif/* PLY_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */

