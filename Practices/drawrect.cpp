
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

	//画矩形  
	//参数为：承载的图像、顶点、对角点、颜色（这里是蓝色）、粗细、大小  
	
	rectangle(gray, cvPoint(112, 119), cvPoint(147, 145), cvScalar(255, 0, 255), 2);
	
	imshow("底板", gray);

	

	
	
	cvWaitKey(0);


	
	return 0;
}

