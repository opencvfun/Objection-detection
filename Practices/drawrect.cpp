
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <math.h>  
#include "highgui.h"
#include <string.h>  
#include <opencv/cv.h>  
#include <stdio.h>  
#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{

	Mat bg=imread("h6.jpg");
	Mat gray;
	
	cvtColor(bg, gray, CV_RGB2GRAY);

	//������  
	//����Ϊ�����ص�ͼ�񡢶��㡢�Խǵ㡢��ɫ����������ɫ������ϸ����С  
	
	rectangle(gray, cvPoint(112, 119), cvPoint(147, 145), cvScalar(255, 0, 255), 2);
	
	imshow("�װ�", gray);

	

	
	
	cvWaitKey(0);


	
	return 0;
}

