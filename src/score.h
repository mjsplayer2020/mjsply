/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： 麻雀AI：MJSakuraモジュール
 * バージョン     ： 0.0.2.0.6(点数計算をリーチ無前提に変更)
 * プログラム名   ： mjs
 * ファイル名     ： score.h
 * クラス名       ： 得点計算関数
 * 処理概要       ： 得点計算関数
 * Ver0.0.2作成日 ： 2025/01/02 15:34:38
 * 最終更新日     ： 2025/01/12 14:19:33
 * 
 * Copyright (c) 2010-2025 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/* ---------------------------------------------------------------------------------------------- */
// 固定値
/* ---------------------------------------------------------------------------------------------- */

// 翻定数
#define NORMAL_FU_SCORE_COUNT    10     // 通常点の符個数
#define NORMAL_HAN_SCORE_COUNT    4     // 通常点の翻個数
#define MANGAN_HAN_SCORE_COUNT    5     // 満貫以上の翻個数

/* ---------------------------------------------------------------------------------------------- */
//  構造体
/* ---------------------------------------------------------------------------------------------- */
// 役情報構造体
struct MJSYakuinfo{

	// -----------------------------
	// 流局時
	// -----------------------------
	bool ryukyoku_flg;                       // 流局であるのか？
	LBRKStat ryukyoku_stat;                  // 局終了状態
	int  ply_tempai_count;                   // テンパイしているプレーヤー数
	bool ply_tempai_flg[PLAYER_MAX];         // プレーヤごとのテンパイ

	// 得点情報
	int kyoku_score[PLAYER_MAX];             // 各局の最終得点(リーチ棒、ツミ棒込み)

	// -----------------------------
	// 和了プレーヤー
	// -----------------------------

	int agari_ply_num;                       // 和了プレーヤー
	int furikomi_ply_num;                    // 振込プレーヤー

	// -----------------------------
	// 和了状態
	// -----------------------------

	// 和了情報
	LBAgariTehai agari_stat;                 // 和了形式
	int ie[PLAYER_MAX];                      // 家情報
	bool agari_ply_oya_flg;                  // 和了プレーヤーが親であるのか？
	bool tsumo_agari_flg;                    // 自摸和了であるのか？
	bool menzen_flg;                         // 面前であるのか？

	// 和了状態(リーチ)
	bool riichi_flg;                         // 通常リーチをかけているか？
	bool w_riichi_flg;                       // ダブルリーチをかけているか？
	bool ippatsu_riichi_flg;                 // リーチ一発の状態であるのか？
	int agari_ply_tsumo_count;               // 和了プレーヤーの自摸回数
	int agari_ply_riichi_count;              // 和了プレーヤーのリーチ後の自摸回数

	// -----------------------------
	// 和了牌
	// -----------------------------

	// 和了牌
	int  agari_hai;                          // 和了した時の牌番号
	bool agari_aka;                          // 和了した時の牌の赤牌有無

	// 雀頭情報
	int  agari_ata_hai;                      // 和了時点の雀頭の牌番号
	int  agari_ata_aka;                      // 和了時点の雀頭の赤牌枚数
	int  agari_ata_19zi;                     // 和了時点の雀頭のヤオチュウ有無(0:中張 1:ヤオチュウ 2:役牌)
	int  atamaFu;                            // 雀頭符

	// 和了面子情報
	int   agari_men_count;                   // 和了メンツ数
	LBMen agari_men_stat[MEN_MAX];           // 和了メンツ状態
	int   agari_men_hai[MEN_MAX];            // 和了メンツ牌
	int   agari_men_aka_count[MEN_MAX];      // 和了メンツの赤牌数
	int   agari_men_Fu[MEN_MAX];             // 和了メンツの符
	int   agari_men_19zi[MEN_MAX];           // 和了メンツのヤオチュウ有無(0:中張 1:ヤオチュウ 2:役牌)

