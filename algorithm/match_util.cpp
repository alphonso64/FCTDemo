#include "match_util.h"
#include "pic.h"
#include "m_matchtemp.h"
#include <QDebug>
/////////////////////////////////////////定义///////////////////////////////////////////////
short double2short(double num)
{
	int iv=round(num);
	return (short)((unsigned)(iv - SHRT_MIN) <= (unsigned)USHRT_MAX ? iv : iv > 0 ? SHRT_MAX : SHRT_MIN);
}

void m_rotate(Pic<uchar> matSrc, Pic<uchar> &matDst, double degree)
{
	if (matSrc.cols==0) return;
	if(degree==0){
		matDst.create(matSrc.cols,matSrc.rows);
		matSrc.convertTo(matDst);
		return;
	}
	double angle = degree * PI / 180.;
	double alpha = cos(angle);
	double beta = sin(angle);
	int iWidth = matSrc.cols;
	int iHeight = matSrc.rows;
	int iNewWidth = round(iWidth * fabs(alpha) + iHeight * fabs(beta));
	int iNewHeight = round(iHeight * fabs(alpha) + iWidth * fabs(beta));

	double m[6];
	m[0] = alpha;
	m[1] = beta;
	m[2] = (1 - alpha) * iWidth / 2. - beta * iHeight / 2.;
	m[3] = -m[1];
	m[4] = m[0];
	m[5] = beta * iWidth / 2. + (1 - alpha) * iHeight / 2.;

	//cv::Mat M = cv::Mat(2, 3, CV_64F, m);
	//matDst = cv::Mat(cv::Size(iNewWidth, iNewHeight), matSrc.type(), cv::Scalar::all(0));
	matDst.create(iNewWidth,iNewHeight,matSrc.channels);
	matDst.all(0);

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

			//int sy  = cvFloor(fy);
			int sy=(int)(fy>=0?fy:fy-1);
			fy -= sy;
			sy = std::min(sy, iHeight-2);
			sy = std::max(0, sy);
			//if (sy < 0 || sy >= iHeight) continue;

			short cbufy[2];
			//cbufy[0] = cv::saturate_cast<short>((1.f - fy) * 2048);
			cbufy[0] = double2short((1.f - fy) * 2048);
			cbufy[1] = 2048 - cbufy[0];

			//int sx = cvFloor(fx);
			int sx=(int)(fx>=0?fx:fx-1);
			fx -= sx;
			if (sx < 0) {
				fx = 0, sx = 0;
			}
			if (sx >= iWidth - 1) {
				fx = 0, sx = iWidth - 2;
			}
			//if (sx < 0 || sx >= iWidth) continue;

			short cbufx[2];
			//cbufx[0] = cv::saturate_cast<short>((1.f - fx) * 2048);
			cbufx[0] = double2short((1.f - fx) * 2048);
			cbufx[1] = 2048 - cbufx[0];

			uchar* dataSrc=matSrc.data;
			uchar* dataDst=matDst.data;
			int stepDst = matDst.step;
			int stepSrc = matSrc.step;
			int channels=matSrc.channels;
			for (int k=0; k<channels; ++k)
			{				
				*(dataDst+ y*stepDst + channels*x + k) = (*(dataSrc + sy*stepSrc + channels*sx + k) * cbufx[0] * cbufy[0] + 
					*(dataSrc + (sy+1)*stepSrc + channels*sx + k) * cbufx[0] * cbufy[1] + 
					*(dataSrc + sy*stepSrc + channels*(sx+1) + k) * cbufx[1] * cbufy[0] + 
					*(dataSrc + (sy+1)*stepSrc + channels*(sx+1) + k) * cbufx[1] * cbufy[1]) >> 22;				
			}
		}
	}
}

//////////////////////////////////////二值化//////////////////////////////////
void m_threshold(Pic<uchar> img ,Pic<uchar>& dst, uchar th)
{
	dst.create(img.cols,img.rows);
	uchar* p=img.data;
	uchar* p2=dst.data;
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			for(int k=0;k<img.channels;k++){
				if(p[i*img.step+j*img.channels+k]>th)
					*p2=255;
				else
					*p2=0;
				p2++;
			}
		}
	}
}

///////////////////////////////////////做模板/////////////////////////////////////
vector<Pic<uchar>> make_temps(Pic<uchar> temp){
	vector<Pic<uchar>> temps;
	Pic<uchar> img,scale_image,scale_angle_image;
	m_threshold(temp, img, TH);
	double scale[3]={1.05,1,0.95};
	double angle[3]={1,0,359};
	for(int i=0;i<3;i++){
		m_resize(img,scale_image,(int)(img.cols*scale[i]),(int)(img.rows*scale[i]));
		for(int j=0;j<3;j++){
			//scale_angle_image=rotateImage(scale_image,angle[j]);
			m_rotate(scale_image,scale_angle_image,angle[j]);
			temps.push_back(scale_angle_image);
		}
		scale_image.release();
	}
	img.release();
	return temps;
}

