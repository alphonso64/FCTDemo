#ifndef MATCH_UTIL
#define MATCH_UTIL
#include "vector"
#include "m_matchtemp.h"
#include "pic.h"
#include "iostream"
#include <algorithm>
using namespace std;
#define  PI   3.1415926535897932384626433832795
#define TH 60

///////////////////////////////////////////����///////////////////////////////////////////////
short double2short(double num);
void m_rotate(Pic<uchar> matSrc, Pic<uchar> &matDst, double degree);
void m_threshold(Pic<uchar> img ,Pic<uchar>& dst, uchar th);
vector<Pic<uchar>> make_temps(Pic<uchar> temp);
void release(vector<Pic<uchar>> temps);
double mul_tempRoi(Pic<uchar> _img, vector<Pic<uchar>> temps, int MatchMethod);
double mul_tempRoi(Pic<uchar> _img, vector<Pic<uchar>> temps, int MatchMethod,int th);
vector<Pic<uchar>> make_temps(Pic<uchar> temp);
vector<Pic<uchar>> make_temps(Pic<uchar> temp,int th);
void m_resize(Pic<uchar> src, Pic<uchar> &dst, int cols, int rows);

#endif
