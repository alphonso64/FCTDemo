#include "m_interal.h"
#include "pic.h"
#include "m_autobuffer.h"
#include "iostream"
void m_integral_( const uchar* src, int srcstep, double* sum, int sumstep,
                double* sqsum, int sqsumstep, double* tilted, int tiltedstep,
                m_size size, int cn )
{
    int x, y, k;
    memset( sum, 0, (size.cols+cn)*sizeof(sum[0]));
    sum += sumstep + cn;

    if( sqsum )
    {
        memset( sqsum, 0, (size.cols+cn)*sizeof(sqsum[0]));
        sqsum += sqsumstep + cn;
    }

    if( tilted )
    {
        memset( tilted, 0, (size.cols+cn)*sizeof(tilted[0]));
        tilted += tiltedstep + cn;
    }

    if( sqsum == 0 && tilted == 0 )
    {
        for( y = 0; y < size.rows; y++, src += srcstep - cn, sum += sumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++ )
            {
                double s = sum[-cn] = 0;
                for( x = 0; x < size.cols; x += cn )
                {
                    s += src[x];
                    sum[x] = sum[x - sumstep] + s;
                }
            }
        }
    }
    else if( tilted == 0 )
    {
        for( y = 0; y < size.rows; y++, src += srcstep - cn,
                        sum += sumstep - cn, sqsum += sqsumstep - cn )
        {
            for( k = 0; k < cn; k++, src++, sum++, sqsum++ )
            {
                double s = sum[-cn] = 0;
                double sq = sqsum[-cn] = 0;
                for( x = 0; x < size.cols; x += cn )
                {
                    uchar it = src[x];
                    s += it;
                    sq += (double)it*it;
                    double t = sum[x - sumstep] + s;
                    double tq = sqsum[x - sqsumstep] + sq;
                    sum[x] = t;
                    sqsum[x] = tq;
                }
            }
        }
    }
    else
    {
        mAutoBuffer<double> _buf(size.cols+cn);
        double* buf = _buf;
        double s;
        double sq;
        for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
        {
            sum[-cn] = tilted[-cn] = 0;

            for( x = 0, s = 0, sq = 0; x < size.cols; x += cn )
            {
                uchar it = src[x];
                buf[x] = tilted[x] = it;
                s += it;
                sq += (double)it*it;
                sum[x] = s;
                if( sqsum )
                    sqsum[x] = sq;
            }

            if( size.cols == cn )
                buf[cn] = 0;

            if( sqsum )
            {
                sqsum[-cn] = 0;
                sqsum++;
            }
        }

        for( y = 1; y < size.rows; y++ )
        {
            src += srcstep - cn;
            sum += sumstep - cn;
            tilted += tiltedstep - cn;
            buf += -cn;

            if( sqsum )
                sqsum += sqsumstep - cn;

            for( k = 0; k < cn; k++, src++, sum++, tilted++, buf++ )
            {
                uchar it = src[0];
                double t0 = s = it;
                double tq0 = sq = (double)it*it;

                sum[-cn] = 0;
                if( sqsum )
                    sqsum[-cn] = 0;
                tilted[-cn] = tilted[-tiltedstep];

                sum[0] = sum[-sumstep] + t0;
                if( sqsum )
                    sqsum[0] = sqsum[-sqsumstep] + tq0;
                tilted[0] = tilted[-tiltedstep] + t0 + buf[cn];

                for( x = cn; x < size.cols - cn; x += cn )
                {
                    double t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    t1 += buf[x + cn] + t0 + tilted[x - tiltedstep - cn];
                    tilted[x] = t1;
                }

                if( size.cols > cn )
                {
                    double t1 = buf[x];
                    buf[x - cn] = t1 + t0;
                    t0 = it = src[x];
                    tq0 = (double)it*it;
                    s += t0;
                    sq += tq0;
                    sum[x] = sum[x - sumstep] + s;
                    if( sqsum )
                        sqsum[x] = sqsum[x - sqsumstep] + sq;
                    tilted[x] = t0 + t1 + tilted[x - tiltedstep - cn];
                    buf[x] = t0;
                }

                if( sqsum )
                    sqsum++;
            }
        }
    }
}

void m_integral( Pic<uchar>  src, Pic<double>& sum, Pic<double>& sqsum)
{
	int cn=1;
    m_size ssize = src.size(), isize(ssize.cols + 1, ssize.rows + 1);
	sum.create( isize);
	sqsum.create( isize);
	Pic<double> tilted;
	tilted.data=0;
	//tilted.create( isize);
    
    m_integral_( src.ptr(), src.step, (double*)sum.ptr(), sum.step, (double*)sqsum.ptr(), sqsum.step,
          (double*)tilted.ptr(), tilted.step, src.size(), cn );
}