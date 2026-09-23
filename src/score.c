/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： 麻雀AI：MJSakuraモジュール
 * バージョン     ： 0.0.2.0.6(点数計算をリーチ無前提に変更)
 * プログラム名   ： mjs
 * ファイル名     ： score.c
 * クラス名       ： 得点計算関数
 * 処理概要       ： 得点計算関数
 * Ver0.0.2作成日 ： 2025/01/02 15:34:38
 * 最終更新日     ： 2025/01/12 14:19:33
 * 
 * Copyright (c) 2010-2025 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "score.h"

/* ---------------------------------------------------------------------------------------------- */
// 得点計算クラスの初期化
/* ---------------------------------------------------------------------------------------------- */
void ScoreInit(){

}

/* ---------------------------------------------------------------------------------------------- */
// 得点計算クラスの終了処理
/* ---------------------------------------------------------------------------------------------- */
void ScorePost(){

}

/* ---------------------------------------------------------------------------------------------- */
// 役情報定義
/* ---------------------------------------------------------------------------------------------- */
void SetYakuInfo(){

	// 翻数定義・通常役
	yakuhan[NOYAKU]     = 0;
	yakuhan[RIICH]      = 1;
	yakuhan[WRIICH]     = 2;
	yakuhan[IPPATSU]    = 1;
	yakuhan[CHINISO]    = 6;
	yakuhan[HONISO]     = 3;
	yakuhan[JUNCHAN]    = 3;
	yakuhan[RYANPEKO]   = 3;
	yakuhan[HONROTO]    = 2;
	yakuhan[SHOSANGEN]  = 2;
	yakuhan[ITSU]       = 2;
	yakuhan[SANDOKOU]   = 2;
	yakuhan[SANDOJUN]   = 2;
	yakuhan[SANKANTSU]  = 2;
	yakuhan[SANANKO]    = 2;
	yakuhan[TOITOI]     = 2;
	yakuhan[CHANTA]     = 2;
	yakuhan[CHITOI]     = 2;
	yakuhan[PINFU]      = 1;
	yakuhan[TANYAO]     = 1;
	yakuhan[IPEKO]      = 1;
	yakuhan[BAKAZE]     = 1;
	yakuhan[ZIKAZE]     = 1;
	yakuhan[YAKUHAIHAKU]  = 1;
	yakuhan[YAKUHAIHATSU] = 1;
	yakuhan[YAKUHAICHUN]  = 1;
	yakuhan[HAITEI]     = 1;
	yakuhan[HOUTEI]     = 1;
	yakuhan[RINSHAN]    = 1;
	yakuhan[CHANKAN]    = 1;
	yakuhan[TSUMO]      = 1;
	yakuhan[DORA]       = 0;
	yakuhan[URADORA]    = 0;
	yakuhan[AKAHAI]     = 0;
	yakuhan[RENHO]      = 5;
	yakuhan[NAGASHIMAN] = 5;

	// 翻数定義・通常役：鳴きあり
	nakihan[NOYAKU]     = 0;
	nakihan[RIICH]      = 0;
	nakihan[WRIICH]     = 0;
	nakihan[IPPATSU]    = 0;
	nakihan[CHINISO]    = 5;
	nakihan[HONISO]     = 2;
	nakihan[JUNCHAN]    = 2;
	nakihan[RYANPEKO]   = 0;
	nakihan[HONROTO]    = 2;
	nakihan[SHOSANGEN]  = 2;
	nakihan[ITSU]       = 1;
	nakihan[SANDOKOU]   = 2;
	nakihan[SANDOJUN]   = 1;
	nakihan[SANKANTSU]  = 2;
	nakihan[SANANKO]    = 2;
	nakihan[TOITOI]     = 2;
	nakihan[CHANTA]     = 1;
	nakihan[CHITOI]     = 0;
	nakihan[PINFU]      = 0;
	nakihan[TANYAO]     = 1;
	nakihan[IPEKO]      = 0;
	nakihan[BAKAZE]     = 1;
	nakihan[ZIKAZE]     = 1;
	nakihan[YAKUHAIHAKU]  = 1;
	nakihan[YAKUHAIHATSU] = 1;
	nakihan[YAKUHAICHUN]  = 1;
	nakihan[HAITEI]     = 1;
	nakihan[HOUTEI]     = 1;
	nakihan[RINSHAN]    = 1;
	nakihan[CHANKAN]    = 1;
	nakihan[TSUMO]      = 0;
	nakihan[DORA]       = 0;
	nakihan[URADORA]    = 0;
	nakihan[AKAHAI]     = 0;
	nakihan[RENHO]      = 0;
	nakihan[NAGASHIMAN] = 5;

	// 役満
	yakuman_bai[NOYAKUMAN]    = 0;
	yakuman_bai[TENHO]        = 1;
	yakuman_bai[CHIHO]        = 1;
	yakuman_bai[CHUREN9MEN]   = 1;
	yakuman_bai[CHUREN]       = 1;
	yakuman_bai[KOKUSHI13MEN] = 1;
	yakuman_bai[KOKUSHI]      = 1;
	yakuman_bai[DAISANGEN]    = 1;
	yakuman_bai[DAISUSHI]     = 1;
	yakuman_bai[SHOSUSHI]     = 1;
	yakuman_bai[TSUISO]       = 1;
	yakuman_bai[CHINROTO]     = 1;
	yakuman_bai[RYUISO]       = 1;
	yakuman_bai[SUKANTSU]     = 1;
	yakuman_bai[SUANKOTANKI]  = 1;
	yakuman_bai[SUANKO]       = 1;
	yakuman_bai[RENHOYAKUMAN] = 1;
}