void release(vector<Pic<uchar>> temps)
{
	for(int i=0;i<temps.size();i++){
        if(temps[i].data!=NULL)
        {
            qDebug()<<"pattern.temps release"<<temps[i].data;
            delete [] temps[i].data;
            temps[i].data = NULL;
        }
	}
}

//////////////////////////////////////////resize//////////////////////////////////////
void m_resize(Pic<uchar> src, Pic<uchar> &dst, int cols, int rows)
{
	if(src.cols==cols&&src.rows==rows){
		dst.create(cols,rows);
		src.convertTo(dst);
		return;
	}
	double scale_x = (double)src.cols / cols;
	double scale_y = (double)src.rows / rows;
	dst.create(cols,rows);
	uchar* dataDst = dst.data;
	int stepDst = dst.step;
	uchar* dataSrc = src.data;
	int stepSrc = src.step;
	int iWidthSrc = src.cols;
	int iHiehgtSrc = src.rows;

	for (int j = 0; j < dst.rows; ++j)
	{
		float fy = (float)((j + 0.5) * scale_y - 0.5);
		int sy = (int)(fy>=0?fy:fy-1);
		fy -= sy;
		sy = std::min(sy, iHiehgtSrc - 2);
		sy = std::max(0, sy);

		short cbufy[2];
		cbufy[0] = double2short((1.f - fy) * 2048);    //溢出保护
		cbufy[1] = 2048 - cbufy[0];

		for (int i = 0; i < dst.cols; ++i)
		{
			float fx = (float)((i + 0.5) * scale_x - 0.5);
			int sx = (int)(fx>=0?fx:fx-1);
			fx -= sx;

			if (sx < 0) {
				fx = 0, sx = 0;
			}
			if (sx >= iWidthSrc - 1) {
				fx = 0, sx = iWidthSrc - 2;
			}

			short cbufx[2];
			cbufx[0] = double2short((1.f - fx) * 2048);
			cbufx[1] = 2048 - cbufx[0];

			int channels=src.channels;
			for (int k = 0; k < channels; ++k)
			{
				*(dataDst+ j*stepDst + channels*i + k) = (*(dataSrc + sy*stepSrc + channels*sx + k) * cbufx[0] * cbufy[0] + 
					*(dataSrc + (sy+1)*stepSrc + channels*sx + k) * cbufx[0] * cbufy[1] + 
					*(dataSrc + sy*stepSrc + channels*(sx+1) + k) * cbufx[1] * cbufy[0] + 
					*(dataSrc + (sy+1)*stepSrc + channels*(sx+1) + k) * cbufx[1] * cbufy[1]) >> 22;
			}
		}
	}
}

////////////////////二值图匹配/////////////////////////////////////////////////
double mul_tempRoi(Pic<uchar> _img, vector<Pic<uchar>> temps, int MatchMethod)
{
		/***********************************************
		【0】- 平方差匹配法(SQDIFF)
		【1】- 归一化平方差匹配法(SQDIFF NORMED)
		【2】- 相关匹配法(TM CCORR)\n
		【3】- 归一化相关匹配法(TM CCORR NORMED)
		【4】- 相关系数匹配法(TM COEFF)
		【5】- 归一化相关系数匹配法(TM COEFF NORMED)
		*************************************************/
	//cvtColor(img,img,CV_RGB2GRAY);
	Pic<uchar> img;
	m_threshold(_img, img, TH);
    if((img.cols<temps[0].cols)|(img.rows<temps[0].rows)){

		return -1;         //模板大于匹配区域
	}
	Pic<float> result;
	vector<float> minValues,maxValues;
	float minValue, maxValue; 
	m_point minLocation; m_point maxLocation;
	/*  定义结果图的大小*/
	for(int i=0;i<9;i++){
		m_matchTemplate( img, temps[i], result, MatchMethod );      //匹配

		//min_max( result, &minValue, &maxValue, &minLocation, &maxLocation, Mat() );
		result.min_max(minValue,maxValue,minLocation,maxLocation);
		minValues.push_back(minValue);
		maxValues.push_back(maxValue);
		result.release();
	}
	//根据匹配模式取值
	if( MatchMethod  == TM_SQDIFF || MatchMethod == TM_SQDIFF_NORMED )
	{ 
		vector<float>::iterator smallest=min_element(minValues.begin(),minValues.end());
		img.release();
		return *smallest; 
	}
	else
	{ 
		vector<float>::iterator biggest=max_element(maxValues.begin(),maxValues.end());
		img.release();
		return *biggest; 
	}
	
}
