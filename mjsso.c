/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： 麻雀AI：MJSakuraモジュール
 * バージョン     ： 0.0.1.0.14(mjai呼び出し関数の引数変更)
 * プログラム名   ： mjs
 * ファイル名     ： mjsso.c
 * クラス名       ： MJSMjaiClient
 * 処理概要       ： Mjaiクライアント処理クラス
 * Ver0.0.1作成日 ： 2024/06/01 16:03:43
 * 最終更新日     ： 2024/07/06 22:47:29
 * 
 * Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include <Python.h>
#include "client.h"

/* ---------------------------------------------------------------------------------------------- */
// 初期化処理
/* ---------------------------------------------------------------------------------------------- */
static PyObject* init_mjs_module(PyObject* self, PyObject* args){

	// 変数定義
	int ply_id;
	int ret;

	// 引数変換
    if ( !PyArg_ParseTuple(args, "i", &ply_id) ){
        return NULL;
    }

	// 初期化処理
	set_ply_id(ply_id);
	ret = 0;

	// 処理終了：返り値
    return Py_BuildValue("i", ret);

}


/* ---------------------------------------------------------------------------------------------- */
// メッセージ定義処理
/* ---------------------------------------------------------------------------------------------- */
static PyObject* get_message(PyObject* self, PyObject* args){

	// 変数定義
    char*  res_mes;            // 受信メッセージ用文字列
	char   snd_mes[1024];      // 送信メッセージ用文字列

	// 引数変換
    if ( !PyArg_ParseTuple(args, "s", &res_mes) ){
        return NULL;
    }

	// 解析処理：メイン
	set_taku_stat_main(res_mes, snd_mes);

	// 処理終了：返り値
    return Py_BuildValue("s", snd_mes);

}

/* ---------------------------------------------------------------------------------------------- */
// Function Definition struct
/* ---------------------------------------------------------------------------------------------- */
static PyMethodDef myMethods[] = {
    { "init_mjs_module", init_mjs_module, METH_VARARGS, "Init Module" },
    { "get_message", get_message, METH_VARARGS, "Get messages" },
    { NULL }
};

/* ---------------------------------------------------------------------------------------------- */
// Function Definition struct
/* ---------------------------------------------------------------------------------------------- */
static struct PyModuleDef mjsmodule = {
    PyModuleDef_HEAD_INIT,"mjsmodule","C API Module",-1,myMethods
};

/* ---------------------------------------------------------------------------------------------- */
// Function Definition struct
/* ---------------------------------------------------------------------------------------------- */
PyMODINIT_FUNC PyInit_mjsmodule(void){
    return PyModule_Create(&mjsmodule);
}

/* ---------------------------------------------------------------------------------------------- */
// ソース終了
/* ---------------------------------------------------------------------------------------------- */
