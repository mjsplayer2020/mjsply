/* ---------------------------------------------------------------------------------------------- 
 * 
 * プログラム概要 ： 麻雀AI：MJSakuraモジュール
 * バージョン     ： 0.0.1.0.8(ロン処理実装)
 * プログラム名   ： mjs
 * ファイル名     ： mjs.c
 * クラス名       ： MJSMjaiClient
 * 処理概要       ： Mjaiクライアント処理クラス
 * Ver0.0.1作成日 ： 2024/06/01 16:03:43
 * 最終更新日     ： 2024/06/22 17:13:12
 * 
 * Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include <Python.h>
#include "mjs.h"

/* ---------------------------------------------------------------------------------------------- */
// メッセージ定義処理
/* ---------------------------------------------------------------------------------------------- */
static PyObject* get_message(PyObject* self, PyObject* args){

	// 変数定義
	struct MJSClient cli;
    char*  res_mes;
	char   snd_mes[1024];

	// 引数変換
    if ( !PyArg_ParseTuple(args, "s", &res_mes) ){
        return NULL;
    }

	// 解析処理：メイン
	set_taku_stat_main(&cli, res_mes, snd_mes);

	// 処理終了：返り値
    return Py_BuildValue("s", snd_mes);

}

/* ---------------------------------------------------------------------------------------------- */
// Function Definition struct
/* ---------------------------------------------------------------------------------------------- */
static PyMethodDef myMethods[] = {
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