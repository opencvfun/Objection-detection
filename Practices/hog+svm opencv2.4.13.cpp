#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/ml/ml.hpp>
#include<ctime>

using namespace std;
using namespace cv;

int main()
{
	cout << "Red:Hog+svm------Green:Hog+cascade" << endl;
	Mat src = imread("2.jpg", 1);
	vector<Rect> found1, found_filtered1, found2, found_filtered2;//���ο�����

	clock_t start1, end1, start2, end2;
	//����1��Hog+svm
	start1 = clock();
	HOGDescriptor hog;//HOG���������
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());//����SVM������ΪĬ�ϲ���	
	hog.detectMultiScale(src, found1, 0, Size(2, 2), Size(0, 0), 1.05, 2);//��ͼ����ж�߶ȼ�⣬��ⴰ���ƶ�����Ϊ(8,8)
	end1 = (double)(1000 * (clock() - start1) / CLOCKS_PER_SEC);
	////����2.Hog+cascade
	//start2 = clock();
	//CascadeClassifier *cascade = new CascadeClassifier;
	//cascade->load("hogcascade_pedestrians.xml");
	//cascade->detectMultiScale(src, found2);
	//end2 = (double)(1000 * (clock() - start2) / CLOCKS_PER_SEC);

	cout << "Hog+svm:  " << end1 << "ms" /*<< "    Hog+cascade:  " << end2 << "ms"*/ << endl;
	//�ҳ�����û��Ƕ�׵ľ��ο�r,������found_filtered��,�����Ƕ�׵Ļ�,��ȡ���������Ǹ����ο����found_filtered��
	for (int i = 0; i < found1.size(); i++)
	{
		Rect r = found1[i];
		int j = 0;
		for (; j < found1.size(); j++)
			if (j != i && (r & found1[j]) == r)
				break;
		if (j == found1.size())
			found_filtered1.push_back(r);
	}
	for (int i = 0; i < found2.size(); i++)
	{
		Rect r = found2[i];
		int j = 0;
		for (; j < found2.size(); j++)
			if (j != i && (r & found2[j]) == r)
				break;
		if (j == found2.size())
			found_filtered2.push_back(r);
	}

	//�����ο���Ϊhog�����ľ��ο��ʵ�������Ҫ��΢��Щ,����������Ҫ��һЩ����
	for (int i = 0; i<found_filtered1.size(); i++)
	{
		Rect r = found_filtered1[i];
		r.x += cvRound(r.width*0.1);
		r.width = cvRound(r.width*0.8);
		r.y += cvRound(r.height*0.07);
		r.height = cvRound(r.height*0.8);
		rectangle(src, r.tl(), r.br(), Scalar(0, 0, 255), 3);
	}
	for (int i = 0; i<found_filtered2.size(); i++)
	{
		Rect r = found_filtered2[i];
		r.x += cvRound(r.width*0.1);
		r.width = cvRound(r.width*0.8);
		r.y += cvRound(r.height*0.07);
		r.height = cvRound(r.height*0.8);
		rectangle(src, r.tl(), r.br(), Scalar(0, 255, 0), 3);
	}
	imshow("src", src);
	waitKey();

	system("pause");
	return 0;
}