/* ---------------------------------------------------------------------------------------------- */
// 基礎得点テーブルの設定
/* ---------------------------------------------------------------------------------------------- */
void SetBaseScoreTable(){

	// 得点情報
	// https://mj-dragon.com/calc/index-score.html
	// http://yahoo-mbga.jp/page/stdgame/300001/majan_09.html

	// -----------------------------
	// 親ロン
	// -----------------------------

	// 親ロン・一翻
	score_ron_oya[0][0] = 0;    // 20符
	score_ron_oya[0][1] = 1500; // 30符
	score_ron_oya[0][2] = 2000; // 40符
	score_ron_oya[0][3] = 2400; // 50符
	score_ron_oya[0][4] = 2900; // 60符
	score_ron_oya[0][5] = 3400; // 70符
	score_ron_oya[0][6] = 3900; // 80符
	score_ron_oya[0][7] = 4400; // 90符
	score_ron_oya[0][8] = 4800; // 100符
	score_ron_oya[0][9] = 5300; // 110符

	// 親ロン・二翻
	score_ron_oya[1][0] = 2100;  // 20符
	score_ron_oya[1][1] = 2900;  // 30符
	score_ron_oya[1][2] = 3900;  // 40符
	score_ron_oya[1][3] = 4800;  // 50符
	score_ron_oya[1][4] = 5800;  // 60符
	score_ron_oya[1][5] = 6800;  // 70符
	score_ron_oya[1][6] = 7700;  // 80符
	score_ron_oya[1][7] = 8700;  // 90符
	score_ron_oya[1][8] = 9600;  // 100符
	score_ron_oya[1][9] = 10600; // 110符

	// 親ロン・三翻
	score_ron_oya[2][0] = 3900;  // 20符
	score_ron_oya[2][1] = 5800;  // 30符
	score_ron_oya[2][2] = 7700;  // 40符
	score_ron_oya[2][3] = 9600;  // 50符
	score_ron_oya[2][4] = 11600; // 60符
	score_ron_oya[2][5] = 12000; // 70符
	score_ron_oya[2][6] = 12000; // 80符
	score_ron_oya[2][7] = 12000; // 90符
	score_ron_oya[2][8] = 12000; // 100符
	score_ron_oya[2][9] = 12000; // 110符

	// 親ロン・四翻
	score_ron_oya[3][0] =  5800; // 20符
	score_ron_oya[3][1] = 11600; // 30符
	score_ron_oya[3][2] = 12000; // 40符
	score_ron_oya[3][3] = 12000; // 50符
	score_ron_oya[3][4] = 12000; // 60符
	score_ron_oya[3][5] = 12000; // 70符
	score_ron_oya[3][6] = 12000; // 80符
	score_ron_oya[3][7] = 12000; // 90符
	score_ron_oya[3][8] = 12000; // 100符
	score_ron_oya[3][9] = 12000; // 110符

	// 親ロン・七対子
	score_chitoi_ron_oya[0] = 1200;  // 一翻25符
	score_chitoi_ron_oya[1] = 2400;  // 二翻25符
	score_chitoi_ron_oya[2] = 4800;  // 三翻25符
	score_chitoi_ron_oya[3] = 9600;  // 四翻25符

	// 親ロン・満貫以上
	score_mangan_ron_oya[0] = 12000; // 満貫
	score_mangan_ron_oya[1] = 18000; // 跳満
	score_mangan_ron_oya[2] = 24000; // 倍満
	score_mangan_ron_oya[3] = 36000; // 三倍満
	score_mangan_ron_oya[4] = 48000; // 数え役満

	// 親ロン・役満
	score_yakuman_ron_oya = 48000;

	// -----------------------------
	// 子ロン
	// -----------------------------

	// 子ロン・一翻
	score_ron_ko[0][0] = 0;    // 20符
	score_ron_ko[0][1] = 1000; // 30符
	score_ron_ko[0][2] = 1300; // 40符
	score_ron_ko[0][3] = 1600; // 50符
	score_ron_ko[0][4] = 2000; // 60符
	score_ron_ko[0][5] = 2300; // 70符
	score_ron_ko[0][6] = 2600; // 80符
	score_ron_ko[0][7] = 2900; // 90符
	score_ron_ko[0][8] = 3200; // 100符
	score_ron_ko[0][9] = 3600; // 110符

	// 子ロン・二翻
	score_ron_ko[1][0] = 1300; // 20符
	score_ron_ko[1][1] = 2000; // 30符
	score_ron_ko[1][2] = 2600; // 40符
	score_ron_ko[1][3] = 3200; // 50符
	score_ron_ko[1][4] = 3900; // 60符
	score_ron_ko[1][5] = 4500; // 70符
	score_ron_ko[1][6] = 5200; // 80符
	score_ron_ko[1][7] = 5800; // 90符
	score_ron_ko[1][8] = 6400; // 100符
	score_ron_ko[1][9] = 7100; // 110符

	// 子ロン・三翻
	score_ron_ko[2][0] = 2600; // 20符
	score_ron_ko[2][1] = 3900; // 30符
	score_ron_ko[2][2] = 5200; // 40符
	score_ron_ko[2][3] = 6400; // 50符
	score_ron_ko[2][4] = 7700; // 60符
	score_ron_ko[2][5] = 8000; // 70符
	score_ron_ko[2][6] = 8000; // 80符
	score_ron_ko[2][7] = 8000; // 90符
	score_ron_ko[2][8] = 8000; // 100符
	score_ron_ko[2][9] = 8000; // 110符

	// 子ロン・四翻
	score_ron_ko[3][0] = 5200; // 20符
	score_ron_ko[3][1] = 7700; // 30符
	score_ron_ko[3][2] = 8000; // 40符
	score_ron_ko[3][3] = 8000; // 50符
	score_ron_ko[3][4] = 8000; // 60符
	score_ron_ko[3][5] = 8000; // 70符
	score_ron_ko[3][6] = 8000; // 80符
	score_ron_ko[3][7] = 8000; // 90符
	score_ron_ko[3][8] = 8000; // 100符
	score_ron_ko[3][9] = 8000; // 110符

	// 子ロン・七対子
	score_chitoi_ron_oya[0] =  800;  // 一翻25符
	score_chitoi_ron_oya[1] = 1600;  // 二翻25符
	score_chitoi_ron_oya[2] = 3200;  // 三翻25符
	score_chitoi_ron_oya[3] = 6400;  // 四翻25符

	// 子ロン・満貫以上
	score_mangan_ron_ko[0] =  8000; // 満貫
	score_mangan_ron_ko[1] = 12000; // 跳満
	score_mangan_ron_ko[2] = 16000; // 倍満
	score_mangan_ron_ko[3] = 24000; // 三倍満
	score_mangan_ron_ko[4] = 32000; // 数え役満

	// 子ロン・役満
	score_yakuman_ron_ko = 32000;

	// -----------------------------
	// 自摸和了・親支払い
	// -----------------------------

	// 自摸和了親支払い・一翻
	score_tsumo_oya[0][0] =    0; // 20符
	score_tsumo_oya[0][1] =  500; // 30符
	score_tsumo_oya[0][2] =  700; // 40符
	score_tsumo_oya[0][3] =  800; // 50符
	score_tsumo_oya[0][4] = 1000; // 60符
	score_tsumo_oya[0][5] = 1200; // 70符
	score_tsumo_oya[0][6] = 1300; // 80符
	score_tsumo_oya[0][7] = 1500; // 90符
	score_tsumo_oya[0][8] = 1600; // 100符
	score_tsumo_oya[0][9] = 1800; // 110符

	// 自摸和了親支払い・二翻
	score_tsumo_oya[1][0] =  700; // 20符
	score_tsumo_oya[1][1] = 1000; // 30符
	score_tsumo_oya[1][2] = 1300; // 40符
	score_tsumo_oya[1][3] = 1600; // 50符
	score_tsumo_oya[1][4] = 2000; // 60符
	score_tsumo_oya[1][5] = 2300; // 70符
	score_tsumo_oya[1][6] = 2600; // 80符
	score_tsumo_oya[1][7] = 2900; // 90符
	score_tsumo_oya[1][8] = 3200; // 100符
	score_tsumo_oya[1][9] = 3600; // 110符

	// 自摸和了親支払い・三翻
	score_tsumo_oya[2][0] = 1300; // 20符
	score_tsumo_oya[2][1] = 2000; // 30符
	score_tsumo_oya[2][2] = 2600; // 40符
	score_tsumo_oya[2][3] = 3200; // 50符
	score_tsumo_oya[2][4] = 3900; // 60符
	score_tsumo_oya[2][5] = 4000; // 70符
	score_tsumo_oya[2][6] = 4000; // 80符
	score_tsumo_oya[2][7] = 4000; // 90符
	score_tsumo_oya[2][8] = 4000; // 100符
	score_tsumo_oya[2][9] = 4000; // 110符

	// 自摸和了親支払い・四翻
	score_tsumo_oya[3][0] = 2600; // 20符
	score_tsumo_oya[3][1] = 3900; // 30符
	score_tsumo_oya[3][2] = 4000; // 40符
	score_tsumo_oya[3][3] = 4000; // 50符
	score_tsumo_oya[3][4] = 4000; // 60符
	score_tsumo_oya[3][5] = 4000; // 70符
	score_tsumo_oya[3][6] = 4000; // 80符
	score_tsumo_oya[3][7] = 4000; // 90符
	score_tsumo_oya[3][8] = 4000; // 100符
	score_tsumo_oya[3][9] = 4000; // 110符

	// 自摸和了親支払い・七対子
	score_chitoi_tsumo_oya[0] =  400;
	score_chitoi_tsumo_oya[1] =  800;
	score_chitoi_tsumo_oya[2] = 1600;
	score_chitoi_tsumo_oya[3] = 3200;

	// 自摸和了親支払い・満貫以上
	score_mangan_tsumo_oya[0] =  4000;
	score_mangan_tsumo_oya[1] =  6000;
	score_mangan_tsumo_oya[2] =  8000;
	score_mangan_tsumo_oya[3] = 12000;
	score_mangan_tsumo_oya[4] = 16000;

	// 自摸和了親支払い・役満
	score_yakuman_tsumo_oya = 16000;

	// -----------------------------
	// 自摸和了・子支払い
	// -----------------------------

	// 自摸和了子支払い・一翻
	score_tsumo_ko[0][0] = 0;    // 20符
	score_tsumo_ko[0][1] = 300;  // 30符
	score_tsumo_ko[0][2] = 400;  // 40符
	score_tsumo_ko[0][3] = 400;  // 50符
	score_tsumo_ko[0][4] = 500;  // 60符
	score_tsumo_ko[0][5] = 600;  // 70符
	score_tsumo_ko[0][6] = 700;  // 80符
	score_tsumo_ko[0][7] = 800;  // 90符
	score_tsumo_ko[0][8] = 800;  // 100符
	score_tsumo_ko[0][9] = 900;  // 110符

	// 自摸和了子支払い・二翻
	score_tsumo_ko[1][0] =  400;  // 20符
	score_tsumo_ko[1][1] =  500;  // 30符
	score_tsumo_ko[1][2] =  700;  // 40符
	score_tsumo_ko[1][3] =  800;  // 50符
	score_tsumo_ko[1][4] = 1000;  // 60符
	score_tsumo_ko[1][5] = 1200;  // 70符
	score_tsumo_ko[1][6] = 1300;  // 80符
	score_tsumo_ko[1][7] = 1500;  // 90符
	score_tsumo_ko[1][8] = 1600;  // 100符
	score_tsumo_ko[1][9] = 1800;  // 110符

	// 自摸和了子支払い・三翻
	score_tsumo_ko[2][0] =  700; // 20符
	score_tsumo_ko[2][1] = 1000; // 30符
	score_tsumo_ko[2][2] = 1300; // 40符
	score_tsumo_ko[2][3] = 1600; // 50符
	score_tsumo_ko[2][4] = 2000; // 60符
	score_tsumo_ko[2][5] = 2000; // 70符
	score_tsumo_ko[2][6] = 2000; // 80符
	score_tsumo_ko[2][7] = 2000; // 90符
	score_tsumo_ko[2][8] = 2000; // 100符
	score_tsumo_ko[2][9] = 2000; // 110符

	// 自摸和了子支払い・四翻
	score_tsumo_ko[3][0] = 1300; // 20符
	score_tsumo_ko[3][1] = 2000; // 30符
	score_tsumo_ko[3][2] = 2000; // 40符
	score_tsumo_ko[3][3] = 2000; // 50符
	score_tsumo_ko[3][4] = 2000; // 60符
	score_tsumo_ko[3][5] = 2000; // 70符
	score_tsumo_ko[3][6] = 2000; // 80符
	score_tsumo_ko[3][7] = 2000; // 90符
	score_tsumo_ko[3][8] = 2000; // 100符
	score_tsumo_ko[3][9] = 2000; // 110符

	// 自摸和了子支払い・七対子
	score_chitoi_tsumo_ko[0] =  200;
	score_chitoi_tsumo_ko[1] =  400;
	score_chitoi_tsumo_ko[2] =  800;
	score_chitoi_tsumo_ko[3] = 1600;

	// 自摸和了子支払い・満貫以上
	score_mangan_tsumo_ko[0] = 2000;
	score_mangan_tsumo_ko[1] = 3000;
	score_mangan_tsumo_ko[2] = 4000;
	score_mangan_tsumo_ko[3] = 6000;
	score_mangan_tsumo_ko[4] = 8000;

	// 自摸和了子支払い・役満
	score_yakuman_tsumo_ko   = 8000;

}

/* ---------------------------------------------------------------------------------------------- */
// メイン処理：和了得点設定(一時確認)
/* ---------------------------------------------------------------------------------------------- */
void ChkAgariScoreInfo(struct MJSYakuinfo *yk){

}

/* ---------------------------------------------------------------------------------------------- */
// メイン処理：和了得点設定
/* ---------------------------------------------------------------------------------------------- */
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
	bool agari_aka,           // 和了牌の赤牌有無
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
	bool tmp_riichi_flg,          // リーチフラグ
	bool tmp_riichi_ippatsu_flg,  // リーチ一発フラグ
	bool tmp_double_riichi_flg    // ダブルリーチフラグ
	){

	// -----------------------------
	// 事前定義
	// -----------------------------
	SetYakuInfo();
	SetBaseScoreTable();

	// -----------------------------
	// メイン処理
	// -----------------------------

	// 01:初期化処理
	Chk_initAgariScore(yk);

	// -----------------------------
	// score構造体に和了情報設定
	// -----------------------------
	yk->agari_stat        = agari_stat;           // 和了形式
	yk->agari_ply_num     = agari_ply_num;        // 和了プレーヤ
	yk->furikomi_ply_num  = furikomi_ply_num;     // 振込プレーヤ
	yk->tsumo_agari_flg   = tsumoagari_flg;       // 自摸和了
	yk->agari_hai         = agari_hai;            // 和了牌
	yk->agari_aka         = agari_aka;            // 和了牌赤

	// -----------------------------
	// 局情報の設定
	// -----------------------------

	// 流局フラグ
	yk->ryukyoku_flg = false;

	// 親フラグの設定
	if( ie[agari_ply_num] == 0 ){
		yk->agari_ply_oya_flg = true;
	}else{
		yk->agari_ply_oya_flg = false;
	}

	// 面前フラグの設定
	if(nakimen_count == 0){
		yk->menzen_flg = true;
	}else{
		yk->menzen_flg = false;
	}

	// 場風時風の設定
	yk->agari_ply_bakaze = 31+(kyoku/4);
	yk->agari_ply_zikaze = 31+ie[agari_ply_num];

	// -----------------------------
	// 赤牌設定
	// -----------------------------

	// 作業用変数の設定
	yk->agari_aka_count[0] = aka_count[0];
	yk->agari_aka_count[1] = aka_count[1];
	yk->agari_aka_count[2] = aka_count[2];

	// 和了牌の加算
	if(agari_aka == true){
		yk->agari_aka_count[(agari_hai-5)/10]++;
	}

	// 02:事前和了情報の設定
	Chk_preAgariScore(yk,
	atama_hai,
	men_count,
	men_stat,
	men_hai,
	men_idx,
	nakimen_count,
	nakimen_stat,
	nakimen_hai,
	nakimen_idx,
	nakimen_aka,
	tmp_riichi_flg,
	tmp_riichi_ippatsu_flg,
	tmp_double_riichi_flg
	);

	// 和了形式ごとの符計算
	if(yk->agari_stat == AGARI_NORMAL){
		// 通常形式の得点計算
		Chk_mentsu(yk, dora_count, dora, uradora);          // 03:面子確認
		Chk_tehai_count(yk);                                // 04:手牌枚数確認
		Chk_fu(yk);                                         // 05:符計算
	}else if(yk->agari_stat == AGARI_CHITOI){
		Chk_chitoi_mentsu(yk);
	}else if(yk->agari_stat == AGARI_KOKUSHI){
		Chk_kokushi_mentsu(yk);
	}

	// 06:役確認
	Chk_yaku(yk, tehai_hist);

	// 07:得点計算
	Chk_score(yk);

}

