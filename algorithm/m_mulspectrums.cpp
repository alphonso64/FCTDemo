#include "m_mulspectrums.h"
#include "pic.h"
#include "m_parameter.h"
void m_mulSpectrums( Pic<float> srcA, Pic<float> srcB,
                       Pic<float>& dst, int flags, bool conjB )
{  
	int depth = 5, cn = 1, type = 5;
    int rows = srcA.rows, cols = srcA.cols;
    int j, k;

    bool is_1d = (flags & m_DFT_ROWS) || (rows == 1 || (cols == 1 &&
             srcA.isContinuous() && srcB.isContinuous() && dst.isContinuous()));

    if( is_1d && !(flags & m_DFT_ROWS) )
        cols = cols + rows - 1, rows = 1;

    int ncols = cols*cn;
    int j0 = cn == 1;
    int j1 = ncols - (cols % 2 == 0 && cn == 1);

    const float* dataA = srcA.ptr();
    const float* dataB = srcB.ptr();
    float* dataC = dst.ptr();

	int stepA = srcA.step;
    int stepB = srcB.step;
    int stepC = dst.step;

    if( !is_1d && cn == 1 )
    {
        for( k = 0; k < (cols % 2 ? 1 : 2); k++ )
        {
            if( k == 1 )
                dataA += cols - 1, dataB += cols - 1, dataC += cols - 1;
            dataC[0] = dataA[0]*dataB[0];
            if( rows % 2 == 0 )
                dataC[(rows-1)*stepC] = dataA[(rows-1)*stepA]*dataB[(rows-1)*stepB];
            if( !conjB )
                for( j = 1; j <= rows - 2; j += 2 )
                {
                    double re = (double)dataA[j*stepA]*dataB[j*stepB] -
                                (double)dataA[(j+1)*stepA]*dataB[(j+1)*stepB];
                    double im = (double)dataA[j*stepA]*dataB[(j+1)*stepB] +
                                (double)dataA[(j+1)*stepA]*dataB[j*stepB];
                    dataC[j*stepC] = (float)re; dataC[(j+1)*stepC] = (float)im;
                }
            else
                for( j = 1; j <= rows - 2; j += 2 )
                {
                    double re = (double)dataA[j*stepA]*dataB[j*stepB] +
                                (double)dataA[(j+1)*stepA]*dataB[(j+1)*stepB];
                    double im = (double)dataA[(j+1)*stepA]*dataB[j*stepB] -
                                (double)dataA[j*stepA]*dataB[(j+1)*stepB];
                    dataC[j*stepC] = (float)re; dataC[(j+1)*stepC] = (float)im;
                }
            if( k == 1 )
                dataA -= cols - 1, dataB -= cols - 1, dataC -= cols - 1;
        }
    }

    for( ; rows--; dataA += stepA, dataB += stepB, dataC += stepC )
    {
        if( is_1d && cn == 1 )
        {
            dataC[0] = dataA[0]*dataB[0];
            if( cols % 2 == 0 )
                dataC[j1] = dataA[j1]*dataB[j1];
        }

        if( !conjB )
            for( j = j0; j < j1; j += 2 )
            {
                double re = (double)dataA[j]*dataB[j] - (double)dataA[j+1]*dataB[j+1];
                double im = (double)dataA[j+1]*dataB[j] + (double)dataA[j]*dataB[j+1];
                dataC[j] = (float)re; dataC[j+1] = (float)im;
            }
        else
            for( j = j0; j < j1; j += 2 )
            {
                double re = (double)dataA[j]*dataB[j] + (double)dataA[j+1]*dataB[j+1];
                double im = (double)dataA[j+1]*dataB[j] - (double)dataA[j]*dataB[j+1];
                dataC[j] = (float)re; dataC[j+1] = (float)im;
            }
		}
    
}