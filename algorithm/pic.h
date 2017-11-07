#ifndef PIC_H
#define PIC_H
#include "m_size.h"
#include "m_point.h"
#include "scalar.h"
#include <algorithm>
#include <QImage>
typedef  unsigned char uchar;

////////////////////////PIC///////////////////////////
template<typename T> class Pic
{
public:
	T* data;
	int rows,cols;
	int step;
	int channels;

	Pic();
	~Pic();
	Pic(int cols,int rows);
	Pic(m_size size);
	void create(int size);
	void create(int col,int row);
	void create(int col,int row,int channel);
	void create(m_size size);
    void createToGray(QImage image,int depth);
    void createToRotate90(Pic image);
    void createToRotate180(Pic image);
    void createToRotate270(Pic image);
	void release();
	void all(T num=0);
	void min_max(T& min, T& max, m_point& minPoint, m_point& maxPoint);
	m_size size();
	bool isContinuous();
	T* ptr(int row=0);
	template<typename QT>  void convertTo(Pic<QT> dst);
};

/////////////////////////////////////pic//////////////////////////////
template<typename T>
Pic<T>::Pic():rows(0),cols(0),step(0),channels(1){}
template<typename T>
Pic<T>::~Pic(){}
template<typename T>
void Pic<T>::release(){
        if(data != NULL)
        {
            delete[] data;
            data = NULL;
        }
	}
template<typename T>
Pic<T>::Pic(int col, int row)
{
	data=new T[col*row];
	step=col;
	rows=row;
	cols=col;
	channels=1;
}
template<typename T>
Pic<T>::Pic(m_size size)
{
	data=new T[size.cols*size.rows];
	step=size.cols;
	rows=size.rows;
	cols=size.cols;
	channels=1;
}
template<typename T>
void Pic<T>::createToGray(QImage image,int depth)
{
    data=new T[image.height()*image.width()];
    step=image.width();
    rows=image.height();
    cols=image.width();
    channels=1;
    for (int ii = 0; ii < image.height(); ii++) {
        uchar* scan = image.scanLine(ii);
        for (int jj = 0; jj < image.width(); jj++) {
            QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + jj*depth);
            T gray = (T)qGray(*rgbpixel);
            data[ii*step+jj] =gray;

        }
    }
}
template<typename T>
void Pic<T>::createToRotate90(Pic image)
{
    data=new T[image.cols*image.rows];
    uchar *src_temp = data;
    step=image.rows;
    rows=image.cols;
    cols=image.rows;
    channels=1;
    for (int ii = 0; ii < image.cols; ii++) {
        uchar* scan = image.data+image.cols*(image.rows-1)+ii;
        for (int jj = 0; jj < image.rows; jj++) {
            *src_temp = *scan;
            src_temp++;
            scan -= image.cols;
        }
    }
}
template<typename T>
void Pic<T>::createToRotate180(Pic image)
{
    data=new T[image.cols*image.rows];
    uchar *src_temp = data;
    step=image.cols;
    rows=image.rows;
    cols=image.cols;
    channels=1;
    for (int ii = 0; ii < image.rows; ii++) {
        uchar* scan = image.data+image.cols*(image.rows-ii);;
        for (int jj = 0; jj < image.cols; jj++) {
            *src_temp = *scan;
            src_temp++;
            scan--;
        }
    }
}
template<typename T>
void Pic<T>::createToRotate270(Pic image)
{
    data=new T[image.cols*image.rows];
    uchar *src_temp = data;
    step=image.rows;
    rows=image.cols;
    cols=image.rows;
    channels=1;
    for (int ii = 0; ii < image.cols; ii++) {
        uchar* scan = image.data+image.cols-1-ii;
        for (int jj = 0; jj < image.rows; jj++) {
            *src_temp = *scan;
            src_temp++;
            scan += image.cols;
        }
    }
}
template<typename T>
void Pic<T>::create(int size)
{
	data=new T[size];
}
template<typename T>
void Pic<T>::create(int col, int row)
{
	data=new T[col*row];
	step=col;
	rows=row;
	cols=col;
	channels=1;
}
template<typename T>
void Pic<T>::create(int col, int row, int channel)
{
	data=new T[col*row*channel];
	step=col*channel;
	rows=row;
	cols=col;
	channels=channel;
}
template<typename T>
void Pic<T>::create(m_size size)
{
	data=new T[size.cols*size.rows];
	step=size.cols;
	rows=size.rows;
	cols=size.cols;
	channels=1;
}
template<typename T>
void Pic<T>::all(T num)
{
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			for(int k=0;k<channels;k++)
				data[i*step+j*channels+k]=num;
}
template<typename T>
m_size Pic<T>::size()
{
	return m_size(cols,rows);
}
template<typename T>
bool Pic<T>::isContinuous()
{
	return step==cols*channels;
}
template<typename T>
T* Pic<T>::ptr(int row)
{
	return (data+row*step);
}
template<typename T> template<typename QT> 
void Pic<T>::convertTo(Pic<QT>  dst)
{
	dst.cols=cols;
	dst.rows=rows;
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			for(int k=0;k<channels;k++)
				dst.data[i*dst.step+j*channels+k]=(QT)data[i*step+j*channels+k];
}
template<typename T> 
void Pic<T>::min_max(T& min, T& max, m_point& minPoint, m_point& maxPoint)
{
	T* p=data;
	min=*p;max=*p;
	minPoint.set(0,0);maxPoint.set(0,0);
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			if(data[j+i*step]<min){
				min=data[j+i*step];minPoint.set(j,i);
			}
			if(data[j+i*step]>max){
				max=data[j+i*step];maxPoint.set(j,i);
			}
		}
	}
}
////////////////////some function////////////////////////
template<typename T>
Pic<T> roi(Pic<T> img,int x,int y,int width,int height);
int cus_round(double val);
template<typename T>
Pic<T> roi(Pic<T> img,int x,int y,int width,int height)
{
	Pic<T> roi_img;
	roi_img.data=img.data+(y*img.step+x);
	roi_img.cols=width;
	roi_img.rows=height;
	roi_img.step=img.step;
	roi_img.channels=img.channels;
	return roi_img;
}
#endif
