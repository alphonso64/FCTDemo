#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#include "util_liang.h"
using namespace cv;
using namespace std;

void getLCDRoi(string img,string temp1,string temp2,Point *left,Point *right)
{
	Mat g_srcImage; 
	Mat g_templateImage1; 
	Mat g_templateImage2;
	Mat g_resultImage;
	int g_nMatchMethod=1;
	double minValue; double maxValue; Point minLocation; Point maxLocation;
	Point matchLocation1;
	Point matchLocation2;

	g_srcImage = imread( img, 1 );
	g_templateImage1 = imread( temp1, 1 );
	g_templateImage2 = imread( temp2, 1 );


	//【1】给局部变量初始化
	Mat srcImage;
	g_srcImage.copyTo( srcImage );

	//【2】初始化用于结果输出的矩阵
	int resultImage_cols =  g_srcImage.cols - g_templateImage1.cols + 1;
	int resultImage_rows = g_srcImage.rows - g_templateImage1.rows + 1;
	g_resultImage.create( resultImage_cols, resultImage_rows, CV_32FC1 );

	//【3】进行匹配和标准化
	matchTemplate( g_srcImage, g_templateImage1, g_resultImage, g_nMatchMethod );
	normalize( g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat() );

	//【4】通过函数 minMaxLoc 定位最匹配的位置
	minMaxLoc( g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat() );

	//【5】对于方法 SQDIFF 和 SQDIFF_NORMED, 越小的数值有着更高的匹配结果.
	if( g_nMatchMethod  == TM_SQDIFF || g_nMatchMethod == TM_SQDIFF_NORMED )
	{ matchLocation1 = minLocation; }
	else
	{ matchLocation1 = maxLocation; }

	/********************************************/
		//【2】初始化用于结果输出的矩阵
	resultImage_cols =  g_srcImage.cols - g_templateImage2.cols + 1;
	resultImage_rows = g_srcImage.rows - g_templateImage2.rows + 1;
	g_resultImage.create( resultImage_cols, resultImage_rows, CV_32FC1 );

	//【3】进行匹配和标准化
	matchTemplate( g_srcImage, g_templateImage2, g_resultImage, g_nMatchMethod );
	normalize( g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat() );

	//【4】通过函数 minMaxLoc 定位最匹配的位置
	minMaxLoc( g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat() );

	//【5】对于方法 SQDIFF 和 SQDIFF_NORMED, 越小的数值有着更高的匹配结果.
	if( g_nMatchMethod  == TM_SQDIFF || g_nMatchMethod == TM_SQDIFF_NORMED )
	{ matchLocation2 = minLocation; }
	else
	{ matchLocation2 = maxLocation; }

	left->x=matchLocation1.x+g_templateImage1.cols/2;
	left->y=matchLocation1.y+g_templateImage1.rows/2;
	right->x=matchLocation2.x+g_templateImage2.cols/2;
	right->y=matchLocation2.y+g_templateImage2.rows/2;

}

Mat rotateImage(Mat image,double angle)
{
	 Point2f center=Point2f(image.cols/2,image.rows/2);//旋转中心
	 double scale=1;//缩放尺度
	 double degree=angle*CV_PI/180;
	 double a=sin(degree),b=cos(degree);
	 Mat image_rotate;
	  image_rotate.cols= (image.cols*fabs(b)+image.rows*fabs(a));
	  image_rotate.rows=(image.cols*fabs(a)+image.rows*fabs(b));
	 // Point2f center=Point2f(image_rotate.cols/2,image_rotate.rows/2);//也不能把图像移到中间
	 // float map[6];
	 Mat rotateMat(2,3,CV_32FC1);
	 rotateMat=getRotationMatrix2D(center,angle,scale);
	// map[2]+=(image_rotate.cols-image.cols)/2;
	 //map[5]+=(image_rotate.rows-image.rows)/2;
	 Mat rotateImage;
	 warpAffine(image,rotateImage,rotateMat,image_rotate.size());
	 return rotateImage;
}