/* ---------------------------------------------------------------------------------------------- */
// 01:初期化処理
/* ---------------------------------------------------------------------------------------------- */
void Chk_initAgariScore(struct MJSYakuinfo *yk){

	// 和了牌面子
	yk->agari_men_num_agari_hai = 999;

	// ドラ
	yk->agari_dora_count = 0; 
	yk->agari_uradora_count = 0;

	// 赤牌
	yk->agari_aka_count[0] = 0;
	yk->agari_aka_count[1] = 0;
	yk->agari_aka_count[2] = 0;

	// 面子数
	yk->mentsu_count_shuntsu = 0;
	yk->mentsu_count_minshun = 0;
	yk->mentsu_count_anko    = 0;
	yk->mentsu_count_minko   = 0;
	yk->mentsu_count_ankan   = 0;
	yk->mentsu_count_minkan  = 0;

	yk->mentsu_count_19zi = 0;
	yk->mentsu_count_chunchan = 0;
	yk->mentsu_count_manzu = 0;
	yk->mentsu_count_pinzu = 0;
	yk->mentsu_count_souzu = 0;
	yk->mentsu_count_zihai = 0;
	yk->mentsu_count_green = 0;

	// 符の設定
	yk->basefu = 20;
	yk->agari_men_Fu[0]=0;
	yk->agari_men_Fu[1]=0;
	yk->agari_men_Fu[2]=0;
	yk->agari_men_Fu[3]=0;
	yk->atamaFu=0;
	yk->menzenFu=0;
	yk->machiFu=0;
	yk->tsumoFu=0;

	// 符の合計
	yk->totalFu = yk->basefu;
	yk->scoreFu = yk->totalFu;

}

