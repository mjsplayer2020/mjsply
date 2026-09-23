/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： mjsply：Mjaiクライアント
 * バージョン     ： 1.0.0.0.0(アーカイブFix版)
 * プログラム名   ： mjs
 * ファイル名     ： player.c
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

#include "player.h"

/* ---------------------------------------------------------------------------------------------- */
// 卓開始処理
/* ---------------------------------------------------------------------------------------------- */
void PlyActTakuStart(int tmp_ply_id, int tmp_init_score, int tmp_aka_man_max, int tmp_aka_pin_max, int tmp_aka_sou_max){

	// ----------------------------------------
	// 内部変数初期化
	// ----------------------------------------

	// 結果表示モードの設定
	// print_ply_mode = 999;
	print_ply_mode = 0;

	// プレーヤタイプ設定
	ply_type = PLYCHAR_MOMIJI;  // アーカイブ用

	// 局INDEX初期化
	kyoku_index = 0;

	// ----------------------------------------
	// プレーヤ番号
	// ----------------------------------------

	// 自分のプレーヤ番号を設定
	ply_id = tmp_ply_id;

	// 下家のプレーヤ番号を設定
	ply_id_shimo = ( tmp_ply_id + 3 ) % 4;

	// ----------------------------------------
	// 赤牌情報定義
	// ----------------------------------------

	// 赤牌最大数の設定
	max_aka_count[0] = tmp_aka_man_max;
	max_aka_count[1] = tmp_aka_pin_max;
	max_aka_count[2] = tmp_aka_sou_max;

	// ----------------------------------------
	// 得点設定
	// ----------------------------------------

	// 局開始得点設定
	for(int tmp_ply = 0; tmp_ply < PLAYER_MAX; tmp_ply++){
		ply_kyoku_score[tmp_ply] = tmp_init_score;
	}

	// ----------------------------------------
	// 結果表示
	// ----------------------------------------

	// バージョン情報
	print_version_info();

	// 卓開始情報
	print_taku_start();

}

/* ---------------------------------------------------------------------------------------------- */
// 局開始処理
/* ---------------------------------------------------------------------------------------------- */
void PlyActKyokuStart(int tmp_kaze, int tmp_kyoku, int tmp_honba, int tmp_riichibo, int tmp_ie, bool tmp_score_flg, int tmp_score[], int tmp_dora_marker){

	// ----------------------------------------
	// 値設定
	// ----------------------------------------

	// 家情報
	for(int tmp_i=0; tmp_i< PLAYER_MAX; tmp_i++){   
		ie[(( ply_id + tmp_i ) % 4)] = ( tmp_ie + tmp_i ) % 4;
	}

	// 局情報
	kyoku = tmp_kyoku;                  // 局
	honba = tmp_honba;                  // 本場
	riichibo = tmp_riichibo;            // リーチ棒
	ply_bakaze = tmp_kaze;              // 場風の牌番号
	ply_zikaze = TONNUM + ie[ply_id];   // 自風の牌番号

	// ドラ情報
	dora_count = 1;
	dora_marker[0] = tmp_dora_marker;             // ドラ表示牌
	// dora_marker_aka[0] = tmp_dora_marker_aka   // ドラ表示牌赤(残牌枚数を数える際に利用)
	dora_hai[0] = Get_dora_hai(tmp_dora_marker);  // ドラ牌(ドラ表示牌ではない)

	// ----------------------------------------
	// 変数初期化
	// ----------------------------------------

	// 残り枚数(自摸合計数)
	kyoku_tsumo_count = 0;

	// 配牌初期化
	for(int i=0; i< PAI_MAX; i++){
		tehai[i] = 0;                 // 手牌
		open_haiparts_count[i] = 0;   // 表示牌枚数
	}

	// 赤牌初期化
	aka_count[0] = 0;
	aka_count[1] = 0;
	aka_count[2] = 0;

	// プレーヤ変数の初期化
	ply_act       = NOACT;
	ply_tsumo_hai = 0;
	ply_sute_hai  = 0;

	// 鳴き枚数
	naki_count  = 0;
	ankan_count = 0;
	kakan_count = 0;

	// リーチ状態の初期化
	ply_riichi_mode = 0;

	// 向聴の初期化
	shanten_normal  = 8;
	shanten_kokushi = 8;
	shanten_chitoi  = 8;

	// 捨牌候補数
	sutekoho_count  = 0;

	// 鳴き候補テーブル
	nakikoho_tbl_count = 0;
	ply_tehai_naki_stat = false;
	ply_yakuhai_stat = false;

	// 鳴きアクション
	ply_naki_idx = 0;
	ply_naki_aka_count = 0;

	// 河情報、リーチ情報
	ply_riichi_stat_count = 0;
	for(int tmp_ply = 0; tmp_ply < PLAYER_MAX; tmp_ply++){

		// 河枚数
		ply_kawa_count[tmp_ply]  = 0;

		// リーチ状態
		ply_riichi_stat[tmp_ply] = false;

		// リーチ時の捨牌巡目
		for(int tmp_ply2 = 0; tmp_ply2 < PLAYER_MAX; tmp_ply2++){
			postriichi_turn_count[tmp_ply][tmp_ply2] = 999;
		}

		// スジ壁情報
		for(int tmp_i = 0; tmp_i < AKA_TYPE_MAX_COUNT; tmp_i++){

			// スジ初期化
			for(int tmp_j = 0; tmp_j < 7; tmp_j++){
				suzi[tmp_ply][tmp_i][tmp_j] = false;
				urasuzi[tmp_ply][tmp_i][tmp_j] = false;
			}

			// 壁初期化
			for(int tmp_j = 0; tmp_j < 4; tmp_j++){
				kabe[tmp_ply][tmp_i][tmp_j] = false;
			}

			// 間四軒初期化
			for(int tmp_j = 0; tmp_j < 6; tmp_j++){
				aidayonken[tmp_ply][tmp_i][tmp_j] = false;
			}

		}

	}

	// オリ状態
	ply_tehai_ori_stat = false;   // オリ状態
	ply_ori_algo_num = 0;         // オリアルゴリズム番号
	orihai_count = 0;             // オリ牌枚数

	// 得点情報更新
	if(tmp_score_flg == true){
		for(int tmp_ply = 0; tmp_ply < PLAYER_MAX; tmp_ply++){
			ply_kyoku_score[tmp_ply] = tmp_score[tmp_ply];
		}
	}

	// 仮向聴テーブル初期化
	karitbl_count      = 0;
	karitbl_calc_count = 0;

	// ----------------------------------------
	// 結果表示：局開始処理
	// ----------------------------------------
	print_kyoku_start();

}

/* ---------------------------------------------------------------------------------------------- */
// 局終了処理
/* ---------------------------------------------------------------------------------------------- */
void PlyActKyokuEnd(){

	// 局INDEX+1
	kyoku_index++;

}