void m_rotate(Mat matSrc, Mat &matDst, double degree)
{

	if (matSrc.empty()) return;

	double angle = degree * CV_PI / 180.;
	double alpha = cos(angle);
	double beta = sin(angle);
	int iWidth = matSrc.cols;
	int iHeight = matSrc.rows;
	int iNewWidth = cvRound(iWidth * fabs(alpha) + iHeight * fabs(beta));
	int iNewHeight = cvRound(iHeight * fabs(alpha) + iWidth * fabs(beta));

	double m[6];
	m[0] = alpha;
	m[1] = beta;
	m[2] = (1 - alpha) * iWidth / 2. - beta * iHeight / 2.;
	m[3] = -m[1];
	m[4] = m[0];
	m[5] = beta * iWidth / 2. + (1 - alpha) * iHeight / 2.;

	cv::Mat M = cv::Mat(2, 3, CV_64F, m);
	matDst = cv::Mat(cv::Size(iNewWidth, iNewHeight), matSrc.type(), cv::Scalar::all(0));

	double D = m[0]*m[4] - m[1]*m[3];
	D = D != 0 ? 1./D : 0;
	double A11 = m[4]*D, A22 = m[0]*D;
	m[0] = A11; m[1] *= -D;
	m[3] *= -D; m[4] = A22;
	double b1 = -m[0]*m[2] - m[1]*m[5];
	double b2 = -m[3]*m[2] - m[4]*m[5];
	m[2] = b1; m[5] = b2;

	for (int y=0; y<iNewHeight; ++y)
	{
		for (int x=0; x<iNewWidth; ++x)
		{
			//int tmpx = cvFloor(m[0] * x + m[1] * y + m[2]);
			//int tmpy = cvFloor(m[3] * x + m[4] * y + m[5]);
			double fx = m[0] * x + m[1] * y + m[2];
			double fy = m[3] * x + m[4] * y + m[5];

			int sy  = cvFloor(fy);
			fy -= sy;
			//sy = std::min(sy, iHeight-2);
			//sy = std::max(0, sy);
			if (sy < 0 || sy >= iHeight) continue;

			short cbufy[2];
			cbufy[0] = cv::saturate_cast<short>((1.f - fy) * 2048);
			cbufy[1] = 2048 - cbufy[0];

			int sx = cvFloor(fx);
			fx -= sx;
			//if (sx < 0) {
			//	fx = 0, sx = 0;
			//}
			//if (sx >= iWidth - 1) {
			//	fx = 0, sx = iWidth - 2;
			//}
			if (sx < 0 || sx >= iWidth) continue;

			short cbufx[2];
			cbufx[0] = cv::saturate_cast<short>((1.f - fx) * 2048);
			cbufx[1] = 2048 - cbufx[0];

			uchar* dataSrc=matSrc.data;
			uchar* dataDst=matDst.data;
			int stepDst = matDst.step;
			int stepSrc = matSrc.step;
			int channels=matSrc.channels();
			for (int k=0; k<matSrc.channels(); ++k)
			{
				if (sy == iHeight - 1 || sx == iWidth - 1) {
					continue;
				} else {
					/*
					matDst.at<cv::Vec3b>(y, x)[k] = (matSrc.at<cv::Vec3b>(sy, sx)[k] * cbufx[0] * cbufy[0] +
						matSrc.at<cv::Vec3b>(sy+1, sx)[k] * cbufx[0] * cbufy[1] +
						matSrc.at<cv::Vec3b>(sy, sx+1)[k] * cbufx[1] * cbufy[0] +
						matSrc.at<cv::Vec3b>(sy+1, sx+1)[k] * cbufx[1] * cbufy[1]) >> 22;
					*/
					*(dataDst+ y*stepDst + channels*x + k) = (*(dataSrc + sy*stepSrc + channels*sx + k) * cbufx[0] * cbufy[0] + 
						*(dataSrc + (sy+1)*stepSrc + channels*sx + k) * cbufx[0] * cbufy[1] + 
						*(dataSrc + sy*stepSrc + channels*(sx+1) + k) * cbufx[1] * cbufy[0] + 
						*(dataSrc + (sy+1)*stepSrc + channels*(sx+1) + k) * cbufx[1] * cbufy[1]) >> 22;
				}
			}
		}
	}
}

