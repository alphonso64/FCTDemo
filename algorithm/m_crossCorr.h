#ifndef M_CROSSCORR
#define M_CROSSCORR
#include "m_dft.h"
#include "pic.h"
#include "m_mulspectrums.h"
void m_crossCorr( const Pic<uchar>& img, const Pic<uchar>& templ, Pic<float>& corr,
                m_size corrsize);
#endif