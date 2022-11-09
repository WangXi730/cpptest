#include<iostream>
#include<opencv.hpp>
#include"demo.hpp"

using namespace std;
using namespace cv;

int main() {
	//1、加载一个图像，接口说明
	// cv::Mat cv::imread(string uri, int format);//参数2：默认为彩色图像IMREAD_GRAYSCALE是灰度图
	Mat hutao = imread("C:\\Users\\DELL\\Desktop\\胡桃.jpg");//
	//判断是否加载成功
	if (hutao.empty()) {
		cout << "加载失败" << endl;
		return -1;
	}
	//2、创建一个窗口，接口说明
	// namedWindow(string name, int format);//参数2：窗口格式，默认为跟图片大小一样
	namedWindow("胡桃",WINDOW_FREERATIO);//自适应窗口大小
	//3、在指定的窗口中，展示图片，接口说明
	// imshow(string name, Mat m);
	imshow("胡桃", hutao);
	//打印灰度图并保存
	Demo::BgrToGray(hutao);
	Demo::BgrToHsv(hutao);
	//构造矩阵测试
	Demo::mat_creation_demo(hutao);
	//4、阻塞等待，接口说明
	// waitKey(int time); time的单位是ms，若为0，则阻塞等待
	waitKey(0);

	return 0;
}