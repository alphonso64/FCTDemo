#ifndef M_COMPLEX
#define M_COMPLEX
template<typename _Tp> class mComplex
{
public:

    //! constructors
    mComplex();
    mComplex( _Tp _re, _Tp _im = 0 );

    //! conversion to another data type
    template<typename T2> operator mComplex<T2>() const;
    //! conjugation
    mComplex conj() const;

    _Tp re, im; //< the real and the imaginary parts
};
template<typename _Tp> inline
mComplex<_Tp>::mComplex()
    : re(0), im(0) {}

template<typename _Tp> inline
mComplex<_Tp>::mComplex( _Tp _re, _Tp _im )
    : re(_re), im(_im) {}

template<typename _Tp> template<typename T2> inline
mComplex<_Tp>::operator mComplex<T2>() const
{
    return mComplex<T2>(saturate_cast<T2>(re), saturate_cast<T2>(im));
}

template<typename _Tp> inline
mComplex<_Tp> mComplex<_Tp>::conj() const
{
    return mComplex<_Tp>(re, -im);
}


template<typename _Tp> static inline
bool operator == (const mComplex<_Tp>& a, const mComplex<_Tp>& b)
{
    return a.re == b.re && a.im == b.im;
}

template<typename _Tp> static inline
bool operator != (const mComplex<_Tp>& a, const mComplex<_Tp>& b)
{
    return a.re != b.re || a.im != b.im;
}

template<typename _Tp> static inline
mComplex<_Tp> operator + (const mComplex<_Tp>& a, const mComplex<_Tp>& b)
{
    return mComplex<_Tp>( a.re + b.re, a.im + b.im );
}

template<typename _Tp> static inline
mComplex<_Tp>& operator += (mComplex<_Tp>& a, const mComplex<_Tp>& b)
{
    a.re += b.re; a.im += b.im;
    return a;
}

template<typename _Tp> static inline
mComplex<_Tp> operator - (const mComplex<_Tp>& a, const mComplex<_Tp>& b)
{
    return mComplex<_Tp>( a.re - b.re, a.im - b.im );
}

template<typename _Tp> static inline
mComplex<_Tp>& operator -= (mComplex<_Tp>& a, const mComplex<_Tp>& b)
{
    a.re -= b.re; a.im -= b.im;
    return a;
}

template<typename _Tp> static inline
mComplex<_Tp> operator - (const mComplex<_Tp>& a)
{
    return mComplex<_Tp>(-a.re, -a.im);
}

template<typename _Tp> static inline
mComplex<_Tp> operator * (const mComplex<_Tp>& a, const mComplex<_Tp>& b)
{
    return mComplex<_Tp>( a.re*b.re - a.im*b.im, a.re*b.im + a.im*b.re );
}

template<typename _Tp> static inline
mComplex<_Tp> operator * (const mComplex<_Tp>& a, _Tp b)
{
    return mComplex<_Tp>( a.re*b, a.im*b );
}

template<typename _Tp> static inline
mComplex<_Tp> operator * (_Tp b, const mComplex<_Tp>& a)
{
    return mComplex<_Tp>( a.re*b, a.im*b );
}

template<typename _Tp> static inline
mComplex<_Tp> operator + (const mComplex<_Tp>& a, _Tp b)
{
    return mComplex<_Tp>( a.re + b, a.im );
}

template<typename _Tp> static inline
mComplex<_Tp> operator - (const mComplex<_Tp>& a, _Tp b)
{ return mComplex<_Tp>( a.re - b, a.im ); }

template<typename _Tp> static inline
mComplex<_Tp> operator + (_Tp b, const mComplex<_Tp>& a)
{
    return mComplex<_Tp>( a.re + b, a.im );
}

template<typename _Tp> static inline
mComplex<_Tp> operator - (_Tp b, const mComplex<_Tp>& a)
{
    return mComplex<_Tp>( b - a.re, -a.im );
}

template<typename _Tp> static inline
mComplex<_Tp>& operator += (mComplex<_Tp>& a, _Tp b)
{
    a.re += b; return a;
}

template<typename _Tp> static inline
mComplex<_Tp>& operator -= (mComplex<_Tp>& a, _Tp b)
{
    a.re -= b; return a;
}

template<typename _Tp> static inline
mComplex<_Tp>& operator *= (mComplex<_Tp>& a, _Tp b)
{
    a.re *= b; a.im *= b; return a;
}

template<typename _Tp> static inline
double abs(const mComplex<_Tp>& a)
{
    return std::sqrt( (double)a.re*a.re + (double)a.im*a.im);
}

template<typename _Tp> static inline
mComplex<_Tp> operator / (const mComplex<_Tp>& a, const mComplex<_Tp>& b)
{
    double t = 1./((double)b.re*b.re + (double)b.im*b.im);
    return mComplex<_Tp>( (_Tp)((a.re*b.re + a.im*b.im)*t),
                        (_Tp)((-a.re*b.im + a.im*b.re)*t) );
}

template<typename _Tp> static inline
mComplex<_Tp>& operator /= (mComplex<_Tp>& a, const mComplex<_Tp>& b)
{
    return (a = a / b);
}

template<typename _Tp> static inline
mComplex<_Tp> operator / (const mComplex<_Tp>& a, _Tp b)
{
    _Tp t = (_Tp)1/b;
    return mComplex<_Tp>( a.re*t, a.im*t );
}

template<typename _Tp> static inline
mComplex<_Tp> operator / (_Tp b, const mComplex<_Tp>& a)
{
    return mComplex<_Tp>(b)/a;
}

template<typename _Tp> static inline
mComplex<_Tp> operator /= (const mComplex<_Tp>& a, _Tp b)
{
    _Tp t = (_Tp)1/b;
    a.re *= t; a.im *= t; return a;
}

#endif