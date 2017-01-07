#ifndef INTERAL
#define INTERAL
#include "m_autobuffer.h"
#include "pic.h"
void m_integral( Pic<uchar>  _src, Pic<double>& _sum, Pic<double>& _sqsum);
void m_integral_( const uchar* src, int _srcstep, double* sum, int _sumstep,
                double* sqsum, int _sqsumstep, double* tilted, int _tiltedstep,
                m_size size, int cn );
#endif