#include "m_point.h"
///////////////////////////////////point///////////////////////////
m_point::m_point():x(0),y(0){}
m_point::m_point(int _x,int _y)
{
	x=_x;
	y=_y;
}
void m_point::set(int _x, int _y){
	x=_x;
	y=_y;
}