double tempRoi(Mat img, Mat temp, int MatchMethod)
{
		/***********************************************
		【0】- 平方差匹配法(SQDIFF)
		【1】- 归一化平方差匹配法(SQDIFF NORMED)
		【2】- 相关匹配法(TM CCORR)\n
		【3】- 归一化相关匹配法(TM CCORR NORMED)
		【4】- 相关系数匹配法(TM COEFF)
		【5】- 归一化相关系数匹配法(TM COEFF NORMED)
		*************************************************/
	if((img.cols<temp.cols)|(img.rows<temp.rows))
		return -1;         //模板大于匹配区域
	Mat result;

	/*  定义结果图的大小*/
	int resultImage_cols =  img.cols - temp.cols + 1;
	int resultImage_rows = img.rows - temp.rows + 1;
	result.create( resultImage_cols, resultImage_rows, CV_32FC1 );

	matchTemplate( img, temp, result, MatchMethod );      //匹配

	double minValue; double maxValue; Point minLocation; Point maxLocation;
	minMaxLoc( result, &minValue, &maxValue, &minLocation, &maxLocation, Mat() );

	//根据匹配模式取值
	if( MatchMethod  == TM_SQDIFF || MatchMethod == TM_SQDIFF_NORMED )
	{ return minValue; }
	else
	{ return maxValue; }
}
//多尺度匹配
double mul_tempRoi(Mat img, Mat temp, int MatchMethod)
{
		/***********************************************
		【0】- 平方差匹配法(SQDIFF)
		【1】- 归一化平方差匹配法(SQDIFF NORMED)
		【2】- 相关匹配法(TM CCORR)\n
		【3】- 归一化相关匹配法(TM CCORR NORMED)
		【4】- 相关系数匹配法(TM COEFF)
		【5】- 归一化相关系数匹配法(TM COEFF NORMED)
		*************************************************/
	cvtColor(img,img,CV_RGB2GRAY);
	cvtColor(temp,temp,CV_RGB2GRAY);
	threshold(img, img, THRESHOLD, 255, CV_THRESH_BINARY);
	threshold(temp, temp, THRESHOLD, 255, CV_THRESH_BINARY);
	//namedWindow("show");
	//imshow("show",img);
	if((img.cols*0.9<temp.cols)|(img.rows*0.9<temp.rows)){

		return tempRoi(img,temp,MatchMethod);         //模板大于匹配区域
	}
	Mat scale_image,scale_angle_image,result;
	vector<Mat> imgs;
	vector<double> minValues,maxValues;
	double minValue; double maxValue; Point minLocation; Point maxLocation;
	double scale[5]={1.15,1.1,1.05,1,0.95};
	double angle[5]={2,1,0,359,358};
	for(int i=0;i<5;i++){
		resize(img,scale_image,Size(img.cols*scale[i],img.rows*scale[i]));
		for(int j=0;j<5;j++){
			scale_angle_image=rotateImage(scale_image,angle[j]);
			imgs.push_back(scale_angle_image);
		}
	}
	/*  定义结果图的大小*/
	for(int i=0;i<25;i++){
		int resultImage_cols =  imgs[i].cols - temp.cols + 1;
		int resultImage_rows = imgs[i].rows - temp.rows + 1;
		result.create( resultImage_cols, resultImage_rows, CV_32FC1 );

		matchTemplate( imgs[i], temp, result, MatchMethod );      //匹配
	
		minMaxLoc( result, &minValue, &maxValue, &minLocation, &maxLocation, Mat() );
		minValues.push_back(minValue);
		maxValues.push_back(maxValue);
	}

	//根据匹配模式取值
	if( MatchMethod  == TM_SQDIFF || MatchMethod == TM_SQDIFF_NORMED )
	{ 
		vector<double>::iterator smallest=min_element(minValues.begin(),minValues.end());
		return *smallest; 
	}
	else
	{ 
		vector<double>::iterator biggest=max_element(maxValues.begin(),maxValues.end());
		return *biggest; 
	}
}

