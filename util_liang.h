#ifndef UTIL_LIANG_H
#define UTIL_LIANG_H
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#define THRESHOLD 60
using namespace cv;
using namespace std;

void getLCDRoi(string img,string temp1,string temp2,Point* left,Point* right);
Mat rotateImage(Mat image,double angle);
void m_rotate(Mat matSrc, Mat &matDst, double degree);
double tempRoi(Mat img, Mat temp, int MatchMethod);
double mul_tempRoi(Mat img, Mat temp, int MatchMethod);
double mul_tempRoi(Mat img, vector<Mat> temps, int MatchMethod);
double find_flaw(Mat img, Mat temp, int MatchMethod);
void detect_color(Mat img,double* color);
double humatch(Mat img,Mat temp);
vector<Mat> make_temps(const char* name);
void m_resize(Mat src, Mat &dst, int cols, int rows);//Ë«ÏßÐÔ²åÖµ

#endif
