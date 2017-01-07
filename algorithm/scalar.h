#ifndef SCALAR
#define SCALAR
/////////////////////////////////////scalar/////////////////////////////////
template<typename T> class scalar
{
public:
	T val[4];
	scalar();
	scalar(T v0,T v1,T v2, T v3);
	void all(T num=0);
};

///////////////////////////////////scalar////////////////////////////
template<typename T> 
scalar<T>::scalar(){
	val[0]=val[1]=val[2]=val[3]=0;
}
template<typename T> 
scalar<T>::scalar(T v0,T v1,T v2, T v3)
{
	val[0]=v0;
	val[1]=v1;
	val[2]=v2;
	val[3]=v3;
}
template<typename T> 
void scalar<T>::all(T num)
{
	val[0]=val[1]=val[2]=val[3]=num;
}
#endif