double mul_tempRoi(Mat img, vector<Mat> temps, int MatchMethod)
{
		/***********************************************
		【0】- 平方差匹配法(SQDIFF)
		【1】- 归一化平方差匹配法(SQDIFF NORMED)
		【2】- 相关匹配法(TM CCORR)\n
		【3】- 归一化相关匹配法(TM CCORR NORMED)
		【4】- 相关系数匹配法(TM COEFF)
		【5】- 归一化相关系数匹配法(TM COEFF NORMED)
		*************************************************/
	cvtColor(img,img,CV_RGB2GRAY);
	threshold(img, img, THRESHOLD, 255, CV_THRESH_BINARY);
	if((img.cols<temps[0].cols)|(img.rows*0.9<temps[0].rows)){

		return tempRoi(img,temps[12],MatchMethod);         //模板大于匹配区域
	}
	Mat scale_image,scale_angle_image,result;
	vector<double> minValues,maxValues;
	double minValue; double maxValue; Point minLocation; Point maxLocation;
	/*  定义结果图的大小*/
	for(int i=0;i<25;i++){
		int resultImage_cols =  img.cols - temps[i].cols + 1;
		int resultImage_rows = img.rows - temps[i].rows + 1;
		result.create( resultImage_cols, resultImage_rows, CV_32FC1 );

		matchTemplate( img, temps[i], result, MatchMethod );      //匹配
	
		minMaxLoc( result, &minValue, &maxValue, &minLocation, &maxLocation, Mat() );
		minValues.push_back(minValue);
		maxValues.push_back(maxValue);
	}
	//根据匹配模式取值
	if( MatchMethod  == TM_SQDIFF || MatchMethod == TM_SQDIFF_NORMED )
	{ 
		vector<double>::iterator smallest=min_element(minValues.begin(),minValues.end());
		return *smallest; 
	}
	else
	{ 
		vector<double>::iterator biggest=max_element(maxValues.begin(),maxValues.end());
		return *biggest; 
	}
}

/*****************************************************************
分离图像通道，统计BGR三个通道的大于阈值的像素值占整个区域面积之比
然后归一化
******************************************************************/
void detect_color(Mat img,double* color){
	vector<Mat> channels;
	split(img,channels);      //分离通道
	double max=0;
	double area=img.cols*img.rows;      //区域面积
	for(int i=0;i<3;i++){
		double sum=0;
		Mat single=channels.at(i);
		uchar *p=single.data;
		for(int m=0;m<img.cols*img.rows;m++){
			if(p[m]>126)
				sum++;
		}
		color[i]=sum/area;
		if(color[i]>max)
			max=color[i];            //用于归一化
	}
	if(max<0.001)
		max=1;
	for(int i=0;i<3;i++)
		color[i]/=max;
}

double find_flaw(Mat img, Mat temp, int MatchMethod)
{
			/***********************************************
		【0】- 平方差匹配法(SQDIFF)
		【1】- 归一化平方差匹配法(SQDIFF NORMED)
		【2】- 相关匹配法(TM CCORR)\n
		【3】- 归一化相关匹配法(TM CCORR NORMED)
		【4】- 相关系数匹配法(TM COEFF)
		【5】- 归一化相关系数匹配法(TM COEFF NORMED)
		*************************************************/
	if((img.cols<temp.cols)|(img.rows<temp.rows))
		return -1;
	Mat img2,temp2;
	Mat result;

	//找出缺陷，使用二值化匹配
	cvtColor(img,img,CV_RGB2GRAY);
	cvtColor(temp,temp,CV_RGB2GRAY);
	int resultImage_cols =  img.cols - temp.cols + 1;
	int resultImage_rows = img.rows - temp.rows + 1;
	result.create( resultImage_cols, resultImage_rows, CV_32FC1 );
	threshold(img, img2, THRESHOLD, 255, CV_THRESH_BINARY);
	threshold(temp, temp2, THRESHOLD, 255, CV_THRESH_BINARY);
	/*namedWindow("src");
	namedWindow("temp");
	imshow("src",img2);
	imshow("temp",temp2);
	waitKey();*/

	matchTemplate( img2, temp2, result, MatchMethod );

	double minValue; double maxValue; Point minLocation; Point maxLocation;
	minMaxLoc( result, &minValue, &maxValue, &minLocation, &maxLocation, Mat() );

	
	if( MatchMethod  == TM_SQDIFF || MatchMethod == TM_SQDIFF_NORMED )
	{ return minValue; }
	else
	{ return maxValue; }
}

