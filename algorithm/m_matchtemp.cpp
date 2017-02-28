#include "m_matchtemp.h"
#include "pic.h"
#include "iostream"
void m_matchTemplate( Pic<uchar> img, Pic<uchar>& templ, Pic<float>& result, int method)
{

    int type = 0, depth = 0, cn = 1;
    bool needswap = img.rows < templ.rows || img.cols < templ.cols;


    int numType = method == TM_CCORR || method == TM_CCORR_NORMED ? 0 :
                  method == TM_CCOEFF || method == TM_CCOEFF_NORMED ? 1 : 2;
    bool isNormed = method == TM_CCORR_NORMED ||
                    method == TM_SQDIFF_NORMED
					||method == TM_CCOEFF_NORMED;

    if (needswap)
        std::swap(img, templ);

    m_size corrSize(img.cols - templ.cols + 1, img.rows - templ.rows + 1);

    m_crossCorr( img, templ, result, corrSize);

    if( method == TM_CCORR )
        return;

    double invArea = 1./((double)templ.rows * templ.cols);

    Pic<double> sum, sqsum;
    scalar<double>  templMean, templSdv;
    double *q0 = 0, *q1 = 0, *q2 = 0, *q3 = 0;
    double templNorm = 0, templSum2 = 0;

	m_integral(img, sum, sqsum);
    m_meanStdDev( templ, templMean, templSdv);

    templNorm = templSdv.val[0]*templSdv.val[0] + templSdv.val[1]*templSdv.val[1] 
		+ templSdv.val[2]*templSdv.val[2] + templSdv.val[3]*templSdv.val[3];

    if( templNorm < DBL_EPSILON && method == TM_CCOEFF_NORMED )
    {
        result.all(1);
        return;
    }

    templSum2 = templNorm + templMean.val[0]*templMean.val[0] + templMean.val[1]*templMean.val[1] 
		+ templMean.val[2]*templMean.val[2] + templMean.val[3]*templMean.val[3];

    if( numType != 1 )
    {
        templMean.all(0);
        templNorm = templSum2;
    }

    templSum2 /= invArea;
    templNorm = std::sqrt(templNorm);
    templNorm /= std::sqrt(invArea); // care of accuracy here

    q0 = (double*)sqsum.data;
    q1 = q0 + templ.cols*cn;
    q2 = (double*)(sqsum.data + templ.rows*sqsum.step);
    q3 = q2 + templ.cols*cn;


    double* p0 = (double*)sum.data;
    double* p1 = p0 + templ.cols*cn;
    double* p2 = (double*)(sum.data + templ.rows*sum.step);
    double* p3 = p2 + templ.cols*cn;

	int sumstep = sum.data ? (int)(sum.step) : 0;
    int sqstep = sqsum.data ? (int)(sqsum.step) : 0;

    int i, j, k;

    for( i = 0; i < result.rows; i++ )
    {
        float* rrow = result.ptr(i);
        int idx = i * sumstep;
        int idx2 = i * sqstep;

        for( j = 0; j < result.cols; j++, idx += cn, idx2 += cn )
        {
            double num = rrow[j], t;
            double wndMean2 = 0, wndSum2 = 0;

            if( numType == 1 )
            {
                for( k = 0; k < cn; k++ )
                {
                    t = p0[idx+k] - p1[idx+k] - p2[idx+k] + p3[idx+k];
                    wndMean2 += t*t;
                    num -= t*templMean.val[k];
                }

                wndMean2 *= invArea;
            }

            if( isNormed || numType == 2 )
            {
                for( k = 0; k < cn; k++ )
                {
                    t = q0[idx2+k] - q1[idx2+k] - q2[idx2+k] + q3[idx2+k];
                    wndSum2 += t;
                }

                if( numType == 2 )
                {
                    num = wndSum2 - 2*num + templSum2;
                    num = MAX(num, 0.);
                }
            }

            if( isNormed )
            {
                t = std::sqrt(MAX(wndSum2 - wndMean2,0))*templNorm;
                if( fabs(num) < t )
                    num /= t;
                else if( fabs(num) < t*1.125 )
                    num = num > 0 ? 1 : -1;
                else
                    num = method != TM_SQDIFF_NORMED ? 0 : 1;
            }

            rrow[j] = (float)num;
        }
    }
	sum.release();
	sqsum.release();
}