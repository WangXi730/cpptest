#include<iostream>
#include<opencv.hpp>
#include"demo.hpp"

using namespace std;
using namespace cv;

int main() {
	//1������һ��ͼ�񣬽ӿ�˵��
	// cv::Mat cv::imread(string uri, int format);//����2��Ĭ��Ϊ��ɫͼ��IMREAD_GRAYSCALE�ǻҶ�ͼ
	Mat hutao = imread("C:\\Users\\DELL\\Desktop\\����.jpg");//
	//�ж��Ƿ���سɹ�
	if (hutao.empty()) {
		cout << "����ʧ��" << endl;
		return -1;
	}
	//2������һ�����ڣ��ӿ�˵��
	// namedWindow(string name, int format);//����2�����ڸ�ʽ��Ĭ��Ϊ��ͼƬ��Сһ��
	namedWindow("����",WINDOW_FREERATIO);//����Ӧ���ڴ�С
	//3����ָ���Ĵ����У�չʾͼƬ���ӿ�˵��
	// imshow(string name, Mat m);
	imshow("����", hutao);
	//��ӡ�Ҷ�ͼ������
	Demo::BgrToGray(hutao);
	Demo::BgrToHsv(hutao);
	//����������
	Demo::mat_creation_demo(hutao);
	//4�������ȴ����ӿ�˵��
	// waitKey(int time); time�ĵ�λ��ms����Ϊ0���������ȴ�
	waitKey(0);

	return 0;
}