	// 和了面子情報(七対子)
	int agari_chitoi_men_hai[CHITOI_MEN_MAX];          // 和了メンツ牌(七対子)
	int agari_chitoi_men_aka_count[CHITOI_MEN_MAX];    // 和了メンツの赤牌数(七対子)

	// 和了牌の面子番号
	int agari_men_num_agari_hai;                  // 和了牌を含む面子の面子番号

	// 待ち形式
	LBMen agari_machi_stat;                       // 和了時の待ち形式

	// ドラ枚数
	int agari_dora_count;
	int agari_uradora_count;

	// 赤枚数
	int agari_aka_count[AKA_TYPE_MAX_COUNT]; // 赤牌枚数

	// 特定種別の面子数
	int mentsu_count_shuntsu;                     // 順子数
	int mentsu_count_minshun;
	int mentsu_count_anko;
	int mentsu_count_minko;
	int mentsu_count_ankan;
	int mentsu_count_minkan;

	int mentsu_count_19zi;                        // 一九字の面子数
	int mentsu_count_chunchan;                    // 中張牌の面子数

	int mentsu_count_manzu;                       // 萬子数
	int mentsu_count_pinzu;                       // 筒子数
	int mentsu_count_souzu;                       // 索子数
	int mentsu_count_zihai;                       // 字牌の数
	int mentsu_count_green;                       // 緑牌の数

	// 和了状態
	int agari_ply_bakaze;                         // 場風の牌番号
	int agari_ply_zikaze;                         // 自風の牌番号

	// 面子ヒストグラム
	int anko_hist[PAI_MAX];                       // 暗刻ヒストグラム
	int shuntsu_hist[PAI_MAX];                    // 順子ヒストグラム

	/* ----------------------------- */
	// 局得点情報(役・符)
	/* ----------------------------- */

	// 符
	int basefu;                                   // 基礎符
	int menzenFu;                                 // 面前符
	int machiFu;                                  // 待ち符
	int tsumoFu;                                  // 自摸符
	int totalFu;                                  // 符の合計
	int scoreFu;                                  // 符の合計(切り上げ後)

	// 通常役の情報
	bool yaku_flg[YAKU_SHUBETSU_MAX];             // 役フラグ
	int  yaku_han[YAKU_SHUBETSU_MAX];             // 役ごとの翻数
	int  yakucount;                               // 役の個数
	int  agari_ply_han;                           // 和了プレーヤーの合計翻数
	int  agari_ply_mangan_count;                  // 和了プレーヤーの満貫以上個数

	// 役満の情報
	bool yakuman_flg[YAKUMAN_SHUBETSU_MAX];       // 役満フラグ
	int  yakuman_bai[YAKUMAN_SHUBETSU_MAX];       // 役満の倍数
	int  yakuman_count;                           // 役満の個数
	int  yakuman_agari_ply_bai;                   // 和了倍数

	// 得点情報 - 相手
	int agari_ply_ron;
	int agari_ply_tsumo_oya; 
	int agari_ply_tsumo_ko; 

};

