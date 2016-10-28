#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
//Release ����ƽ̨
#include <iostream>
#include <cstdio>

using namespace std;
using namespace cv;

void processing(Mat &frame, Mat &output);

string windowResult = "Extracting foreground object";
string windowSource = "Original Video";
Mat gray;	// ��ǰ�Ҷ�ͼƬ
Mat background;	// �ۻ�����
Mat backImage;	// ����ͼƬ
Mat foreground;	// ǰ��ͼƬ
double learningRate = 0.01;	// ���Ʊ����ۻ�ѧϰ������
int nThreshold = 30;	// ǰ����ȡ����ֵ

int main()
{
	Mat frame;
	Mat result;

	// 	CvCapture* capture = cvCaptureFromCAM( -1 );	// ����ͷ��ȡ�ļ�����
	VideoCapture capture("testVideo.avi");

	if (capture.isOpened()/*capture*/)	// ����ͷ��ȡ�ļ�����
	{
		while (true)
		{
			// frame = cvQueryFrame( capture );	// ����ͷ��ȡ�ļ�����
			capture >> frame;//��֡���

			if (!frame.empty())
			{
				processing(frame, result);
			}
			else
			{
				printf(" --(!) No captured frame -- Break!");
				break;
			}

			int c = waitKey(33);
			if ((char)c == 27)//ASCII��Ϊ27=ESC
			{
				break;
			}
		}
	}
	return 0;
}

void processing(Mat &frame, Mat &output)
{
	cvtColor(frame, gray, CV_BGR2GRAY);
	// ���ڵ�һ֡����ʼ������
	if (background.empty())
	{
		gray.convertTo(background, CV_32F);
	}
	background.convertTo(backImage, CV_8U);
	// ���㵱ǰͼƬ�ͱ����Ĳ��
	absdiff(backImage, gray, foreground);
	// �Եõ���ǰ��������ֵѡȡ��ȥ��αǰ��
	threshold(foreground, output, nThreshold, 255, THRESH_BINARY_INV);
	// ʵʱ���±���
	accumulateWeighted(gray, background, learningRate, output);

	imshow(windowSource, frame);
	imshow(windowResult, output);
}