/* ---------------------------------------------------------------------------------------------- */
// 02:事前和了情報の設定
/* ---------------------------------------------------------------------------------------------- */
void Chk_preAgariScore(
	struct MJSYakuinfo *yk,
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
	bool tmp_riichi_flg,          // リーチフラグ
	bool tmp_riichi_ippatsu_flg,  // リーチ一発フラグ
	bool tmp_double_riichi_flg    // ダブルリーチフラグ
	){

	// -----------------------------
	// 作業用変数の定義
	// -----------------------------
	// 赤牌
	int tmp_aka_man;
	int tmp_aka_pin;
	int tmp_aka_sou;

	// 一発鳴きフラグ
	// bool tmp_ippatsu_naki_flg;

	// -----------------------------
	// 和了プレーヤーの和了自摸回数・リーチ状態確認(初期化)
	// -----------------------------
	yk->riichi_flg = tmp_riichi_flg;
	yk->ippatsu_riichi_flg  = tmp_riichi_ippatsu_flg;
	yk->w_riichi_flg        = tmp_double_riichi_flg;
	yk->agari_ply_tsumo_count  = 0;
	yk->agari_ply_riichi_count = 0;

	// -----------------------------
	// 赤牌初期化
	// -----------------------------

	// 作業用変数の設定
	tmp_aka_man = yk->agari_aka_count[0];
	tmp_aka_pin = yk->agari_aka_count[1];
	tmp_aka_sou = yk->agari_aka_count[2];

	// -----------------------------
	// 雀頭情報の設定
	// -----------------------------

	// 雀頭設定
	yk->agari_ata_hai = atama_hai;

	// 和了牌の面子番号設定
	if (yk->agari_ata_hai == yk->agari_hai){

		// 面子番号は仮置きの「999」とする
		yk->agari_men_num_agari_hai = 999;

	}

	// 赤牌設定
	yk->agari_ata_aka = 0;

	if(yk->agari_ata_hai == 5){
		if(tmp_aka_man>2){
			yk->agari_ata_aka=2;
			tmp_aka_man=tmp_aka_man-2;
		}else{
			yk->agari_ata_aka=tmp_aka_man;
			tmp_aka_man=0;
		}
	}

	if(yk->agari_ata_hai == 15){
		if(tmp_aka_pin>2){
			yk->agari_ata_aka=2;
			tmp_aka_pin=tmp_aka_pin-2;
		}else{
			yk->agari_ata_aka=tmp_aka_pin;
			tmp_aka_pin=0;
		}
	}

	if(yk->agari_ata_hai == 25){
		if(tmp_aka_sou>2){
			yk->agari_ata_aka=tmp_aka_sou=2;
			tmp_aka_sou=tmp_aka_sou-2;
		}else{
			yk->agari_ata_aka=tmp_aka_sou;
			tmp_aka_sou=0;
		}
	}

	// -----------------------------
	// 手牌面子の設定
	// -----------------------------

	// 面子数設定
	yk->agari_men_count = men_count;

	// メンツ情報の格納
	for(int tmp_i = 0; tmp_i < yk->agari_men_count; tmp_i++){

		// -----------------------------
		// メンツ情報の格納
		// -----------------------------

		yk->agari_men_stat[tmp_i]      = men_stat[tmp_i];  
		yk->agari_men_hai[tmp_i]       = men_hai[tmp_i];   
		yk->agari_men_aka_count[tmp_i] = 0;                      // 赤牌の初期化

		// -----------------------------
		// 暗刻処理
		// -----------------------------
		if ( yk->agari_men_stat[tmp_i] == ANKO){

			// 萬子処理
			if(yk->agari_men_hai[tmp_i] == 5){
				if(tmp_aka_man>3){
					yk->agari_men_aka_count[tmp_i]=3;
					tmp_aka_man=tmp_aka_man-3;
				}else{
					yk->agari_men_aka_count[tmp_i]=tmp_aka_man;
					tmp_aka_man=0;
				}
			}

			// 筒子処理
			if(yk->agari_men_hai[tmp_i] == 15){
				if(tmp_aka_pin>2){
					yk->agari_men_aka_count[tmp_i]=3;
					tmp_aka_pin=tmp_aka_pin-3;
				}else{
					yk->agari_men_aka_count[tmp_i]=tmp_aka_pin;
					tmp_aka_pin=0;
				}
			}

			// 索子処理
			if(yk->agari_men_hai[tmp_i] == 25){
				if(tmp_aka_sou>2){
					yk->agari_men_aka_count[tmp_i]=3;
					tmp_aka_sou=tmp_aka_sou-3;
				}else{
					yk->agari_men_aka_count[tmp_i]=tmp_aka_sou;
					tmp_aka_sou=0;
				}
			}

			// 和了牌の面子番号設定 - 暗刻の場合
			if ( yk->agari_men_hai[tmp_i] == yk->agari_hai){

				// 面子番号の設定
				yk->agari_men_num_agari_hai = tmp_i;

				// ロン和了の面子番号は鳴きメンツに変更する
				if(yk->tsumo_agari_flg == false){
					yk->agari_men_stat[tmp_i] = MINKO;
				}

			}
		}

		// -----------------------------
		// 順子処理
		// -----------------------------
		if ( yk->agari_men_stat[tmp_i] == SHUNTSU){

			// 萬子処理
			if(yk->agari_men_hai[tmp_i] == 3 || 
			   yk->agari_men_hai[tmp_i] == 4 ||
			   yk->agari_men_hai[tmp_i] == 5){

				// 赤牌があるなら
				if(tmp_aka_man>0){
					yk->agari_men_aka_count[tmp_i]++;
					tmp_aka_man--;
				}
			}

			// 筒子処理
			if(yk->agari_men_hai[tmp_i] == 13 || 
			   yk->agari_men_hai[tmp_i] == 14 ||
			   yk->agari_men_hai[tmp_i] == 15){

				// 赤牌があるなら
				if(tmp_aka_pin>0){
					yk->agari_men_aka_count[tmp_i]++;
					tmp_aka_pin--;
				}
			}

			// 索子処理
			if(yk->agari_men_hai[tmp_i] == 23 || 
			   yk->agari_men_hai[tmp_i] == 24 ||
			   yk->agari_men_hai[tmp_i] == 25){

				// 赤牌があるなら
				if(tmp_aka_sou>0){
					yk->agari_men_aka_count[tmp_i]++;
					tmp_aka_sou--;
				}
			}

			// 和了牌の面子番号設定 - 順子の場合
			if ( yk->agari_men_hai[tmp_i]   == yk->agari_hai || 
			     yk->agari_men_hai[tmp_i]+1 == yk->agari_hai || 
			     yk->agari_men_hai[tmp_i]+2 == yk->agari_hai ){

				// 面子番号の設定
				yk->agari_men_num_agari_hai = tmp_i;

				// ロン和了の面子番号は鳴きメンツに変更する
				if(yk->tsumo_agari_flg == false){
					yk->agari_men_stat[tmp_i] = MINSHUN;
				}
			}

		}

	}

	// -----------------------------
	// 晒し面子(鳴き面子)の設定
	// -----------------------------

	// 晒し面子の追加
	for(int tmp_i = 0; tmp_i < nakimen_count; tmp_i++){

		// 加槓確認
		if( nakimen_stat[tmp_i] == KAKAN){

			// 加槓面子設定
			for(int tmp_j = 0; tmp_j < nakimen_count; tmp_j++){

				// 加槓した暗刻であれば
				if(yk->agari_men_hai[tmp_j] == nakimen_hai[tmp_i]){

					// メンツ情報の格納(加槓)
					yk->agari_men_stat[tmp_j] = MINKAN;

					// 赤牌+1加算
					if( nakimen_aka[tmp_j] > 0){
						yk->agari_men_aka_count[tmp_j]++;
					}

				}
			}

		// 加槓以外
		}else{

			// メンツ情報の格納
			yk->agari_men_stat[yk->agari_men_count]       = nakimen_stat[tmp_i];
			yk->agari_men_hai[yk->agari_men_count]        = nakimen_idx[tmp_i];
			yk->agari_men_aka_count[yk->agari_men_count]  = nakimen_aka[tmp_i];
			yk->agari_men_count++;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 03:面子確認
/* ---------------------------------------------------------------------------------------------- */
void Chk_mentsu(struct MJSYakuinfo *yk, int dora_count, int dora[], int uradora[]){

	// -----------------------------
	// 変数定義
	// -----------------------------

	// 赤牌作業用
	// int tmp_aka_man;
	// int tmp_aka_pin;
	// int tmp_aka_sou;

	yk->agari_aka_count[0] = 0;
	yk->agari_aka_count[1] = 0;
	yk->agari_aka_count[2] = 0;

	// -----------------------------
	// 赤牌初期化
	// -----------------------------

	// tmp_aka_man = 0;
	// tmp_aka_pin = 0;
	// tmp_aka_sou = 0;

	// -----------------------------
	// 待ち形式の確認
	// -----------------------------

	// 単騎待ち確認
	if( yk->agari_men_num_agari_hai == 999){
		yk->agari_machi_stat = TANKI;

	// 順子関連の待ち
	}else if( yk->agari_men_stat[yk->agari_men_num_agari_hai] == SHUNTSU ||
              yk->agari_men_stat[yk->agari_men_num_agari_hai] == MINSHUN ){

		// 和了牌が面子INDEXと同じなら
		if( yk->agari_men_hai[yk->agari_men_num_agari_hai] == yk->agari_hai ){

			// ペンチャンを調べる
			if( yk->agari_hai ==  7 || 
			    yk->agari_hai == 17 || 
			    yk->agari_hai == 27 ){
				yk->agari_machi_stat = PENCHAN ; 
			}else{
				yk->agari_machi_stat = RYANMEN;
			}

		}

		// 和了牌が面子INDEX+1なら
		if( yk->agari_men_hai[yk->agari_men_num_agari_hai] + 1 == yk->agari_hai ){
			yk->agari_machi_stat = KANCHAN;
		}

		// 和了牌が面子INDEX+2なら
		if( yk->agari_men_hai[yk->agari_men_num_agari_hai] + 2 == yk->agari_hai ){

			// ペンチャンを調べる
			if( yk->agari_hai ==  3 || 
			    yk->agari_hai == 13 || 
			    yk->agari_hai == 23 ){
				yk->agari_machi_stat = PENCHAN ; 
			}else{
				yk->agari_machi_stat = RYANMEN;
			}

		}

	// シャンポン待ち確認
	}else if( yk->agari_men_stat[yk->agari_men_num_agari_hai] == ANKO  ||
              yk->agari_men_stat[yk->agari_men_num_agari_hai] == MINKO ){
				yk->agari_machi_stat = TOITSU;

	// その他
	}else{
		yk->agari_machi_stat = NOMENTSU;
	}

	// -----------------------------
	// ドラカウント
	// -----------------------------

	// ドラカウント
	Chk_tehai_dora_count(yk, dora_count, dora, uradora);

	// -----------------------------
	// 赤牌カウント
	// -----------------------------

	yk->agari_aka_count[0] = 0;
	yk->agari_aka_count[1] = 0;
	yk->agari_aka_count[2] = 0;

	// 頭赤カウント
	if(yk->agari_ata_hai == MAN5NUM){
		yk->agari_aka_count[0]=yk->agari_ata_aka;
	}else if(yk->agari_ata_hai == PIN5NUM){
		yk->agari_aka_count[1]=yk->agari_ata_aka;
	}else if(yk->agari_ata_hai == SOU5NUM){
		yk->agari_aka_count[2]=yk->agari_ata_aka;
	}

	// 面子赤カウント
	for(int tmp_i = 0; tmp_i < 4; tmp_i++){

		// 面子赤カウント - 萬子
		if( yk->agari_men_hai[tmp_i] == MAN3NUM || 
		    yk->agari_men_hai[tmp_i] == MAN4NUM ||
		    yk->agari_men_hai[tmp_i] == MAN5NUM ){

			// 赤牌加算
			yk->agari_aka_count[0] = yk->agari_aka_count[0] + yk->agari_men_aka_count[tmp_i];

		// 面子赤カウント - 筒子
		}else if(yk->agari_men_hai[tmp_i] == PIN3NUM ||
		         yk->agari_men_hai[tmp_i] == PIN4NUM ||
		         yk->agari_men_hai[tmp_i] == PIN5NUM ){

			// 赤牌加算
			yk->agari_aka_count[1] = yk->agari_aka_count[1] + yk->agari_men_aka_count[tmp_i];

		// 面子赤カウント - 索子
		}else if(yk->agari_men_hai[tmp_i] == SOU3NUM ||
		         yk->agari_men_hai[tmp_i] == SOU4NUM ||
		         yk->agari_men_hai[tmp_i] == SOU5NUM ){

			// 赤牌加算
			yk->agari_aka_count[2] = yk->agari_aka_count[2] + yk->agari_men_aka_count[tmp_i];

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 03-01:事前和了情報の設定(七対子)
/* ---------------------------------------------------------------------------------------------- */
void Chk_chitoi_mentsu(struct MJSYakuinfo *yk){


}

/* ---------------------------------------------------------------------------------------------- */
// 03-02:事前和了情報の設定(国士)
/* ---------------------------------------------------------------------------------------------- */
void Chk_kokushi_mentsu(struct MJSYakuinfo *yk){

	// 待ち形式
	yk->agari_machi_stat = TANKI;

	// 符の設定
	yk->basefu = 20;
	yk->agari_men_Fu[0]=0;
	yk->agari_men_Fu[1]=0;
	yk->agari_men_Fu[2]=0;
	yk->agari_men_Fu[3]=0;
	yk->atamaFu=0;
	yk->menzenFu=0;
	yk->machiFu=0;
	yk->tsumoFu=0;

	// 符の合計
	yk->totalFu = yk->basefu;
	yk->scoreFu = yk->totalFu;
}

/* ---------------------------------------------------------------------------------------------- */
// 04:手牌枚数確認
/* ---------------------------------------------------------------------------------------------- */
void Chk_tehai_count(struct MJSYakuinfo *yk){

	// -----------------------------
	// 各手牌の枚数確認
	// -----------------------------

	// 変数初期化
	yk->mentsu_count_shuntsu = 0;
	yk->mentsu_count_minshun = 0;
	yk->mentsu_count_anko    = 0;
	yk->mentsu_count_minko   = 0;
	yk->mentsu_count_ankan   = 0;
	yk->mentsu_count_minkan  = 0;

	yk->mentsu_count_19zi     = 0;             // 一九字の数
	yk->mentsu_count_chunchan = 0;             // 中張牌の面子数

	yk->mentsu_count_manzu    = 0;             // 萬子数
	yk->mentsu_count_pinzu    = 0;             // 筒子数
	yk->mentsu_count_souzu    = 0;             // 索子数
	yk->mentsu_count_zihai    = 0;             // 字牌の数
	yk->mentsu_count_green    = 0;             // 緑牌の数

	// ヒストグラムの初期化
	for(int tmp_i = 0; tmp_i < PAI_MAX; tmp_i++){
		yk->anko_hist[tmp_i]    = 0;
		yk->shuntsu_hist[tmp_i] = 0;
	}

	// -----------------------------
	// 雀頭確認処理
	// -----------------------------

		// -----------------------------
		// 雀頭確認処理
		// -----------------------------

		// 役牌確認
		if (yk->agari_ata_hai == yk->agari_ply_bakaze ||
		    yk->agari_ata_hai == yk->agari_ply_zikaze ||
		    yk->agari_ata_hai == 35 ||
	        yk->agari_ata_hai == 36 ||
		    yk->agari_ata_hai == 37 ){

			// 役牌設定
			yk->agari_ata_19zi = 2; 

			// 面子数の加算
			yk->mentsu_count_19zi++;

		// 一九字牌確認
		}else if (yk->agari_ata_hai == 1 ||
		    yk->agari_ata_hai ==  9 ||
		    yk->agari_ata_hai == 11 ||
	        yk->agari_ata_hai == 19 ||
		    yk->agari_ata_hai == 21 ||
	        yk->agari_ata_hai == 29 ||
		    yk->agari_ata_hai == 31 ||
	        yk->agari_ata_hai == 32 ||
	        yk->agari_ata_hai == 33 ||
		    yk->agari_ata_hai == 34 ){

			// 一九字牌設定
			yk->agari_ata_19zi = 1;

			// 面子数の加算
			yk->mentsu_count_19zi++;

		// 中張牌確認
		}else{

			// 中張牌設定
			yk->agari_ata_19zi = 0;

			// 面子数の加算
			yk->mentsu_count_chunchan++;

		}

		// -----------------------------
		// 萬子・筒子・索子・字牌の枚数確認(雀頭)
		// -----------------------------

		// 萬子加算
		if (yk->agari_ata_hai >  0 &&
		    yk->agari_ata_hai < 10 ){

			// 萬子加算
			yk->mentsu_count_manzu++;

		// 筒子加算
		}else if (yk->agari_ata_hai > 10 &&
		          yk->agari_ata_hai < 20 ){

			// 筒子加算
			yk->mentsu_count_pinzu++;

		// 索子加算
		}else if (yk->agari_ata_hai > 20 &&
		          yk->agari_ata_hai < 30 ){

			// 索子加算
			yk->mentsu_count_souzu++;

		// 字牌加算
		}else if (yk->agari_ata_hai > 30 &&
		          yk->agari_ata_hai < 38 ){

			// 字牌加算
			yk->mentsu_count_zihai++;

		}

	// -----------------------------
	// 緑牌の枚数確認(雀頭)
	// -----------------------------





	// -----------------------------
	// 面子確認処理
	// -----------------------------

	for(int tmp_i = 0; tmp_i < 4; tmp_i++){

		// -----------------------------
		// 一九字確認(メンツ)
		// -----------------------------

		if (yk->agari_men_hai[tmp_i] == yk->agari_ply_bakaze ||
		    yk->agari_men_hai[tmp_i] == yk->agari_ply_zikaze ||
		    yk->agari_men_hai[tmp_i] == 35 ||
	        yk->agari_men_hai[tmp_i] == 36 ||
		    yk->agari_men_hai[tmp_i] == 37 ){

			// 役牌設定
			yk->agari_men_19zi[tmp_i] = 2; 

			// 面子数の加算
			yk->mentsu_count_19zi++;

		}else if (yk->agari_men_hai[tmp_i] == 1 ||
		    yk->agari_men_hai[tmp_i] ==  9 ||
		    yk->agari_men_hai[tmp_i] == 11 ||
	        yk->agari_men_hai[tmp_i] == 19 ||
		    yk->agari_men_hai[tmp_i] == 21 ||
		    yk->agari_men_hai[tmp_i] == 29 ||
		    yk->agari_men_hai[tmp_i] == 31 ||
		    yk->agari_men_hai[tmp_i] == 32 ||
		    yk->agari_men_hai[tmp_i] == 33 ||
		    yk->agari_men_hai[tmp_i] == 34 ){

			// 一九字設定
			yk->agari_men_19zi[tmp_i] = 1; 

			// 面子数の加算
			yk->mentsu_count_19zi++;

		// 789のペンチャンの場合
		}else if((yk->agari_men_stat[tmp_i] == SHUNTSU || yk->agari_men_stat[tmp_i] == MINSHUN) && 
                 (yk->agari_men_hai[tmp_i] == 7  || 
		          yk->agari_men_hai[tmp_i] == 17 || 
		          yk->agari_men_hai[tmp_i] == 27 )){

			// 一九字設定
			yk->agari_men_19zi[tmp_i] = 1; 

			// 面子数の加算
			yk->mentsu_count_19zi++;


		}else{

			// 中張牌設定
			yk->agari_men_19zi[tmp_i] = 0;

			// 面子数の加算
			yk->mentsu_count_chunchan++;

		}

		// -----------------------------
		// 萬子・筒子・索子・字牌の枚数確認(面子)
		// -----------------------------

		// 萬子加算
		if (yk->agari_men_hai[tmp_i] >  0 &&
		    yk->agari_men_hai[tmp_i] < 10 ){

			// 萬子加算
			yk->mentsu_count_manzu++;

		// 筒子加算
		}else if (yk->agari_men_hai[tmp_i] > 10 &&
		          yk->agari_men_hai[tmp_i] < 20 ){

			// 筒子加算
			yk->mentsu_count_pinzu++;

		// 索子加算
		}else if (yk->agari_men_hai[tmp_i] > 20 &&
		          yk->agari_men_hai[tmp_i] < 30 ){

			// 索子加算
			yk->mentsu_count_souzu++;

		// 字牌加算
		}else if (yk->agari_men_hai[tmp_i] > 30 &&
		          yk->agari_men_hai[tmp_i] < 38 ){

			// 字牌加算
			yk->mentsu_count_zihai++;

		}

		// -----------------------------
		// 緑牌の枚数確認
		// -----------------------------




		// -----------------------------
		// 順子・暗刻のヒストグラム設定
		// -----------------------------

		if( yk->agari_men_stat[tmp_i] == SHUNTSU ){

			// 面子種別の加算
			yk->mentsu_count_shuntsu++;

			// ヒストグラム加算
			yk->shuntsu_hist[yk->agari_men_hai[tmp_i]]++;

		}else if(yk->agari_men_stat[tmp_i] == MINSHUN ){

			// 面子種別の加算
			yk->mentsu_count_minshun++;

			// ヒストグラム加算
			yk->shuntsu_hist[yk->agari_men_hai[tmp_i]]++;

		}else if(yk->agari_men_stat[tmp_i] == ANKO){

			// 面子種別の加算
			yk->mentsu_count_anko++;

			// ヒストグラム加算
			yk->anko_hist[yk->agari_men_hai[tmp_i]]++;

		}else if(yk->agari_men_stat[tmp_i] == MINKO){

			// 面子種別の加算
			yk->mentsu_count_minko++;

			// ヒストグラム加算
			yk->anko_hist[yk->agari_men_hai[tmp_i]]++;

		}else if(yk->agari_men_stat[tmp_i] == ANKAN){

			// 面子種別の加算
			yk->mentsu_count_ankan++;

			// ヒストグラム加算
			yk->anko_hist[yk->agari_men_hai[tmp_i]]++;

		}else if(yk->agari_men_stat[tmp_i] == MINKAN){

			// 面子種別の加算
			yk->mentsu_count_minkan++;

			// ヒストグラム加算
			yk->anko_hist[yk->agari_men_hai[tmp_i]]++;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 05:符計算
/* ---------------------------------------------------------------------------------------------- */
void Chk_fu(struct MJSYakuinfo *yk){

	// 符計算
	// https://kinmaweb.jp/mahjong-rule/fukeisan

	// -----------------------------
	// 雀頭の符計算
	// -----------------------------

	// 雀頭の符
	if (yk->agari_ata_19zi == 2){

		// 雀頭の符
		yk->atamaFu = 2;

	}else{

		// 雀頭の符
		yk->atamaFu = 0;

	}

	// -----------------------------
	// 面子の符計算
	// -----------------------------

	// for(int tmp_i = 0; tmp_i < tk->mentu_count; tmp_i++){
	for(int tmp_i = 0; tmp_i < 4; tmp_i++){

		if(yk->agari_men_stat[tmp_i] == ANKO){

			if (yk->agari_men_19zi[tmp_i] == 1 || 
			    yk->agari_men_19zi[tmp_i] == 2 ){

				yk->agari_men_Fu[tmp_i] = 8;

			}else{

				yk->agari_men_Fu[tmp_i] = 4;

			}

		}else if (yk->agari_men_stat[tmp_i] == MINKO){

			if (yk->agari_men_19zi[tmp_i] == 1 || 
			    yk->agari_men_19zi[tmp_i] == 2 ){

				yk->agari_men_Fu[tmp_i] = 4;

			}else{

				yk->agari_men_Fu[tmp_i] = 2;

			}

		}else if (yk->agari_men_stat[tmp_i] == ANKAN){

			if (yk->agari_men_19zi[tmp_i] == 1 || 
			    yk->agari_men_19zi[tmp_i] == 2 ){

				yk->agari_men_Fu[tmp_i] = 32;

			}else{

				yk->agari_men_Fu[tmp_i] = 16;

			}

		}else if (yk->agari_men_stat[tmp_i] == MINKAN){

			if (yk->agari_men_19zi[tmp_i] == 1 || 
			    yk->agari_men_19zi[tmp_i] == 2 ){

				yk->agari_men_Fu[tmp_i] = 16;

			}else{

				yk->agari_men_Fu[tmp_i] = 8;

			}

		}else if ( yk->agari_men_stat[tmp_i] == SHUNTSU || 
                   yk->agari_men_stat[tmp_i] == MINSHUN ){

				yk->agari_men_Fu[tmp_i] = 0;

		}else{

				// デバグ用
				yk->agari_men_Fu[tmp_i] = 99;

		}

	}

	// -----------------------------
	// 面前符
	// -----------------------------

	if(yk->menzen_flg      == true  && 
       yk->tsumo_agari_flg == false ){
		yk->menzenFu=10;
	}else{
		yk->menzenFu=0;
	}

	// -----------------------------
	// 待ち符計算
	// -----------------------------
	if( yk->agari_machi_stat == TANKI || 
	    yk->agari_machi_stat == PENCHAN || 
	    yk->agari_machi_stat == KANCHAN ){

		yk->machiFu=2;

	}else{
		yk->machiFu=0;
	}

	// -----------------------------
	// 自摸符
	// -----------------------------

	if(yk->tsumo_agari_flg == true){
		yk->tsumoFu=2;
	}else{
		yk->tsumoFu=0;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 06:役確認
/* ---------------------------------------------------------------------------------------------- */
void Chk_yaku(struct MJSYakuinfo *yk, int  tehai_hist[]){

	// -----------------------------
	// 初期化
	// -----------------------------
	yk->yakucount     = 0;
	yk->yakuman_count = 0;
	yk->agari_ply_han = 0;
	yk->agari_ply_mangan_count = 0;
	yk->yakuman_agari_ply_bai=0;

	// -----------------------------
	// フラグ初期化
	// -----------------------------

	// 役満
	for(int tmp_i = 0; tmp_i < YAKUMAN_SHUBETSU_MAX; tmp_i++){
		yk->yakuman_flg[tmp_i] = false;
	}

	// 通常役
	for(int tmp_i = 0; tmp_i < YAKU_SHUBETSU_MAX; tmp_i++){
		yk->yaku_flg[tmp_i] = false;
	}

	// -----------------------------
	// 役確認
	// -----------------------------

	ChkYakuRiich(yk);             // リーチ
	ChkYakuChitoiIpeko(yk);       // 七対子、一盃口、二盃口 
	ChkYakuChinItsu_HonItsu(yk);  // 一色
	ChkYakuAnko(yk);              // 暗刻
	ChkYakuChanta(yk);            // チャンタ
	ChkYakuSanshoku(yk);          // 三色
	ChkYakuItsu(yk);              // 一通
	ChkYakuPinfu(yk);             // 平和
	ChkYakuTanyao(yk);            // タンヤオ
	ChkYakuYakuhai(yk);           // 役牌
	ChkYakuDaisangen(yk);         // 大三元・小三元
	ChkYakuDaisushi(yk);          // 大四喜和・小四喜和
	ChkYakuKokushi(yk);           // 国士無双
	ChkYakuChuren(yk,tehai_hist); // 九連宝燈
	ChkYakuTenho(yk);             // 天和
	ChkYakuEtc(yk);               // その他

	// -----------------------------
	// 役テーブル設定
	// -----------------------------

		// 役満確認
		for(int tmp_i = 0; tmp_i < YAKUMAN_SHUBETSU_MAX; tmp_i++){

			// 役設定有無
			if(yk->yakuman_flg[tmp_i] == true){

				// 役テーブル設定
				yk->yakuman_count++;

				// 役満倍の設定
				yk->yakuman_bai[tmp_i] = yakuman_bai[tmp_i];

				// 役満合計倍数カウント
				yk->yakuman_agari_ply_bai = yk->yakuman_agari_ply_bai + yakuman_bai[tmp_i];

			}

		}

	// 通常役
	if( yk->yakuman_count == 0 ){

		// 通常役確認
		for(int tmp_i = 0; tmp_i < YAKU_SHUBETSU_MAX; tmp_i++){

			// 役設定有無
			if(yk->yaku_flg[tmp_i] == true){

				// 役テーブル設定
				yk->yakucount++;

				// 翻数設定
				if(yk->menzen_flg == true){
					// 翻数設定(鳴きなし)
					yk->yaku_han[tmp_i] = yakuhan[tmp_i];
				}else{
					// 翻数設定(鳴きなし)
					yk->yaku_han[tmp_i] = nakihan[tmp_i];
				}

				// 合計翻数のカウント
				yk->agari_ply_han = yk->agari_ply_han + yk->yaku_han[tmp_i];

			}
		}

		// 満貫以上確認
		if (yk->agari_ply_han == 5){
			// 満貫
			yk->agari_ply_mangan_count = 1;
		}else if(yk->agari_ply_han >=6 && yk->agari_ply_han <= 7){
			// 跳満
			yk->agari_ply_mangan_count = 2;
		}else if(yk->agari_ply_han >=8 && yk->agari_ply_han <= 10){
			// 倍満
			yk->agari_ply_mangan_count = 3;
		}else if(yk->agari_ply_han >=11 && yk->agari_ply_han <= 12){
			// 三倍満
			yk->agari_ply_mangan_count = 4;
		}else if(yk->agari_ply_han >=13){
			// 数え役満
			yk->agari_ply_mangan_count = 5;
		}

	}

	// -----------------------------
	// 符の合計(ピンヅモ有無確認後に実行)
	// -----------------------------

	yk->basefu = 20;

	// 符の合計
	yk->totalFu = yk->basefu + 
	yk->agari_men_Fu[0] +
	yk->agari_men_Fu[1] +
	yk->agari_men_Fu[2] +
	yk->agari_men_Fu[3] +
	yk->atamaFu +
	yk->menzenFu +
	yk->machiFu +
	yk->tsumoFu;

	// -----------------------------
	// 符の切り上げ
	// -----------------------------

	if(yk->totalFu % 10 == 0){
		yk->scoreFu = yk->totalFu;
	}else{
		yk->scoreFu = yk->totalFu+10-(yk->totalFu % 10);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 07:得点計算
/* ---------------------------------------------------------------------------------------------- */
void Chk_score(struct MJSYakuinfo *yk){

	// -----------------------------
	// 得点 - 和了得点
	// -----------------------------

	// 自摸和了であるかどうか
	if (yk->tsumo_agari_flg == true){

		// -----------------------------
		// ツモ和了・親
		// -----------------------------
		if (yk->agari_ply_oya_flg == true){

			// 役満の場合
			if( yk->yakuman_count > 0 ){

					// 得点設定
					yk->agari_ply_ron       = 0;
					yk->agari_ply_tsumo_oya = 16000*yk->yakuman_agari_ply_bai;
					yk->agari_ply_tsumo_ko  = 0;

			// 通常役の場合
			}else{

				// 満貫以上
				if(yk->agari_ply_mangan_count > 0){

					// 得点設定
					yk->agari_ply_ron       = 0;
					yk->agari_ply_tsumo_oya = score_mangan_tsumo_oya[yk->agari_ply_mangan_count-1];
					yk->agari_ply_tsumo_ko  = 0;

				// 満貫未満
				}else{
					// 形式確認
					if(yk->agari_stat == AGARI_CHITOI){
						// 得点設定(七対子)
						yk->agari_ply_ron       = 0;
						yk->agari_ply_tsumo_oya = score_chitoi_tsumo_oya[yk->agari_ply_han-1];
						yk->agari_ply_tsumo_ko  = 0;
					}else{
						// 得点設定(通常)
						yk->agari_ply_ron       = 0;
						yk->agari_ply_tsumo_oya = score_tsumo_oya[yk->agari_ply_han-1][(yk->scoreFu-20)/10];
						yk->agari_ply_tsumo_ko  = 0;
					}
				}
			}

		// -----------------------------
		// ツモ和了・子
		// -----------------------------
		}else{

			// 役満の場合
			if( yk->yakuman_count > 0 ){

					// 得点設定
					yk->agari_ply_ron       = 0;
					yk->agari_ply_tsumo_oya = 16000*yk->yakuman_agari_ply_bai;
					yk->agari_ply_tsumo_ko  = 8000*yk->yakuman_agari_ply_bai;

			// 通常役の場合
			}else{

				// 満貫以上
				if(yk->agari_ply_mangan_count > 0){

					// 得点設定
					yk->agari_ply_ron       = 0;
					yk->agari_ply_tsumo_oya = score_mangan_tsumo_oya[yk->agari_ply_mangan_count-1];
					yk->agari_ply_tsumo_ko  = score_mangan_tsumo_ko[yk->agari_ply_mangan_count-1];

				// 満貫未満
				}else{
					// 形式確認
					if(yk->agari_stat == AGARI_CHITOI){
						// 得点設定(七対子)
						yk->agari_ply_ron       = 0;
						yk->agari_ply_tsumo_oya = score_chitoi_tsumo_oya[yk->agari_ply_han-1];
						yk->agari_ply_tsumo_ko  = score_chitoi_tsumo_ko[yk->agari_ply_han-1];
					}else{
						// 得点設定(通常)
						yk->agari_ply_ron       = 0;
						yk->agari_ply_tsumo_oya = score_tsumo_oya[yk->agari_ply_han-1][(yk->scoreFu-20)/10];
						yk->agari_ply_tsumo_ko  = score_tsumo_ko[yk->agari_ply_han-1][(yk->scoreFu-20)/10];
					}
				}
			}
		}

	}else{

		// -----------------------------
		// ロン和了・親
		// -----------------------------
		if (yk->agari_ply_oya_flg == true){

			// 役満の場合
			if( yk->yakuman_count > 0 ){

					// 得点設定
					yk->agari_ply_ron       = 48000*yk->yakuman_agari_ply_bai;
					yk->agari_ply_tsumo_oya = 0;
					yk->agari_ply_tsumo_ko  = 0;

			// 通常役の場合
			}else{

				// 満貫以上
				if(yk->agari_ply_mangan_count > 0){

					// 得点設定
					yk->agari_ply_ron       = score_mangan_ron_oya[yk->agari_ply_mangan_count-1];
					yk->agari_ply_tsumo_oya = 0;
					yk->agari_ply_tsumo_ko  = 0;

				// 満貫未満
				}else{
					// 形式確認
					if(yk->agari_stat == AGARI_CHITOI){
						// 得点設定(七対子)
						yk->agari_ply_ron       = score_chitoi_ron_oya[yk->agari_ply_han-1];
						yk->agari_ply_tsumo_oya = 0;
						yk->agari_ply_tsumo_ko  = 0;
					}else{
						// 得点設定(通常)
						yk->agari_ply_ron       = score_ron_oya[yk->agari_ply_han-1][(yk->scoreFu-20)/10];
						yk->agari_ply_tsumo_oya = 0;
						yk->agari_ply_tsumo_ko  = 0;
					}
				}
			}

		// -----------------------------
		// ロン和了・子
		// -----------------------------
		}else{

			// 役満の場合
			if( yk->yakuman_count > 0 ){

					// 得点設定
					yk->agari_ply_ron       = 32000*yk->yakuman_agari_ply_bai;
					yk->agari_ply_tsumo_oya = 0;
					yk->agari_ply_tsumo_ko  = 0;

			// 通常役の場合
			}else{

				// 満貫以上
				if(yk->agari_ply_mangan_count > 0){

					// 得点設定(満貫)
					yk->agari_ply_ron       = score_mangan_ron_ko[yk->agari_ply_mangan_count-1];
					yk->agari_ply_tsumo_oya = 0;
					yk->agari_ply_tsumo_ko  = 0;

				// 満貫未満
				}else{
					// 形式確認
					if(yk->agari_stat == AGARI_CHITOI){
						// 得点設定(七対子)
						yk->agari_ply_ron       = score_chitoi_tsumo_ko[yk->agari_ply_han-1];
						yk->agari_ply_tsumo_oya = 0;
						yk->agari_ply_tsumo_ko  = 0;
					}else{
						// 得点設定(通常)
						yk->agari_ply_ron       = score_ron_ko[yk->agari_ply_han-1][(yk->scoreFu-20)/10];
						yk->agari_ply_tsumo_oya = 0;
						yk->agari_ply_tsumo_ko  = 0;
					}
				}
			}

		}

	}

	// -----------------------------
	// 得点 - プレーヤーごとの清算
	// -----------------------------

	// 初期化
	yk->kyoku_score[0] = 0;
	yk->kyoku_score[1] = 0;
	yk->kyoku_score[2] = 0;
	yk->kyoku_score[3] = 0;

	// 自摸ロン確認
	if (yk->tsumo_agari_flg == true){

		if (yk->agari_ply_oya_flg == true){

			// ツモ和了・親
			for(int tmp_i = 0; tmp_i < 4; tmp_i++){
				if(tmp_i == yk->agari_ply_num){
					yk->kyoku_score[tmp_i] = yk->agari_ply_tsumo_oya*3;
				}else{
					yk->kyoku_score[tmp_i] = yk->agari_ply_tsumo_oya*(-1);
				}
			}

		}else{

			// ツモ和了・子
			for(int tmp_i = 0; tmp_i < 4; tmp_i++){
				if(tmp_i == yk->agari_ply_num){
					yk->kyoku_score[tmp_i] = yk->agari_ply_tsumo_oya+yk->agari_ply_tsumo_ko*2;
				}else{
					if(yk->ie[tmp_i]==0){
						yk->kyoku_score[tmp_i] = yk->agari_ply_tsumo_oya*(-1);
					}else{
						yk->kyoku_score[tmp_i] = yk->agari_ply_tsumo_ko*(-1);
					}
				}
			}

		}

	}else{

			// ロン和了
			yk->kyoku_score[yk->agari_ply_num] = yk->agari_ply_ron;
			yk->kyoku_score[yk->furikomi_ply_num]  = yk->agari_ply_ron*(-1);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ドラ枚数の確認
/* ---------------------------------------------------------------------------------------------- */
void Chk_tehai_dora_count(struct MJSYakuinfo *yk, int dora_count, int dora[], int ura_dora[]){

	// 初期化
	yk->agari_dora_count = 0; 
	yk->agari_uradora_count = 0;

	// ドラカウント
	for(int tmp_dora_i = 0; tmp_dora_i < dora_count; tmp_dora_i++){

		// 表ドラカウント
		sub_tehai_dora_count(yk, Get_dora_hai(dora[tmp_dora_i]), true);

		// リーチならば、裏ドラカウント
		if(yk->riichi_flg == true){
			sub_tehai_dora_count(yk, Get_dora_hai(ura_dora[tmp_dora_i]), false);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ドラ枚数の確認
/* ---------------------------------------------------------------------------------------------- */
void sub_tehai_dora_count(struct MJSYakuinfo *yk, int dora_hai, bool omote_dora_type){

	// 頭ドラカウント
	if(yk->agari_ata_hai == dora_hai){
		if(omote_dora_type == true){
			yk->agari_dora_count=yk->agari_dora_count+2;
		}else{
			yk->agari_uradora_count=yk->agari_uradora_count+2;
		}
	}

	// 面子ドラカウント
	for(int tmp_i = 0; tmp_i < 4; tmp_i++){

		// アンコの場合
		if ( yk->agari_men_stat[tmp_i] == ANKO    || yk->agari_men_stat[tmp_i] == MINKO  ){

			// ドラカウント
			if(yk->agari_men_hai[tmp_i] == dora_hai){
				if(omote_dora_type == true){
					yk->agari_dora_count=yk->agari_dora_count+3;
				}else{
					yk->agari_uradora_count=yk->agari_uradora_count+3;
				}
			}

		// カンツの場合
		}else if ( yk->agari_men_stat[tmp_i] == ANKAN   || yk->agari_men_stat[tmp_i] == MINKAN ){

			// ドラカウント
			if(yk->agari_men_hai[tmp_i] == dora_hai){
				if(omote_dora_type == true){
					yk->agari_dora_count=yk->agari_dora_count+4;
				}else{
					yk->agari_uradora_count=yk->agari_uradora_count+4;
				}
			}

		// 順子の場合
		}else if ( yk->agari_men_stat[tmp_i] == SHUNTSU || yk->agari_men_stat[tmp_i] == MINSHUN){

			// ドラカウント
			if( yk->agari_men_hai[tmp_i]     == dora_hai ||
			    yk->agari_men_hai[tmp_i] + 1 == dora_hai ||
			    yk->agari_men_hai[tmp_i] + 2 == dora_hai ){
				if(omote_dora_type == true){
					yk->agari_dora_count=yk->agari_dora_count+1;
				}else{
					yk->agari_uradora_count=yk->agari_uradora_count+1;
				};
			}

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ドラ表示牌→ドラ牌の変換
/* ---------------------------------------------------------------------------------------------- */
int Get_dora_hai(int dora_hai){

	// ドラ表示牌→ドラ牌の変換
	if(dora_hai == 9){
		return 1;
	}else if(dora_hai == 19){
		return 11;
	}else if(dora_hai == 29){
		return 21;
	}else if(dora_hai == 34){
		return 31;
	}else if(dora_hai == 37){
		return 35;
	// デバグ用
	}else if(dora_hai < 1 || dora_hai > 37){
		return 0;
	}else{
		return dora_hai+1;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// リーチ系
/* ---------------------------------------------------------------------------------------------- */
void ChkYakuRiich(struct MJSYakuinfo *yk){

	// -----------------------------------------------------------------------
	// 01: リーチ
	// -----------------------------------------------------------------------

	if (yk->riichi_flg == true){
		// 役flg有効化
		yk->yaku_flg[RIICH] = true;
	}

	// -----------------------------------------------------------------------
	// 02: ダブルリーチ
	// -----------------------------------------------------------------------

	if (yk->w_riichi_flg == true){
		// 役flg有効化
		yk->yaku_flg[RIICH]  = false;
		yk->yaku_flg[WRIICH] = true;
	}

	// -----------------------------------------------------------------------
	// 03: 一発
	// -----------------------------------------------------------------------

	if (yk->ippatsu_riichi_flg == true){
		// 役flg有効化
		yk->yaku_flg[IPPATSU] = true;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 七対子、一盃口、二盃口 
/* ---------------------------------------------------------------------------------------------- */
void ChkYakuChitoiIpeko(struct MJSYakuinfo *yk){

	/* ----------------------------------------------------------------------- */
	// 一盃口・二盃口
	/* ----------------------------------------------------------------------- */
	for(int tmp_i = 1; tmp_i < 28; tmp_i++){

		// 二盃口有効化
		if ( yk->shuntsu_hist[tmp_i] > 1 && 
		     yk->menzen_flg == true &&
			 yk->yaku_flg[IPEKO] == true){

			// 二盃口有効化
			yk->yaku_flg[IPEKO] = false;
			yk->yaku_flg[RYANPEKO] = true;
			break;

		// 一盃口の有効化確認
		}else if ( yk->shuntsu_hist[tmp_i] > 1 && yk->menzen_flg == true ){
			// 役flg有効化
			yk->yaku_flg[IPEKO] = true;

		// 七対子の有効化確認
		}else if(yk->agari_stat == AGARI_CHITOI){

			// 役flg有効化
			yk->yaku_flg[CHITOI] = true;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 混一系
/* ---------------------------------------------------------------------------------------------- */
void ChkYakuChinItsu_HonItsu(struct MJSYakuinfo *yk){

	// 通常形式
	if(yk->agari_stat == AGARI_NORMAL){

		// -----------------------------------------------------------------------
		// 04: 清一色
		// -----------------------------------------------------------------------
		if ( yk->mentsu_count_manzu == 5 ||
		     yk->mentsu_count_pinzu == 5 ||
		     yk->mentsu_count_souzu == 5 ){

			// 役flg有効化
			yk->yaku_flg[CHINISO]=true;

		// -----------------------------------------------------------------------
		// 10: 字一色
		// -----------------------------------------------------------------------
		}else if( yk->mentsu_count_zihai == 5){

			// 役flg有効化
			yk->yakuman_flg[TSUISO]=true;

		// -----------------------------------------------------------------------
		// 04: 混一色
		// -----------------------------------------------------------------------
		}else if( yk->mentsu_count_manzu + yk->mentsu_count_zihai == 5 ||
		          yk->mentsu_count_pinzu + yk->mentsu_count_zihai == 5 ||
		          yk->mentsu_count_souzu + yk->mentsu_count_zihai == 5 ){

			// 役flg有効化
			yk->yaku_flg[HONISO]=true;

		// -----------------------------------------------------------------------
		// 12: 緑一色
		// -----------------------------------------------------------------------

		}

	// 七対子形式
	}else if(yk->agari_stat == AGARI_CHITOI){

		// -----------------------------------------------------------------------
		// 04: 清一色
		// -----------------------------------------------------------------------
		if ( yk->mentsu_count_manzu == 7 ||
		     yk->mentsu_count_pinzu == 7 ||
		     yk->mentsu_count_souzu == 7 ){

			// 役flg有効化
			yk->yaku_flg[CHINISO]=true;

		// -----------------------------------------------------------------------
		// 10: 字一色
		// -----------------------------------------------------------------------
		}else if( yk->mentsu_count_zihai == 7){

			// 役flg有効化
			yk->yakuman_flg[TSUISO]=true;

		// -----------------------------------------------------------------------
		// 04: 混一色
		// -----------------------------------------------------------------------
		}else if( yk->mentsu_count_manzu + yk->mentsu_count_zihai == 7 ||
		          yk->mentsu_count_pinzu + yk->mentsu_count_zihai == 7 ||
		          yk->mentsu_count_souzu + yk->mentsu_count_zihai == 7 ){

			// 役flg有効化
			yk->yaku_flg[HONISO]=true;
		}
	}


}

/* ---------------------------------------------------------------------------------------------- */
// 暗刻系
/* ---------------------------------------------------------------------------------------------- */
void ChkYakuAnko(struct MJSYakuinfo *yk){

	// -----------------------------------------------------------------------
	// 役満14: 四槓子
	// -----------------------------------------------------------------------
	if ( yk->mentsu_count_ankan  +
	     yk->mentsu_count_minkan == 4 ){

		// 役flg有効化
		yk->yakuman_flg[SUKANTSU] = true;

	}

	// -----------------------------------------------------------------------
	// 13: 三槓子
	// -----------------------------------------------------------------------
	if ( yk->mentsu_count_ankan  +
	     yk->mentsu_count_minkan == 3 ){

		// 役flg有効化
		yk->yaku_flg[SANKANTSU] = true;

	}

	// -----------------------------------------------------------------------
	// 役満15: 四暗刻
	// -----------------------------------------------------------------------
	if ( yk->mentsu_count_anko  +
	     yk->mentsu_count_ankan == 4 ){

		// 役flg有効化
		yk->yakuman_flg[SUANKO]=true;

	}

	// -----------------------------------------------------------------------
	// 14: 三暗刻
	// -----------------------------------------------------------------------
	if ( yk->mentsu_count_anko  +
	     yk->mentsu_count_ankan == 3 ){

		// 役flg有効化
		yk->yaku_flg[SANANKO] = true;

	}

	// -----------------------------------------------------------------------
	// 15: 対々和
	// -----------------------------------------------------------------------
	if ( yk->mentsu_count_anko  +
	     yk->mentsu_count_minko +
	     yk->mentsu_count_ankan +
	     yk->mentsu_count_minkan == 4 ){

		// 役flg有効化
		yk->yaku_flg[TOITOI] = true;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 純全帯
/* ---------------------------------------------------------------------------------------------- */
void ChkYakuChanta(struct MJSYakuinfo *yk){


	// 通常形式
	if(yk->agari_stat == AGARI_NORMAL){

		/* ----------------------------------------------------------------------- */
		// チャンタ系(通常役)
		/* ----------------------------------------------------------------------- */
		if (yk->mentsu_count_19zi == 5){
			// 全てアンコの場合
			if ( yk->mentsu_count_anko  +
			     yk->mentsu_count_minko +
			     yk->mentsu_count_ankan +
			     yk->mentsu_count_minkan == 4 ){
				// 字牌数確認
				if(yk->mentsu_count_zihai == 0){
					// 役flg有効化
					yk->yaku_flg[JUNCHAN] = true;
				}else{
					// 役flg有効化
					yk->yaku_flg[CHANTA] = true;
				}
			// 順子がある場合
			}else{
				// 字牌数確認
				if(yk->mentsu_count_zihai == 0){
					// 役flg有効化
					yk->yakuman_flg[CHINROTO]=true;
				}else{
					// 役flg有効化
					yk->yaku_flg[HONROTO] = true;
				}
			}
		}

	// 七対子形式
	}else if(yk->agari_stat == AGARI_CHITOI){

		/* ----------------------------------------------------------------------- */
		// チャンタ系(七対子)
		/* ----------------------------------------------------------------------- */
		if (yk->mentsu_count_19zi == 7){
			// 役flg有効化
			yk->yaku_flg[HONROTO] = true;
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 三色系
/* ---------------------------------------------------------------------------------------------- */
void ChkYakuSanshoku(struct MJSYakuinfo *yk){

	// -----------------------------------------------------------------------
	// 11: 三色同刻
	// 12: 三色同順
	// -----------------------------------------------------------------------
	for(int i = 0; i < 9; i++){

		// 三色同刻確認
		if ( yk->shuntsu_hist[1+i]  > 0 &&
		     yk->shuntsu_hist[11+i] > 0 &&
		     yk->shuntsu_hist[21+i] > 0 ){

			// 役flg有効化
			yk->yaku_flg[SANDOJUN] = true;

		}

		// 三色同刻確認
		if ( yk->anko_hist[1+i]  > 0 &&
		     yk->anko_hist[11+i] > 0 &&
		     yk->anko_hist[21+i] > 0 ){

			// 役flg有効化
			yk->yaku_flg[SANDOKOU] = true;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 一通系
/* ---------------------------------------------------------------------------------------------- */
void ChkYakuItsu(struct MJSYakuinfo *yk){

	// -----------------------------------------------------------------------
	// 10: 一気通貫
	// -----------------------------------------------------------------------
	for(int i = 0; i < 3; i++){
		if ( yk->shuntsu_hist[1+10*i] > 0 &&
		     yk->shuntsu_hist[4+10*i] > 0 &&
		     yk->shuntsu_hist[7+10*i] > 0 ){

			// 役flg有効化
			yk->yaku_flg[ITSU] = true;

		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 平和系
/* ---------------------------------------------------------------------------------------------- */
void ChkYakuPinfu(struct MJSYakuinfo *yk){

	// -----------------------------------------------------------------------
	// 10: 平和
	// -----------------------------------------------------------------------

	// 鳴き確認
	if(yk->menzen_flg == false ){
		return ;
	}

	// 順子数の確認
	if( (yk->mentsu_count_shuntsu != 4 ) && 
	    (yk->mentsu_count_shuntsu != 3 || yk->mentsu_count_minshun != 1 )
	){
		return ;
	}

	// 雀頭の役牌確認→agari_ata_19zi=2の場合は平和にならない
	if( yk->agari_ata_19zi == 2){
		return ;
	}

	// 両面の確認
	if(yk->agari_machi_stat != RYANMEN ){
		return ;
	}

	// 役flg有効化
	yk->yaku_flg[PINFU] = true;

	// 平和の自摸符は0符
	yk->tsumoFu=0;

}

/* ---------------------------------------------------------------------------------------------- */
// タンヤオ系
/* ---------------------------------------------------------------------------------------------- */
void ChkYakuTanyao(struct MJSYakuinfo *yk){

	/* ----------------------------------------------------------------------- */
	// 10: タンヤオ
	/* ----------------------------------------------------------------------- */
	if (yk->mentsu_count_chunchan == 5){

		// 役flg有効化
		yk->yaku_flg[TANYAO] = true;

	}
}


/* ---------------------------------------------------------------------------------------------- */
// 役牌系
/* ---------------------------------------------------------------------------------------------- */
void ChkYakuYakuhai(struct MJSYakuinfo *yk){

	// -----------------------------------------------------------------------
	// 21: 場風牌
	// -----------------------------------------------------------------------
	if ( yk->anko_hist[yk->agari_ply_bakaze] > 0 ){

		// 役flg有効化
		yk->yaku_flg[BAKAZE] = true;

	}

	/* ----------------------------------------------------------------------- */
	// 22: 自風牌
	/* ----------------------------------------------------------------------- */
	if ( yk->anko_hist[yk->agari_ply_zikaze] > 0 ){

		// 役flg有効化
		yk->yaku_flg[ZIKAZE] = true;

	}

	// -----------------------------------------------------------------------
	// 23: 三元牌白
	// -----------------------------------------------------------------------
	if ( yk->anko_hist[HAKUNUM] > 0 ){

		// 役flg有効化
		yk->yaku_flg[YAKUHAIHAKU] = true;

	}

	// -----------------------------------------------------------------------
	// 24: 三元牌発
	// -----------------------------------------------------------------------
	if ( yk->anko_hist[HATSUNUM] > 0 ){

		// 役flg有効化
		yk->yaku_flg[YAKUHAIHATSU] = true;

	}

	// -----------------------------------------------------------------------
	// 25: 三元牌中
	// -----------------------------------------------------------------------
	if ( yk->anko_hist[CHUNNUM] > 0){

		// 役flg有効化
		yk->yaku_flg[YAKUHAICHUN] = true;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 大三元・小三元
/* ---------------------------------------------------------------------------------------------- */
void ChkYakuDaisangen(struct MJSYakuinfo *yk){

	/* ----------------------------------------------------------------------- */
	// 小三元・白(HAKUNUM)アタマ
	/* ----------------------------------------------------------------------- */
	if (( yk->agari_ata_hai == HAKUNUM ) &&
		( yk->anko_hist[HATSUNUM] > 0 ) &&
		( yk->anko_hist[CHUNNUM]  > 0 ) ){

		// 役flg有効化
		yk->yaku_flg[SHOSANGEN]=true;
	}

	/* ----------------------------------------------------------------------- */
	// 小三元・発(HAKUNUM)アタマ
	/* ----------------------------------------------------------------------- */
	if (( yk->agari_ata_hai == HATSUNUM ) &&
		( yk->anko_hist[HAKUNUM] > 0 ) &&
		( yk->anko_hist[CHUNNUM]  > 0 ) ){

		// 役flg有効化
		yk->yaku_flg[SHOSANGEN]=true;
	}

	/* ----------------------------------------------------------------------- */
	// 小三元・中(HAKUNUM)アタマ
	/* ----------------------------------------------------------------------- */
	if (( yk->agari_ata_hai == CHUNNUM ) &&
		( yk->anko_hist[HAKUNUM]   > 0 ) &&
		( yk->anko_hist[HATSUNUM]  > 0 ) ){

		// 役flg有効化
		yk->yaku_flg[SHOSANGEN]=true;
	}

	/* ----------------------------------------------------------------------- */
	// 大三元
	/* ----------------------------------------------------------------------- */
	if (( yk->anko_hist[HAKUNUM]  > 0 ) &&
		( yk->anko_hist[HATSUNUM] > 0 ) &&
		( yk->anko_hist[CHUNNUM]  > 0 ) ){

		// 役flg有効化
		yk->yakuman_flg[DAISANGEN]=true;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 大四喜和・小四喜和
/* ---------------------------------------------------------------------------------------------- */
void ChkYakuDaisushi(struct MJSYakuinfo *yk){

	/* ----------------------------------------------------------------------- */
	// 小四喜和・東アタマ
	/* ----------------------------------------------------------------------- */

	if (( yk->agari_ata_hai == TONNUM ) &&
		( yk->anko_hist[NANNUM] > 0 ) &&
		( yk->anko_hist[SHANUM] > 0 ) &&
		( yk->anko_hist[PEINUM] > 0 ) ){

		// 役flg有効化
		yk->yakuman_flg[SHOSUSHI]=true;

	}

	/* ----------------------------------------------------------------------- */
	// 小四喜和・南アタマ
	/* ----------------------------------------------------------------------- */

	if (( yk->agari_ata_hai == NANNUM ) &&
		( yk->anko_hist[TONNUM] > 0 ) &&
		( yk->anko_hist[SHANUM] > 0 ) &&
		( yk->anko_hist[PEINUM] > 0 ) ){

		// 役flg有効化
		yk->yakuman_flg[SHOSUSHI]=true;

	}

	/* ----------------------------------------------------------------------- */
	// 小四喜和・西アタマ
	/* ----------------------------------------------------------------------- */

	if (( yk->agari_ata_hai == SHANUM ) &&
		( yk->anko_hist[TONNUM] > 0 ) &&
		( yk->anko_hist[NANNUM] > 0 ) &&
		( yk->anko_hist[PEINUM] > 0 ) ){

		// 役flg有効化
		yk->yakuman_flg[SHOSUSHI]=true;

	}

	/* ----------------------------------------------------------------------- */
	// 小四喜和・北アタマ
	/* ----------------------------------------------------------------------- */

	if (( yk->agari_ata_hai == PEINUM ) &&
		( yk->anko_hist[TONNUM] > 0 ) &&
		( yk->anko_hist[NANNUM] > 0 ) &&
		( yk->anko_hist[SHANUM] > 0 ) ){

		// 役flg有効化
		yk->yakuman_flg[SHOSUSHI]=true;

	}

	// -----------------------------------------------------------------------
	// 役満07: 大四喜和
	// -----------------------------------------------------------------------

	if (( yk->anko_hist[TONNUM] > 0 ) &&
		( yk->anko_hist[NANNUM] > 0 ) &&
		( yk->anko_hist[SHANUM] > 0 ) &&
		( yk->anko_hist[PEINUM] > 0 ) ){

		// 役flg有効化
		yk->yakuman_flg[DAISUSHI]=true;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 国士無双
/* ---------------------------------------------------------------------------------------------- */
void ChkYakuKokushi(struct MJSYakuinfo *yk){
/*
	// 手配形式が国士であるのか？
	if(yk->agari_stat == AGARI_KOKUSHI){
		// 13面確認
		if ( yk->ply_act_tehai[yk->agari_hai] > 0){
			// 役flg有効化
			yk->yakuman_flg[KOKUSHI13MEN] = true;
		}else{
			// 役flg有効化
			yk->yakuman_flg[KOKUSHI] = true;
		}
	}
*/
}

/* ---------------------------------------------------------------------------------------------- */
// 九連宝燈
/* ---------------------------------------------------------------------------------------------- */
void ChkYakuChuren(struct MJSYakuinfo *yk, int tehai_hist[]){

	// 変数設定
	bool agari_flg;

	/* ----------------------------------------------------------------------- */
	// 役満03: 九連宝燈・萬子
	/* ----------------------------------------------------------------------- */

	// 和了フラグ初期化
	agari_flg = true;

	// 雀頭と面子4枚がすべて同一の索子であること
	if ( yk->mentsu_count_manzu != 5){
		agari_flg = false ;
	}

	// 一牌と九牌が3枚以上あること
    if ( (tehai_hist[MAN1NUM] < 3) || 
	     (tehai_hist[MAN9NUM] < 3) ){
		agari_flg = false ;
	}

	// 一牌から九牌まで全て揃っていること
	for (int tmp_i = 1; tmp_i < 10; tmp_i++) {
        if (tehai_hist[tmp_i] == 0){
			agari_flg = false ;
		}
    }

	// 和了確認
	if (agari_flg == true){

		// 役flg有効化
		yk->yakuman_flg[CHUREN]=true;

	}

	/* ----------------------------------------------------------------------- */
	// 役満03: 九連宝燈・筒子
	/* ----------------------------------------------------------------------- */

	// 和了フラグ初期化
	agari_flg = true;

	// 雀頭と面子4枚がすべて同一の索子であること
	if ( yk->mentsu_count_pinzu != 5){
		agari_flg = false ;
	}

	// 一牌と九牌が3枚以上あること
    if ( (tehai_hist[PIN1NUM] < 3) || 
	     (tehai_hist[PIN9NUM] < 3) ){
		agari_flg = false ;
	}

	// 一牌から九牌まで全て揃っていること
	for (int tmp_i = 11; tmp_i < 20; tmp_i++) {
        if (tehai_hist[tmp_i] == 0){
			agari_flg = false ;
		}
    }

	// 和了確認
	if (agari_flg == true){

		// 役flg有効化
		yk->yakuman_flg[CHUREN]=true;

	}

	/* ----------------------------------------------------------------------- */
	// 役満03: 九連宝燈・索子
	/* ----------------------------------------------------------------------- */

	// 和了フラグ初期化
	agari_flg = true;

	// 雀頭と面子4枚がすべて同一の索子であること
	if ( yk->mentsu_count_souzu != 5){
		agari_flg = false ;
	}

	// 一牌と九牌が3枚以上あること
    if ( (tehai_hist[SOU1NUM] < 3) || 
	     (tehai_hist[SOU9NUM] < 3) ){

		// 和了フラグ無効化
		agari_flg = false ;
	}

	// 一牌から九牌まで全て揃っていること
	for (int tmp_i = 21; tmp_i < 30; tmp_i++) {
        if (tehai_hist[tmp_i] == 0){
			agari_flg = false ;
		}
    }

	// 和了確認
	if (agari_flg == true){

		// 役flg有効化
		yk->yakuman_flg[CHUREN]=true;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 天和
/* ---------------------------------------------------------------------------------------------- */
void ChkYakuTenho(struct MJSYakuinfo *yk){

	// -----------------------------------------------------------------------
	// 役満01: 天和
	// -----------------------------------------------------------------------
	if(yk->agari_ply_tsumo_count == 1 && yk->tsumo_agari_flg == true){

		// 役flg有効化
		// yk->yakuman_flg[TENHO]=true;

	}

	// -----------------------------------------------------------------------
	// 役満02: 地和
	// -----------------------------------------------------------------------
	if(yk->agari_ply_tsumo_count == 0 && yk->tsumo_agari_flg == false){

		// 役flg有効化
		// yk->yakuman_flg[CHIHO]=true;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// その他処理
/* ---------------------------------------------------------------------------------------------- */
void ChkYakuEtc(struct MJSYakuinfo *yk){

	// -----------------------------------------------------------------------
	// 29: 門前清自摸和
	// -----------------------------------------------------------------------

	if(yk->tsumo_agari_flg == true && 
	   yk->menzen_flg      == true ){

		// 役flg有効化
		yk->yaku_flg[TSUMO] = true;

	}

	// -----------------------------
	// 31: ドラ
	// -----------------------------
	if( yk->agari_dora_count > 0 ){

		// 役flg有効化
		yk->yaku_flg[DORA] = true;

		// 翻数設定
		yakuhan[DORA] = yk->agari_dora_count;
		nakihan[DORA] = yakuhan[DORA];

	}

	// -----------------------------
	// 32: 裏ドラ
	// -----------------------------
	if( yk->agari_uradora_count > 0 ){

		// 役flg有効化
		yk->yaku_flg[URADORA] = true;

		// 翻数設定
		yakuhan[URADORA] = yk->agari_uradora_count;
		nakihan[URADORA] = yakuhan[URADORA];

	}

	// -----------------------------
	// 33: 赤牌
	// -----------------------------
	if(yk->agari_aka_count[0] > 0 ||
	   yk->agari_aka_count[1] > 0 ||
	   yk->agari_aka_count[2] > 0 ){

		// 役flg有効化
		yk->yaku_flg[AKAHAI] = true;

		// 翻数設定
		yakuhan[AKAHAI] = yk->agari_aka_count[0] + 
		                  yk->agari_aka_count[1] +
		                  yk->agari_aka_count[2] ;
		nakihan[AKAHAI] = yakuhan[AKAHAI];

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 荒牌時得点設定
/* ---------------------------------------------------------------------------------------------- */
void SetHowanpaiScore(struct MJSYakuinfo *yk){

	// -----------------------------------------------------------
	// ステータス定義
	// -----------------------------------------------------------
	yk->ryukyoku_stat = HOWANPAI;

	// -----------------------------------------------------------
	// 得点設定
	// -----------------------------------------------------------
	for(int tmp_num = 0; tmp_num< PLAYER_MAX; tmp_num++){
		if(yk->ply_tempai_count == 0 || yk->ply_tempai_count == 4){
			yk->kyoku_score[tmp_num] = 0;
		}else if(yk->ply_tempai_count == 1 && yk->ply_tempai_flg[tmp_num] == true){
			yk->kyoku_score[tmp_num] = 3000;
		}else if(yk->ply_tempai_count == 1 && yk->ply_tempai_flg[tmp_num] == false){
			yk->kyoku_score[tmp_num] = -1000;
		}else if(yk->ply_tempai_count == 2 && yk->ply_tempai_flg[tmp_num] == true){
			yk->kyoku_score[tmp_num] = 1500;
		}else if(yk->ply_tempai_count == 2 && yk->ply_tempai_flg[tmp_num] == false){
			yk->kyoku_score[tmp_num] = -1500;
		}else if(yk->ply_tempai_count == 3 && yk->ply_tempai_flg[tmp_num] == true){
			yk->kyoku_score[tmp_num] = 1000;
		}else if(yk->ply_tempai_count == 3 && yk->ply_tempai_flg[tmp_num] == false){
			yk->kyoku_score[tmp_num] = -3000;
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