/* ---------------------------------------------------------------------------------------------- */
// 変数
/* ---------------------------------------------------------------------------------------------- */

	// 翻数
	static int yakuhan[YAKU_SHUBETSU_MAX];
	static int nakihan[YAKU_SHUBETSU_MAX];
	static int yakuman_bai[YAKUMAN_SHUBETSU_MAX];       // 二倍役満であるかどうか

	// 得点テーブル・通常得点
	static int score_ron_oya[NORMAL_HAN_SCORE_COUNT][NORMAL_FU_SCORE_COUNT];
	static int score_ron_ko[NORMAL_HAN_SCORE_COUNT][NORMAL_FU_SCORE_COUNT];
	static int score_tsumo_oya[NORMAL_HAN_SCORE_COUNT][NORMAL_FU_SCORE_COUNT];
	static int score_tsumo_ko[NORMAL_HAN_SCORE_COUNT][NORMAL_FU_SCORE_COUNT];

	// 得点テーブル・満貫以上
	static int score_mangan_ron_oya[MANGAN_HAN_SCORE_COUNT];
	static int score_mangan_ron_ko[MANGAN_HAN_SCORE_COUNT];
	static int score_mangan_tsumo_oya[MANGAN_HAN_SCORE_COUNT];
	static int score_mangan_tsumo_ko[MANGAN_HAN_SCORE_COUNT];

	// 得点テーブル・七対子
	static int score_chitoi_ron_oya[NORMAL_HAN_SCORE_COUNT];
	static int score_chitoi_ron_ko[NORMAL_HAN_SCORE_COUNT];
	static int score_chitoi_tsumo_oya[NORMAL_HAN_SCORE_COUNT];
	static int score_chitoi_tsumo_ko[NORMAL_HAN_SCORE_COUNT];

	// 得点テーブル・役満
	static int score_yakuman_ron_oya;
	static int score_yakuman_ron_ko;
	static int score_yakuman_tsumo_oya;
	static int score_yakuman_tsumo_ko;

