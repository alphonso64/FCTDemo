#include "m_crossCorr.h"
#include "vector"
#include "m_dft.h"
#include "pic.h"
#include "m_mulspectrums.h"
void m_crossCorr( const Pic<uchar>& img, const Pic<uchar>& templ, Pic<float>& corr,
                m_size corrsize)
{
    const double blockScale = 4.5;
    const int minBlockSize = 256;
	int borderType=0;
	m_point anchor(0,0);
    std::vector<uchar> buf;

	int depth = 0, cn = img.channels;
	int tdepth = 0, tcn = templ.channels;
    //int cdepth = 5, ccn = 1;

    corr.create(corrsize);

    //int maxDepth = depth > CV_8S ? CV_64F : std::max(std::max(CV_32F, tdepth), cdepth);
    m_size blocksize, dftsize;

    blocksize.cols = round(templ.cols*blockScale);
    blocksize.cols = std::max( blocksize.cols, minBlockSize - templ.cols + 1 );
    blocksize.cols = std::min( blocksize.cols, corr.cols );
    blocksize.rows = round(templ.rows*blockScale);
    blocksize.rows = std::max( blocksize.rows, minBlockSize - templ.rows + 1 );
    blocksize.rows = std::min( blocksize.rows, corr.rows );

    dftsize.cols = std::max(getOptimalDFTSize(blocksize.cols + templ.cols - 1), 2);
    dftsize.rows = getOptimalDFTSize(blocksize.rows + templ.rows - 1);

    // recompute block size
    blocksize.cols = dftsize.cols - templ.cols + 1;
    blocksize.cols = MIN( blocksize.cols, corr.cols );
    blocksize.rows = dftsize.rows - templ.rows + 1;
    blocksize.rows = MIN( blocksize.rows, corr.rows );

    Pic<float> dftTempl(dftsize.cols, dftsize.rows*tcn);
    Pic<float> dftImg( dftsize);

    int i, k, bufSize = 0;
    buf.resize(bufSize);

    // compute DFT of each template plane
    for( k = 0; k < tcn; k++ )
    {
        int yofs = k*dftsize.rows;
        Pic<uchar> src = templ;
		Pic<float> dst=roi(dftTempl,0,yofs,dftsize.cols,dftsize.rows);
		Pic<float> dst1=roi(dftTempl,0,yofs,templ.cols,templ.rows);
        src.convertTo(dst1);

        if( dst.cols > templ.cols )
        {
			Pic<float> part=roi(dst,templ.cols,0,dst.cols-templ.cols,templ.rows);
			part.all(0);
        }		
        m_dft(dst, dst, 0, templ.rows);
    }

    int tileCountX = (corr.cols + blocksize.cols - 1)/blocksize.cols;
    int tileCountY = (corr.rows + blocksize.rows - 1)/blocksize.rows;
    int tileCount = tileCountX * tileCountY;

	m_size wholeSize(img.cols,img.rows);
    m_point roiofs(0,0);
    Pic<uchar> img0 = img;

    borderType |= mBORDER_ISOLATED;

    // calculate correlation by blocks
    for( i = 0; i < tileCount; i++ )
    {
        int x = (i%tileCountX)*blocksize.cols;
        int y = (i/tileCountX)*blocksize.rows;

        m_size bsz(std::min(blocksize.cols, corr.cols - x),
                 std::min(blocksize.rows, corr.rows - y));
        m_size dsz(bsz.cols + templ.cols - 1, bsz.rows + templ.rows - 1);
        int x0 = x - anchor.x + roiofs.x, y0 = y - anchor.y + roiofs.y;
        int x1 = std::max(0, x0), y1 = std::max(0, y0);
        int x2 = std::min(img0.cols, x0 + dsz.cols);
        int y2 = std::min(img0.rows, y0 + dsz.rows);
		Pic<uchar> src0=roi(img0, x1,y1,x2-x1,y2-y1);
        Pic<float> dst=roi(dftImg,0,0,dsz.cols,dsz.rows);
        Pic<float> dst1=roi(dftImg,x1-x0,y1-y0,x2-x1,y2-y1);
        Pic<float> cdst=roi(corr,x,y,bsz.cols,bsz.rows);

        for( k = 0; k < cn; k++ )
        {
            Pic<uchar> src = src0;
            dftImg.all(0);
            src.convertTo(dst1);
            m_dft( dftImg, dftImg, 0, dsz.rows );
			Pic<float> dftTempl1=roi(dftTempl,0,tcn > 1 ? k*dftsize.rows : 0,dftsize.cols,dftsize.rows);
            m_mulSpectrums(dftImg, dftTempl1, dftImg, 0, true);
            m_dft( dftImg, dftImg, m_DFT_INVERSE + m_DFT_SCALE, bsz.rows );

            Pic<float> src1 =roi( dftImg,0, 0, bsz.cols, bsz.rows);
            src1.convertTo(cdst);
        }
    }
	dftTempl.release();
	dftImg.release();
}