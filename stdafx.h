// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

//#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
#include <vector>

#include <opencv2/opencv.hpp>
/***
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/core/core.hpp>
***/

#ifdef _DEBUG
	#pragma comment(lib,"opencv_core249d.lib")
	#pragma comment(lib,"opencv_imgproc249d.lib")
	#pragma comment(lib,"opencv_highgui249d.lib")
	#pragma comment(lib,"opencv_video249d.lib")
	#pragma comment(lib,"opencv_objdetect249d.lib")
	#pragma comment(lib,"opencv_legacy249d.lib")
	#pragma comment(lib,"opencv_calib3d249d.lib")
	#pragma comment(lib,"opencv_contrib249d.lib")
	#pragma comment(lib,"opencv_features2d249d.lib")
	#pragma comment(lib,"opencv_flann249d.lib")
//	#pragma comment(lib,"opencv_haartraining_engined.lib")
	#pragma comment(lib,"opencv_ml249d.lib")
	#pragma comment(lib,"opencv_gpu249d.lib")
#else
	
	#pragma comment(lib,"opencv_core249.lib")
	#pragma comment(lib,"opencv_imgproc249.lib")
	#pragma comment(lib,"opencv_highgui249.lib")
	#pragma comment(lib,"opencv_video249.lib")
	#pragma comment(lib,"opencv_objdetect249.lib")
	#pragma comment(lib,"opencv_legacy249.lib")
	#pragma comment(lib,"opencv_calib3d249.lib")
	#pragma comment(lib,"opencv_contrib249.lib")
	#pragma comment(lib,"opencv_features2d249.lib")
	#pragma comment(lib,"opencv_flann249.lib")
//	#pragma comment(lib,"opencv_haartraining_engine.lib")
	#pragma comment(lib,"opencv_ml249.lib")
	#pragma comment(lib,"opencv_gpu249.lib")
#endif
