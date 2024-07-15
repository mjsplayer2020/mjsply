/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： 麻雀AI：MJSakuraモジュール
 * バージョン     ： 0.0.1.0.19(局情報、ドラ情報)
 * プログラム名   ： mjs
 * ファイル名     ： player.c
 * クラス名       ： MJSPlayerクラス
 * 処理概要       ： プレーヤークラス
 * Ver0.0.1作成日 ： 2024/06/01 16:03:43
 * 最終更新日     ： 2024/07/15 16:18:29
 * 
 * Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "player.h"

/* ---------------------------------------------------------------------------------------------- */
// 卓開始処理
/* ---------------------------------------------------------------------------------------------- */
void PlyActTakuStart(int tmp_ply_num, int tmp_init_score, int tmp_aka_man_max, int tmp_aka_pin_max, int tmp_aka_sou_max){

	// -----------------------------
	// プレーヤ番号
	// -----------------------------

	// 自分のプレーヤ番号を設定
	ply_num = tmp_ply_num;

	// 下家のプレーヤ番号を設定
	ply_num_shimo = ( tmp_ply_num + 3 ) % 4;

	// -----------------------------
	// 赤牌情報定義
	// -----------------------------

	// 赤牌最大数の設定
	max_aka_count[0] = tmp_aka_man_max;
	max_aka_count[1] = tmp_aka_pin_max;
	max_aka_count[2] = tmp_aka_sou_max;

	// -----------------------------
	// 内部初期化
	// -----------------------------

	// プレーヤタイプ設定
	ply_type = PLYCHAR_MJSPLY_TEST;

	// 結果表示のモード設定
	print_ply_mode = 0;

	// ----------------------------------------
	// 結果表示
	// ----------------------------------------

	// バージョン情報
	print_version_info();

	// 卓開始情報
	if( print_ply_mode > 0){
		print_taku_start();
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 局開始処理
/* ---------------------------------------------------------------------------------------------- */
void PlyActKyokuStart(int tmp_kyoku, int tmp_kaze, int tmp_ie, int tmp_dora, int tmp_dora_aka){

	// 家情報
	kyoku = tmp_kyoku;             // 局
	ie = tmp_ie;                   // 家のプレーヤー番号
	ply_bakaze = tmp_kaze;         // 場風の牌番号
	ply_zikaze = TONNUM + ie;      // 自風の牌番号

	// ドラ情報
	dora_hai[0] = tmp_dora;
	dora_aka[0] = tmp_dora_aka;

	// 残り枚数(自摸合計数)
	kyoku_tsumo_count = 0;

	// 配牌初期化
	for(int i=0; i< PAI_MAX; i++){
		tehai[i] = 0;
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

	// 河情報
	for(int tmp_ply=0; tmp_ply < PLAYER_MAX; tmp_ply++){
		ply_kawa_count[tmp_ply]  = 0;
		ply_riichi_stat[tmp_ply] = false;
	}

	// プレーヤステータス
	ply_tehai_ori_stat = false;   // オリ無効化

	// ----------------------------------------
	// 結果表示：局開始処理
	// ----------------------------------------
	if( print_ply_mode > 0){
		// 局開始情報
		print_kyoku_start();
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 配牌処理
/* ---------------------------------------------------------------------------------------------- */
void PlyActHaipai(int tmp_tsumo_hai, bool tmp_tsumo_aka){

	// ヒストグラムに牌の枚数を加算
	tehai[tmp_tsumo_hai]++;

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

	// 配牌直後の手牌状態確認
	ChkTsumoNashiShanten();

	// 配牌後の手牌状態確認(ステータス確認メイン)
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

	// ----------------------------------------
	// アクション設定
	// ----------------------------------------

	// 自摸アクションの設定
	ply_act = ACTTSUMO;

	// 自摸アクションの設定
	ply_tsumo_hai = tmp_tsumo_hai;
	ply_tsumo_aka = tmp_tsumo_aka;

	// ----------------------------------------
	// 自摸回数カウント
	// ----------------------------------------
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
	// 自摸有の向聴算出
	// ----------------------------------------
	ChkTsumoAriShanten();

	// ----------------------------------------
	// オリ状態の確認
	// ----------------------------------------
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
		if(naki_count-ankan_count == 0){

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

			// アクション確認 - 暗槓
			// MJAIの不具合により、暗槓アクションをしない
		/*	if (ply_act == ACTTSUMO){
				PlyChkAnkan(tmp_tsumo_hai, tmp_tsumo_aka);
			}
		*/

			// アクション確認 - 加槓
			if (ply_act == ACTTSUMO){
				PlyChkKakan(tmp_tsumo_hai, tmp_tsumo_aka);
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

	// オリ状態確認
	if(ply_tehai_ori_stat == true){
		ply_sute_hai = ply_ori_hai;
	}else{
		// 捨牌確定
		ply_sute_hai = sutekoho_hai[fixed_sutekoho_num];
	}
	// ----------------------------------------
	// リーチ宣言確認
	// ----------------------------------------
	if( shanten_normal == 0          && // シャンテンが0
	    ply_riichi_mode == 0         && // リーチモードが0：リーチをかけていない
	    naki_count-ankan_count == 0  && // 鳴いていない
	    kyoku_tsumo_count      <= 66 ){ // 自摸番がある(残り牌が4枚以上)

		ply_act = ACTRIICH;
		// アクション定義
		ply_sute_hai = 0;
		ply_sute_aka=false;
		ply_riichi_mode = 1;   // リーチ宣言モード

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
			ply_riichi_mode = 2;   // リーチ宣言後モード
		}

	// ----------------------------------------
	// その他は捨牌処理
	// ----------------------------------------
	}else{

		// アクションの指定
		ply_act = ACTSUTE;

		// 赤牌設定
		// TODO:赤牌の優先順位を実装する
		if( ( ply_sute_hai == MAN5NUM && aka_count[0] > 0) || 
		    ( ply_sute_hai == PIN5NUM && aka_count[1] > 0) || 
		    ( ply_sute_hai == SOU5NUM && aka_count[2] > 0) ){
			ply_sute_aka=true;
		}else{
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
	// 変数定義
	// ----------------------------------------

	// リーチプレーヤ定義
	int  tmp_fixed_riichi_ply = 0;  // オリを定義するプレーヤ

	// 最終オリ牌定義
	int  tmp_ori_hai;              // 仮のオリ牌
	bool tmp_ori_aka;              // 仮のオリ牌の赤有無
	bool chk_flg;                  // チェックフラグ

	// オリ候補牌定義
	int  tmp_orihai_count;         // オリ牌枚数
	int  tmp_orihai_count2;        // オリ牌枚数
	int  tmp_orihai_num[14];       // 手牌番号
	int  tmp_orihai_num2[14];      // 手牌番号
//	int  tmp_orihai_ranknum[14];   // 手牌内のランク番号
	int  tmp_orihai_ranknum2[14];  // 手牌内のランク番号

	// ----------------------------------------
	// オリ無効化
	// ----------------------------------------
	ply_tehai_ori_stat = false;

	// ----------------------------------------
	// 相手プレーヤの内の誰かがリーチしているのか？
	// ----------------------------------------
	if( ply_riichi_stat[0] == true || ply_riichi_stat[1] == true || ply_riichi_stat[2] == true || ply_riichi_stat[3] == true){

		// 手牌のシャンテン数確認
		// テンパイしていない場合はその局をオリる
		if ( shanten_normal > 0){

			// オリモードの有効化
			ply_tehai_ori_stat = true;

			// 1名の相手プレーヤを決めて、その捨牌からオリを決める
			// その他2名の捨牌は考慮しない
			for( int tmp_i=0; tmp_i < PLAYER_MAX; tmp_i++ ){
				if( ply_riichi_stat[tmp_i] == true){
					tmp_fixed_riichi_ply = tmp_i;
					break;
				}
			}

			// 1.捨牌候補(手牌1枚以上)と牌ラングを定義する
			tmp_orihai_count2 = 0;
			for( int tmp_i=0; tmp_i < PAI_MAX; tmp_i++ ){

				// 手牌内にあれば(0以上ならば)、オリ候補牌として設定
				if(tehai[tmp_i] > 0){ 

					// オリ牌決定
					tmp_orihai_num2[tmp_orihai_count2] = tmp_i;

					// ランク確認
					if( tmp_i > 30){
							tmp_orihai_ranknum2[tmp_orihai_count2] = 5;
					}else{
						if( (tmp_i % 10) - 5 > 0 ){
							tmp_orihai_ranknum2[tmp_orihai_count2] = (tmp_i % 10) - 5;
						}else{
							tmp_orihai_ranknum2[tmp_orihai_count2] = 5 - (tmp_i % 10);
						}
					}

					// 加算
					tmp_orihai_count2++;

				}
			}

			// 2.ランク優先順位の低い順に並び替え
			tmp_orihai_count = 0;
			for( int tmp_rank=0; tmp_rank < 6; tmp_rank++ ){
				for( int tmp_i=0; tmp_i < tmp_orihai_count2; tmp_i++ ){

					// ランク番号確認
					if( 5 - tmp_rank == tmp_orihai_ranknum2[tmp_i] ){
	
						// 並び替え後のオリ牌番号設定
						tmp_orihai_num[tmp_orihai_count]      = tmp_orihai_num2[tmp_i];
						// tmp_orihai_ranknum[tmp_orihai_count]  = tmp_orihai_ranknum2[tmp_i];

						// 加算
						tmp_orihai_count++;

					}
				}
			}

			// オリ牌算出
			chk_flg = false;
			for( int tmp_i=0; tmp_i < tmp_orihai_count; tmp_i++ ){

				// 相手プレーヤの河確認
				for( int tmp_j=0; tmp_j < ply_kawa_count[tmp_fixed_riichi_ply]; tmp_j++ ){

					// tmp_fixed_riichi_plyの河に捨牌があれば、それをオリ牌と定義する
					if( tmp_orihai_num[tmp_i] == kawa[tmp_fixed_riichi_ply][tmp_j] ){

						// オリ牌定義
						ply_ori_hai = kawa[tmp_fixed_riichi_ply][tmp_j];

						// 赤牌確認
						if( ply_ori_hai == 5 || ply_ori_hai == 15 || ply_ori_hai == 25){

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

			// もしオリ牌が無いなら、オリモードは無効化する(オリない)
			if ( chk_flg == false){
				ply_tehai_ori_stat = false;
			}

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
	naki_stat[naki_count]=KAKAN;
	naki_hai[naki_count]=tmp_naki_hai;
	naki_idx[naki_count]=tmp_naki_hai;
	naki_aka[naki_count]=tmp_naki_aka_count;

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

	// 捨牌後の手牌状態確認(ステータス確認メイン)
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
// (3-4-1.)自摸捨牌時の手牌ヒストグラム処理
/* ---------------------------------------------------------------------------------------------- */
void PlySetTsumoSuteTehaiHist(){

	// ----------------------------------------
	// 捨牌処理
	// ----------------------------------------

		// 捨牌処理
		tehai[ply_sute_hai]--;

		// 赤牌数変更(捨牌)
		if(      ply_sute_hai == MAN5NUM && ply_sute_aka == true ){
			aka_count[0]--;
		}else if(ply_sute_hai == PIN5NUM && ply_sute_aka == true ){
			aka_count[1]--;
		}else if(ply_sute_hai == SOU5NUM && ply_sute_aka == true ){
			aka_count[2]--;
		}

		// 河情報設定
		kawa[ply_num][ply_kawa_count[ply_num]]     = ply_sute_hai;
		kawa_aka[ply_num][ply_kawa_count[ply_num]] = ply_sute_aka;
		ply_kawa_count[ply_num]++;

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
		if(      ply_tsumo_hai == MAN5NUM && ply_tsumo_aka == true ){
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
// (3-4-2.)プレーヤ手牌の状態確認(メイン処理)
/* ---------------------------------------------------------------------------------------------- */
void PlyChkPlyStat(){

	// 初期化
	ply_tehai_naki_stat = false;
	ply_yakuhai_stat    = false;

	// 役牌が三枚以上あれば
	if( tehai[HAKUNUM] > 2 || tehai[HATSUNUM] > 2 || tehai[CHUNNUM] > 2 || tehai[ply_bakaze] > 2 || tehai[ply_zikaze] > 2){

		ply_tehai_naki_stat = true;
		ply_yakuhai_stat    = true;

	}else{

		// 鳴きテーブルを確認して役牌が鳴かれているか確認する
		for( int tmp_i=0; tmp_i < naki_count; tmp_i++){
			if( naki_hai[tmp_i] == HAKUNUM || naki_hai[tmp_i] == HATSUNUM || naki_hai[tmp_i] == CHUNNUM || naki_hai[tmp_i] == ply_bakaze || naki_hai[tmp_i] == ply_zikaze ){
				ply_tehai_naki_stat = true;
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
// (3-4-3.)役有り確認
/* ---------------------------------------------------------------------------------------------- */
void PlyChkYaku(){

	// 役あり確認
	if(ply_yakuhai_stat == true || ply_riichi_mode > 1){
		ply_tehai_yaku_stat=true;
	}else{
		ply_tehai_yaku_stat=false;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// (3-4-4.)フリテン確認
/* ---------------------------------------------------------------------------------------------- */
void PlyChkFuriten(){

	// 初期定義
	ply_furiten_stat = false;

	// 和了確認
	for(int tmp_i = 0; tmp_i < nakikoho_tbl_count; tmp_i++){
		// ロンであること
		if( nakikoho_tbl_act[tmp_i] == ACTRON){
			for(int tmp_j=0; tmp_j < ply_kawa_count[ply_num]; tmp_j++){
				// 捨て牌にあるなら
				if(nakikoho_tbl_hai[tmp_i] == kawa[ply_num][tmp_j]){
					ply_furiten_stat = true;
				}
			}
		}
	}


}

/* ---------------------------------------------------------------------------------------------- */
// (3-4-5.)鳴きテーブルの状態確認
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
	kyoku_tsumo_count++;

}

/* ---------------------------------------------------------------------------------------------- */
// 他プレーヤの自摸
/* ---------------------------------------------------------------------------------------------- */
void PlyChkOthPlyRiichi(int tmp_ply_num){

	// ----------------------------------------
	// 自摸回数カウント
	// ----------------------------------------
	ply_riichi_stat[tmp_ply_num] = true;

}

/* ---------------------------------------------------------------------------------------------- */
// 鳴き確認
/* ---------------------------------------------------------------------------------------------- */
void PlyChkNaki(struct MJSPlyInfo *pinfo, int suteply, int hai, bool tmp_aka){

	// 初期設定
	ply_act = ACTNONAKI;
	ply_naki_idx = 0;
	ply_naki_aka_count = 0;

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
			}else if( nakikoho_tbl_yesno[tmp_i] == true && nakikoho_tbl_act[tmp_i] == ACTPON ){

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
			}else if( nakikoho_tbl_yesno[tmp_i] == true && nakikoho_tbl_act[tmp_i] == ACTCHI && suteply == ply_num_shimo){

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

	// (デバグ用)鳴き処理なし
/*	if( ply_act != ACTRON){
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

		// pinfo定義：ロン和了
		set_pinfo(pinfo, ply_act, ply_naki_idx, ply_naki_idx, ply_naki_aka_count);

	// ----------------------------------------
	// pinfo定義：チー
	// ----------------------------------------
	}else if( ply_act == ACTCHI){

		// pinfo定義：ロン和了
		set_pinfo(pinfo, ply_act, hai, ply_naki_idx, ply_naki_aka_count);

	// ----------------------------------------
	// pinfo定義：その他(鳴き無し)
	// ----------------------------------------
	}else{

		// pinfo定義：鳴き無し
		// set_pinfo(pinfo, ply_act, 0, 0, 0);
		set_pinfo(pinfo, ACTNONAKI, 0, 0, 0);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 鳴きアクション
/* ---------------------------------------------------------------------------------------------- */
void PlyActNaki(struct MJSPlyInfo *pinfo, int naki_ply_num, LBPAct naki_ply_act, int hai, int chi_hai_idx, int naki_aka_count){

	// 鳴きプレーヤー確認(鳴いたのが自分であれば)
	if( ply_num == naki_ply_num ){

		// ----------------------------------------
		// 晒し牌設定 - ポンの場合
		// ----------------------------------------
		if( naki_ply_act == ACTPON ){

			// ヒストグラムに牌の枚数を減算
			tehai[hai]-=2;

			// 赤牌枚数の減算
			if( hai == 5 || hai == 15 || hai == 25){
				aka_count[(hai-5)/10] = aka_count[(hai-5)/10] - ply_naki_aka_count;
			}

			// 晒し枚数追加
			naki_stat[naki_count]=MINKO;
			naki_hai[naki_count] = hai;
			naki_idx[naki_count] = hai;
			naki_aka[naki_count] = naki_aka_count;
			naki_count++;

		// ----------------------------------------
		// 晒し牌設定 - チーの場合
		// ----------------------------------------
		}else if( naki_ply_act == ACTCHI ){

			// ヒストグラムに牌の枚数を減算
			tehai[chi_hai_idx]--;
			tehai[chi_hai_idx+1]--;
			tehai[chi_hai_idx+2]--;
			tehai[hai]++;

			// 赤牌枚数の減算
			if( chi_hai_idx == 3 || chi_hai_idx == 13 || hai == 23){
				aka_count[(chi_hai_idx-3)/10] = aka_count[(chi_hai_idx-3)/10] - ply_naki_aka_count;
			}else if( chi_hai_idx == 4 || chi_hai_idx == 14 || hai == 24){
				aka_count[(chi_hai_idx-4)/10] = aka_count[(chi_hai_idx-4)/10] - ply_naki_aka_count;
			}else if( chi_hai_idx == 5 || chi_hai_idx == 15 || hai == 25){
				aka_count[(chi_hai_idx-5)/10] = aka_count[(chi_hai_idx-5)/10] - ply_naki_aka_count;
			}

			// 晒し枚数追加
			naki_stat[naki_count] = MINSHUN;
			naki_hai[naki_count]  = hai;
			naki_idx[naki_count]  = chi_hai_idx;
			naki_aka[naki_count]  = naki_aka_count;
			naki_count++;

		}

		// ----------------------------------------
		// シャンテン確認・捨牌確定
		// ----------------------------------------
		PlyChkNakiSute(pinfo);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 鳴き捨牌アクション決定
/* ---------------------------------------------------------------------------------------------- */
void PlyChkNakiSute(struct MJSPlyInfo *pinfo){

	// 自摸有の向聴算出
	ChkTsumoAriShanten();

	// 鳴き捨牌アクション時点ではオリは行わない

	// 捨牌設定
	ply_sute_hai=sutekoho_hai[fixed_sutekoho_num];

	// 赤牌設定
	// TODO:赤牌の優先順位を実装する
	if( ( ply_sute_hai ==  5 && aka_count[0] > 0) || 
	    ( ply_sute_hai == 15 && aka_count[1] > 0) || 
	    ( ply_sute_hai == 25 && aka_count[2] > 0) ){
		ply_sute_aka=true;
	}else{
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
// 鳴き捨牌処理
/* ---------------------------------------------------------------------------------------------- */
void PlyActNakiSute(){

	// 捨牌処理
	tehai[ply_sute_hai]--;

	// 赤牌数変更(捨牌)
	if( ply_sute_hai == 5 && ply_sute_aka==true ){
		aka_count[0]--;
	}else if(ply_sute_hai == 15 && ply_sute_aka==true){
		aka_count[1]--;
	}else if(ply_sute_hai == 25 && ply_sute_aka==true){
		aka_count[2]--;
	}


	// 河情報設定
	kawa[ply_num][ply_kawa_count[ply_num]]     = ply_sute_hai;
	kawa_aka[ply_num][ply_kawa_count[ply_num]] = ply_sute_aka;
	ply_kawa_count[ply_num]++;

	// 捨牌後の手牌状態確認
	ChkTsumoNashiShanten();

	// 捨牌後の手牌状態確認(ステータス確認メイン)
	PlyChkPlyStat();

}

/* ---------------------------------------------------------------------------------------------- */
// 自摸有りの向聴算出
/* ---------------------------------------------------------------------------------------------- */
void ChkTsumoAriShanten(){

	// ----------------------------------------
	// 初期化
	// ----------------------------------------
	int tmp_shanten2;        // 14枚シャンテン値の一時置き
	sutekoho_count = 0;

	// ----------------------------------------
	// シャンテン確認
	// ----------------------------------------

	// 自摸牌の追加
	if (ply_act == ACTTSUMO){
		tehai[ply_tsumo_hai]++;
	}

	// 14枚時点のシャンテン確認
	NormalShanten();  
	tmp_shanten2 = shanten_normal;

	// ----------------------------------------
	// 捨牌候補の確認
	// ----------------------------------------
	for(int i=0; i< PAI_MAX; i++){
		if(tehai[i]>0){
			// 定義初期化
			sutekoho_shanten[sutekoho_count]  = 0;
			yuko_haishu_count[sutekoho_count] = 0;
			yuko_hai_count[sutekoho_count]    = 0;
			sutekoho_hai[sutekoho_count]      = i;
			sutekoho_count++;
		}
	}

	// ----------------------------------------
	// 捨牌候補ごとのシャンテン確認
	// ----------------------------------------
	for(int tmp_count=0; tmp_count< sutekoho_count; tmp_count++){
		// 捨牌候補の設定
		tehai[sutekoho_hai[tmp_count]]--; // 自摸仮置き
		NormalShanten();
		sutekoho_shanten[tmp_count]=shanten_normal;
		yuko_haishu_count[tmp_count]=0;
		// 有効牌算出
		for(int j=1; j< PAI_MAX; j++){
			// 定義初期化
			yuko_hai[tmp_count][j]=false;
			//有効牌確認
			if (j !=10 && j!=20 && j!=30){
				// シャンテンが下がってないなら、有効牌を算出
				if (sutekoho_shanten[tmp_count] == tmp_shanten2){
					// シャンテン確認する牌の範囲を限定する
					if(tehai[j-2] >0 || tehai[j-1] >0 || tehai[j] >0 || tehai[j+1] >0 || tehai[j+2] >0){
						tehai[j]++;
						NormalShanten();
						if(shanten_normal == sutekoho_shanten[tmp_count]-1){
							yuko_hai[tmp_count][j]=true;
							yuko_haishu_count[tmp_count]++;
							yuko_hai_count[tmp_count]=yuko_hai_count[tmp_count]+4-tehai[j]+1;  // +1しているのはtehai[j]で仮置きしてるから
						}
						tehai[j]--;
					}
				}
			}
		}
		// 捨牌候補の設定戻し
		tehai[sutekoho_hai[tmp_count]]++;// 自摸戻し
	}

	// シャンテン値の戻し
	shanten_normal = tmp_shanten2;

	// 自摸牌の解除
	if (ply_act == ACTTSUMO){
		tehai[ply_tsumo_hai]--;
	}

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
	int tmp_shanten2;        // 14枚シャンテン値の一時置き
	nakikoho_tbl_count=0;

	// シャンテン確認
	NormalShanten_detail();
	tmp_shanten2 = shanten_normal;

	// 有効牌算出
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

				// 手牌仮置き
				tehai[j]++;
				NormalShanten_detail();

				// シャンテン数が減る場合
				if(shanten_normal == tmp_shanten2-1){

					// 有効牌の設定
					yuko_hai_13mai[j] = true;

					// テンパイならば、和了牌としてテーブルに格納する
					if(shanten_normal == -1){

						nakikoho_tbl_hai[nakikoho_tbl_count] = j;
						nakikoho_tbl_act[nakikoho_tbl_count] = ACTRON;
						nakikoho_tbl_idx[nakikoho_tbl_count] = j;
						nakikoho_tbl_yesno[nakikoho_tbl_count] = false;
						nakikoho_tbl_count++;

					}else{

						// 有効鳴き牌の確認
						for(int k=0; k< mentu_count; k++){

							// 鳴き牌設定(ポンの場合)
							if( mentu_stat[k] == ANKO && j == mentu_hai[k] ){
								// 鳴き牌設定
								nakikoho_tbl_hai[nakikoho_tbl_count] = j;
								nakikoho_tbl_act[nakikoho_tbl_count] = ACTPON;
								nakikoho_tbl_idx[nakikoho_tbl_count] = j;
								nakikoho_tbl_yesno[nakikoho_tbl_count] = false;
								nakikoho_tbl_count++;
							}

							// 鳴き牌設定(チーの場合)
							if( mentu_stat[k] == SHUNTSU && ( j == mentu_hai[k] || j == mentu_hai[k]+1 || j == mentu_hai[k]+2 )){
								// 鳴き牌設定
								nakikoho_tbl_hai[nakikoho_tbl_count] = j;
								nakikoho_tbl_act[nakikoho_tbl_count] = ACTCHI;
								nakikoho_tbl_idx[nakikoho_tbl_count] = mentu_hai[k];
								nakikoho_tbl_yesno[nakikoho_tbl_count] = false;
								nakikoho_tbl_count++;
							}

						}
					}
				}

				// 手牌仮置きの無効化
				tehai[j]--;

			}
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 捨牌候補の優先順位算出
/* ---------------------------------------------------------------------------------------------- */
void SetSutekohoPriority(){

	for(int tmp_count=0; tmp_count< sutekoho_count; tmp_count++){

		// 捨牌候補の優先順位設定
		if (sutekoho_hai[tmp_count] < 30){

			// 距離測定
			if( 5 - (sutekoho_hai[tmp_count] %10) > 0){
				sutekoho_priority[tmp_count] =  5 - (sutekoho_hai[tmp_count] %10);
			}else{
				sutekoho_priority[tmp_count] =( 5 - (sutekoho_hai[tmp_count] %10) )*-1;
			}

		}else if (sutekoho_hai[tmp_count] > 30 && sutekoho_hai[tmp_count] < 35){
			sutekoho_priority[tmp_count]=8;
		}else if (sutekoho_hai[tmp_count] > 34 && sutekoho_hai[tmp_count] < 38){
			sutekoho_priority[tmp_count]=7;
		}else{
			sutekoho_priority[tmp_count]=9;
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 捨牌候補の確認
/* ---------------------------------------------------------------------------------------------- */
void SetFixedSutekoho(){

	// 初期化
	int tmp_sutekoho_priority = -999;
	fixed_sutekoho_num=0;
	yuko_max_count=0;

	// 最大有効牌数
	for(int tmp_count=0; tmp_count< sutekoho_count; tmp_count++){
		if(shanten_normal == sutekoho_shanten[tmp_count]){
			if(yuko_max_count <= yuko_hai_count[tmp_count]){
				yuko_max_count = yuko_hai_count[tmp_count];
			}
		}
	}

	// 捨牌候補情報
	for(int tmp_count=0; tmp_count< sutekoho_count; tmp_count++){
		if(shanten_normal == sutekoho_shanten[tmp_count] && yuko_max_count == yuko_hai_count[tmp_count]){
			if( tmp_sutekoho_priority <= sutekoho_priority[tmp_count]){
				fixed_sutekoho_num = tmp_count;
				tmp_sutekoho_priority = sutekoho_priority[tmp_count];
			}
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 向聴数確認(通常)
/* ---------------------------------------------------------------------------------------------- */
void NormalShanten(){

	// 初期化
	shanten_normal   = 8;
	tmp_shanten      = 0;
	tmp_atama_count  = 0;
	tmp_mentu_count  = 0;
	tmp_taatu_count  = 0;

	// tmp_atama_hai=0;   // 頭牌番号の初期化

	// 処理開始
	for(int hai=1; hai<PAI_MAX; hai++){
		//
		if(tehai[hai] >= 2){            
			tmp_atama_count++;
			tehai[hai] -= 2;
			// tmp_atama_hai=i;  // 頭牌番号の設定
			mentu_cut(1);
			tehai[hai] += 2;
			// tmp_atama_hai=0;  // 頭牌番号の無効化
			tmp_atama_count--;
		}
	}

    // 頭なしの場合
    mentu_cut(1);

}

/* ---------------------------------------------------------------------------------------------- */
// メンツ削除処理
/* ---------------------------------------------------------------------------------------------- */
void mentu_cut(int hai){

	// ----------------------------------------
	// 0枚はスキップ
	// ----------------------------------------
	for(;!tehai[hai]; hai++);

	// ----------------------------------------
	// 無ければターツ検索
	// ----------------------------------------
	if( hai >= PAI_MAX ){
		taatu_cut(1);

		// 処理の返し
		return;
	}

	// ----------------------------------------
	// アンコ情報セット
	// ----------------------------------------
	if(tehai[hai] >= 3){

		tmp_mentu_count++;
		tehai[hai]-=3;
		mentu_cut(hai);  // メンツカットの再起処理
		tehai[hai]+=3;
		tmp_mentu_count--;

	}

	// ----------------------------------------
	// シュンツ情報セット
	// ----------------------------------------
	if(tehai[hai+1] && tehai[hai+2] && hai<30){

		tmp_mentu_count++;
		tehai[hai]--;
		tehai[hai+1]--;
		tehai[hai+2]--;
		mentu_cut(hai);   // メンツカットの再起処理
		tehai[hai]++;
		tehai[hai+1]++;
		tehai[hai+2]++;
		tmp_mentu_count--;

	}

	// ----------------------------------------
	// 次のメンツカットの再起処理
	// ----------------------------------------
	mentu_cut(hai+1);

}

/* ---------------------------------------------------------------------------------------------- */
// ターツ削除処理
/* ---------------------------------------------------------------------------------------------- */
void taatu_cut(int hai){

	// ----------------------------------------
	// 0枚はスキップ
	// ----------------------------------------
	for(;!tehai[hai]; hai++);

	// ----------------------------------------
	// 無ければシャンテン算出
	// ----------------------------------------
	if( hai >= PAI_MAX ){

		// シャンテン数の算出
		// tmp_shanten = 8-tmp_mentu_count*2-tmp_taatu_count-tmp_atama_count;
		tmp_shanten = 8-(naki_count-kakan_count)*2-tmp_mentu_count*2-tmp_taatu_count-tmp_atama_count;

		if( tmp_shanten < shanten_normal){

			// 通常シャンテンの仮置き
			shanten_normal=tmp_shanten;

		}

		// 処理の返し
		return;
	}

	// ----------------------------------------
	// ターツ情報セット
	// ----------------------------------------
	// if(tmp_mentu_count+tmp_taatu_count<4){
	if( (naki_count-kakan_count)+tmp_mentu_count+tmp_taatu_count < 4 ){

		// トイツカット
		if(tehai[hai]==2){

			tmp_taatu_count++;
			tehai[hai]-=2;
			taatu_cut(hai);
			tehai[hai]+=2;
			tmp_taatu_count--;
		}

		// 両面カット
		if(tehai[hai+1] && hai<30){

			tmp_taatu_count++;
			tehai[hai]--, tehai[hai+1]--;
			taatu_cut(hai);
			tehai[hai]++, tehai[hai+1]++;
			tmp_taatu_count--;
		}

		// カンチャンカット
		if( tehai[hai+2]&& hai<30 && hai%10<=8 ){

			tmp_taatu_count++;
			tehai[hai]--, tehai[hai+2]--;
			taatu_cut(hai);
			tehai[hai]++, tehai[hai+2]++;
			tmp_taatu_count--;
		}
	}

	// ----------------------------------------
	// 次のターツ再起処理
	// ----------------------------------------
	taatu_cut(hai+1);

}

/* ---------------------------------------------------------------------------------------------- */
// 向聴数確認(通常_面子情報付与版)
/* ---------------------------------------------------------------------------------------------- */
void NormalShanten_detail(){

	// 初期化
	shanten_normal   = 8;
	tmp_shanten      = 0;
	tmp_atama_count  = 0;
	tmp_mentu_count  = 0;
	tmp_taatu_count  = 0;

	tmp_atama_hai = 0;   // 頭牌番号の初期化

	// 処理開始
	for(int hai=1; hai<PAI_MAX; hai++){
		//
		if(tehai[hai] >= 2){            
			tmp_atama_count++;
			tehai[hai] -= 2;
			tmp_atama_hai = hai;   // 頭牌番号の設定
			mentu_cut_detail(1);
			tehai[hai] += 2;
			tmp_atama_hai = 0;     // 頭牌番号の無効化
			tmp_atama_count--;
		}
	}

    // 頭なしの場合
    mentu_cut_detail(1);

}

/* ---------------------------------------------------------------------------------------------- */
// メンツ削除処理(面子情報付与版)
/* ---------------------------------------------------------------------------------------------- */
void mentu_cut_detail(int hai){

	// ----------------------------------------
	// 0枚はスキップ
	// ----------------------------------------
	for(;!tehai[hai]; hai++);

	// ----------------------------------------
	// 無ければターツ検索
	// ----------------------------------------
	if( hai >= PAI_MAX ){
		taatu_cut_detail(1);

		// 処理の返し
		return;
	}

	// ----------------------------------------
	// アンコ情報セット
	// ----------------------------------------
	if(tehai[hai] >= 3){

		tmp_mentu_stat[tmp_mentu_count] = ANKO;     // 面子情報設定
		tmp_mentu_hai[tmp_mentu_count]  = hai;      // 牌番号設定
		tmp_mentu_count++;
		tehai[hai]-=3;
		mentu_cut_detail(hai);  // メンツカットの再起処理
		tehai[hai]+=3;
		tmp_mentu_count--;
		tmp_mentu_stat[tmp_mentu_count] = NOMENTSU;   // 面子情報設定
		tmp_mentu_hai[tmp_mentu_count]  = hai;        // 牌番号設定

	}

	// ----------------------------------------
	// シュンツ情報セット
	// ----------------------------------------
	if(tehai[hai+1] && tehai[hai+2] && hai<30){

		tmp_mentu_stat[tmp_mentu_count] = SHUNTSU;  // 面子情報設定
		tmp_mentu_hai[tmp_mentu_count]  = hai;      // 牌番号設定
		tmp_mentu_count++;
		tehai[hai]--;
		tehai[hai+1]--;
		tehai[hai+2]--;
		mentu_cut_detail(hai);   // メンツカットの再起処理
		tehai[hai]++;
		tehai[hai+1]++;
		tehai[hai+2]++;
		tmp_mentu_count--;
		tmp_mentu_stat[tmp_mentu_count] = NOMENTSU;   // 面子情報設定
		tmp_mentu_hai[tmp_mentu_count]  = hai;        // 牌番号設定

	}

	// ----------------------------------------
	// 次のメンツカットの再起処理
	// ----------------------------------------
	mentu_cut_detail(hai+1);

}

/* ---------------------------------------------------------------------------------------------- */
// ターツ削除処理(ターツ情報付与版)
/* ---------------------------------------------------------------------------------------------- */
void taatu_cut_detail(int hai){

	// ----------------------------------------
	// 0枚はスキップ
	// ----------------------------------------
	for(;!tehai[hai]; hai++);

	// ----------------------------------------
	// 無ければシャンテン算出
	// ----------------------------------------
	if( hai >= PAI_MAX ){

		// シャンテン数の算出
		// tmp_shanten = 8-tmp_mentu_count*2-tmp_taatu_count-tmp_atama_count;
		tmp_shanten = 8-(naki_count-kakan_count)*2-tmp_mentu_count*2-tmp_taatu_count-tmp_atama_count;

		if( tmp_shanten < shanten_normal){

			// 通常シャンテンの仮置き
			shanten_normal=tmp_shanten;

			// アタマ情報セット
			atama_count = tmp_atama_count;
			atama_hai   = tmp_atama_hai;

			// メンツ情報セット
			mentu_count = tmp_mentu_count;
			for(int tmp_i=0;tmp_i<tmp_mentu_count;tmp_i++){
				mentu_stat[tmp_i] = tmp_mentu_stat[tmp_i];  // 面子情報設定
				mentu_hai[tmp_i]  = tmp_mentu_hai[tmp_i];   // 牌番号設定
			}

			// ターツ情報セット
			taatu_count = tmp_taatu_count;
			for(int tmp_i=0;tmp_i<tmp_taatu_count;tmp_i++){
				taatsu_stat[tmp_i]=tmp_mentu_stat[tmp_i];  // ターツ情報設定
				taatsu_hai[tmp_i]=tmp_taatsu_hai[tmp_i];   // 牌番号設定
			}

		}

		// 処理の返し
		return;
	}

	// ----------------------------------------
	// ターツ情報セット
	// ----------------------------------------
	// if(tmp_mentu_count+tmp_taatu_count<4){
	if( (naki_count-kakan_count)+tmp_mentu_count+tmp_taatu_count < 4 ){

		// トイツカット
		if(tehai[hai]==2){
			tmp_taatsu_stat[tmp_mentu_count] = TOITSU;   // ターツ情報設定
			tmp_taatsu_hai[tmp_mentu_count]  = hai;      // 牌番号設定
			tmp_taatu_count++;
			tehai[hai]-=2;
			taatu_cut_detail(hai);
			tehai[hai]+=2;
			tmp_taatu_count--;
			tmp_taatsu_stat[tmp_mentu_count] = NOMENTSU;  // ターツ情報設定
			tmp_taatsu_hai[tmp_mentu_count]  = hai;       // 牌番号設定
		}

		// 両面カット
		if(tehai[hai+1] && hai<30){

			tmp_taatsu_stat[tmp_mentu_count] = TOITSU;   // ターツ情報設定
			tmp_taatsu_hai[tmp_mentu_count]  = hai;      // 牌番号設定
			tmp_taatu_count++;
			tehai[hai]--, tehai[hai+1]--;
			taatu_cut_detail(hai);
			tehai[hai]++, tehai[hai+1]++;
			tmp_taatu_count--;
			tmp_taatsu_stat[tmp_mentu_count] = NOMENTSU;  // ターツ情報設定
			tmp_taatsu_hai[tmp_mentu_count]  = hai;       // 牌番号設定
		}

		// カンチャンカット
		if( tehai[hai+2]&& hai<30 && hai%10<=8 ){

			tmp_taatsu_stat[tmp_mentu_count] = TOITSU;   // ターツ情報設定
			tmp_taatsu_hai[tmp_mentu_count]  = hai;      // 牌番号設定
			tmp_taatu_count++;
			tehai[hai]--, tehai[hai+2]--;
			taatu_cut_detail(hai);
			tehai[hai]++, tehai[hai+2]++;
			tmp_taatu_count--;
			tmp_taatsu_stat[tmp_mentu_count] = NOMENTSU;  // ターツ情報設定
			tmp_taatsu_hai[tmp_mentu_count]  = hai;       // 牌番号設定
		}
	}

	// ----------------------------------------
	// 次のターツ再起処理
	// ----------------------------------------
	taatu_cut_detail(hai+1);
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
	printf("================\n");

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

	// ply_id(起家)情報
	printf("ply_id = %d\n", ply_num);
	printf("ply_id_shimo = %d\n", ply_num_shimo);

	// 赤牌情報
	for(int tmp_i = 0; tmp_i < 3; tmp_i++){
		printf("max_aka_count[%d] = %d\n", tmp_i, max_aka_count[tmp_i]);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：局開始情報
/* ---------------------------------------------------------------------------------------------- */
void print_kyoku_start(){

	// 区切り線
	print_separator();

	// 局情報
	printf("kyoku = %d\n", kyoku);
	printf("ie = %d\n", ie);
	printf("ply_bakaze  = %d\n", ply_bakaze);
	printf("ply_zikaze  = %d\n", ply_zikaze);
	printf("dora_hai[0] = %d\n", dora_hai[0]);
	if(dora_aka[0] == true){
		printf("dora_aka[0] = true\n");
	}else{
		printf("dora_aka[0] = false\n");
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：配牌情報
/* ---------------------------------------------------------------------------------------------- */
void print_haipai(int tmp_tsumo_hai, bool tmp_tsumo_aka){

	printf("---\n");
	printf("tmp_tsumo_hai = %d\n", tmp_tsumo_hai);
	if(tmp_tsumo_aka == true){
		printf("tmp_tsumo_aka = true\n");
	}else{
		printf("tmp_tsumo_aka = false\n");
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：ライン手牌情報表示
/* ---------------------------------------------------------------------------------------------- */
void print_tehai_line(){

	// 初期化
	int tmp_count=0;

	// 手牌表示
	print_separator();
	for(int tmp_i=0; tmp_i < PAI_MAX; tmp_i++){
		for(int tmp_j=0; tmp_j < tehai[tmp_i]; tmp_j++){
			printf("%2d ", tmp_i);
			tmp_count++;
		}
	}

	// 改行
	printf("\n");

	// 枚数
	printf("手牌：%d枚\n", tmp_count);

	// 鳴き情報
	for(int tmp_i=0; tmp_i < naki_count; tmp_i++){
		printf("%d:", tmp_i);
		print_mentsu(naki_stat[tmp_i], naki_hai[tmp_i], naki_idx[tmp_i], naki_aka[tmp_i]);
		printf("\n");
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
		printf("%d ", tehai[tmp_i]);
		if(tmp_i==0 || tmp_i==10 || tmp_i==20 || tmp_i==30 || tmp_i==37){
			printf("\n");
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
		printf("aka_count[%d] = %d\n", tmp_i, aka_count[tmp_i]);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：自摸牌情報
/* ---------------------------------------------------------------------------------------------- */
void print_tsumo_hai(){

	// 区切り線
	print_separator();
	printf("自摸牌:%2d\n", ply_tsumo_hai);

	// 自摸赤
	if(ply_tsumo_aka == true){
		printf("ply_tsumo_aka = true\n");
	}else{
		printf("ply_tsumo_aka = false\n");
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：河情報
/* ---------------------------------------------------------------------------------------------- */
void print_kawa_line(){

	// 区切り線
	print_separator();

	for(int tmp_ply=0; tmp_ply < PLAYER_MAX; tmp_ply++){

		// リーチ情報
		if( ply_riichi_stat[tmp_ply] == true){
			printf("id:%d リーチ:true 河:%2d枚 ", tmp_ply, ply_kawa_count[tmp_ply]);
		}else{
			printf("id:%d リーチ:false河:%2d枚 ", tmp_ply, ply_kawa_count[tmp_ply]);
		}

		// 河情報
		for(int tmp_i=0; tmp_i < ply_kawa_count[tmp_ply]; tmp_i++){

			if(kawa_aka[tmp_ply][tmp_i] == true){
				printf("[%2d] ", kawa[tmp_ply][tmp_i]);
			}else{
				printf("%2d ", kawa[tmp_ply][tmp_i]);
			}
		}

		// 改行
		printf("\n");

	}

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
		printf("オリステータス：オリ有効\n");

		// オリ牌表示
		if (ply_ori_aka == true){
			printf("オリ牌番号：%2d赤牌\n", ply_ori_hai);
		}else{
			printf("オリ牌番号：%2d黒牌\n", ply_ori_hai);
		}

	}else{
		// オリ無効
		printf("オリステータス：オリ無効\n");
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：自摸有り手牌情報
/* ---------------------------------------------------------------------------------------------- */
void print_tsumoari_tehai_info(){

	// 区切り線
	print_separator();

	// 自摸有り表記
	printf("手牌情報：自摸有り\n");
	printf("自摸回数：%d\n", kyoku_tsumo_count);

	// 有効牌
	printf("向聴数%d枚\n"  , shanten_normal);
	printf("頭枚数%d枚\n"  , atama_count);
	printf("メンツ数%d枚\n", mentu_count);
	printf("ターツ数%d枚\n", taatu_count);

	// 捨牌候補数
	printf("捨牌候補%d種\n", sutekoho_count);

	// 一覧表示
	for(int tmp_i = 0; tmp_i < sutekoho_count; tmp_i++){
		print_sutekoho(tmp_i);
	}

	// 最終捨牌候補
	printf("---\n");
	printf("最終捨牌候補：No.%d：牌%2d\n", fixed_sutekoho_num+1, sutekoho_hai[fixed_sutekoho_num]);

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：自摸無し手牌情報
/* ---------------------------------------------------------------------------------------------- */
void print_tsumonashi_tehai_info(){

	// 自摸あり表記
	print_separator();
	printf("手牌情報：自摸無し\n");

	// 有効牌
	printf("向聴数%d枚\n"  , shanten_normal);
	printf("頭枚数%d枚\n"  , atama_count);
	printf("メンツ数%d枚\n", mentu_count);
	printf("ターツ数%d枚\n", taatu_count);

	// 萬子
	printf("m ");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(yuko_hai_13mai[tmp_j+1] == true){
			printf("%d",tmp_j+1);
		}else{
			printf(" ");
		}
	}
	printf("\n");

	// 筒子
	printf("p ");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(yuko_hai_13mai[tmp_j+11] == true){
			printf("%d",tmp_j+1);
		}else{
			printf(" ");
		}
	}
	printf("\n");

	// 索子
	printf("s ");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(yuko_hai_13mai[tmp_j+21] == true){
			printf("%d",tmp_j+1);
		}else{
			printf(" ");
		}
	}
	printf("\n");

	// 字牌
	printf("z ");
	for(int tmp_j = 0; tmp_j < 7; tmp_j++){
		if(yuko_hai_13mai[tmp_j+31] == true){
			printf("%d",tmp_j+1);
		}else{
			printf(" ");
		}
	}
	printf("\n");

	// 鳴き情報
	printf("鳴き候補枚数%d枚\n", nakikoho_tbl_count);

	// 鳴きテーブル情報
	for(int tmp_i = 0; tmp_i < nakikoho_tbl_count; tmp_i++){

		// 1段目・牌番号
		printf("%d:牌%d,IDX%d\n", tmp_i+1, nakikoho_tbl_hai[tmp_i], nakikoho_tbl_idx[tmp_i]);

		// 2段目・アクション
		if( nakikoho_tbl_act[tmp_i] == ACTRON){
			printf("Act:ロン");
		}else if( nakikoho_tbl_act[tmp_i] == ACTPON){
			printf("Act:ポン");
		}else if( nakikoho_tbl_act[tmp_i] == ACTCHI){
			printf("Act:チー");
		}else{
			printf("Act:不明");
		}

		// 3段目・鳴きの有無
		if( nakikoho_tbl_yesno[tmp_i] == true){
			printf("鳴有");
		}else{
			printf("鳴無");
		}

		// 改行
		printf("\n");

	}

	// 河情報
	print_kawa_line();

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：捨牌候補情報
/* ---------------------------------------------------------------------------------------------- */
void print_sutekoho(int sutenum){

	// パーツ表示(候補牌)
	printf("捨牌候補%2d：牌%2d　：", sutenum+1, sutekoho_hai[sutenum]);

	// 候補数表示
	printf("%d向%2d種%2d枚ポインタ%d　：", 
		sutekoho_shanten[sutenum], 
		yuko_haishu_count[sutenum],
		yuko_hai_count[sutenum],
		sutekoho_priority[sutenum]);

	// 候補牌 - 萬子
	printf("m ");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(yuko_hai[sutenum][tmp_j+1] == true){
			printf("%d",tmp_j+1);
		}else{
			printf(" ");
		}
	}

	// 候補牌 - 筒子
	printf("p ");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(yuko_hai[sutenum][tmp_j+11] == true){
			printf("%d",tmp_j+1);
		}else{
			printf(" ");
		}
	}

	// 候補牌 - 索子
	printf("s ");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(yuko_hai[sutenum][tmp_j+21] == true){
			printf("%d",tmp_j+1);
		}else{
			printf(" ");
		}
	}

	// 候補牌 - 字牌
	printf("z");
	for(int tmp_j = 0; tmp_j < 7; tmp_j++){
		if(yuko_hai[sutenum][tmp_j+31] == true){
			printf("%d",tmp_j+1);
		}else{
			printf(" ");
		}
	}

	// 改行
	printf("\n");

}

/* ---------------------------------------------------------------------------------------------- */
// 表示処理：キャラ情報
/* ---------------------------------------------------------------------------------------------- */
void print_char_info(){

	// キャラ表示
	if( ply_type == PLYCHAR_NONAME ){
		fprintf(stderr, "CHAR : NONAME_CHAR\n");
	}else if( ply_type == PLYCHAR_MJSPLY_TEST ){
		fprintf(stderr, "CHAR : MJSPLAY_TEST\n");
	}else{
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
// 表示処理：面子情報
/* ---------------------------------------------------------------------------------------------- */
void print_mentsu(LBMen men_stat, int men_hai, int men_idx, int aka_count){

	if(men_stat == MINSHUN){
		printf("明順");
	}else if(men_stat == MINKO){
		printf("明刻");
	}else if(men_stat == ANKAN){
		printf("暗槓");
	}else if(men_stat == MINKAN){
		printf("明槓");
	}else if(men_stat == KAKAN){
		printf("加槓");
	}else{
		printf("不明");
	}

	// 牌番号
	printf(" men_hai=%2d men_idx=%2d aka_count=%d", men_hai, men_idx, aka_count);

}

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