double humatch(Mat img,Mat temp)
{
	if((img.cols<temp.cols)|(img.rows<temp.rows))
		return -1;
	Mat img2,temp2;
	vector<Point> w_img,w_temp;
	cvtColor(img,img,CV_RGB2GRAY);
	cvtColor(temp,temp,CV_RGB2GRAY);Mat bimg,btemp;
	threshold(img, img2, THRESHOLD, 255, CV_THRESH_BINARY);
	threshold(temp, temp2, THRESHOLD, 255, CV_THRESH_BINARY);
	uchar *p=img2.data;
	int row=img2.rows;
	int col=img2.cols;
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if(p[i*col+j]>100){
				w_img.push_back(Point(i,j));
			}
		}
	}
	p=temp2.data;
	row=temp2.rows;
	col=temp2.cols;
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if(p[i*col+j]>100){
				w_temp.push_back(Point(i,j));
			}
		}
	}
	if(w_img.size()<30)
		return -1;
	double result=matchShapes(w_img,w_temp,CV_CONTOURS_MATCH_I3,1.0);
	return result;
}

vector<Mat> make_temps(const char* name){
	vector<Mat> temps;
	Mat img,scale_image,scale_angle_image;
	img=imread(name,0);
	threshold(img, img, THRESHOLD, 255, CV_THRESH_BINARY);
	double scale[5]={1.1,1.05,1,0.95,0.9};
	double angle[5]={2,1,0,359,358};
	for(int i=0;i<5;i++){
		resize(img,scale_image,Size(img.cols*scale[i],img.rows*scale[i]));
		for(int j=0;j<5;j++){
			//scale_angle_image=rotateImage(scale_image,angle[j]);
			m_rotate(scale_image,scale_angle_image,angle[j]);
			temps.push_back(scale_angle_image);
		}
	}
	return temps;
}

void m_resize(Mat src, Mat &dst, int cols, int rows)
{
	double scale_x = (double)src.cols / dst.cols;
	double scale_y = (double)src.rows / dst.rows;
	uchar* dataDst = dst.data;
	int stepDst = dst.step;
	uchar* dataSrc = src.data;
	int stepSrc = src.step;
	int iWidthSrc = src.cols;
	int iHiehgtSrc = src.rows;

	for (int j = 0; j < dst.rows; ++j)
	{
		float fy = (float)((j + 0.5) * scale_y - 0.5);
		int sy = cvFloor(fy);
		fy -= sy;
		sy = std::min(sy, iHiehgtSrc - 2);
		sy = std::max(0, sy);

		short cbufy[2];
		cbufy[0] = cv::saturate_cast<short>((1.f - fy) * 2048);    //溢出保护
		cbufy[1] = 2048 - cbufy[0];

		for (int i = 0; i < dst.cols; ++i)
		{
			float fx = (float)((i + 0.5) * scale_x - 0.5);
			int sx = cvFloor(fx);
			fx -= sx;

			if (sx < 0) {
				fx = 0, sx = 0;
			}
			if (sx >= iWidthSrc - 1) {
				fx = 0, sx = iWidthSrc - 2;
			}

			short cbufx[2];
			cbufx[0] = cv::saturate_cast<short>((1.f - fx) * 2048);
			cbufx[1] = 2048 - cbufx[0];

			int channels=src.channels();
			for (int k = 0; k < src.channels(); ++k)
			{
				*(dataDst+ j*stepDst + channels*i + k) = (*(dataSrc + sy*stepSrc + channels*sx + k) * cbufx[0] * cbufy[0] + 
					*(dataSrc + (sy+1)*stepSrc + channels*sx + k) * cbufx[0] * cbufy[1] + 
					*(dataSrc + sy*stepSrc + channels*(sx+1) + k) * cbufx[1] * cbufy[0] + 
					*(dataSrc + (sy+1)*stepSrc + channels*(sx+1) + k) * cbufx[1] * cbufy[1]) >> 22;
			}
		}
	}
}

