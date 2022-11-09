#pragma once
#include<opencv.hpp>
#include<string>
using namespace std;
using namespace cv;

class Demo {
public:
	static void BgrToGray(const Mat& image, string path = "") {
		//5��ת��ͼ��ӿڽ���
		// void cv::cvtColor(Mat oldimage, Mat& newimage, int method);
		// oldimage��ת����ͼƬ����һ���������
		// newimage��ת����ɵ�ͼƬ����һ���������
		// method��ת��������COLOR��ͷ�ĺ꣬���У�COLOR_BGR2GRAY��bgrͼ��ת���Ҷ�ͼ
		Mat gray;
		cvtColor(image, gray, COLOR_BGR2GRAY);
		//��ͼƬչʾ������������
		imshow("gray", gray);
		if(path != "")
			imwrite(path, gray);
	}
	static void BgrToHsv(const Mat& image, string path = "") {
		//HSVͼ��H��0~180��S��V��0��255
		//H��S��ʾ��ɫ��V��ʾ����
		Mat hsv;
		cvtColor(image, hsv, COLOR_BGR2HSV);
		//չʾͼƬ������
		imshow("hsv", hsv);
		if (path != "")
			imwrite(path, hsv);
	}
	//Mat��ֵ
	static void mat_creation_demo(const Mat& image) {
		//ֱ�Ӹ�ֵ��ǳ����
		Mat m1 = image;
		imshow("m1", m1);
		//ʹ�÷�����clone���������
		Mat m2 = image.clone();
		imshow("m2", m2);
		//ʹ�÷��� copyTo()�������
		Mat m3;
		image.copyTo(m3);
		imshow("m3", m3);
		//����հ׶���
		Mat m4 = Mat::ones(Size(600, 300),CV_8UC3);//����һ��n*m�����ص���󣬰�ÿ�����صĵ�һ��ͨ����ʼ��Ϊ1
											   //CV8UC+һ�����֣�������ֱ�ʾͨ��������
		//cout << m4 << endl;
		imshow("m4",m4);
		//����ones��zeros������ֱ�Ӹ�ֵһ�����֣��ѵ�һ��ͨ����ʼ�����Ǹ�����
		m4 = 128;
		imshow("m4_2", m4);
		//ͨ��Scalar��ǰn��ͨ�����и�ֵ
		m4 = Scalar(0, 0, 256);
		imshow("m4_3", m4);
	}
};