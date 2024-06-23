/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： 麻雀AI：MJSakuraモジュール
 * バージョン     ： 0.0.1.0.9(暗槓処理実装)
 * プログラム名   ： mjs
 * ファイル名     ： player.c
 * クラス名       ： MJSPlayerクラス
 * 処理概要       ： プレーヤークラス
 * Ver0.0.1作成日 ： 2024/06/01 16:03:43
 * 最終更新日     ： 2024/06/23 10:53:04
 * 
 * Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "player.h"

/* ---------------------------------------------------------------------------------------------- */
// ライン手牌情報表示
/* ---------------------------------------------------------------------------------------------- */
void print_tehai_line(){

}

/* ---------------------------------------------------------------------------------------------- */
// ヒストグラム手牌情報表示
/* ---------------------------------------------------------------------------------------------- */
void print_tehai_hist(){

	printf("================\n");
	for(int tmp_i=0; tmp_i < 38; tmp_i++){
		printf("%d ", tehai[tmp_i]);
		if(tmp_i==0 || tmp_i==10 || tmp_i==20 || tmp_i==30 || tmp_i==37){
			printf("\n");
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// ライン手牌情報表示
/* ---------------------------------------------------------------------------------------------- */
void print_tehai_aka(){

	printf("================\n");
	for(int tmp_i=0; tmp_i < 3; tmp_i++){
		printf("aka_count[%d] = %d\n", tmp_i, aka_count[tmp_i]);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 自摸有り手牌情報
/* ---------------------------------------------------------------------------------------------- */
void print_tsumoari_tehai_info(){

	// 自摸あり表記
	printf("================\n");
	printf("手牌情報：自摸有り\n");

	// 捨牌候補数
	printf("捨牌候補%d種\n", sutekoho_count);

	// 一覧表示
	for(int tmp_i = 0; tmp_i < sutekoho_count; tmp_i++){
		print_sutekoho(tmp_i);
	}

	// 最終捨牌候補
	printf("---\n");
	printf("最終捨牌候補：No.%d：牌%2d\n", fixed_sutekoho_num+1, sutekoho_hai[fixed_sutekoho_num]);
	// dparts->DispHai( SPACE_XSIZE+80, PLY_YSTART+380, sutekoho_hai[fixed_sutekoho_num], false, false, 0, 0);

	// 手牌ヒストグラム表示
	print_tehai_hist();

	// 赤牌情報
	print_tehai_aka();

/*
	// アクション表示
	if( ply_act == ACTSUTE){
		sprintf(tmp_disp_msg, "捨牌　　");

		// 牌表示
		if(ply_sute_aka == true){
			dparts->DispHai( 270, PLY_YSTART+380, ply_sute_hai, true, false, 0, 0);
		}else{
			dparts->DispHai( 270, PLY_YSTART+380, ply_sute_hai, false, false, 0, 0);
		}

	}else if(ply_act == ACTTSUMOGIRI){

		// アクション表示
		printf(tmp_disp_msg, "自摸切り");

		// 牌表示
		if(ply_sute_aka == true){
		dparts->DispHai( 270, PLY_YSTART+380, ply_sute_hai, true, false, 0, 0);
		}else{
		dparts->DispHai( 270, PLY_YSTART+380, ply_sute_hai, false, false, 0, 0);
		}

	}else if(ply_act == ACTNAKISUTE){

		// アクション表示
		printf(tmp_disp_msg, "鳴き捨て");

		// 牌表示
		if(ply_sute_aka == true){
		dparts->DispHai( 270, PLY_YSTART+380, ply_sute_hai, true, false, 0, 0);
		}else{
		dparts->DispHai( 270, PLY_YSTART+380, ply_sute_hai, false, false, 0, 0);
		}

	}else if(ply_act == ACTRIICH){
		printf(tmp_disp_msg, "リーチ　");

	}else if(ply_act == ACTANKAN){

		// アクション表示
		printf(tmp_disp_msg, "暗槓　　");

		// 牌表示
		dparts->DispHai( 270, PLY_YSTART+380, ply_naki_idx, false, false, 0, 0);

	}else if(ply_act == ACTKAKAN){

		// アクション表示
		printf(tmp_disp_msg, "加槓　　");

		// 牌表示
		dparts->DispHai( 270, PLY_YSTART+380, ply_naki_idx, false, false, 0, 0);

	}else{
		printf(tmp_disp_msg, "不明　　");
	}

	// アクション表示
	printf(150, PLY_YSTART+400"Act：%s", tmp_disp_msg);
*/

}

/* ---------------------------------------------------------------------------------------------- */
// 自摸無し手牌情報
/* ---------------------------------------------------------------------------------------------- */
void print_tsumonashi_tehai_info(){

	// 自摸あり表記
	printf("================\n");
	printf("手牌情報：自摸無し\n");


	// 有効牌
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

}

/* ---------------------------------------------------------------------------------------------- */
// 捨牌候補情報
/* ---------------------------------------------------------------------------------------------- */
void print_sutekoho(int sutenum){

	// パーツ表示(候補牌)
	// dparts->DispHai(x, y+30, sutekoho_hai[sutenum], false, false, 0, 0);
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
// 卓開始処理
/* ---------------------------------------------------------------------------------------------- */
void PlyActTakuStart(int tmp_ply_num){

	// 自分のプレーヤ番号を設定
	ply_num = tmp_ply_num;

	// 下家のプレーヤ番号を設定
	ply_num_shimo = ( tmp_ply_num + 3 ) % 4;

	// ----------------------------------------
	// 結果表示
	// ----------------------------------------
/*	printf("================\n");
	printf("ply_num = %d\n", ply_num);
	printf("ply_num_shimo = %d\n", ply_num_shimo);
*/

}

/* ---------------------------------------------------------------------------------------------- */
// 局開始処理
/* ---------------------------------------------------------------------------------------------- */
void PlyActKyokuStart(int tmp_kaze, int tmp_ie){

	// プレーヤタイプ設定
	ply_type = PLYCHAR_NONAME;

	// 家情報
	ie = tmp_ie;
	ply_bakaze = tmp_kaze;
	ply_zikaze = tmp_kaze + ie;

	// 配牌初期化
	for(int i=0; i< PAI_MAX; i++){
		tehai[i] = 0;
	}

	// 赤牌最大数の設定
	max_aka_count[0] = 1;
	max_aka_count[1] = 1;
	max_aka_count[2] = 1;

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

	// ----------------------------------------
	// 結果表示
	// ----------------------------------------
/*	printf("================\n");
	printf("ie = %d\n", ie);
	printf("ply_bakaze = %d\n", ply_bakaze);
	printf("ply_zikaze = %d\n", ply_zikaze);
*/

}

/* ---------------------------------------------------------------------------------------------- */
// 配牌処理
/* ---------------------------------------------------------------------------------------------- */
void PlyActHaipai(int tmp_tsumo_hai, bool tmp_tsumo_aka){

	// ヒストグラムに牌の枚数を加算
	tehai[tmp_tsumo_hai]++;

	// 赤牌有無
	if(tmp_tsumo_aka==true){
		aka_count[(tmp_tsumo_hai-5)/10]++;
	}

	// ----------------------------------------
	// 結果表示
	// ----------------------------------------
/*
	printf("---\n");
	printf("tmp_tsumo_hai = %d\n", tmp_tsumo_hai);
	if(tmp_tsumo_aka==true){
		printf("tmp_tsumo_aka = true\n");
	}else{
		printf("tmp_tsumo_aka = false\n");
	}
*/

}

/* ---------------------------------------------------------------------------------------------- */
// 配牌後の確認処理
/* ---------------------------------------------------------------------------------------------- */
void PlyActPostHaipai(){

	// 配牌直後の手牌状態確認
	ChkTsumoNashiShanten();

	// プレーヤーステータスの確認
	PlyChkPlyStat();

	// プレーヤー鳴きテーブルの更新
	PlyChkNakitbl();

	// ----------------------------------------
	// 結果表示
	// ----------------------------------------

	// 手牌ヒストグラム表示
	// print_tehai_hist();

	// 赤牌情報
	// print_tehai_aka();

	// 自摸無し手牌詳細情報
	// print_tsumonashi_tehai_info();

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

	// 自摸有の向聴算出
	ChkTsumoAriShanten();

	// ----------------------------------------
	// 結果表示
	// ----------------------------------------

	// 自摸有り手牌情報詳細
	// print_tsumoari_tehai_info();

	// 自摸牌
	// printf("自摸牌%2d\n", tmp_tsumo_hai);

	// ----------------------------------------
	// 自摸和了確認
	// ----------------------------------------
	if (shanten_normal == -1){

		// アクション決定(自摸和了)
		ply_act = ACTTSUMOAGARI;

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
			if (ply_act == ACTTSUMO){
				PlyChkAnkan(tmp_tsumo_hai, tmp_tsumo_aka);
			}

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
	// pinfo定義
	// ----------------------------------------

	// 自摸和了の場合
	if ( ply_act == ACTTSUMOAGARI){

		// アクション定義
		pinfo->ply_act = ply_act;

		// アクション牌の定義(自摸牌)
		pinfo->act_hai = ply_tsumo_hai;

		// 牌INDEXの定義
		pinfo->act_idx = ply_tsumo_hai;

		// 赤牌判定
		if(ply_tsumo_aka == true){
			pinfo->act_aka_count = 1;
		}else{
			pinfo->act_aka_count = 0;
		}

	// 暗槓の場合
	}else if( ply_act == ACTANKAN){

		// アクション定義
		pinfo->ply_act = ply_act;

		// アクション牌の定義(自摸牌)
		pinfo->act_hai = ply_naki_idx;

		// 牌INDEXの定義
		pinfo->act_idx = ply_naki_idx;

		// 赤牌枚数
		pinfo->act_aka_count = 1;

	// その他の場合(捨牌、自摸切り)
	}else{

		// アクション定義
		pinfo->ply_act = ply_act;

		// アクション牌の定義
		pinfo->act_hai = ply_sute_hai;

		// 牌INDEXの定義
		pinfo->act_idx = ply_sute_hai;

		// 赤牌判定
		if(ply_sute_aka == true){
			pinfo->act_aka_count = 1;
		}else{
			pinfo->act_aka_count = 0;
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

	// 捨牌確定
	ply_sute_hai = sutekoho_hai[fixed_sutekoho_num];

	// ----------------------------------------
	// リーチ宣言確認
	// ----------------------------------------
	if(shanten_normal == 0 && ply_riichi_mode == 0 && naki_count-ankan_count == 0){

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

	// プレーヤー手牌ヒストグラムの更新
	PlySetTsumoSuteTehaiHist();

	// プレーヤーステータスの確認
	PlyChkPlyStat();

	// プレーヤー鳴きテーブルの更新
	PlyChkNakitbl();

	// 手牌ヒストグラム表示
	// print_tehai_hist();

	// 赤牌情報
	// print_tehai_aka();

	// 自摸無し手牌詳細情報
	// print_tsumonashi_tehai_info();

}

/* ---------------------------------------------------------------------------------------------- */
// 自摸捨牌時の手牌ヒストグラム処理
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
// プレーヤ手牌の状態確認
/* ---------------------------------------------------------------------------------------------- */
void PlyChkPlyStat(){

	ply_tehai_naki_stat = false;
	ply_yakuhai_stat    = false;

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


}

/* ---------------------------------------------------------------------------------------------- */
// 鳴きテーブルの状態確認
/* ---------------------------------------------------------------------------------------------- */
void PlyChkNakitbl(){

	// 鳴きテーブル確認
	for(int tmp_i = 0; tmp_i < nakikoho_tbl_count; tmp_i++){

		if( ply_yakuhai_stat == true ){
			nakikoho_tbl_yesno[tmp_i] = true;
		}else if( nakikoho_tbl_hai[tmp_i]==HAKUNUM    || 
		          nakikoho_tbl_hai[tmp_i]==HATSUNUM   || 
		          nakikoho_tbl_hai[tmp_i]==CHUNNUM    || 
		          nakikoho_tbl_hai[tmp_i]==ply_bakaze || 
		          nakikoho_tbl_hai[tmp_i]==ply_zikaze ){ 
			nakikoho_tbl_yesno[tmp_i] = true;
		}else{
			nakikoho_tbl_yesno[tmp_i] = false;;
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 鳴き確認
/* ---------------------------------------------------------------------------------------------- */
void PlyChkNaki(struct MJSPlyInfo *pinfo, int suteply, int hai){

	// 初期設定
	ply_act = ACTNONAKI;
	ply_naki_idx = 0;
	ply_naki_aka_count = 0;

	// 処理開始
	for( int tmp_i=0; tmp_i < nakikoho_tbl_count; tmp_i++){

		// 牌が該当しているのであれば
		if( nakikoho_tbl_hai[tmp_i] == hai ){

			// ----------------------------------------
			// ロン確認
			// ----------------------------------------
			if( nakikoho_tbl_act[tmp_i] == ACTRON ){

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
	// pinfo定義
	// ----------------------------------------

	// 自摸和了の場合
	if ( ply_act == ACTRON){

		// アクション定義
		pinfo->ply_act = ply_act;

		// アクション牌の定義(鳴きINDEX牌)
		pinfo->act_hai = ply_naki_idx;

		// 牌INDEXの定義
		pinfo->act_idx = ply_naki_idx;

		// 赤牌判定
		pinfo->act_aka_count = ply_naki_aka_count;

	}else{

		// アクション定義
		pinfo->ply_act = ACTNONAKI;

		// アクション牌の定義(鳴きINDEX牌)
		pinfo->act_hai = 0;

		// 牌INDEXの定義
		pinfo->act_idx = 0;

		// 赤牌判定
		pinfo->act_aka_count = 0;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 鳴きアクション
/* ---------------------------------------------------------------------------------------------- */
void PlyActNaki(int naki_ply_num, LBPAct naki_ply_act, int hai, int chi_hai_idx, int naki_aka_count){

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
		PlyChkNakiSute();

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 鳴き捨牌アクション
/* ---------------------------------------------------------------------------------------------- */
void PlyChkNakiSute(){

		// 自摸有の向聴算出
		ChkTsumoAriShanten();

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

	// 捨牌後の手牌状態確認
	ChkTsumoNashiShanten();

	// 鳴き捨牌処理
	// PlySetTsumoSuteTehaiHist();
	PlyChkPlyStat();
	PlyChkNakitbl();

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
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