/* ---------------------------------------------------------------------------------------------- */
// 配牌処理
/* ---------------------------------------------------------------------------------------------- */
void PlyActHaipai(int tmp_tsumo_hai, bool tmp_tsumo_aka){

	// ヒストグラムに牌の枚数を加算
	tehai[tmp_tsumo_hai]++;

	// 表示牌の加算
	open_haiparts_count[tmp_tsumo_hai]++;

	// 赤牌有無
	if(tmp_tsumo_aka == true){
		aka_count[(tmp_tsumo_hai-5)/10]++;
	}

	// ----------------------------------------
	// 結果表示
	// ----------------------------------------
	if( print_ply_mode > 0){
		// 配牌情報の表示
		print_haipai(tmp_tsumo_hai, tmp_tsumo_aka);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 配牌後の確認処理
/* ---------------------------------------------------------------------------------------------- */
void PlyActPostHaipai(){

	// 自摸無し時の向聴数確認
	ChkTsumoNashiShanten();

	// プレーヤの手牌ステータス更新
	PlyChkPlyStat();

	// ----------------------------------------
	// 結果表示
	// ----------------------------------------
	if( print_ply_mode > 0){

		// 手牌表示(ライン表示)
		print_tehai_line();

		// 手牌表示
		// print_tehai_hist();

		// 赤牌情報
		print_tehai_aka();

		// 自摸無し手牌詳細情報
		print_tsumonashi_tehai_info();

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 自摸処理
/* ---------------------------------------------------------------------------------------------- */
void PlyActTsumo(struct MJSPlyInfo *pinfo, int tmp_tsumo_hai, bool tmp_tsumo_aka){

	// 時間測定1
	// action_timestamp1 = GetTickCount();

	// ----------------------------------------
	// アクション設定
	// ----------------------------------------

	// 自摸アクションの設定
	ply_act = ACTTSUMO;

	// 自摸アクションの設定
	ply_tsumo_hai = tmp_tsumo_hai;
	ply_tsumo_aka = tmp_tsumo_aka;

	// 表示牌の加算
	open_haiparts_count[tmp_tsumo_hai]++;

	// 自摸回数カウント
	kyoku_tsumo_count++;

	// ----------------------------------------
	// 結果表示：手牌、自摸牌
	// ----------------------------------------
	if( print_ply_mode > 0){

		// 手牌表示(ライン表示)
		print_tehai_line();

		// 手牌ヒストグラム表示
		// print_tehai_hist();

		// 赤牌情報
		print_tehai_aka();

		// 自摸牌情報
		print_tsumo_hai();

	}

	// ----------------------------------------
	// 捨牌設定
	// ----------------------------------------

	// 自摸有の向聴算出
	ChkTsumoAriShanten();

	// 捨牌決定
	// PlyChkAISutehai();

	// オリ状態の確認
	PlyChkTehaiOri();

	// ----------------------------------------
	// 結果表示：自摸有り手牌情報
	// ----------------------------------------
	if( print_ply_mode > 0){
		// 自摸有り手牌情報詳細
		print_tsumoari_tehai_info();
		// オリ情報
		print_ori_info();
	}

	// ----------------------------------------
	// 自摸和了確認
	// ----------------------------------------
	if (shanten_normal == -1){

		 // 鳴いていない
		if(naki_count - ankan_count == 0){

			// アクション決定(自摸和了)
			ply_act = ACTTSUMOAGARI;

		}else{

			// 和了役があるなら
			if(ply_tehai_yaku_stat==true){
				// アクション決定(自摸和了)
				ply_act = ACTTSUMOAGARI;
			}else{
				// アクション決定(自摸切り)
				ply_act = ACTTSUMOGIRI;
			}

		}

	}else{

		// ----------------------------------------
		// リーチ確定状態ならそのまま自摸切り
		// ----------------------------------------
		if (ply_riichi_mode == 2){

			// アクション決定(自摸切り)
			ply_act = ACTTSUMOGIRI;

			// 捨牌確定
			ply_sute_hai=ply_tsumo_hai;

		// ----------------------------------------
		// リーチ確定でない場合のアクション決定
		// ----------------------------------------
		}else{

			if(kyoku_tsumo_count != 70){                  // 鳴きタイミングがラス牌でないのか？

				// アクション確認 - 暗槓
				// MJAIの不具合により、暗槓アクションをしない
				// if (ply_act == ACTTSUMO){
				//	PlyChkAnkan(tmp_tsumo_hai, tmp_tsumo_aka);
				// }

				// アクション確認 - 加槓
				if (ply_act == ACTTSUMO){
					PlyChkKakan(tmp_tsumo_hai, tmp_tsumo_aka);
				}

			}

			// アクション確認 - 捨牌
			if (ply_act == ACTTSUMO){
				PlyChkTsumoSute();
			}

		}
	}

	// (デバグ用)自摸切りアクション
	// ply_act = ACTTSUMOGIRI;
	// ply_sute_hai = ply_tsumo_hai;
	// ply_sute_aka = ply_tsumo_aka;

	// ----------------------------------------
	// pinfo定義：自摸和了の場合
	// ----------------------------------------
	if ( ply_act == ACTTSUMOAGARI){

		// pinfo定義
		if(ply_tsumo_aka == true){
			// 赤牌設定
			set_pinfo(pinfo, ply_act, ply_tsumo_hai, ply_tsumo_hai, 1);
		}else{
			set_pinfo(pinfo, ply_act, ply_tsumo_hai, ply_tsumo_hai, 0);
		}

	// ----------------------------------------
	// pinfo定義：暗槓の場合
	// ----------------------------------------
	}else if( ply_act == ACTANKAN){

		// pinfo定義
		if( ply_naki_idx == MAN5NUM || 
		    ply_naki_idx == PIN5NUM || 
		    ply_naki_idx == SOU5NUM ){
			// カン時の赤牌最大数
			set_pinfo(pinfo, ply_act, ply_naki_idx, ply_naki_idx, max_aka_count[(ply_naki_idx-5)/10]);
		}else{
			// 赤牌なし
			set_pinfo(pinfo, ply_act, ply_naki_idx, ply_naki_idx, 0);
		}

	// ----------------------------------------
	// pinfo定義：加槓の場合
	// ----------------------------------------
	}else if( ply_act == ACTKAKAN){

		// pinfo定義：加槓の場合
		set_pinfo(pinfo, ply_act, ply_naki_idx, ply_naki_idx, ply_naki_aka_count);

	// ----------------------------------------
	// pinfo定義：捨牌、自摸切り
	// ----------------------------------------
	}else{

		// pinfo定義：捨牌、自摸切り
		if(ply_sute_aka == true){
			set_pinfo(pinfo, ply_act, ply_sute_hai, ply_sute_hai, 1);
		}else{
			set_pinfo(pinfo, ply_act, ply_sute_hai, ply_sute_hai, 0);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 暗槓確認
/* ---------------------------------------------------------------------------------------------- */
void PlyChkAnkan(int tmp_tsumo_hai, bool tmp_tsumo_aka){

	// 枚数確認
	for( int tmp_i=0; tmp_i < PAI_MAX; tmp_i++ ){

		// 自摸で4枚揃ったら、暗槓
		if ( (tehai[tmp_i] >= 3 && tmp_tsumo_hai == tmp_i) ||
		      tehai[tmp_i] >= 4 ){

			// ----------------------------------------
			// アクション設定 - 暗槓
			// ----------------------------------------

			// 暗槓牌設定
			ply_naki_idx = tmp_i;

			// 暗槓処理
			ply_act = ACTANKAN;

			// 処理を抜ける(暗槓は1回しかできないため)
			break ;

		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 加槓確認
/* ---------------------------------------------------------------------------------------------- */
void PlyChkKakan(int tmp_tsumo_hai, bool tmp_tsumo_aka){

	// 処理開始
	for( int tmp_i=0; tmp_i < naki_count; tmp_i++ ){

		// ツモ牌が明刻の鳴き牌と同じであれば
		if(naki_stat[tmp_i] == MINKO && naki_hai[tmp_i] == tmp_tsumo_hai){

			// 加槓牌設定
			ply_naki_idx = tmp_tsumo_hai;

			// 加槓赤
			if(tmp_tsumo_aka == true){
				ply_naki_aka_count=1;
			}else{
				ply_naki_aka_count=0;
			}

			// 加槓処理
			ply_act = ACTKAKAN;

			// 処理を抜ける(加槓は1回しかできないため)
			break ;

		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 自摸捨牌確認
/* ---------------------------------------------------------------------------------------------- */
void PlyChkTsumoSute(){

	// オリ状態確認(「オリモードである」且つ「リーチ宣言していない」)
	if(ply_tehai_ori_stat == true && ply_riichi_mode == 0){
		ply_sute_hai = ply_ori_hai;
	}else{
		// 捨牌確定
		ply_sute_hai = sutekoho_hai[fixed_sutekoho_num];
	}
	// ----------------------------------------
	// リーチ宣言確認
	// ----------------------------------------
	if( shanten_normal == 0              &&    // シャンテンが0(向聴している)
	    ply_riichi_mode == 0             &&    // リーチモードが0：リーチをかけていない
	    naki_count - ankan_count == 0    &&    // 鳴いていない
		ply_kyoku_score[ply_id]  >= 1000 &&    // プレーヤ得点が1000点以上
	    kyoku_tsumo_count        <= 66   ){    // 自摸番がある(残り牌が4枚以上)

		// アクション定義
		ply_act = ACTRIICH;            // リーチアクション
		ply_sute_hai = 0;              // 捨牌初期化
		ply_sute_aka = false;          // 赤牌初期化
		ply_riichi_mode = 1;           // リーチ宣言モード

	// ----------------------------------------
	// 自摸切り確認(条件：「自摸牌と捨牌が同一」かつ「手牌内の捨牌が0枚」→自摸切り)
	// ----------------------------------------
	}else if(ply_tsumo_hai == ply_sute_hai && tehai[ply_sute_hai] == 0){

		// アクションの指定
		ply_act = ACTTSUMOGIRI;

		// 赤牌設定
		ply_sute_aka=ply_tsumo_aka;

		// 前のアクションが「リーチアクション」ならば、リーチモードの変更
		if( ply_riichi_mode == 1 ){
			ply_riichi_mode = 2;        // リーチ宣言後モード
		}

	// ----------------------------------------
	// その他は捨牌処理
	// ----------------------------------------
	}else{

		// アクションの指定
		ply_act = ACTSUTE;

		// 赤牌設定
		if( ( ply_sute_hai == MAN5NUM && aka_count[0] > 0 && tehai[ply_sute_hai] == aka_count[0]) || 
		    ( ply_sute_hai == PIN5NUM && aka_count[1] > 0 && tehai[ply_sute_hai] == aka_count[1]) || 
		    ( ply_sute_hai == SOU5NUM && aka_count[2] > 0 && tehai[ply_sute_hai] == aka_count[2]) ){ 

			// 赤牌有効
			ply_sute_aka=true;
		}else{
			// 赤牌無効
			ply_sute_aka=false;
		}

		// 前のアクションが「リーチアクション」ならば、リーチモードの変更
		if( ply_riichi_mode == 1 ){
			ply_riichi_mode = 2;
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 手牌オリ確認
/* ---------------------------------------------------------------------------------------------- */
void PlyChkTehaiOri(){

	// ----------------------------------------
	// オリ無効化
	// ----------------------------------------
	ply_tehai_ori_stat = false;

	// ----------------------------------------
	// 0.(前提条件)手牌状態(シャンテン数確認)
	// ----------------------------------------

	// 相手プレーヤの内の誰かがリーチしているのか？
	if( ply_riichi_stat[0] == true || ply_riichi_stat[1] == true || ply_riichi_stat[2] == true || ply_riichi_stat[3] == true){

		// 自分がリーチしてない且つリーチ宣言前なら降り状態確認
		if(ply_riichi_stat[ply_id] != true && ply_riichi_mode == 0){

			// オリ状態確認
			set_ori_stat();

		}
	}

	// ----------------------------------------
	// オリ牌選択
	// ----------------------------------------

	// オリモードならば、オリ牌選択
	if (ply_tehai_ori_stat == true ){

		// オリ情報定義
		set_ori_info();

		// オリ牌選択
		set_ori_hai();

	}
}

/* ---------------------------------------------------------------------------------------------- */
// 手牌オリ確認
/* ---------------------------------------------------------------------------------------------- */
void set_ori_stat(){

	// ----------------------------------------
	// 変数定義
	// ----------------------------------------

	// リーチプレーヤ初期化
	fixed_riichi_ply = 0;  // オリを定義するプレーヤ

	// ----------------------------------------
	// リーチプレーヤ定義
	// ----------------------------------------

	// 一人の相手リーチプレーヤを決めて、そのプレーヤの捨牌からオリ牌を決める
	// その他2名の捨牌は考慮しない

	// 親プレーヤがリーチをしているか？

		// 子プレーヤからリーチプレーヤを任意に決定する
		for( int tmp_ply = 0; tmp_ply < PLAYER_MAX; tmp_ply++ ){
			if( ply_riichi_stat[tmp_ply] == true){
				fixed_riichi_ply = tmp_ply;
				break;
			}
		}

	// ----------------------------------------
	// オリステータス定義
	// ----------------------------------------

	// リーチプレーヤが一人→条件確認
	if(ply_riichi_stat_count == 1){

		// リーチが6順目を超える(→6順目以内なら押しモード)
		// if(){

			// ----------------------------------------
			// 聴牌なら
			// ----------------------------------------
			if ( shanten_normal == 0){
			// 押しモード
			ply_tehai_ori_stat = false;

			// ----------------------------------------
			// 1シャンテンなら
			// ----------------------------------------
			}else if(shanten_normal == 1){

				// 有効牌が10枚以上
				if(yuko_max_count > 9){
					// 押しモード
					ply_tehai_ori_stat = false;
				}else{
					// オリモード
					ply_tehai_ori_stat = true;
				}

			// ----------------------------------------
			// 2シャンテン以下なら
			// ----------------------------------------
			}else{
				// オリモード
				ply_tehai_ori_stat = true;
			}

	// リーチプレーヤが二人以上いる→ベタオリモード
	}else{
		// オリモード
		ply_tehai_ori_stat = true;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// オリ情報定義(オリランク牌、スジ壁情報)
/* ---------------------------------------------------------------------------------------------- */
void set_ori_info(){

	// ----------------------------------------
	// 変数定義
	// ----------------------------------------

	// 作業用
	int tmp_pre_orihai_count;                            // オリ牌枚数
	int tmp_pre_orihai_num[SUTE_KOHO_MAX_COUNT];         // 手牌番号
	int tmp_pre_orihai_ranknum[SUTE_KOHO_MAX_COUNT];     // 手牌内のランク順位

	// ----------------------------------------
	// オリ牌ランクテーブル(仮定義)
	// ----------------------------------------

	// オリ牌枚数処理科
	tmp_pre_orihai_count = 0;

	// 捨牌候補(手牌1枚以上)とランク牌を定義する
	for( int tmp_i=0; tmp_i < PAI_MAX; tmp_i++ ){

		// 手牌内にあれば(0以上ならば)、オリ候補牌として設定
		if(tehai[tmp_i] > 0){ 

			// オリ牌候補定義
			tmp_pre_orihai_num[tmp_pre_orihai_count] = tmp_i;

			// ランク確定義(字牌)
			if( tmp_i > 30){
					tmp_pre_orihai_ranknum[tmp_pre_orihai_count] = 5;
			}else{

				// ランク確認(数牌)
				if( (tmp_i % 10) - 5 > 0 ){
					tmp_pre_orihai_ranknum[tmp_pre_orihai_count] = (tmp_i % 10) - 5;
				}else{
					tmp_pre_orihai_ranknum[tmp_pre_orihai_count] = 5 - (tmp_i % 10);
				}

			}

			// 加算
			tmp_pre_orihai_count++;

		}
	}

	// ----------------------------------------
	// オリ牌ランクテーブル
	// ----------------------------------------

	// ランク優先順位の低い順に並び替え
	orihai_count = 0;
	for( int tmp_rank=0; tmp_rank < 6; tmp_rank++ ){
		for( int tmp_i=0; tmp_i < tmp_pre_orihai_count; tmp_i++ ){
			// ランク番号確認
			if( 5 - tmp_rank == tmp_pre_orihai_ranknum[tmp_i] ){
				// 並び替え後のオリ牌番号設定
				orihai_num[orihai_count]      = tmp_pre_orihai_num[tmp_i];
				orihai_ranknum[orihai_count]  = tmp_pre_orihai_ranknum[tmp_i];
				// 加算
				orihai_count++;
			}
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// オリ牌選択
/* ---------------------------------------------------------------------------------------------- */
void set_ori_hai(){

	// ----------------------------------------
	// 変数定義
	// ----------------------------------------
	int  tmp_ori_hai;              // 仮のオリ牌
	bool tmp_ori_aka;              // 仮のオリ牌の赤有無
	bool chk_flg;                  // チェックフラグ

	// ----------------------------------------
	// モード1. リーチプレーヤの捨牌
	// ----------------------------------------
	chk_flg = false;
	for( int tmp_i=0; tmp_i < orihai_count; tmp_i++ ){

		// 相手リーチプレーヤの河確認
		for( int tmp_j=0; tmp_j < ply_kawa_count[fixed_riichi_ply]; tmp_j++ ){

			// fixed_riichi_plyの河に捨牌があれば、それをオリ牌と定義する
			if( orihai_num[tmp_i] == kawa[fixed_riichi_ply][tmp_j] ){

				// オリ牌定義
				ply_ori_algo_num = 1;   // オリアルゴリズム番号
				ply_ori_hai = kawa[fixed_riichi_ply][tmp_j];

				// 赤牌確認
				if( ply_ori_hai == MAN5NUM || 
				    ply_ori_hai == PIN5NUM || 
			        ply_ori_hai == SOU5NUM ){ 

					// オリ牌で黒牌がないなら
					if( tehai[ply_ori_hai] - aka_count[(ply_ori_hai-5)/10] == 0){
						ply_ori_aka = true;
					}else{
						ply_ori_aka = false;
					}

				// 赤牌でないなら
				}else{
					ply_ori_aka = false;
				}

				// フラグ有効化
				chk_flg = true;
				break;
			}

		}

		// フラグが有効なら抜ける
		if ( chk_flg == true){
			break;
		}

	}

	// ----------------------------------------
	// モード2. リーチ後の自他プレーヤの捨牌
	// ----------------------------------------
	if ( chk_flg == false){

		// オリ牌ごとの算出
		for( int tmp_i=0; tmp_i < orihai_count; tmp_i++ ){

			// 各プレーヤごとの確認
			for( int tmp_pnum=0; tmp_pnum < 4; tmp_pnum++ ){

				// 相手リーチプレーヤの河確認
				for( int tmp_j = postriichi_turn_count[fixed_riichi_ply][tmp_pnum]; tmp_j < ply_kawa_count[tmp_pnum]; tmp_j++ ){

					// fixed_riichi_plyの河に捨牌があれば、それをオリ牌と定義する
					if( orihai_num[tmp_i] == kawa[tmp_pnum][tmp_j] ){

						// オリ牌定義
						ply_ori_algo_num = 2;   // オリアルゴリズム番号
						ply_ori_hai = orihai_num[tmp_i];

						// 赤牌確認
						if( ply_ori_hai == MAN5NUM || 
						    ply_ori_hai == PIN5NUM || 
					        ply_ori_hai == SOU5NUM ){ 

							// オリ牌で黒牌がないなら
							if( tehai[ply_ori_hai] - aka_count[(ply_ori_hai-5)/10] == 0){
								ply_ori_aka = true;
							}else{
								ply_ori_aka = false;
							}
						// 赤牌でないなら
						}else{
							ply_ori_aka = false;
						}

						// フラグ有効化(河ループ)
						chk_flg = true;
						break;
					}

				}

				// フラグが有効なら抜ける(プレーヤループ)
				if ( chk_flg == true){
					break;
				}

			} // プレーヤループ

			// フラグが有効なら抜ける(オリ牌ループ)
			if ( chk_flg == true){
				break;
			}

		} // オリ牌ループ

	} // if文

	// ----------------------------------------
	// モード3. スジ、カベ牌の算出
	// ----------------------------------------



	// ----------------------------------------
	// モード4. オリ牌が無いので、ランク牌の優先順位が低い牌でオリる
	// ----------------------------------------
	if ( chk_flg == false){

		// オリ牌定義
		ply_ori_algo_num = 4;   // オリアルゴリズム番号
		ply_ori_hai = orihai_num[0];

		// 赤牌確認
		if( ply_ori_hai == MAN5NUM || 
		    ply_ori_hai == PIN5NUM || 
		    ply_ori_hai == SOU5NUM ){ 

			// オリ牌で黒牌がないなら
			if( tehai[ply_ori_hai] - aka_count[(ply_ori_hai-5)/10] == 0){
				ply_ori_aka = true;
			}else{
				ply_ori_aka = false;
			}

		// 赤牌でないなら
		}else{
			ply_ori_aka = false;
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 暗槓アクション
/* ---------------------------------------------------------------------------------------------- */
void PlyActAnkan(int tmp_naki_hai){

	// ----------------------------------------
	// 手牌・自摸処理
	// ----------------------------------------

	// ヒストグラムに牌の枚数を減算
	tehai[tmp_naki_hai] = 0;

	// 自摸牌加算
	if ( ply_tsumo_hai != tmp_naki_hai){
		tehai[ply_tsumo_hai]++;           // 自摸牌
	}

	// ----------------------------------------
	// 晒し枚数追加
	// ----------------------------------------
	naki_stat[naki_count] = ANKAN;
	naki_hai[naki_count]  = tmp_naki_hai;
	naki_idx[naki_count]  = tmp_naki_hai;

	// 晒し処理(赤牌)
	if( tmp_naki_hai == MAN5NUM || 
	    tmp_naki_hai == PIN5NUM || 
	    tmp_naki_hai == SOU5NUM ){

		// 赤牌設定
		naki_aka[naki_count] = max_aka_count[(tmp_naki_hai-5)/10];  // 暗槓のために最大数を定義
		aka_count[(tmp_naki_hai-5)/10] = 0;                         // 手持ち赤はなし

	}else{
		naki_aka[naki_count] = 0;
	}

	// 晒し枚数加算
	naki_count++;
	ankan_count++;

	// ----------------------------------------
	// 手牌状態確認 - 暗槓
	// ----------------------------------------

	// 捨牌後(自摸無し)の手牌状態確認
	ChkTsumoNashiShanten();


}

/* ---------------------------------------------------------------------------------------------- */
// 加槓アクション
/* ---------------------------------------------------------------------------------------------- */
void PlyActKakan(int tmp_naki_hai, int tmp_naki_aka_count){

	// ----------------------------------------
	// 手牌・自摸処理
	// ----------------------------------------

	// 自摸牌加算
	if ( ply_tsumo_hai != tmp_naki_hai){
		tehai[ply_tsumo_hai]++;           // 自摸牌
		tehai[tmp_naki_hai]--;            // 加槓の牌
	}

	// ----------------------------------------
	// 晒し枚数追加
	// ----------------------------------------

	// 晒し枚数追加
	naki_stat[naki_count] = KAKAN;
	naki_hai[naki_count]  = tmp_naki_hai;
	naki_idx[naki_count]  = tmp_naki_hai;
	naki_aka[naki_count]  = tmp_naki_aka_count;

	// 晒し枚数加算
	naki_count++;
	kakan_count++;

	// ----------------------------------------
	// 手牌状態確認 - 加槓
	// ----------------------------------------

	// 捨牌後(自摸無し)の手牌状態確認
	ChkTsumoNashiShanten();

}

/* ---------------------------------------------------------------------------------------------- */
// 4.捨牌時アクション処理
/* ---------------------------------------------------------------------------------------------- */
void PlyActTsumoSute(){

	// ----------------------------------------
	// 捨牌後処理
	// ----------------------------------------

	// プレーヤー手牌ヒストグラムの更新
	PlySetTsumoSuteTehaiHist();

	// プレーヤの手牌ステータスの更新
	PlyChkPlyStat();

	// ----------------------------------------
	// 結果表示
	// ----------------------------------------
	if( print_ply_mode > 0){

		// 手牌表示(ライン表示)
		print_tehai_line();

		// 手牌ヒストグラム表示
		// print_tehai_hist();

		// 赤牌情報
		print_tehai_aka();

		// 自摸無し手牌詳細情報
		print_tsumonashi_tehai_info();

	}
}

/* ---------------------------------------------------------------------------------------------- */
// (1.)自摸捨牌時の手牌ヒストグラム処理
/* ---------------------------------------------------------------------------------------------- */
void PlySetTsumoSuteTehaiHist(){

	// ----------------------------------------
	// 捨牌処理
	// ----------------------------------------

		// 捨牌処理
		tehai[ply_sute_hai]--;

		// 赤牌数変更(捨牌)
		      if(ply_sute_hai == MAN5NUM && ply_sute_aka == true ){
			aka_count[0]--;
		}else if(ply_sute_hai == PIN5NUM && ply_sute_aka == true ){
			aka_count[1]--;
		}else if(ply_sute_hai == SOU5NUM && ply_sute_aka == true ){
			aka_count[2]--;
		}

		// 河情報設定
		kawa[ply_id][ply_kawa_count[ply_id]]     = ply_sute_hai;
		kawa_aka[ply_id][ply_kawa_count[ply_id]] = ply_sute_aka;
		ply_kawa_count[ply_id]++;

		// 捨牌の初期化
		ply_sute_hai = 0;

	// ----------------------------------------
	// 自摸処理
	// ----------------------------------------

	// 自摸牌がある場合
	if ( ply_act == ACTSUTE || ply_act == ACTTSUMOGIRI){

		// 手牌数変更
		tehai[ply_tsumo_hai]++;

		// 赤牌数変更(自摸)
		      if(ply_tsumo_hai == MAN5NUM && ply_tsumo_aka == true ){
			aka_count[0]++;
		}else if(ply_tsumo_hai == PIN5NUM && ply_tsumo_aka == true ){
			aka_count[1]++;
		}else if(ply_tsumo_hai == SOU5NUM && ply_tsumo_aka == true ){
			aka_count[2]++;
		}

		// ツモ牌の初期化
		ply_tsumo_hai = 0;

	}

	// 捨牌後(自摸無し)の手牌状態確認
	ChkTsumoNashiShanten();

}

/* ---------------------------------------------------------------------------------------------- */
// (2.)プレーヤ手牌の状態確認(メイン処理)
/* ---------------------------------------------------------------------------------------------- */
void PlyChkPlyStat(){

	// 初期化
	ply_tehai_naki_stat = false;
	ply_yakuhai_stat    = false;

	// 役牌が三枚以上あれば
	if( tehai[HAKUNUM]    > 2 || 
	    tehai[HATSUNUM]   > 2 || 
	    tehai[CHUNNUM]    > 2 || 
	    tehai[ply_bakaze] > 2 || 
	    tehai[ply_zikaze] > 2 ){

		// 鳴きモードの有効化
		ply_tehai_naki_stat = true;
		// 役牌モードの有効化
		ply_yakuhai_stat    = true;

	}else{

		// 鳴きテーブルを確認して役牌が鳴かれているか確認する
		for( int tmp_i = 0; tmp_i < naki_count; tmp_i++){

			// 鳴き牌に役牌(明刻)があるのか？
			if( naki_hai[tmp_i] == HAKUNUM    || 
			    naki_hai[tmp_i] == HATSUNUM   || 
			    naki_hai[tmp_i] == CHUNNUM    || 
			    naki_hai[tmp_i] == ply_bakaze || 
			    naki_hai[tmp_i] == ply_zikaze ){ 

				// 鳴きモードの有効化
				ply_tehai_naki_stat = true;
				// 役牌モードの有効化
				ply_yakuhai_stat    = true;
				break;

			}

		}

	}

	// 手牌役のあるなし確認
	PlyChkYaku();

	// フリテン確認
	PlyChkFuriten();

	// プレーヤー鳴きテーブルの更新
	PlyChkNakitbl();

}

/* ---------------------------------------------------------------------------------------------- */
// (3.)役有り確認
/* ---------------------------------------------------------------------------------------------- */
void PlyChkYaku(){

	// 役あり確認
	if( ply_yakuhai_stat == true ||     // 役牌を持っているのか？
	    ply_riichi_mode > 1      ){     // リーチが掛けているのか？
		// 「手牌役有り」状態
		ply_tehai_yaku_stat=true;
	}else{
		// 「手牌役無し」状態
		ply_tehai_yaku_stat=false;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// (4.)フリテン確認
/* ---------------------------------------------------------------------------------------------- */
void PlyChkFuriten(){

	// 初期定義
	ply_furiten_stat = false;

	// 和了確認
	for(int tmp_i = 0; tmp_i < nakikoho_tbl_count; tmp_i++){
		// ロンであること
		if( nakikoho_tbl_act[tmp_i] == ACTRON){
			for(int tmp_j=0; tmp_j < ply_kawa_count[ply_id]; tmp_j++){
				// 捨て牌にあるなら
				if(nakikoho_tbl_hai[tmp_i] == kawa[ply_id][tmp_j]){
					ply_furiten_stat = true;
				}
			}
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// (5.)鳴きテーブルの状態確認
/* ---------------------------------------------------------------------------------------------- */
void PlyChkNakitbl(){

	// 鳴きテーブル確認
	for(int tmp_i = 0; tmp_i < nakikoho_tbl_count; tmp_i++){

		// 鳴きアクション有効状態であるなら
		if( ply_yakuhai_stat == true ){
			nakikoho_tbl_yesno[tmp_i] = true;

		// 鳴きアクション有効状態でないなら、役牌2枚だけ有効化する
		}else if( nakikoho_tbl_hai[tmp_i] == HAKUNUM    || 
		          nakikoho_tbl_hai[tmp_i] == HATSUNUM   || 
		          nakikoho_tbl_hai[tmp_i] == CHUNNUM    || 
		          nakikoho_tbl_hai[tmp_i] == ply_bakaze || 
		          nakikoho_tbl_hai[tmp_i] == ply_zikaze ){ 
			nakikoho_tbl_yesno[tmp_i] = true;
		}else{
			nakikoho_tbl_yesno[tmp_i] = false;;
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 他プレーヤの自摸
/* ---------------------------------------------------------------------------------------------- */
void PlyChkOthPlyTsumo(){

	// ----------------------------------------
	// 自摸回数カウント
	// ----------------------------------------

	// 自摸回数カウント
	kyoku_tsumo_count++;

}

/* ---------------------------------------------------------------------------------------------- */
// 他プレーヤのリーチ
/* ---------------------------------------------------------------------------------------------- */
void PlyChkOthPlyRiichi(int tmp_ply_id){

	// ----------------------------------------
	// リーチ有効化
	// ----------------------------------------
	ply_riichi_stat[tmp_ply_id] = true;

	// ----------------------------------------
	// 巡目定義
	// ----------------------------------------
	for(int tmp_ply = 0; tmp_ply < PLAYER_MAX; tmp_ply++){
		postriichi_turn_count[tmp_ply_id][tmp_ply] = ply_kawa_count[tmp_ply];
	}

	// ----------------------------------------
	// リーチ人数加算
	// ----------------------------------------

	// リーチ順番
	ply_riichi_junban[tmp_ply_id] = ply_riichi_stat_count;

	// リーチ人数
	ply_riichi_stat_count++;

}

/* ---------------------------------------------------------------------------------------------- */
// 他プレーヤの鳴き確認
/* ---------------------------------------------------------------------------------------------- */
void PlyChkOthPlyNaki(int naki_ply_id, LBPAct naki_ply_act, int tmp_naki_hai, int tmp_naki_idx, int tmp_aka_count){

}

/* ---------------------------------------------------------------------------------------------- */
// 鳴き確認(相手プレーヤ捨牌確認)
/* ---------------------------------------------------------------------------------------------- */
void PlyChkNaki(struct MJSPlyInfo *pinfo, int suteply, int hai, bool tmp_aka){

	// 初期設定
	ply_act = ACTNONAKI;
	ply_naki_idx = 0;
	ply_naki_aka_count = 0;

	// 表示牌(捨牌)の加算
	open_haiparts_count[hai]++;

	// 捨牌定義
	kawa[suteply][ply_kawa_count[suteply]]     = hai;
	kawa_aka[suteply][ply_kawa_count[suteply]] = tmp_aka;
	ply_kawa_count[suteply]++;

	// 処理開始
	for( int tmp_i=0; tmp_i < nakikoho_tbl_count; tmp_i++){

		// 牌が該当しているのであれば
		if( nakikoho_tbl_hai[tmp_i] == hai ){

			// ----------------------------------------
			// ロン確認
			// ----------------------------------------
			if( nakikoho_tbl_act[tmp_i] == ACTRON && // ロンアクション
			    ply_tehai_yaku_stat == true &&       // 役有
				ply_furiten_stat == false   ){       // フリテンしていない

				// アクション設定
				ply_act = ACTRON;
				ply_naki_idx = nakikoho_tbl_hai[tmp_i];
				ply_naki_aka_count = 0;

			// ----------------------------------------
			// ポン確認
			// ----------------------------------------
			}else if( nakikoho_tbl_yesno[tmp_i] == true   &&     // 鳴きテーブルが可能であるのか？
			          nakikoho_tbl_act[tmp_i]   == ACTPON &&     // 鳴きアクションがポンであるのか？
			          kyoku_tsumo_count != 70){                  // 鳴きタイミングがラス牌でないのか？

				// アクション設定
				ply_act = ACTPON;

				// ポン時の牌INDEX
				ply_naki_idx = nakikoho_tbl_hai[tmp_i];

				// 赤牌であるならば
				if( hai == 5 || hai == 15 || hai == 25){

					// 赤牌が2枚以上ならば
					if(aka_count[(hai-5)/10] > 2){

						// 赤枚数設定
						ply_naki_aka_count = 2;

					}else{

						// 赤枚数設定
						ply_naki_aka_count = aka_count[(hai-5)/10];

					}

				}else{

						// 赤枚数設定
						ply_naki_aka_count = 0;

				}

			// ----------------------------------------
			// チー確認
			// ----------------------------------------
			}else if( nakikoho_tbl_yesno[tmp_i] == true   &&     // 鳴きテーブルが可能であるのか？
			          nakikoho_tbl_act[tmp_i]   == ACTCHI &&     // 鳴きアクションがポンであるのか？
			          suteply == ply_id_shimo             &&     // 捨牌プレーヤが下家であるのか？
			          kyoku_tsumo_count != 70){                  // 鳴きタイミングがラス牌でないのか？

				// アクション設定
				ply_act = ACTCHI;

				// チー時の牌INDEX
				ply_naki_idx = nakikoho_tbl_idx[tmp_i];

				// 赤牌の仮設定
				ply_naki_aka_count=0;

				// 赤牌確認(鳴きINDEXが3の場合)
				if( ply_naki_idx == 3 || ply_naki_idx == 13 || ply_naki_idx == 23){
					if( ( hai != 5 || hai != 15 || hai != 25) && ( aka_count[(hai-3)/10] > 0 ) ){
						ply_naki_aka_count=1;
					}else{
						ply_naki_aka_count=0;
					}
				}

				// 赤牌確認(鳴きINDEXが4の場合)
				if( ply_naki_idx == 4 || ply_naki_idx == 14 || ply_naki_idx == 24){
					if( ( hai != 5 || hai != 15 || hai != 25) && ( aka_count[(hai-4)/10] > 0 ) ){
						ply_naki_aka_count=1;
					}else{
						ply_naki_aka_count=0;
					}
				}

				// 赤牌確認(鳴きINDEXが5の場合)
				if( ply_naki_idx == 5 || ply_naki_idx == 15 || ply_naki_idx == 25){
					if( ( hai != 5 || hai != 15 || hai != 25) && ( aka_count[(hai-5)/10] > 0 ) ){
						ply_naki_aka_count=1;
					}else{
						ply_naki_aka_count=0;
					}
				}

			}

		}
	}

	// オリモードならば、鳴き無し
	if( ply_act != ACTRON && ply_tehai_ori_stat == true){
		ply_act = ACTNONAKI;
	}

	// (デバグ用)鳴き無し
/*	if( ply_act != ACTRON ){
		ply_act = ACTNONAKI;
	}*/

	// ----------------------------------------
	// pinfo定義：ロン和了
	// ----------------------------------------
	if ( ply_act == ACTRON){

		// pinfo定義：ロン和了
		set_pinfo(pinfo, ply_act, ply_naki_idx, ply_naki_idx, ply_naki_aka_count);

	// ----------------------------------------
	// pinfo定義：ポン
	// ----------------------------------------
	}else if( ply_act == ACTPON){

		// pinfo定義：ポン
		set_pinfo(pinfo, ply_act, ply_naki_idx, ply_naki_idx, ply_naki_aka_count);

	// ----------------------------------------
	// pinfo定義：チー
	// ----------------------------------------
	}else if( ply_act == ACTCHI){

		// pinfo定義：チー
		set_pinfo(pinfo, ply_act, hai, ply_naki_idx, ply_naki_aka_count);

	// ----------------------------------------
	// pinfo定義：その他(鳴き無し)
	// ----------------------------------------
	}else{

		// pinfo定義：鳴き無し
		set_pinfo(pinfo, ACTNONAKI, 0, 0, 0);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 鳴きアクション
/* ---------------------------------------------------------------------------------------------- */
void PlyActNaki(struct MJSPlyInfo *pinfo, int naki_ply_id, LBPAct naki_ply_act, int tmp_hai, int tmp_chi_hai_idx, int tmp_naki_aka_count){

	// 鳴きプレーヤー確認(鳴いたのが自分であれば)
	if( ply_id == naki_ply_id ){

		// ----------------------------------------
		// 晒し牌設定 - ポンの場合
		// ----------------------------------------
		if( naki_ply_act == ACTPON ){

			// ヒストグラムに牌の枚数を減算
			tehai[tmp_hai]-=2;

			// 赤牌枚数の減算
			if( tmp_hai == 5 || tmp_hai == 15 || tmp_hai == 25){
				aka_count[(tmp_hai-5)/10] = aka_count[(tmp_hai-5)/10] - tmp_naki_aka_count;
			}

			// 晒し枚数追加
			naki_stat[naki_count] = MINKO;
			naki_hai[naki_count]  = tmp_hai;
			naki_idx[naki_count]  = tmp_hai;
			naki_aka[naki_count]  = tmp_naki_aka_count;
			naki_count++;

		// ----------------------------------------
		// 晒し牌設定 - チーの場合
		// ----------------------------------------
		}else if( naki_ply_act == ACTCHI ){

			// ヒストグラムに牌の枚数を減算
			tehai[tmp_chi_hai_idx]--;
			tehai[tmp_chi_hai_idx+1]--;
			tehai[tmp_chi_hai_idx+2]--;
			tehai[tmp_hai]++;

			// 赤牌枚数の減算
			      if( tmp_chi_hai_idx == 3 || tmp_chi_hai_idx == 13 || tmp_chi_hai_idx == 23){
				aka_count[(tmp_chi_hai_idx-3)/10] = aka_count[(tmp_chi_hai_idx-3)/10] - tmp_naki_aka_count;
			}else if( tmp_chi_hai_idx == 4 || tmp_chi_hai_idx == 14 || tmp_chi_hai_idx == 24){
				aka_count[(tmp_chi_hai_idx-4)/10] = aka_count[(tmp_chi_hai_idx-4)/10] - tmp_naki_aka_count;
			}else if( tmp_chi_hai_idx == 5 || tmp_chi_hai_idx == 15 || tmp_chi_hai_idx == 25){
				aka_count[(tmp_chi_hai_idx-5)/10] = aka_count[(tmp_chi_hai_idx-5)/10] - tmp_naki_aka_count;
			}

			// 晒し枚数追加
			naki_stat[naki_count] = MINSHUN;
			naki_hai[naki_count]  = tmp_hai;
			naki_idx[naki_count]  = tmp_chi_hai_idx;
			naki_aka[naki_count]  = tmp_naki_aka_count;
			naki_count++;

		}

		// ----------------------------------------
		// シャンテン確認・捨牌確定
		// ----------------------------------------
		PlyChkNakiSute(pinfo);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 鳴き捨牌アクション確認
/* ---------------------------------------------------------------------------------------------- */
void PlyChkNakiSute(struct MJSPlyInfo *pinfo){

	// ----------------------------------------
	// 最終捨牌候補の算出
	// ----------------------------------------

	// 自摸牌初期化
	ply_tsumo_hai = 0;

	// 自摸有の向聴算出
	ChkTsumoAriShanten();

	// 捨牌決定
	// PlyChkAISutehai();

	// 鳴き捨牌アクション時点ではオリは行わない
	// PlyChkTehaiOri();

	// ----------------------------------------
	// 捨牌設定
	// ----------------------------------------

	// 捨牌設定
	ply_sute_hai = sutekoho_hai[fixed_sutekoho_num];

	// 赤牌設定
	if( ( ply_sute_hai == MAN5NUM && aka_count[0] > 0 && tehai[ply_sute_hai] == aka_count[0]) || 
	    ( ply_sute_hai == PIN5NUM && aka_count[1] > 0 && tehai[ply_sute_hai] == aka_count[1]) || 
	    ( ply_sute_hai == SOU5NUM && aka_count[2] > 0 && tehai[ply_sute_hai] == aka_count[2]) ){ 

		// 赤牌有効
		ply_sute_aka=true;
	}else{
		// 赤牌無効化
		ply_sute_aka=false;
	}

	// アクションの指定
	ply_act = ACTNAKISUTE;

	// ----------------------------------------
	// pinfo設定
	// ----------------------------------------

	if(ply_sute_aka == true){
		// pinfo定義：鳴き捨牌
		set_pinfo(pinfo, ply_act, ply_sute_hai, ply_sute_hai, 1);
	}else{
		set_pinfo(pinfo, ply_act, ply_sute_hai, ply_sute_hai, 0);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 4-4.鳴き捨牌後アクション処理
/* ---------------------------------------------------------------------------------------------- */
void PlyActNakiSute(){

	// 捨牌処理
	tehai[ply_sute_hai]--;

	// 赤牌数変更(捨牌)
	if( ply_sute_aka == true ){
		aka_count[(ply_sute_hai-5)/10]--;
	}

	// 河情報設定
	kawa[ply_id][ply_kawa_count[ply_id]]     = ply_sute_hai;
	kawa_aka[ply_id][ply_kawa_count[ply_id]] = ply_sute_aka;
	ply_kawa_count[ply_id]++;

	// 自摸無し時の向聴数確認
	ChkTsumoNashiShanten();

	// プレーヤの手牌ステータス更新
	PlyChkPlyStat();

}

/* ---------------------------------------------------------------------------------------------- */
// 5-1.和了終了処理
/* ---------------------------------------------------------------------------------------------- */
void PlyAgari(bool tmp_score_flg, int tmp_score[]){

	// 得点情報更新
	if(tmp_score_flg == true){
		for(int tmp_ply = 0; tmp_ply < PLAYER_MAX; tmp_ply++){
			ply_kyoku_score[tmp_ply] = tmp_score[tmp_ply];
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 5-2.流局終了処理
/* ---------------------------------------------------------------------------------------------- */
void PlyRyuKyoku(bool tmp_score_flg, int tmp_score[]){

	// 得点情報更新
	if(tmp_score_flg == true){
		for(int tmp_ply = 0; tmp_ply < PLAYER_MAX; tmp_ply++){
			ply_kyoku_score[tmp_ply] = tmp_score[tmp_ply];
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 自摸有りの向聴算出
/* ---------------------------------------------------------------------------------------------- */
void ChkTsumoAriShanten(){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------
	int tmp_org_shanten;        // 14枚シャンテン値の一時置き
	sutekoho_count = 0;

	// ----------------------------------------
	// シャンテン確認
	// ----------------------------------------

	// 自摸牌の追加
	if (ply_act == ACTTSUMO){
		tehai[ply_tsumo_hai]++;
	}

	// 14枚時点のシャンテン確認
	set_normal_shanten();

	// シャンテン情報の退避
	tmp_org_shanten = shanten_normal;

	// ----------------------------------------
	// 捨牌候補の確認
	// ----------------------------------------
	for(int i=0; i< PAI_MAX; i++){
		if(tehai[i]>0){
			// 定義初期化
			sutekoho_shanten[sutekoho_count]  = 0;
			yuko_haishu_count[sutekoho_count] = 0;
			yuko_hai_count[sutekoho_count]    = 0;
			yuko_hai_count_open_haiparts[sutekoho_count] = 0;
			sutekoho_hai[sutekoho_count]      = i;
			sutekoho_count++;
		}
	}

	// ----------------------------------------
	// 捨牌候補ごとのシャンテン確認
	// ----------------------------------------
	for(int tmp_count=0; tmp_count< sutekoho_count; tmp_count++){

		// 捨牌候補の設定
		tehai[sutekoho_hai[tmp_count]]--; // 捨牌仮置き

		// シャンテン確認
		set_normal_shanten();
		sutekoho_shanten[tmp_count]  = shanten_normal;
		yuko_haishu_count[tmp_count] = 0;

		// 有効牌算出
		for(int j=1; j< PAI_MAX; j++){

			// 定義初期化
			yuko_hai[tmp_count][j]=false;

			//有効牌確認
			if (j !=10 && j!=20 && j!=30){
				// シャンテンが下がってないなら、有効牌を算出
				if (sutekoho_shanten[tmp_count] == tmp_org_shanten){
					// シャンテン確認する牌の範囲を限定する
					if(tehai[j-2] >0 || tehai[j-1] >0 || tehai[j] >0 || tehai[j+1] >0 || tehai[j+2] >0){
						tehai[j]++;
						set_normal_shanten();
						if(shanten_normal == sutekoho_shanten[tmp_count]-1){
							yuko_hai[tmp_count][j]=true;
							yuko_haishu_count[tmp_count]++;
							yuko_hai_count[tmp_count]=yuko_hai_count[tmp_count]+4-tehai[j]+1;  // +1しているのはtehai[j]で仮置きしてるから
							yuko_hai_count_open_haiparts[tmp_count]=yuko_hai_count_open_haiparts[tmp_count]+(4-open_haiparts_count[j]);// 表示牌から算出
						}
						tehai[j]--;
					}
				}
			}
		}

		// 捨牌候補の設定戻し
		tehai[sutekoho_hai[tmp_count]]++;// 捨牌戻し

	}

	// シャンテン値の戻し
	shanten_normal = tmp_org_shanten;

	// 自摸牌の解除
	if (ply_act == ACTTSUMO){
		tehai[ply_tsumo_hai]--;
	}

	// ----------------------------------------
	// 捨牌ごとの期待値算出
	// ----------------------------------------
	set_tsumoari_kitaichi();

	// ----------------------------------------
	// 捨牌の優先順位設定
	// ----------------------------------------
	SetSutekohoPriority();

	// ----------------------------------------
	// 捨牌候補決定
	// ----------------------------------------
	SetFixedSutekoho();

}

/* ---------------------------------------------------------------------------------------------- */
// 自摸無しの向聴算出
/* ---------------------------------------------------------------------------------------------- */
void ChkTsumoNashiShanten(){

	// ----------------------------------------
	// 定義初期化
	// ----------------------------------------

	// シャンテン情報退避用
	int tmp_org_shanten;                // 13枚シャンテン値の一時置き
	int tmp_yuko_hai_13mai[PAI_MAX];    // 有効牌一時置き

	// 鳴き候補テーブル退避用
	int tmp_nakikoho_tbl_count;
	int tmp_nakikoho_tbl_hai[NAKI_KOHO_MAX_COUNT];
	LBPAct tmp_nakikoho_tbl_act[NAKI_KOHO_MAX_COUNT];
	int tmp_nakikoho_tbl_idx[NAKI_KOHO_MAX_COUNT];
	int tmp_nakikoho_tbl_yesno[NAKI_KOHO_MAX_COUNT];

	// 仮置きシャンテンテーブル
	bool kari_flg;
	bool kari_icchi_flg;
	int kari_icchi_num;

	// シャンテン確認
	set_normal_shanten();

	// シャンテン一時置き
	tmp_org_shanten = shanten_normal;

	// 鳴き候補数
	nakikoho_tbl_count = 0;

	// ----------------------------------------
	// 鳴き候補算出
	// ----------------------------------------
	for(int j=1; j< PAI_MAX; j++){

		// ----------------------------------------
		// 定義初期化
		// ----------------------------------------
		yuko_hai_13mai[j] = false;

		// ----------------------------------------
		// 有効牌確認
		// ----------------------------------------
		if (j !=10 && j!=20 && j!=30){

			// シャンテン確認する牌の範囲を限定する
			if(tehai[j-2] > 0 || tehai[j-1] > 0 || tehai[j] > 0 || tehai[j+1] > 0 || tehai[j+2] > 0){

				// 手牌一時置き
				tehai[j]++;

				// ----------------------------------------
				// 仮向聴テーブル確認
				// ----------------------------------------

				// 計算対象カウント
				karitbl_calc_count++;

				// 仮置きテーブルにあるのか
				kari_icchi_flg=false;
				for(int kari_main=0; kari_main < karitbl_count; kari_main++){

					// フラグ初期化
					kari_flg=false;
					for(int kari_i=1; kari_i< PAI_MAX; kari_i++){
							if (tehai[kari_i] != kari_tehai[kari_main][kari_i]){
								kari_flg=true;
								break;
							}
					}

					// falseのままならテーブル内にシャンテン情報あり
					if(kari_flg == false){
						kari_icchi_flg = true;
						kari_icchi_num = kari_main;
					}

				}

				// テーブルでの存在確認
				if (kari_icchi_flg == false){
				
					// シャンテン確認
					set_normal_shanten();

					// 仮置きテーブル設定
					if (karitbl_count < KARITBL_MAX_COUNT){
						kari_shanten[karitbl_count]=shanten_normal;
						for(int kari_i=1; kari_i< PAI_MAX; kari_i++){
							kari_tehai[karitbl_count][kari_i]=tehai[kari_i];
						}
						karitbl_count++;
					}

				}else{

					// テーブルから情報抽出
					shanten_normal=kari_shanten[kari_icchi_num];

				}

				// ----------------------------------------
				// シャンテン数が減る場合
				// ----------------------------------------
				if(shanten_normal == tmp_org_shanten - 1){

					// 自摸無し有効牌の設定
					yuko_hai_13mai[j] = true;

					// テンパイならば、和了牌としてテーブルに格納する
					if(shanten_normal == -1){
						// ----------------------------------------
						// 鳴き候補テーブル定義(ロン和了)
						// ----------------------------------------
						// 鳴き候補テーブル定義(ロン和了)
						nakikoho_tbl_hai[nakikoho_tbl_count] = j;
						nakikoho_tbl_act[nakikoho_tbl_count] = ACTRON;
						nakikoho_tbl_idx[nakikoho_tbl_count] = j;
						nakikoho_tbl_yesno[nakikoho_tbl_count] = false;
						// 鳴き候補数の加算
						nakikoho_tbl_count++;

					}else{

						// ----------------------------------------
						// 鳴き牌設定(ポンの場合)
						// ----------------------------------------
						if (tehai[j] > 2){
							// ポン設定
							tehai[j]-=3;
							// シャンテン確認
							set_normal_shanten();
							// シャンテンが-1ならば
							if( shanten_normal == tmp_org_shanten - 1 ){
								// 鳴き候補テーブル定義(ポン)
								nakikoho_tbl_hai[nakikoho_tbl_count] = j;
								nakikoho_tbl_act[nakikoho_tbl_count] = ACTPON;
								nakikoho_tbl_idx[nakikoho_tbl_count] = j;
								nakikoho_tbl_yesno[nakikoho_tbl_count] = false;
								// 鳴き候補数の加算
								nakikoho_tbl_count++;
							}
							// ポン解除
							tehai[j]+=3;
						}

						// ----------------------------------------
						// 鳴き牌設定(チーの場合：j == 鳴きIDX)
						// ----------------------------------------
						if (j < 30 && tehai[j] > 0 && tehai[j+1] > 0 && tehai[j+2] > 0){
							// チー設定
							tehai[j]--;
							tehai[j+1]--;
							tehai[j+2]--;
							// シャンテン確認
							set_normal_shanten();
							// シャンテンが-1ならば
							if( shanten_normal == tmp_org_shanten - 1 ){
								// 鳴き牌設定
								nakikoho_tbl_hai[nakikoho_tbl_count] = j;
								nakikoho_tbl_act[nakikoho_tbl_count] = ACTCHI;
								nakikoho_tbl_idx[nakikoho_tbl_count] = j;
								nakikoho_tbl_yesno[nakikoho_tbl_count] = false;
								// 鳴き候補数の加算
								nakikoho_tbl_count++;
							}
							// チー設定
							tehai[j]++;
							tehai[j+1]++;
							tehai[j+2]++;
						}

						// ----------------------------------------
						// 鳴き牌設定(チーの場合：j-1 == 鳴きIDX)
						// ----------------------------------------
						if (j < 30 && tehai[j-1] > 0 && tehai[j] > 0 && tehai[j+1] > 0){
							// チー設定
							tehai[j-1]--;
							tehai[j]--;
							tehai[j+1]--;
							// シャンテン確認
							set_normal_shanten();
							// シャンテンが-1ならば
							if( shanten_normal == tmp_org_shanten - 1 ){
								// 鳴き牌設定
								nakikoho_tbl_hai[nakikoho_tbl_count] = j;
								nakikoho_tbl_act[nakikoho_tbl_count] = ACTCHI;
								nakikoho_tbl_idx[nakikoho_tbl_count] = j-1;
								nakikoho_tbl_yesno[nakikoho_tbl_count] = false;
								// 鳴き候補数の加算
								nakikoho_tbl_count++;
							}
							// チー設定
							tehai[j-1]++;
							tehai[j]++;
							tehai[j+1]++;
						}

						// ----------------------------------------
						// 鳴き牌設定(チーの場合：j-2 == 鳴きIDX)
						// ----------------------------------------
						if (j < 30 && tehai[j-2] > 0 && tehai[j-1] > 0 && tehai[j] > 0){
							// チー設定
							tehai[j-2]--;
							tehai[j-1]--;
							tehai[j]--;
							// シャンテン確認
							set_normal_shanten();
							// シャンテンが-1ならば
							if( shanten_normal == tmp_org_shanten - 1 ){
								// 鳴き牌設定
								nakikoho_tbl_hai[nakikoho_tbl_count] = j;
								nakikoho_tbl_act[nakikoho_tbl_count] = ACTCHI;
								nakikoho_tbl_idx[nakikoho_tbl_count] = j-2;
								nakikoho_tbl_yesno[nakikoho_tbl_count] = false;
								// 鳴き候補数の加算
								nakikoho_tbl_count++;
							}
							// チー設定
							tehai[j-2]++;
							tehai[j-1]++;
							tehai[j]++;
						}

					} // 聴牌かそうでないか

				} // シャンテン数が減る場合

				// 手牌一時置きの戻し
				tehai[j]--;

			} // 手牌確認
		} // 手牌確認
	}

	// 有効牌一時置き
	for(int tmp_i=1; tmp_i< PAI_MAX; tmp_i++){
		tmp_yuko_hai_13mai[tmp_i] = yuko_hai_13mai[tmp_i];
	}

	// 鳴き候補テーブル一時置き
	tmp_nakikoho_tbl_count = nakikoho_tbl_count;
	for(int tmp_i=0; tmp_i< tmp_nakikoho_tbl_count; tmp_i++){
		tmp_nakikoho_tbl_hai[tmp_i]   = nakikoho_tbl_hai[tmp_i];
		tmp_nakikoho_tbl_act[tmp_i]   = nakikoho_tbl_act[tmp_i];
		tmp_nakikoho_tbl_idx[tmp_i]   = nakikoho_tbl_idx[tmp_i];
		tmp_nakikoho_tbl_yesno[tmp_i] = nakikoho_tbl_yesno[tmp_i];
	}

	// ----------------------------------------
	// 期待値算出(テンパイ)
	// ----------------------------------------
	nakikoho_tbl_total_ev_score = 0.0;  // 合計期待値初期化
	if(tmp_org_shanten == 0){

		// 期待値計算
		for(int tmp_i=0; tmp_i < nakikoho_tbl_count; tmp_i++){
			set_tenpai_kitaichi(tmp_i);
		}

	// ----------------------------------------
	// 期待値算出(イーシャンテン)
	// ----------------------------------------
	}else if(tmp_org_shanten == 1){

		// 期待値計算
		 set_1shanten_kitaichi();

	}

	// ----------------------------------------
	// 設定値戻し
	// ----------------------------------------
	shanten_normal = tmp_org_shanten;
	for(int tmp_i=1; tmp_i< PAI_MAX; tmp_i++){
		yuko_hai_13mai[tmp_i] = tmp_yuko_hai_13mai[tmp_i];
	}

	// 鳴き候補テーブル戻し
	nakikoho_tbl_count = tmp_nakikoho_tbl_count;
	for(int tmp_i=0; tmp_i< nakikoho_tbl_count; tmp_i++){
		nakikoho_tbl_hai[tmp_i]   = tmp_nakikoho_tbl_hai[tmp_i];
		nakikoho_tbl_act[tmp_i]   = tmp_nakikoho_tbl_act[tmp_i];
		nakikoho_tbl_idx[tmp_i]   = tmp_nakikoho_tbl_idx[tmp_i];
		nakikoho_tbl_yesno[tmp_i] = tmp_nakikoho_tbl_yesno[tmp_i];
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 期待値計算(自摸有り時)
/* ---------------------------------------------------------------------------------------------- */
void set_tsumoari_kitaichi(){

	// ----------------------------------------
	// 捨牌ごとの期待値
	// ----------------------------------------
	for(int tmp_i=0; tmp_i < sutekoho_count; tmp_i++){

		// テンパイならば
		if(shanten_normal == 0 && sutekoho_shanten[tmp_i] == 0){

			// 捨牌候補の手牌削除
			tehai[ply_tsumo_hai]++;
			tehai[sutekoho_hai[tmp_i]]--;
			nakikoho_tbl_total_ev_score = 0.0;
			ev_1shanten_yukohai_count = 0;

			// 期待値算出
			ChkTsumoNashiShanten();

			// 期待値代入
			sutekoho_ev_score[tmp_i] = nakikoho_tbl_total_ev_score;
			sutekoho_ev_count[tmp_i] = nakikoho_tbl_count;

			// 捨牌候補の手牌戻し
			tehai[ply_tsumo_hai]--;
			tehai[sutekoho_hai[tmp_i]]++;

		// イーシャンテンならば
		}else if(shanten_normal == 1 && sutekoho_shanten[tmp_i] == 1){

			// 捨牌候補の手牌削除
			tehai[ply_tsumo_hai]++;
			tehai[sutekoho_hai[tmp_i]]--;
			ev_1shanten_totalscore = 0.0;
			ev_1shanten_yukohai_count = 0;

			// 期待値算出
			ChkTsumoNashiShanten();

			// 期待値代入
			sutekoho_ev_score[tmp_i] = ev_1shanten_totalscore;
			sutekoho_ev_count[tmp_i] = ev_1shanten_yukohai_count;

			// 捨牌候補の手牌戻し
			tehai[ply_tsumo_hai]--;
			tehai[sutekoho_hai[tmp_i]]++;

		// リャンシャンテン以下なら計算しない
		}else{

			// 期待値代入
			sutekoho_ev_score[tmp_i] = 0.0;
			sutekoho_ev_count[tmp_i] = 0;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 期待値計算(テンパイ)
/* ---------------------------------------------------------------------------------------------- */
void set_tenpai_kitaichi(int yuko_hai_num){

	// 期待値初期化
	unkown_resthai_count = 122.0;   // 残り枚数定義

	// ----------------------------------------
	// 和了得点算出
	// ----------------------------------------

	// 手牌仮置き
	tehai[nakikoho_tbl_hai[yuko_hai_num]]++;

	// シャンテン確認
	set_normal_shanten();

	// 得点確認
	SetAgari(
	&yk,                      // 和了役情報構造体(ポイント渡し)
	0,                        // 局番号
	ie,                       // プレーヤの家情報(配列)
	dora_count,               // 表ドラ牌枚数
	dora_marker,              // 表ドラ牌情報(配列)
	0,                        // 裏ドラ牌枚数
	dora_marker,              // 裏ドラ牌情報
	AGARI_NORMAL,             // 和了形式
	ply_id,                   // 和了プレーヤ(席番号親"0", 席番号子"1")
	((ply_id+1)%4),           // 振込プレーヤ(席番号"3")
	false,                    // 自摸和了の有無(ロン和了)
	nakikoho_tbl_hai[yuko_hai_num],  // 和了牌(有効牌テーブル情報)
	false,                    // 和了牌の赤牌有無
	tehai,                    // 和了時の手牌ヒストグラム
	aka_count,                // 手牌の赤牌枚数
	atama_hai,                // 頭牌
	mentsu_count,             // 面子数
	mentsu_stat,              // 面子状態
	mentsu_hai,               // 面子牌
	mentsu_hai,               // 面子INDEX
	naki_count,               // 鳴き面子数
	naki_stat,                // 鳴き面子状態
	naki_hai,                 // 鳴き面子牌
	naki_idx,                 // 鳴き面子INDEX
	naki_aka,                 // 鳴き面子赤牌枚数
	false,                    // リーチフラグ
	false,                    // リーチ一発フラグ
	false                     // ダブルリーチフラグ
	);

	// 手牌仮置きの無効化
	tehai[nakikoho_tbl_hai[yuko_hai_num]]--;

	// ----------------------------------------
	// 期待値算出
	// ----------------------------------------

	// 得点代入
	nakikoho_tbl_score[yuko_hai_num]          = yk.kyoku_score[ply_id];

	// 和了率算出
	nakikoho_tbl_agari_rate[yuko_hai_num]     = (4-open_haiparts_count[nakikoho_tbl_hai[yuko_hai_num]]) / unkown_resthai_count * 100.0;

	// 期待値算出
	nakikoho_tbl_parts_ev_score[yuko_hai_num] = (4-open_haiparts_count[nakikoho_tbl_hai[yuko_hai_num]]) / unkown_resthai_count * yk.kyoku_score[ply_id];

	// 合計期待値算出
	nakikoho_tbl_total_ev_score = nakikoho_tbl_total_ev_score + nakikoho_tbl_parts_ev_score[yuko_hai_num];

}

/* ---------------------------------------------------------------------------------------------- */
// 期待値計算(イーシャンテン)
/* ---------------------------------------------------------------------------------------------- */
void set_1shanten_kitaichi(){

	// ----------------------------------------
	// 変数初期化
	// ----------------------------------------
	int tmp_sute_koho_count;
	int tmp_sute_koho[TSUMOARI_TEHAI_MAX];
	ev_1shanten_totalscore = 0.0;  // 合計期待値初期化
	ev_1shanten_yukohai_count = 0;

	// 期待値初期化
	unkown_resthai_count = 122.0;   // 残り枚数定義

	// ----------------------------------------
	// 有効牌設定
	// ----------------------------------------
	for(int tmp_i=0; tmp_i < PAI_MAX; tmp_i++){
		// 有効牌なら
		if( yuko_hai_13mai[tmp_i] == true ){
			ev_1shanten_yukohai[ev_1shanten_yukohai_count]=tmp_i;
			ev_1shanten_yukohai_count++;
		}
	}

	// ----------------------------------------
	// 有効牌ごとの捨牌設定
	// ----------------------------------------
	for(int tmp_i=0; tmp_i < ev_1shanten_yukohai_count; tmp_i++){

		// 初期化
		tmp_sute_koho_count = 0;

		// 捨牌候補算出
		for(int tmp_j=0; tmp_j < PAI_MAX; tmp_j++){
			if (tehai[tmp_j] > 0){
				tmp_sute_koho[tmp_sute_koho_count]=tmp_j;
				tmp_sute_koho_count++;
			}
		}

		// 捨牌候補数の初期化
		ev_1shanten_sutehai_count[tmp_i]     = 0;
		ev_1shanten_maxev_sutehai_num[tmp_i] = 0;
		ev_1shanten_maxevscore[tmp_i]        = 0.0;

		// 捨牌候補ごと処理確認
		for(int tmp_j=0; tmp_j < tmp_sute_koho_count; tmp_j++){

			// 手牌加算
			tehai[ev_1shanten_yukohai[tmp_i]]++;
			tehai[tmp_sute_koho[tmp_j]]--;

			// 向聴算出
			set_normal_shanten();

			// シャンテン確認
			if(shanten_normal == 0){

				// 捨牌設定
				ev_1shanten_sutehai[tmp_i][ev_1shanten_sutehai_count[tmp_i]] = tmp_sute_koho[tmp_j];

				// テンパイ時手牌期待値の算出
				ChkTsumoNashiShanten();

				// 有効牌ごとの期待値
				ev_1shanten_evscore[tmp_i][ev_1shanten_sutehai_count[tmp_i]] 
				= (4-open_haiparts_count[ev_1shanten_yukohai[tmp_i]]) / unkown_resthai_count * nakikoho_tbl_total_ev_score;

				// 最大期待値算出
				if (ev_1shanten_maxevscore[tmp_i] < ev_1shanten_evscore[tmp_i][ev_1shanten_sutehai_count[tmp_i]]){
					ev_1shanten_maxevscore[tmp_i] = ev_1shanten_evscore[tmp_i][ev_1shanten_sutehai_count[tmp_i]];
					ev_1shanten_maxev_sutehai_num[tmp_i] = ev_1shanten_sutehai_count[tmp_i];
				}

				// 捨牌候補数の加算
				ev_1shanten_sutehai_count[tmp_i]++;

			}

			// 期待値合計を算出
			ev_1shanten_totalscore = 
			ev_1shanten_totalscore + ev_1shanten_maxevscore[tmp_i];

			// 手牌戻し
			tehai[ev_1shanten_yukohai[tmp_i]]--;
			tehai[tmp_sute_koho[tmp_j]]++;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 捨牌候補の優先順位算出
/* ---------------------------------------------------------------------------------------------- */
void SetSutekohoPriority(){

	// 変数定義
	int tmp_sutehai;

	// 自摸牌加算
	tehai[ply_tsumo_hai]++;

	// 捨牌候補の優先順位設定
	for(int tmp_count=0; tmp_count< sutekoho_count; tmp_count++){

		// 数牌ならば
		if (sutekoho_hai[tmp_count] < 30){

			// 距離測定
			if( 5 - (sutekoho_hai[tmp_count] % 10) > 0){
				sutekoho_priority[tmp_count] =   4 + (sutekoho_hai[tmp_count] % 10);
			}else{
				sutekoho_priority[tmp_count] =  14 - (sutekoho_hai[tmp_count] % 10);
			}

		// 字牌ならば
		}else if (sutekoho_hai[tmp_count] > 30 && sutekoho_hai[tmp_count] < 38){

			// 役牌確認
			if( sutekoho_hai[tmp_count] == HAKUNUM    || 
		        sutekoho_hai[tmp_count] == HATSUNUM   || 
		        sutekoho_hai[tmp_count] == CHUNNUM    || 
		        sutekoho_hai[tmp_count] == ply_bakaze || 
		        sutekoho_hai[tmp_count] == ply_zikaze ){ 
				// 役牌ならば
				sutekoho_priority[tmp_count] = 2;
			}else{
				// オタ風ならば
				sutekoho_priority[tmp_count] = 1;
			}

		// その他(デバグ用)
		}else{
			sutekoho_priority[tmp_count] = 0;
		}

		// くっつき牌確認
		tmp_sutehai = sutekoho_hai[tmp_count];
		sutekoho_nearby_hai_count[tmp_count]=0;

		// 指定なし
		if( tehai[tmp_sutehai]   > 1 ){  // 自分は必ず1枚以上あるから
			sutekoho_nearby_hai_count[tmp_count]++;
		}

		// 3-9であること
		if( (tmp_sutehai> 2 && tmp_sutehai<10) ||
		    (tmp_sutehai>12 && tmp_sutehai<20) ||
		    (tmp_sutehai>22 && tmp_sutehai<30) ){
			if( tehai[tmp_sutehai-2] > 0 ){
				sutekoho_nearby_hai_count[tmp_count]++;
			}

		}

		// 2-9であること
		if( (tmp_sutehai> 1 && tmp_sutehai<10) ||
		    (tmp_sutehai>11 && tmp_sutehai<20) ||
		    (tmp_sutehai>21 && tmp_sutehai<30) ){
			if( tehai[tmp_sutehai-1] > 0 ){
				sutekoho_nearby_hai_count[tmp_count]++;
			}

		}

		// 1-8であること
		if( (tmp_sutehai> 0 && tmp_sutehai<19) ||
		    (tmp_sutehai>10 && tmp_sutehai<19) ||
		    (tmp_sutehai>20 && tmp_sutehai<29) ){
			if( tehai[tmp_sutehai+1] > 0 ){
				sutekoho_nearby_hai_count[tmp_count]++;
			}
		}

		// 1-7であること
		if( (tmp_sutehai> 0 && tmp_sutehai<18) ||
		    (tmp_sutehai>10 && tmp_sutehai<18) ||
		    (tmp_sutehai>20 && tmp_sutehai<28) ){
			if( tehai[tmp_sutehai+2] > 0 ){
				sutekoho_nearby_hai_count[tmp_count]++;
			}
		}

	}

	// 自摸牌戻し
	tehai[ply_tsumo_hai]--;

}

/* ---------------------------------------------------------------------------------------------- */
// 捨牌候補の確認
/* ---------------------------------------------------------------------------------------------- */
void SetFixedSutekoho(){

	// 一時変数の定義
	int tmp_fixed_sutekoho_priority = 999;
	int tmp_sutekoho_priority = 0;
	int tmp_dora_hai;
	int tmp_fixed_sutekoho_dora_num;

	// 初期化
	fixed_sutekoho_num = 0;
	yuko_max_count = 0;

	// ドラ牌定義
	tmp_dora_hai = dora_hai[0];

	// 最大有効牌数
	for(int tmp_count=0; tmp_count < sutekoho_count; tmp_count++){
		if(shanten_normal == sutekoho_shanten[tmp_count]){
			// 手牌数算出(旧版)
			if(yuko_max_count <= yuko_hai_count[tmp_count]){
				yuko_max_count = yuko_hai_count[tmp_count];
			}
		}
	}

	// 最終捨牌候補算出
	prefix_sutekoho_count = 0;
	for(int tmp_count=0; tmp_count < sutekoho_count; tmp_count++){

		// 最大有効牌枚数の確認
		if( shanten_normal == sutekoho_shanten[tmp_count] &&  // シャンテンが同じ
		    yuko_max_count == yuko_hai_count[tmp_count]   ){  // 有効牌数が同じ

			// プレ捨牌候補算出
			prefix_sutekoho_num[prefix_sutekoho_count] = tmp_count;
			prefix_sutekoho_count++;

			// 牌プライオリティ比較(プライオリティが一番低い候補を算出)
			tmp_sutekoho_priority = sutekoho_priority[tmp_count] + sutekoho_nearby_hai_count[tmp_count];
			if( tmp_fixed_sutekoho_priority >= tmp_sutekoho_priority){
				fixed_sutekoho_num = tmp_count;
				tmp_fixed_sutekoho_priority = tmp_sutekoho_priority;
			}

		}
	}

	// 最終捨牌候補算出(ドラ検討)
	// ドラ牌が3-7である
	if( (tmp_dora_hai> 2 && tmp_dora_hai< 8) || 
	    (tmp_dora_hai>12 && tmp_dora_hai<18) || 
	    (tmp_dora_hai>22 && tmp_dora_hai<28) ){

		// 最終捨牌候補がドラ牌かつプレ候補牌が2枚以上
		if( sutekoho_hai[fixed_sutekoho_num] == tmp_dora_hai &&
		    prefix_sutekoho_count > 1){

			// ドラの最終捨牌候補番号
			tmp_fixed_sutekoho_dora_num = fixed_sutekoho_num;

			// もう一度候補牌を確認する
			// 値を初期化
			tmp_fixed_sutekoho_priority = 999;
			tmp_sutekoho_priority = 0;

			// 最終捨牌候補の再計算
			for(int tmp_count=0; tmp_count < prefix_sutekoho_count; tmp_count++){

				// 牌プライオリティ比較(プライオリティが一番低い候補を算出)
				tmp_sutekoho_priority = sutekoho_priority[prefix_sutekoho_num[tmp_count]] + sutekoho_nearby_hai_count[prefix_sutekoho_num[tmp_count]];

				// ドラ候補ではない
				if( tmp_fixed_sutekoho_priority >= tmp_sutekoho_priority          &&
					tmp_fixed_sutekoho_dora_num != prefix_sutekoho_num[tmp_count] ){
					// 再計算後の最終捨牌候補
					fixed_sutekoho_num = prefix_sutekoho_num[tmp_count];
					tmp_fixed_sutekoho_priority = tmp_sutekoho_priority;
				}

			}

		}

	}else{
		// ドラ牌が1289牌又は字牌→変更しない
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 通常向聴数確認
/* ---------------------------------------------------------------------------------------------- */
void set_normal_shanten(){

	// 初期化
	shanten_normal  = 8;
	wrk_shanten     = 0;
	wrk_atama_count = 0;
	wrk_atama_hai   = 0;      // 頭牌番号の初期化

	// ----------------------------------------
	// 頭有りパターン
	// ----------------------------------------
	for(int hai=1; hai<PAI_MAX; hai++){

		// 頭確認
		if(tehai[hai] >= 2){            

			wrk_all_mentsu_count  = 0;
			wrk_all_taatsu_count  = 0;

			wrk_atama_count++;
			tehai[hai] -= 2;
			wrk_atama_hai = hai;   // 頭牌番号の設定

			// 色ごとの向聴算出
			set_mentsu_taatsu_count();

			// 戻し処理
			tehai[hai] += 2;
			wrk_atama_hai = 0;     // 頭牌番号の無効化
			wrk_atama_count--;

		}
	}

	// ----------------------------------------
	// 頭無しパターン
	// ----------------------------------------
	set_mentsu_taatsu_count();

}

/* ---------------------------------------------------------------------------------------------- */
// 面子数・塔子数カウント処理
/* ---------------------------------------------------------------------------------------------- */
void set_mentsu_taatsu_count(){

	// 初期定義
	int tmp_count;

	// 色の分だけ繰り返し処理
	for(int color = 0; color < 4; color++){

		// 初期化
		wrk_color_shanten[color] = 9;
		wrk_mentsu_count[color]  = 0;
		wrk_taatsu_count[color]  = 0;

		// 手牌設定
		for(int color_hai = 0; color_hai < 10; color_hai++){
			if( color !=3 || color_hai < 8){
				wrk_color_tehai[color][color_hai]=tehai[color*10+color_hai];
			}else{
				wrk_color_tehai[color][color_hai]=0;
			}
		}

		// 面子確認
		set_mentsu_count(color, 1);

	}

	// 面子・塔子数確認
	wrk_all_mentsu_count = 0;
	wrk_all_taatsu_count = 0;
	for(int color = 0; color < 4; color++){
		wrk_all_mentsu_count = wrk_all_mentsu_count + wrk_max_mentsu_count[color];
		wrk_all_taatsu_count = wrk_all_taatsu_count + wrk_max_taatsu_count[color];
	}

	// wrk_all_mentsu_count = wrk_max_mentsu_count[0] + wrk_max_mentsu_count[1] + wrk_max_mentsu_count[2] + wrk_max_mentsu_count[3];
	// wrk_all_taatsu_count = wrk_max_taatsu_count[0] + wrk_max_taatsu_count[1] + wrk_max_taatsu_count[2] + wrk_max_taatsu_count[3];

	// 仮向聴設定(鳴きメンツもカウントする)
	if((naki_count-kakan_count+wrk_all_mentsu_count) + wrk_all_taatsu_count > 4){
		// wrk_shanten = 8-(naki_count-kakan_count+wrk_all_mentsu_count)*2 - (4-(naki_count-kakan_count+wrk_all_mentsu_count));
		wrk_shanten = 8 - (naki_count-kakan_count+wrk_all_mentsu_count)*2 - (4-(naki_count-kakan_count+wrk_all_mentsu_count)) - wrk_atama_count;
	}else{
		wrk_shanten = 8 - (naki_count-kakan_count+wrk_all_mentsu_count)*2 - wrk_all_taatsu_count - wrk_atama_count;
	}

	// 向聴比較
	if( wrk_shanten < shanten_normal){

		// 通常向聴設定
		shanten_normal=wrk_shanten;

		// 頭情報セット
		atama_count = wrk_atama_count;
		atama_hai   = wrk_atama_hai;

		// 面子数セット
		mentsu_count = wrk_all_mentsu_count;
		tmp_count = 0;

		// 面子情報セット
		for(int color = 0; color < 4; color++){
			for(int tmp_i = 0; tmp_i < wrk_max_mentsu_count[color]; tmp_i++){
				mentsu_stat[tmp_count] = wrk_max_mentsu_stat[color][tmp_i];              // 面子情報設定
				mentsu_hai[tmp_count]  = wrk_max_mentsu_hai[color][tmp_i]+color*10;      // 牌番号設定
				tmp_count++;
			}
		}

		// 塔子数セット
		taatsu_count = wrk_all_taatsu_count;
		tmp_count = 0;

		// 塔子情報セット
		for(int color = 0; color < 4; color++){
			 for(int tmp_i=0;tmp_i<wrk_max_taatsu_count[color];tmp_i++){
				if(tmp_count < 4){
					taatsu_stat[tmp_count] = wrk_max_taatsu_stat[color][tmp_i];          // 塔子情報設定
					taatsu_hai[tmp_count]  = wrk_max_taatsu_hai[color][tmp_i]+color*10;  // 牌番号設定
					tmp_count++;
				}
			}
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 面子数カウント処理
/* ---------------------------------------------------------------------------------------------- */
void set_mentsu_count(int color, int hai){

	// ----------------------------------------
	// 0枚の場合は次の牌番号に進む
	// ----------------------------------------
	if( wrk_color_tehai[color][hai] == 0 ){
		hai++;
	}


	// ----------------------------------------
	// 無ければ塔子検索
	// ----------------------------------------
	if( hai >= 10 ){

		// 塔子確認
		set_taatsu_count(color, 1);

		// 処理の返し
		return;
	}

	// ----------------------------------------
	// 暗刻情報セット
	// ----------------------------------------
	if(wrk_color_tehai[color][hai] >= 3){

		wrk_mentsu_stat[color][wrk_mentsu_count[color]] = ANKO;       // 面子情報設定
		wrk_mentsu_hai[color][wrk_mentsu_count[color]]  = hai;        // 牌番号設定
		wrk_mentsu_count[color]++;
		wrk_color_tehai[color][hai]-=3;
		set_mentsu_count(color, hai);                                 // 面子情報除外の再起処理
		wrk_color_tehai[color][hai]+=3;
		wrk_mentsu_count[color]--;
		wrk_mentsu_stat[color][wrk_mentsu_count[color]] = NOMENTSU;   // 面子情報設定
		wrk_mentsu_hai[color][wrk_mentsu_count[color]]  = 0;          // 牌番号設定

	}


	// ----------------------------------------
	// 順子情報セット
	// ----------------------------------------
	if(wrk_color_tehai[color][hai]>0 &&  wrk_color_tehai[color][hai+1]>0 && wrk_color_tehai[color][hai+2]>0 && color != 3){

		wrk_mentsu_stat[color][wrk_mentsu_count[color]] = SHUNTSU;    // 面子情報設定
		wrk_mentsu_hai[color][wrk_mentsu_count[color]]  = hai;        // 牌番号設定
		wrk_mentsu_count[color]++;
		wrk_color_tehai[color][hai]--;
		wrk_color_tehai[color][hai+1]--;
		wrk_color_tehai[color][hai+2]--;
		set_mentsu_count(color, hai);                                 // 面子情報除外の再起処理
		wrk_color_tehai[color][hai]++;
		wrk_color_tehai[color][hai+1]++;
		wrk_color_tehai[color][hai+2]++;
		wrk_mentsu_count[color]--;
		wrk_mentsu_stat[color][wrk_mentsu_count[color]] = NOMENTSU;   // 面子情報設定
		wrk_mentsu_hai[color][wrk_mentsu_count[color]]  = 0;          // 牌番号設定

	}

	// ----------------------------------------
	// 次の面子情報除外の再起処理
	// ----------------------------------------
	set_mentsu_count(color, hai+1);

}

/* ---------------------------------------------------------------------------------------------- */
// 塔子数カウント処理
/* ---------------------------------------------------------------------------------------------- */
void set_taatsu_count(int color, int hai){

	// ----------------------------------------
	// 0枚の場合は次の牌番号に進む
	// ----------------------------------------
	if( wrk_color_tehai[color][hai] == 0 ){
		hai++;
	}

	// ----------------------------------------
	// 無ければ向聴算出
	// ----------------------------------------
	if( hai >= 10 ){

		// 色ごと向聴数の算出
		wrk_shanten = 8 - wrk_mentsu_count[color]*2 - wrk_taatsu_count[color];

		// 向聴数が少ないならば
		if( wrk_shanten < wrk_color_shanten[color]){

			// 通常向聴の仮置き
			wrk_color_shanten[color] = wrk_shanten;

			// 面子情報セット
			wrk_max_mentsu_count[color] = wrk_mentsu_count[color];
			for(int tmp_i=0;tmp_i<wrk_max_mentsu_count[color];tmp_i++){
				wrk_max_mentsu_stat[color][tmp_i] = wrk_mentsu_stat[color][tmp_i];      // 面子情報設定
				wrk_max_mentsu_hai[color][tmp_i]  = wrk_mentsu_hai[color][tmp_i];       // 牌番号設定
			}

			// 塔子情報セット
			wrk_max_taatsu_count[color] = wrk_taatsu_count[color];
			for(int tmp_i=0;tmp_i<wrk_max_taatsu_count[color];tmp_i++){
				wrk_max_taatsu_stat[color][tmp_i]=wrk_taatsu_stat[color][tmp_i];        // 塔子情報設定
				wrk_max_taatsu_hai[color][tmp_i]=wrk_taatsu_hai[color][tmp_i];          // 牌番号設定
			}

		}

		// 処理の返し
		return;

	}

	// ----------------------------------------
	// 塔子情報セット
	// ----------------------------------------
	if( wrk_mentsu_count[color] + wrk_taatsu_count[color] < 4 ){

		// 対子除外
		if(wrk_color_tehai[color][hai] == 2){
			wrk_taatsu_stat[color][wrk_taatsu_count[color]] = TOITSU;         // 塔子情報設定
			wrk_taatsu_hai[color][wrk_taatsu_count[color]]  = hai;            // 牌番号設定
			wrk_taatsu_count[color]++;
			wrk_color_tehai[color][hai]-=2;
			set_taatsu_count(color, hai);
			wrk_color_tehai[color][hai]+=2;
			wrk_taatsu_count[color]--;
			wrk_taatsu_stat[color][wrk_taatsu_count[color]] = NOMENTSU;       // 塔子情報設定
			wrk_taatsu_hai[color][wrk_taatsu_count[color]]  = 0;              // 牌番号設定
		}

		// 両面除外
		if(wrk_color_tehai[color][hai]>0 && wrk_color_tehai[color][hai+1]>0 && color != 3){
			wrk_taatsu_stat[color][wrk_taatsu_count[color]] = RYANMEN;        // 塔子情報設定
			wrk_taatsu_hai[color][wrk_taatsu_count[color]]  = hai;            // 牌番号設定
			wrk_taatsu_count[color]++;
			wrk_color_tehai[color][hai]--; 
			wrk_color_tehai[color][hai+1]--;
			set_taatsu_count(color, hai);
			wrk_color_tehai[color][hai]++; 
			wrk_color_tehai[color][hai+1]++;
			wrk_taatsu_count[color]--;
			wrk_taatsu_stat[color][wrk_taatsu_count[color]] = NOMENTSU;       // 塔子情報設定
			wrk_taatsu_hai[color][wrk_taatsu_count[color]]  = 0;              // 牌番号設定
		}

		// 嵌張除外
		if( wrk_color_tehai[color][hai]>0 && wrk_color_tehai[color][hai+2]>0 && color != 3 && hai%10<=8 ){
			wrk_taatsu_stat[color][wrk_taatsu_count[color]] = KANCHAN;        // 塔子情報設定
			wrk_taatsu_hai[color][wrk_taatsu_count[color]]  = hai;            // 牌番号設定
			wrk_taatsu_count[color]++;
			wrk_color_tehai[color][hai]--; 
			wrk_color_tehai[color][hai+2]--;
			set_taatsu_count(color, hai);
			wrk_color_tehai[color][hai]++; 
			wrk_color_tehai[color][hai+2]++;
			wrk_taatsu_count[color]--;
			wrk_taatsu_stat[color][wrk_taatsu_count[color]] = NOMENTSU;       // 塔子情報設定
			wrk_taatsu_hai[color][wrk_taatsu_count[color]]  = 0;              // 牌番号設定
		}
	}

	// ----------------------------------------
	// 次の塔子再起処理
	// ----------------------------------------
	set_taatsu_count(color, hai+1);

}

/* ---------------------------------------------------------------------------------------------- */
// 手牌テーブル定義
/* ---------------------------------------------------------------------------------------------- */
void settehaitbl(){

	// 変数定義
	tehai_count = 0;

	// 赤牌情報の変数定義
	int tmp_aka_man;
	int tmp_aka_pin;
	int tmp_aka_sou;

	// 赤牌情報の仮設定
	tmp_aka_man = aka_count[0];
	tmp_aka_pin = aka_count[1];
	tmp_aka_sou = aka_count[2];

	// 手牌テーブルの設定
	for(int tmp_i = 1; tmp_i < PAI_MAX; tmp_i++){

		// 手牌の数だけ繰り返し
		for(int tmp_j = 0; tmp_j < tehai[tmp_i]; tmp_j++){

			// 手牌テーブル設定
			tehaitbl[tehai_count] = tmp_i;

			// 赤牌テーブル設定
			if(tmp_i == 5 && tmp_aka_man > 0){
				tehaitbl_aka[tehai_count] = true;
				tmp_aka_man--;
			}else if(tmp_i == 15 && tmp_aka_pin > 0){
				tehaitbl_aka[tehai_count] = true;
				tmp_aka_pin--;
			}else if(tmp_i == 25 && tmp_aka_sou > 0){
				tehaitbl_aka[tehai_count] = true;
				tmp_aka_sou--;
			}else{
				tehaitbl_aka[tehai_count] = false;
			}

			// 仮置き手牌数;1
			tehai_count ++;

		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// pinfo情報定義
/* ---------------------------------------------------------------------------------------------- */
void set_pinfo(struct MJSPlyInfo *pinfo, LBPAct tmp_ply_act, int tmp_act_hai, int tmp_act_idx, int tmp_act_aka_count){

	// 値代入
	pinfo->ply_act = tmp_ply_act;             // アクションステータス
	pinfo->act_hai = tmp_act_hai;             // アクション牌
	pinfo->act_idx = tmp_act_idx;             // アクション牌のINDEX
	pinfo->act_aka_count = tmp_act_aka_count; // 赤牌枚数

	// ----------------------------------------
	// pinfo情報表示
	// ----------------------------------------
	if( print_ply_mode > 0){
		print_pinfo_act(pinfo);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：メッセージ表示
/* ---------------------------------------------------------------------------------------------- */
void print_mes(char* tmp_mes){

	// メッセージ表示
	fprintf(stderr, "%s", tmp_mes);

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：区切り線表示
/* ---------------------------------------------------------------------------------------------- */
void print_separator(){

	// 区切り線
	fprintf(stderr,"================\n");

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：卓開始情報
/* ---------------------------------------------------------------------------------------------- */
void print_version_info(){

	// 区切り線
	print_separator();

	// バージョン情報
	fprintf(stderr, "Mjsply Version %d.%d.%d.%d.%d\n", VER1,VER2,VER3,VER4,VER5);

	// プレーヤーキャラクター情報
	print_char_info();

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：卓開始情報
/* ---------------------------------------------------------------------------------------------- */
void print_taku_start(){

	// 区切り線
	print_separator();

	// 表題
	fprintf(stderr,"[start_game]\n");

	// ply_id(起家)情報
	fprintf(stderr,"ply_id = %d\n", ply_id);
	fprintf(stderr,"ply_id_shimo = %d\n", ply_id_shimo);

	// 赤牌情報
	for(int tmp_i = 0; tmp_i < 3; tmp_i++){
		fprintf(stderr,"max_aka_count[%d] = %d\n", tmp_i, max_aka_count[tmp_i]);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：局開始情報
/* ---------------------------------------------------------------------------------------------- */
void print_kyoku_start(){

	// 区切り線
	print_separator();

	// 表題
	fprintf(stderr,"[start_kyoku]\n");

	// 局INDEX情報
	fprintf(stderr,"kyoku_index = %d\n", kyoku_index);

	// 局情報
	fprintf(stderr,"---\n");
	if(ply_bakaze == 31){
		fprintf(stderr,"E-%d kyoku\n", kyoku);
	}else if(ply_bakaze == 32){
		fprintf(stderr,"S-%d kyoku\n", kyoku);
	}else if(ply_bakaze == 33){
		fprintf(stderr,"W-%d kyoku\n", kyoku);
	}else if(ply_bakaze == 34){
		fprintf(stderr,"N-%d kyoku\n", kyoku);
	}else{
		fprintf(stderr,"?-%d kyoku\n", kyoku);
	}

	// 局情報
	fprintf(stderr,"honba = %d\n", honba);
	fprintf(stderr,"riichibo = %d\n", riichibo);
	fprintf(stderr,"ie[ply_id]  = %d\n", ie[ply_id]);
	fprintf(stderr,"ply_bakaze  = %d\n", ply_bakaze);
	fprintf(stderr,"ply_zikaze  = %d\n", ply_zikaze);
	fprintf(stderr,"dora_hai[0] = %d\n", dora_hai[0]);

	// プレーヤの得点情報
	fprintf(stderr,"---\n");
	for(int tmp_ply = 0; tmp_ply < 4; tmp_ply++){
		fprintf(stderr,"ply_kyoku_score[%d] = %d\n", tmp_ply, ply_kyoku_score[tmp_ply] );
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：配牌情報
/* ---------------------------------------------------------------------------------------------- */
void print_haipai(int tmp_tsumo_hai, bool tmp_tsumo_aka){

	// 個別自摸牌
	fprintf(stderr,"---\n");
	fprintf(stderr,"tmp_tsumo_hai = %d : ", tmp_tsumo_hai);
	if(tmp_tsumo_aka == true){
		fprintf(stderr,"tmp_tsumo_aka = true\n");
	}else{
		fprintf(stderr,"tmp_tsumo_aka = false\n");
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：ライン手牌情報表示
/* ---------------------------------------------------------------------------------------------- */
void print_tehai_line(){

	// 初期化
	int tmp_count = 0;

	// 手牌表示
	print_separator();
	for(int tmp_i=0; tmp_i < PAI_MAX; tmp_i++){
		for(int tmp_j=0; tmp_j < tehai[tmp_i]; tmp_j++){
			fprintf(stderr,"%2d ", tmp_i);
			tmp_count++;
		}
	}

	// 改行
	fprintf(stderr,"\n");

	// 枚数
	fprintf(stderr,"手牌：%d枚\n", tmp_count);

	// 鳴き情報
	for(int tmp_i=0; tmp_i < naki_count; tmp_i++){
		fprintf(stderr,"%d:", tmp_i);
		print_mentsu(naki_stat[tmp_i], naki_hai[tmp_i], naki_idx[tmp_i], naki_aka[tmp_i]);
		fprintf(stderr,"\n");
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：ヒストグラム手牌情報表示
/* ---------------------------------------------------------------------------------------------- */
void print_tehai_hist(){

	// 区切り線
	print_separator();

	// ヒストグラム表示
	for(int tmp_i=0; tmp_i < PAI_MAX; tmp_i++){
		fprintf(stderr,"%d ", tehai[tmp_i]);
		if(tmp_i==0 || tmp_i==10 || tmp_i==20 || tmp_i==30 || tmp_i==37){
			fprintf(stderr,"\n");
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：赤牌枚数
/* ---------------------------------------------------------------------------------------------- */
void print_tehai_aka(){

	// 区切り線
	print_separator();
	for(int tmp_i=0; tmp_i < 3; tmp_i++){
		fprintf(stderr,"aka_count[%d] = %d\n", tmp_i, aka_count[tmp_i]);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：自摸牌情報
/* ---------------------------------------------------------------------------------------------- */
void print_tsumo_hai(){

	// 区切り線
	print_separator();
	fprintf(stderr,"自摸牌:%2d\n", ply_tsumo_hai);

	// 自摸赤
	if(ply_tsumo_aka == true){
		fprintf(stderr,"ply_tsumo_aka = true\n");
	}else{
		fprintf(stderr,"ply_tsumo_aka = false\n");
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：河情報
/* ---------------------------------------------------------------------------------------------- */
void print_kawa_line(){

	// 区切り線
	print_separator();

	// 捨牌情報
	for(int tmp_ply=0; tmp_ply < PLAYER_MAX; tmp_ply++){

		// リーチ情報
		if( ply_riichi_stat[tmp_ply] == true){
			fprintf(stderr,"id:%d Riichi:true  河:%2d枚 ", tmp_ply, ply_kawa_count[tmp_ply]);
		}else{
			fprintf(stderr,"id:%d Riichi:false 河:%2d枚 ", tmp_ply, ply_kawa_count[tmp_ply]);
		}

		// 河情報
		for(int tmp_i=0; tmp_i < ply_kawa_count[tmp_ply]; tmp_i++){

			if(kawa_aka[tmp_ply][tmp_i] == true){
				fprintf(stderr,"[%2d] ", kawa[tmp_ply][tmp_i]);
			}else{
				fprintf(stderr,"%2d ", kawa[tmp_ply][tmp_i]);
			}
		}

		// 改行
		fprintf(stderr,"\n");

	}

	// 区切り線
	// print_separator();

	// 表示牌情報

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：オリ情報
/* ---------------------------------------------------------------------------------------------- */
void print_ori_info(){

	// 区切り線
	print_separator();

	// オリステータスであるなら
	if (ply_tehai_ori_stat == true){

		// オリ有効
		fprintf(stderr,"オリ状態：有効\n");
		fprintf(stderr,"オリ番号：%d\n", ply_ori_algo_num);

		// オリ牌表示
		if (ply_ori_aka == true){
			fprintf(stderr,"オリ牌：%2d赤牌\n", ply_ori_hai);
		}else{
			fprintf(stderr,"オリ牌：%2d黒牌\n", ply_ori_hai);
		}

	}else{
		// オリ無効
		fprintf(stderr,"オリ状態：無効\n");
	}

	// 区切り線
	print_separator();

	// 各プレーヤのリーチ状態
	for(int tmp_ply=0; tmp_ply < PLAYER_MAX; tmp_ply++){

		// リーチ情報
		if( ply_riichi_stat[tmp_ply] == true){

			// リーチ状態
			fprintf(stderr,"id:%d Riichi:true  ",tmp_ply);

			// 各プレーヤの巡目
			for(int tmp_ply2=0; tmp_ply2 < PLAYER_MAX; tmp_ply2++){
				fprintf(stderr,"id_%d_Riichi_junme:%2d ",tmp_ply, postriichi_turn_count[tmp_ply][tmp_ply2]);
			}

		}else{
			// リーチ状態
			fprintf(stderr,"id:%d Riichi:false ",tmp_ply);
		}

		// 改行
		fprintf(stderr,"\n");

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：自摸有り手牌情報
/* ---------------------------------------------------------------------------------------------- */
void print_tsumoari_tehai_info(){

	// 区切り線
	print_separator();

	// 自摸有り表記
	fprintf(stderr,"手牌情報：自摸有り\n");
	fprintf(stderr,"自摸回数：%d\n", kyoku_tsumo_count);

	// 有効牌
	fprintf(stderr,"向聴数%d向聴\n", shanten_normal);
	fprintf(stderr,"頭枚数%d枚\n"  , atama_count);
	fprintf(stderr,"メンツ数%d枚\n", mentsu_count);
	fprintf(stderr,"ターツ数%d枚\n", taatsu_count);

	// 捨牌候補数
	fprintf(stderr,"捨牌候補%d種\n", sutekoho_count);

	// 一覧表示
	for(int tmp_i = 0; tmp_i < sutekoho_count; tmp_i++){
		print_sutekoho(tmp_i);
	}

	// 11段目・仮置きシャンテンテーブル情報
	fprintf(stderr,"---\n");
	fprintf(stderr,"仮テーブル行総数：%d 計算対象総数：%d\n", karitbl_count, karitbl_calc_count);

	// 最終捨牌候補
	fprintf(stderr,"---\n");
	fprintf(stderr,"最終捨牌候補：No.%d：牌%2d\n", fixed_sutekoho_num+1, sutekoho_hai[fixed_sutekoho_num]);

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：自摸無し手牌情報
/* ---------------------------------------------------------------------------------------------- */
void print_tsumonashi_tehai_info(){

	// 自摸あり表記
	print_separator();
	fprintf(stderr,"手牌情報：自摸無し\n");

	// 有効牌
	fprintf(stderr,"向聴数%d向聴\n", shanten_normal);
	fprintf(stderr,"頭枚数%d枚\n"  , atama_count);
	fprintf(stderr,"メンツ数%d枚\n", mentsu_count);
	fprintf(stderr,"ターツ数%d枚\n", taatsu_count);

	// 萬子
	fprintf(stderr,"m ");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(yuko_hai_13mai[tmp_j+1] == true){
			fprintf(stderr,"%d",tmp_j+1);
		}else{
			fprintf(stderr," ");
		}
	}
	fprintf(stderr,"\n");

	// 筒子
	fprintf(stderr,"p ");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(yuko_hai_13mai[tmp_j+11] == true){
			fprintf(stderr,"%d",tmp_j+1);
		}else{
			fprintf(stderr," ");
		}
	}
	fprintf(stderr,"\n");

	// 索子
	fprintf(stderr,"s ");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(yuko_hai_13mai[tmp_j+21] == true){
			fprintf(stderr,"%d",tmp_j+1);
		}else{
			fprintf(stderr," ");
		}
	}
	fprintf(stderr,"\n");

	// 字牌
	fprintf(stderr,"z ");
	for(int tmp_j = 0; tmp_j < 7; tmp_j++){
		if(yuko_hai_13mai[tmp_j+31] == true){
			fprintf(stderr,"%d",tmp_j+1);
		}else{
			fprintf(stderr," ");
		}
	}
	fprintf(stderr,"\n");

	// 鳴き情報
	fprintf(stderr,"鳴き候補枚数%d枚\n", nakikoho_tbl_count);

	// 鳴きテーブル情報
	for(int tmp_i = 0; tmp_i < nakikoho_tbl_count; tmp_i++){

		// 1段目・牌番号
		fprintf(stderr,"%d:牌%d,IDX%d\n", tmp_i+1, nakikoho_tbl_hai[tmp_i], nakikoho_tbl_idx[tmp_i]);

		// 2段目・アクション
		if( nakikoho_tbl_act[tmp_i] == ACTRON){
			fprintf(stderr,"Act:ロン");
		}else if( nakikoho_tbl_act[tmp_i] == ACTPON){
			fprintf(stderr,"Act:ポン");
		}else if( nakikoho_tbl_act[tmp_i] == ACTCHI){
			fprintf(stderr,"Act:チー");
		}else{
			fprintf(stderr,"Act:不明");
		}

		// 2段目(続き)・鳴きの有無
		if( nakikoho_tbl_yesno[tmp_i] == true){
			fprintf(stderr,"鳴有");
		}else{
			fprintf(stderr,"鳴無");
		}

		// 改行
		fprintf(stderr,"\n");


		// 3段目・表示されている牌の枚数
		fprintf(stderr,"表示:%d枚\n", open_haiparts_count[nakikoho_tbl_hai[tmp_i]]);

		// 6段目・第一自摸時の和了確率
		fprintf(stderr,"R:%6.3f％\n", nakikoho_tbl_agari_rate[tmp_i]);

		fprintf(stderr,"Sc%6d\n", nakikoho_tbl_score[tmp_i]);

		fprintf(stderr,"ev%8.2f\n", nakikoho_tbl_parts_ev_score[tmp_i]);

		// 改行
		fprintf(stderr,"====\n");

/*
		// デバグ
		fprintf(stderr,"翻%d\n", yk.yakucount);

		// 通常役確認
		for(int tmp_i = 0; tmp_i < YAKU_SHUBETSU_MAX; tmp_i++){
			if(yk.yaku_flg[tmp_i] == true){
				fprintf(stderr,"%2d:有効\n",tmp_i);
			}else{
				// fprintf(stderr,"%2d:無効\n",tmp_i);
			}
		}

		// 改行
		fprintf(stderr,"====\n");
*/

	}

	// 河情報
	print_kawa_line();

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：捨牌候補情報
/* ---------------------------------------------------------------------------------------------- */
void print_sutekoho(int sutenum){

	// パーツ表示(候補牌)
	fprintf(stderr,"捨牌候補%2d：牌%2d　：", sutenum+1, sutekoho_hai[sutenum]);

	// 候補数表示
	fprintf(stderr,"%d向%2d種%2d枚ポインタ%d　：", 
		sutekoho_shanten[sutenum], 
		yuko_haishu_count[sutenum],
		yuko_hai_count[sutenum],
		sutekoho_priority[sutenum]);

	// 候補牌 - 萬子
	fprintf(stderr,"m ");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(yuko_hai[sutenum][tmp_j+1] == true){
			fprintf(stderr,"%d",tmp_j+1);
		}else{
			fprintf(stderr," ");
		}
	}

	// 候補牌 - 筒子
	fprintf(stderr,"p ");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(yuko_hai[sutenum][tmp_j+11] == true){
			fprintf(stderr,"%d",tmp_j+1);
		}else{
			fprintf(stderr," ");
		}
	}

	// 候補牌 - 索子
	fprintf(stderr,"s ");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(yuko_hai[sutenum][tmp_j+21] == true){
			fprintf(stderr,"%d",tmp_j+1);
		}else{
			fprintf(stderr," ");
		}
	}

	// 候補牌 - 字牌
	fprintf(stderr,"z");
	for(int tmp_j = 0; tmp_j < 7; tmp_j++){
		if(yuko_hai[sutenum][tmp_j+31] == true){
			fprintf(stderr,"%d",tmp_j+1);
		}else{
			fprintf(stderr," ");
		}
	}

	// 改行
	fprintf(stderr,"\n");

	// 表示牌合計
	fprintf(stderr,"OP牌%2d枚", yuko_hai_count_open_haiparts[sutenum]);

	// 期待値表示
	fprintf(stderr,"期待値%8.2f %2dパターン", 
	sutekoho_ev_score[sutenum],
	sutekoho_ev_count[sutenum]);

	// 改行
	fprintf(stderr,"\n");

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：プレーヤーキャラクター情報
/* ---------------------------------------------------------------------------------------------- */
void print_char_info(){

	// プレーヤーキャラクター表示
	if( ply_type == PLYCHAR_NONAME ){
		// 00:プレーヤー
		fprintf(stderr, "CHAR : NONAME_CHAR\n");
	}else if( ply_type == PLYCHAR_TAMPOPO ){
		// 01:プレーヤー
		fprintf(stderr, "CHAR : TAMPOPO\n");
	}else if( ply_type == PLYCHAR_HIMAWARI ){
		// 02:プレーヤー
		fprintf(stderr, "CHAR : HIMAWARI\n");
	}else if( ply_type == PLYCHAR_FATABA ){
		// 04:プレーヤー
		fprintf(stderr, "CHAR : FATABA\n");
	}else if( ply_type == PLYCHAR_WAKABA ){
		// 05:プレーヤー
		fprintf(stderr, "CHAR : WAKABA\n");
	}else if( ply_type == PLYCHAR_AOBA ){
		// 06:プレーヤー
		fprintf(stderr, "CHAR : AOBA\n");
	}else if( ply_type == PLYCHAR_AYAME ){
		// 08:プレーヤー
		fprintf(stderr, "CHAR : AYAME\n");
	}else if( ply_type == PLYCHAR_TSUBOMI ){
		// 11:プレーヤー
		fprintf(stderr, "CHAR : TSUBOMI\n");
	}else if( ply_type == PLYCHAR_MOMIJI ){
		// 12:プレーヤー
		fprintf(stderr, "CHAR : MOMIJI\n");
	}else if( ply_type == PLYCHAR_MJSPLY_TEST ){
		// 16:プレーヤー
		fprintf(stderr, "CHAR : MJSPLAY_TEST\n");
	}else{
		// それ以外:プレーヤー
		fprintf(stderr, "CHAR : UNKNOWN_CHAR\n");
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：pinfoアクション
/* ---------------------------------------------------------------------------------------------- */
void print_pinfo_act(struct MJSPlyInfo *pinfo){

	// アクション表示
	print_separator();
	if(pinfo->ply_act == ACTTSUMOAGARI){
		fprintf(stderr,"アクション：自摸和了\n");
	}else if(pinfo->ply_act == ACTSUTE){
		fprintf(stderr,"アクション：捨牌　　\n");
	}else if(pinfo->ply_act == ACTTSUMOGIRI){
		fprintf(stderr,"アクション：自摸切り\n");
	}else if(pinfo->ply_act == ACTNAKISUTE){
		fprintf(stderr,"アクション：鳴き捨牌\n");
	}else if(pinfo->ply_act == ACTRIICH){
		fprintf(stderr,"アクション：リーチ　\n");
	}else if(pinfo->ply_act == ACTANKAN){
		fprintf(stderr,"アクション：暗槓　　\n");
	}else if(pinfo->ply_act == ACTKAKAN){
		fprintf(stderr,"アクション：加槓　　\n");
	}else if(pinfo->ply_act == ACTNONAKI){
		fprintf(stderr,"アクション：鳴き無し\n");
	}else if(pinfo->ply_act == ACTRON){
		fprintf(stderr,"アクション：ロン和了\n");
	}else if(pinfo->ply_act == ACTPON){
		fprintf(stderr,"アクション：ポン\n");
	}else if(pinfo->ply_act == ACTCHI){
		fprintf(stderr,"アクション：チー\n");
	}else{
		fprintf(stderr,"アクション：不明　　\n");
	}

	// 牌情報
	fprintf(stderr,"pinfo->act_hai = %d\n", pinfo->act_hai);
	fprintf(stderr,"pinfo->act_idx = %d\n", pinfo->act_idx);
	fprintf(stderr,"pinfo->act_aka_count = %d\n", pinfo->act_aka_count);
}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：面子情報
/* ---------------------------------------------------------------------------------------------- */
void print_mentsu(LBMen men_stat, int men_hai, int men_idx, int aka_count){

	if(men_stat == MINSHUN){
		fprintf(stderr,"明順");
	}else if(men_stat == MINKO){
		fprintf(stderr,"明刻");
	}else if(men_stat == ANKAN){
		fprintf(stderr,"暗槓");
	}else if(men_stat == MINKAN){
		fprintf(stderr,"明槓");
	}else if(men_stat == KAKAN){
		fprintf(stderr,"加槓");
	}else{
		fprintf(stderr,"不明");
	}

	// 牌番号
	fprintf(stderr,", men_hai=%2d, men_idx=%2d, aka_count=%d", men_hai, men_idx, aka_count);

}

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
