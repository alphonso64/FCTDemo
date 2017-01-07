#ifndef PARAMETER
#define PARAMETER


#define m_DXT_FORWARD  0
#define m_DXT_INVERSE  1
#define m_DXT_SCALE    2 /**< divide result by size of array */
#define m_DXT_INV_SCALE (CV_DXT_INVERSE + CV_DXT_SCALE)
#define m_DXT_INVERSE_SCALE CV_DXT_INV_SCALE
#define m_DXT_ROWS     4 /**< transform each row individually */
#define m_DXT_MUL_CONJ 8 /**< conjugate the second argument of cvMulSpectrums */

enum mBorderTypes {
    mBORDER_CONSTANT    = 0, //!< `iiiiii|abcdefgh|iiiiiii`  with some specified `i`
    mBORDER_REPLICATE   = 1, //!< `aaaaaa|abcdefgh|hhhhhhh`
    mBORDER_REFLECT     = 2, //!< `fedcba|abcdefgh|hgfedcb`
    mBORDER_WRAP        = 3, //!< `cdefgh|abcdefgh|abcdefg`
    mBORDER_REFLECT_101 = 4, //!< `gfedcb|abcdefgh|gfedcba`
    mBORDER_TRANSPARENT = 5, //!< `uvwxyz|absdefgh|ijklmno`

    mBORDER_REFLECT101  = mBORDER_REFLECT_101, //!< same as BORDER_REFLECT_101
    mBORDER_DEFAULT     = mBORDER_REFLECT_101, //!< same as BORDER_REFLECT_101
    mBORDER_ISOLATED    = 16 //!< do not look outside of ROI
};


enum m_DftFlags {
    /** performs an inverse 1D or 2D transform instead of the default forward
        transform. */
    m_DFT_INVERSE        = 1,
    /** scales the result: divide it by the number of array elements. Normally, it is
        combined with DFT_INVERSE. */
    m_DFT_SCALE          = 2,
    /** performs a forward or inverse transform of every individual row of the input
        matrix; this flag enables you to transform multiple vectors simultaneously and can be used to
        decrease the overhead (which is sometimes several times larger than the processing itself) to
        perform 3D and higher-dimensional transformations and so forth.*/
    m_DFT_ROWS           = 4,
    /** performs a forward transformation of 1D or 2D real array; the result,
        though being a complex array, has complex-conjugate symmetry (*CCS*, see the function
        description below for details), and such an array can be packed into a real array of the same
        size as input, which is the fastest option and which is what the function does by default;
        however, you may wish to get a full complex array (for simpler spectrum analysis, and so on) -
        pass the flag to enable the function to produce a full-size complex output array. */
    m_DFT_COMPLEX_OUTPUT = 16,
    /** performs an inverse transformation of a 1D or 2D complex array; the
        result is normally a complex array of the same size, however, if the input array has
        conjugate-complex symmetry (for example, it is a result of forward transformation with
        DFT_COMPLEX_OUTPUT flag), the output is a real array; while the function itself does not
        check whether the input is symmetrical or not, you can pass the flag and then the function
        will assume the symmetry and produce the real output array (note that when the input is packed
        into a real array and inverse transformation is executed, the function treats the input as a
        packed complex-conjugate symmetrical array, and the output will also be a real array). */
    m_DFT_REAL_OUTPUT    = 32,
    /** performs an inverse 1D or 2D transform instead of the default forward transform. */
    m_DCT_INVERSE        = m_DFT_INVERSE,
    /** performs a forward or inverse transform of every individual row of the input
        matrix. This flag enables you to transform multiple vectors simultaneously and can be used to
        decrease the overhead (which is sometimes several times larger than the processing itself) to
        perform 3D and higher-dimensional transforms and so forth.*/
    m_DCT_ROWS           = m_DFT_ROWS
};

enum
{
    TM_SQDIFF        =0,
    TM_SQDIFF_NORMED =1,
    TM_CCORR         =2,
    TM_CCORR_NORMED  =3,
    TM_CCOEFF        =4,
    TM_CCOEFF_NORMED =5
};

#endif


#ifndef MIN
#  define MIN(a,b)  ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#  define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif

