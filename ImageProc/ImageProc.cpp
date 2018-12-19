// ImageProc.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>

using namespace std;
using namespace cv;

//---------------------------[全局变量声明部分]-------------------------------
//               描述：全局变量声明
//----------------------------------------------------------------------------
Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3, g_dstImage4, g_dstImage5;

int g_nBoxFilterValue = 6;        //方框滤波内核值 
int g_nMeanBlurValue = 10;       // 均值滤波内核值
int g_nGaussianBlurValue = 6;    // 高斯滤波内核值
int g_nMedianBlurValue = 10;     // 中值滤波内核值
int g_nBilateralFilterValue = 10;// 双边滤波内核值


//---------------------------[全局函数声明部分]-------------------------------
//               描述：全局变量声明
//----------------------------------------------------------------------------
//轨迹条回调函数

static  void on_BoxFilter(int, void *);              //方框滤波
static  void on_MeanBlur(int, void *);               //均值块滤波
static  void on_GassianBlur(int, void *);            //高斯滤波
static  void on_MedianBlur(int, void *);             //中值滤波
static  void on_BilateralFilter(int, void *);        //双边滤波


int main()
{
	system("color 5E");
	g_srcImage = imread("1.jpg",1);
	if (!g_srcImage.data)
	{
		printf("读取srcImage错误！\n");
		return false;
	}

	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();
	g_dstImage4 = g_srcImage.clone();
	g_dstImage5 = g_srcImage.clone();
	
	namedWindow("【<0>原图窗口】", 1);
	imshow("【<0>原图窗口】", g_srcImage);

//---------------------------[1]方框滤波-----------------------------
//创建窗口
	namedWindow("【<1>方框滤波】", 1);
	createTrackbar("内核值:","【<1>方框滤波】",&g_nBoxFilterValue,40,on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);
//-------------------------------------------------------------------

//---------------------------[2]均值滤波-----------------------------
//创建窗口
	namedWindow("【<2>均值滤波】", 1);
	createTrackbar("内核值:", "【<2>均值滤波】", &g_nMeanBlurValue, 40, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue, 0);
//-------------------------------------------------------------------

//---------------------------[3]高斯滤波-----------------------------
//创建窗口
	namedWindow("【<3>高斯滤波】", 1);
	createTrackbar("内核值:", "【<3>高斯滤波】", &g_nGaussianBlurValue, 40, on_GassianBlur);
	on_GassianBlur(g_nGaussianBlurValue, 0);
//-------------------------------------------------------------------

//---------------------------[4]中值滤波-----------------------------
//创建窗口
	namedWindow("【<4>中值滤波】", 1);
	createTrackbar("内核值:", "【<4>中值滤波】", &g_nMedianBlurValue, 40, on_MedianBlur);
	on_MedianBlur(g_nMedianBlurValue, 0);
//-------------------------------------------------------------------

//---------------------------[5]双边滤波-----------------------------
//创建窗口
	namedWindow("【<5>双边滤波】", 1);
	createTrackbar("内核值:", "【<5>双边滤波】", &g_nBilateralFilterValue, 40, on_BilateralFilter);
	on_BilateralFilter(g_nBilateralFilterValue, 0);
//-------------------------------------------------------------------


//输出一些帮助信息
    cout << endl << "\t,请调整滚动条观察图像效果！\n\n"
		<< "\t按下“q”键时，退出程序!\n";

	while (char(waitKey(1)!='q'))
	{
		
	}

	return 0;

}

//---------------------------[on_BoxFilter()函数]-----------------------------
//               描述：方框滤波操作的回调函数
//----------------------------------------------------------------------------

static  void on_BoxFilter(int, void *)
{
	// 滤波操作
	boxFilter(g_srcImage,g_dstImage1,-1,Size(g_nBoxFilterValue+1, g_nBoxFilterValue + 1 ));
	// 显示窗口
	imshow("【<1>方框滤波】",g_dstImage1);

}

//---------------------------[on_MeanBlur()函数]-----------------------------
//               描述：均值滤波操作的回调函数
//----------------------------------------------------------------------------

static  void on_MeanBlur(int, void *)
{
	// 滤波操作
	blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue + 1, g_nMeanBlurValue + 1),Point(-1,-1));
	// 显示窗口
	imshow("【<2>均值滤波】", g_dstImage2);

}

//---------------------------[on_GassianBlur()函数]-----------------------------
//               描述：高斯滤波操作的回调函数
//----------------------------------------------------------------------------

static  void on_GassianBlur(int, void *)
{
	// 滤波操作
	GaussianBlur(g_srcImage, g_dstImage1, Size(g_nGaussianBlurValue*2 + 1, g_nGaussianBlurValue * 2 + 1),0,0);
	// 显示窗口
	imshow("【<3>高斯滤波】", g_dstImage3);

}

//---------------------------[on_MedianBlur()函数]-----------------------------
//               描述：中值滤波操作的回调函数
//----------------------------------------------------------------------------

static  void on_MedianBlur(int, void *)
{
	// 滤波操作
	medianBlur(g_srcImage, g_dstImage4, g_nMedianBlurValue*2+1);
	// 显示窗口
	imshow("【<4>中值滤波】", g_dstImage4);

}

//---------------------------[on_BilateralFilter()函数]-----------------------------
//               描述：双边滤波操作的回调函数
//----------------------------------------------------------------------------

static  void on_BilateralFilter(int, void *)
{
	// 滤波操作
	bilateralFilter(g_srcImage, g_dstImage5, g_nBilateralFilterValue, g_nBilateralFilterValue*2, g_nBilateralFilterValue/2);
	// 显示窗口
	imshow("【<5>双边滤波】", g_dstImage5);

}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
