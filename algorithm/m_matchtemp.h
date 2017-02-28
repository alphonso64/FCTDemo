#ifndef M_MATCH_TEMPLATE
#define M_MATCH_TEMPLATE
#include "pic.h"
#include "m_crossCorr.h"
#include "m_parameter.h"
#include "m_interal.h"
#include "m_meanStdDev.h"
void m_matchTemplate( Pic<uchar> img, Pic<uchar>& templ, Pic<float>& result, int method);
#endif