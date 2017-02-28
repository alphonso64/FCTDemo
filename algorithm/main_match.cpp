#include "vector"
#include "iostream"
#include "pic.h"
#include "m_matchtemp.h"
#include "match_util.h"
using namespace std;
int main()
{
	int method=3;
	Pic<uchar> pimg,ptemp;
	vector<Pic<uchar>> ptemps;
	FILE* p;
	int cols,rows;
	p=fopen("test/t1.txt","rt");
	fscanf(p,"%d",&cols);fscanf(p,"\t");
	fscanf(p,"%d",&rows);fscanf(p,"\n");
	pimg.create(cols,rows);
	uchar* data=pimg.data;
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			fscanf(p,"%hhu",data+i*cols+j);
			fscanf(p,"\t");
		}
		fscanf(p,"\n");
	}

	p=fopen("test/5.txt","rt");
	fscanf(p,"%d",&cols);fscanf(p,"\t");
	fscanf(p,"%d",&rows);fscanf(p,"\n");
	ptemp.create(cols,rows);
	data=ptemp.data;
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			fscanf(p,"%hhu",data+i*cols+j);
			fscanf(p,"\t");
		}
		fscanf(p,"\n");
	}
	cout<<"load success"<<endl;
	ptemps=make_temps(ptemp);
	cout<<mul_tempRoi(pimg,ptemps,method)<<endl;
	Pic<float> presult;
	m_matchTemplate(pimg,ptemp,presult,method);
	float min,max;
	m_point minp,maxp;
	presult.min_max(min,max,minp,maxp);
	if(method==0||method==1)
		cout<<min<<" "<<"Location("<<minp.x<<","<<minp.y<<")"<<endl;
	else
		cout<<max<<" "<<"Location("<<maxp.x<<","<<maxp.y<<")"<<endl;
	int stop;
	cin>>stop;
	return 0;
}