/* ---------------------------------------------------------------------------------------------- */
// 関数定義
/* ---------------------------------------------------------------------------------------------- */

	// -----------------------------
	// 初期化・終了処理
	// -----------------------------
	void ScoreInit();                                       // 得点計算クラスの初期化
	void ScorePost();                                       // 得点計算クラスの終了処理

	// 事前定義
	void SetYakuInfo();                                     // 役情報定義
	void SetBaseScoreTable();                               // 基礎得点テーブルの設定

	// 和了得点設定(一時確認)
	void ChkAgariScoreInfo(struct MJSYakuinfo *yk);                // 和了得点設定(一時確認)

	// -----------------------------
	// 得点確認(プレ処理)
	// 手牌面子テーブル
	// 鳴き面子テーブル
	// アクションテーブル(リーチ確認のため)
	// -----------------------------

	void SetAgari(
	struct MJSYakuinfo *yk,          // 和了役情報構造体
	int  kyoku,               // 局番号
	int  ie[],                // プレーヤの家情報
	int  dora_count,          // 表ドラ牌枚数
	int  dora[],              // 表ドラ牌情報
	int  uradora_count,       // 裏ドラ牌枚数
	int  uradora[],           // 裏ドラ牌情報
	LBAgariTehai  agari_stat, // 和了形式
	int  agari_ply_num,       // 和了プレーヤ
	int  furikomi_ply_num,    // 振込プレーヤ
	bool tsumoagari_flg,      // 自摸和了の有無
	int  agari_hai,           // 和了牌
	bool  agari_aka,          // 和了牌の赤牌有無
	int  tehai_hist[],        // 和了時の手牌ヒストグラム
	int  aka_count[],         // 手牌の赤牌枚数
	int  atama_hai,           // 頭牌
	int  men_count,           // 面子数
	LBMen men_stat[],         // 面子状態
	int  men_hai[],           // 面子牌
	int  men_idx[],           // 面子INDEX
	int  nakimen_count,       // 鳴き面子数
	LBMen nakimen_stat[],     // 鳴き面子状態
	int  nakimen_hai[],       // 鳴き面子牌
	int  nakimen_idx[],       // 鳴き面子INDEX
	int  nakimen_aka[],       // 鳴き面子赤牌枚数
	bool tmp_riichi_flg,      // リーチフラグ
	bool tmp_riichi_ippatsu_flg,  // リーチ一発フラグ
	bool tmp_double_riichi_flg    // ダブルリーチフラグ
	);

	// 得点確認(サブ処理)
	void Chk_initAgariScore(struct MJSYakuinfo *yk);        // 01:初期化処理
	void Chk_preAgariScore(                                 // 02:事前和了情報の設定
	struct MJSYakuinfo *yk,                                 // 和了役情報構造体
	int  atama_hai,                                         // 頭牌
	int  men_count,                                         // 面子数
	LBMen men_stat[],                                       // 面子状態
	int  men_hai[],                                         // 面子牌
	int  men_idx[],                                         // 面子INDEX
	int  nakimen_count,                                     // 鳴き面子数
	LBMen nakimen_stat[],                                   // 鳴き面子状態
	int  nakimen_hai[],                                     // 鳴き面子牌
	int  nakimen_idx[],                                     // 鳴き面子INDEX
	int  nakimen_aka[],                                     // 鳴き面子赤牌枚数
	bool tmp_riichi_flg,                                    // リーチフラグ
	bool tmp_riichi_ippatsu_flg,                            // リーチ一発フラグ
	bool tmp_double_riichi_flg                              // ダブルリーチフラグ
	);

	void Set_AgariTehaiTbl(struct MJSYakuinfo *yk,                 // 03:和了手牌テーブルの設定
	int  tehai_hist[]);
	void Chk_mentsu(struct MJSYakuinfo *yk,                        // 04:面子確認
	int  dora_count,
	int  dora[], 
	int  uradora[]);

	void Chk_tehai_count(struct MJSYakuinfo *yk);                  // 05:手牌枚数確認
	void Chk_fu(struct MJSYakuinfo *yk);                           // 06:符計算
	void Chk_yaku(struct MJSYakuinfo *yk, int tehai_hist[]);       // 07:役確認
	void Chk_score(struct MJSYakuinfo *yk);                        // 08:得点計算

	// 得点確認(サブ処理・七対子・国士)
	void Chk_chitoi_mentsu(struct MJSYakuinfo *yk);                // 04-01:面子確認(七対子)
	void Chk_kokushi_mentsu(struct MJSYakuinfo *yk);               // 04-02:面子確認(国士)

	// ドラ処理
	void Chk_tehai_dora_count(struct MJSYakuinfo *yk, int dora_count, int dora[], int ura_dora[]);    // ドラ枚数の確認
	void sub_tehai_dora_count(struct MJSYakuinfo *yk, int dora_hai, bool omote_dora_type);            // (サブ関数)ドラ枚数の確認
	int  Get_dora_hai(int dora_hai);                                                                  // ドラ表示牌→ドラ牌の変換

	// 役確認
	void ChkYakuRiich(struct MJSYakuinfo *yk);                     // リーチ系
	void ChkYakuChitoiIpeko(struct MJSYakuinfo *yk);               // 七対子、一盃口、二盃口 
	void ChkYakuChinItsu_HonItsu(struct MJSYakuinfo *yk);          // 清一混一系
	void ChkYakuAnko(struct MJSYakuinfo *yk);                      // 暗刻系
	void ChkYakuChanta(struct MJSYakuinfo *yk);                    // チャンタ系
	void ChkYakuSanshoku(struct MJSYakuinfo *yk);                  // 三色系
	void ChkYakuItsu(struct MJSYakuinfo *yk);                      // 一通系
	void ChkYakuPinfu(struct MJSYakuinfo *yk);                     // 平和系
	void ChkYakuTanyao(struct MJSYakuinfo *yk);                    // タンヤオ系
	void ChkYakuYakuhai(struct MJSYakuinfo *yk);                   // 役牌系
	void ChkYakuDaisangen(struct MJSYakuinfo *yk);                 // 大三元・小三元
	void ChkYakuDaisushi(struct MJSYakuinfo *yk);                  // 大四喜和・小四喜和
	void ChkYakuKokushi(struct MJSYakuinfo *yk);                   // 国士無双
	void ChkYakuChuren(struct MJSYakuinfo *yk, int tehai_hist[]);  // 九連宝燈
	void ChkYakuTenho(struct MJSYakuinfo *yk);                     // 天和
	void ChkYakuEtc(struct MJSYakuinfo *yk);                       // その他の手役

	// 荒牌処理
	void SetHowanpaiScore(struct MJSYakuinfo *yk);                 // 荒牌時得点設定

#endif /* SCORE_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */

