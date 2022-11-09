#pragma once
#include<opencv.hpp>
#include<string>
using namespace std;
using namespace cv;

class Demo {
public:
	static void BgrToGray(const Mat& image, string path = "") {
		//5、转换图像接口介绍
		// void cv::cvtColor(Mat oldimage, Mat& newimage, int method);
		// oldimage：转换的图片，是一个输入参数
		// newimage：转换完成的图片，是一个输出参数
		// method：转换方法，COLOR开头的宏，其中，COLOR_BGR2GRAY是bgr图像转换灰度图
		Mat gray;
		cvtColor(image, gray, COLOR_BGR2GRAY);
		//将图片展示出来，并保存
		imshow("gray", gray);
		if(path != "")
			imwrite(path, gray);
	}
	static void BgrToHsv(const Mat& image, string path = "") {
		//HSV图像：H：0~180，S、V：0！255
		//H、S表示颜色，V表示亮度
		Mat hsv;
		cvtColor(image, hsv, COLOR_BGR2HSV);
		//展示图片并保存
		imshow("hsv", hsv);
		if (path != "")
			imwrite(path, hsv);
	}
	//Mat赋值
	static void mat_creation_demo(const Mat& image) {
		//直接赋值，浅拷贝
		Mat m1 = image;
		imshow("m1", m1);
		//使用方法：clone，进行深拷贝
		Mat m2 = image.clone();
		imshow("m2", m2);
		//使用方法 copyTo()进行深拷贝
		Mat m3;
		image.copyTo(m3);
		imshow("m3", m3);
		//构造空白对象
		Mat m4 = Mat::ones(Size(600, 300),CV_8UC3);//构造一个n*m的像素点矩阵，把每个像素的第一个通道初始化为1
											   //CV8UC+一个数字，这个数字表示通道的数量
		//cout << m4 << endl;
		imshow("m4",m4);
		//除了ones和zeros，可以直接赋值一个数字，把第一个通道初始化成那个数字
		m4 = 128;
		imshow("m4_2", m4);
		//通过Scalar对前n个通道进行赋值
		m4 = Scalar(0, 0, 256);
		imshow("m4_3", m4);
	}
};