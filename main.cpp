#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace cv;
using namespace std;


Point Center(vector<vector<Point> > contours2, int i)//�õ�������������ĵ�λ��
{
	int centerx = 0, centery = 0, n = contours2[i].size();
	centerx = (contours2[i][n / 4].x + contours2[i][n * 2 / 4].x + contours2[i][3 * n / 4].x + contours2[i][n - 1].x) / 4;
	centery = (contours2[i][n / 4].y + contours2[i][n * 2 / 4].y + contours2[i][3 * n / 4].y + contours2[i][n - 1].y) / 4;
	Point point1 = Point(centerx, centery);
	return point1;
}

int main(int argc, char** argv[])
{
	Mat src = imread("2.jpg", 1);
	Mat gray,src1,thresh;
	src1 = src.clone();

	cvtColor(src, gray, CV_BGR2GRAY);//�ȻҶȻ�
	blur(gray, gray, Size(3, 3));//��ֵ�˲�ģ������

	imshow("gray", gray);

	vector<vector<Point> > contours,contours2,contours3;
	vector<Vec4i> hierarchy;
	threshold(gray, thresh, 80, 255, 1);//��ֵ��
	findContours(thresh, contours, hierarchy, CV_RETR_TREE, CHAIN_APPROX_NONE, Point(0, 0));//Ѱ������

	
	int a,b,c,d;
	for (int i = 0; i< contours.size(); i++)//��������
	{
		//hierarchy[i][3] != -1 [ , , ,-1],���ĸ�����ʾ������
		//���Ϊ-1��־��û�и�����,����ʾ����i�������������
		if (hierarchy[i][3] == -1)//i�������������
		{
			a = hierarchy[i][2];
			d = i;
			if (a!=-1)//a��i������������һ������������
			{
				b =  hierarchy[a][2];
				if (b!=-1)//b��a��������,b��i�����������ڶ�������������
				{
					c = hierarchy[b][2];
					if (c==-1)//c�����������������������
					{
							contours2.push_back(contours[d]);//�ҵ������������������ռ�
					}
				}
			}
		}
	}

	vector<Moments>mu(contours2.size());//�Ƚ����������С
	for (int i = 0; i < contours2.size(); i++)
	{
		mu[i] = moments(contours2[i], 0);
	}
	vector<Point2f>mc(contours2.size());
	double max = 0;
	double sum = 0;
	double average = 0;
	int e=0;
	for (int i = 0; i < contours2.size(); i++)
	{
		mc[i] = Point2f(static_cast<float> (mu[i].m10/mu[i].m00),static_cast<float>(mu[i].m10 / mu[i].m00));
			sum += mu[i].m00;//�ۼ��������
	}
	average = sum / contours2.size(); //������������ƽ�����
	for (int i = 0; i < contours2.size(); i++)
	{
		mc[i] = Point2f(static_cast<float> (mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m10 / mu[i].m00));
		if (abs(mu[i].m00 - average) > max)
		{
			max = abs(mu[i].m00 - average);//���ҵ�i�����������ƽ�������ֵ�����ֵ
			e = i;//���������ֵ����������iֵ
		}
	}
	
	for (int i = 0; i < contours2.size(); i++)
	{
		cout << "����" << i << "��������mu���Ϊ����" << mu[i].m00 << endl;
		if (i!=e)//�ų����������ֵ��������
		{
			contours3.push_back(contours2[i]);
			drawContours(src1, contours2, i, Scalar(255, 0, 0), -1);
		}
	}

	Point point[4];
	for (int i = 0; i < contours3.size(); i++)
	{
		point[i] = Center(contours3, i);//�����ձȽϵõ��������������ĵ�����
	}
		line(src1, point[0], point[1], Scalar(0, 255, 0), 2);
		line(src1, point[0], point[2], Scalar(0, 255, 0), 2);
		line(src1, point[2], point[1], Scalar(0, 255, 0), 2);

		imshow("src1", src1);
		waitKey();
		return 0;
}