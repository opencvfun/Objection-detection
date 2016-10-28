#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
//Release 编译平台
#include <iostream>
#include <cstdio>

using namespace std;
using namespace cv;

void processing(Mat &frame, Mat &output);

string windowResult = "Extracting foreground object";
string windowSource = "Original Video";
Mat gray;	// 当前灰度图片
Mat background;	// 累积背景
Mat backImage;	// 背景图片
Mat foreground;	// 前景图片
double learningRate = 0.01;	// 控制背景累积学习的速率
int nThreshold = 30;	// 前景提取的阈值

int main()
{
	Mat frame;
	Mat result;

	// 	CvCapture* capture = cvCaptureFromCAM( -1 );	// 摄像头读取文件开关
	VideoCapture capture("testVideo.avi");

	if (capture.isOpened()/*capture*/)	// 摄像头读取文件开关
	{
		while (true)
		{
			// frame = cvQueryFrame( capture );	// 摄像头读取文件开关
			capture >> frame;//逐帧输出

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
			if ((char)c == 27)//ASCII码为27=ESC
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
	// 对于第一帧，初始化背景
	if (background.empty())
	{
		gray.convertTo(background, CV_32F);
	}
	background.convertTo(backImage, CV_8U);
	// 计算当前图片和背景的差别
	absdiff(backImage, gray, foreground);
	// 对得到的前景进行阈值选取，去掉伪前景
	threshold(foreground, output, nThreshold, 255, THRESH_BINARY_INV);
	// 实时更新背景
	accumulateWeighted(gray, background, learningRate, output);

	imshow(windowSource, frame);
	imshow(windowResult, output);
}