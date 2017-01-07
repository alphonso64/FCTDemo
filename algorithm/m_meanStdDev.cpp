#include "m_meanStdDev.h"
#include "pic.h"
#include "m_autobuffer.h"
#include "iostream"
#include <algorithm>
void m_meanStdDev( Pic<uchar> src, scalar<double>& _mean, scalar<double>& _sdv )
{
    int k, cn = src.channels, depth = 0;
	uchar* ptrs;
	uchar* ptrs2=NULL;
	int total = (int)src.cols*src.rows, blockSize = total, intSumBlockSize = 0;
    int j, count = 0, nz0 = 0;
    mAutoBuffer<double> _buf(cn*4);
    double *s = (double*)_buf, *sq = s + cn;
    int *sbuf = (int*)s, *sqbuf = (int*)sq;
	bool blockSum = true, blockSqSum = true;
    size_t esz = 0;

    for( k = 0; k < cn; k++ )
        s[k] = sq[k] = 0;

    if( blockSum )
    {
        intSumBlockSize = 1 << 15;
        blockSize = std::min(blockSize, intSumBlockSize);
        sbuf = (int*)(sq + cn);
        if( blockSqSum )
            sqbuf = sbuf + cn;
        for( k = 0; k < cn; k++ )
            sbuf[k] = sqbuf[k] = 0;
        esz = 1;
    }
	ptrs=src.data;
    for( int i = 0; i < 1; i++ )
    {
        for( j = 0; j < total; j += blockSize )
        {
            int bsz = std::min(total - j, blockSize);
			int nz = m_sumsqr_( ptrs, ptrs2, sbuf, sqbuf, bsz, cn );
            count += nz;
            nz0 += nz;
            if( blockSum && (count + blockSize >= intSumBlockSize || (i+1 >= 1 && j+bsz >= total)) )
            {
                for( k = 0; k < cn; k++ )
                {
                    s[k] += sbuf[k];
                    sbuf[k] = 0;
                }
                if( blockSqSum )
                {
                    for( k = 0; k < cn; k++ )
                    {
                        sq[k] += sqbuf[k];
                        sqbuf[k] = 0;
                    }
                }
                count = 0;
            }
            ptrs[0] += bsz*esz;
            if( ptrs[1] )
                ptrs[1] += bsz;
        }
    }

    double scale = nz0 ? 1./nz0 : 0.;
    for( k = 0; k < cn; k++ )
    {
        s[k] *= scale;
        sq[k] = std::sqrt(std::max(sq[k]*scale - s[k]*s[k], 0.));
    }
	_mean=scalar<double>(s[0],0,0,0);
	_sdv=scalar<double>(sq[0],0,0,0);
}