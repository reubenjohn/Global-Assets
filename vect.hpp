/*
 * vect.hpp
 *
 *  Created on: Jul 14, 2013
 *      Author: Reuben
 */

#ifndef VECT_HPP_
#define VECT_HPP_

#include <math.h>
#include <fstream>

using namespace std;

class vect
{
public:
	long double x,y,z;
	vect(long double user_x,long double user_y,long double user_z)
	{
		x=user_x;
		y=user_y;
		z=user_z;
	}
	vect()
	{
		x=y=z=0;
	}
	virtual vect reverse()
	{
		vect temp;
		temp.x=-x;
		temp.y=-y;
		temp.z=-z;
		return temp;
	}
	virtual vect operator=(vect b)
	{
		x=b.x;
		y=b.y;
		z=b.z;
		return *this;
	}
	virtual bool operator==(vect b)
	{
		return (x==b.x&&y==b.y&&z==b.z);
	}
	virtual bool operator!=(vect b)
	{
		return (x!=b.x&&y!=b.y&&z!=b.z);
	}
	virtual vect operator+(vect b)
	{
		vect temp;
		temp.x=x+b.x;
		temp.y=y+b.y;
		temp.z=z+b.z;
		return temp;
	}
	virtual vect operator-(vect b)
	{
		vect temp;
		temp.x=x-b.x;
		temp.y=y-b.y;
		temp.z=z-b.z;
		return temp;
	}
	virtual vect operator*(vect b)
	{
		vect temp;
		temp.x=x*b.x;
		temp.y=y*b.y;
		temp.z=z*b.z;
		return temp;
	}
	virtual vect operator*(long double scalar)
	{
		vect temp;
		temp.x=x*scalar;
		temp.y=y*scalar;
		temp.z=z*scalar;
		return temp;
	}
	virtual vect operator/(long double scalar)
	{
		vect temp;
		temp.x=x/scalar;
		temp.y=y/scalar;
		temp.z=z/scalar;
		return temp;
	}
	virtual long double operator|(vect b)
	{
		return x*b.x+y*b.y+z*b.z;
	}
	virtual vect operator^(vect b)
	{
		vect temp;
		temp.x=y*b.z-z*b.y;
		temp.y=-(x*b.z-b.x*z);
		temp.z=x*b.y-b.x*y;
		return temp;
	}
	virtual vect operator+=(vect b)
	{
		x+=b.x;
		y+=b.y;
		z+=b.z;
		return *this;
	}
	virtual vect operator-=(vect b)
	{
		x-=b.x;
		y-=b.y;
		z-=b.z;
		return *this;
	}
	virtual vect operator*=(vect b)
	{
		x*=b.x;
		y*=b.y;
		z*=b.z;
		return *this;
	}
	virtual vect operator*=(long double scalar)
	{
		x*=scalar;
		y*=scalar;
		z*=scalar;
		return *this;
	}
	virtual vect operator/=(long double scalar)
	{
		x/=scalar;
		y/=scalar;
		z/=scalar;
		return *this;
	}
	virtual long double mag()
	{
		return sqrt(x*x+y*y+z*z);
	}
	virtual long double separation(vect U)
	{
		vect temp(*this-U);
		return sqrt(temp.x*temp.x+temp.y*temp.y+temp.z*temp.z);
	}
	virtual vect dir()
	{
		vect temp;
		temp.x=x;
		temp.y=y;
		temp.z=z;
		return temp/temp.mag();
	}
	virtual vect reset()
	{
		x=y=z=0.0;
		return *this;
	}
	virtual ~vect()
	{

	}
};
vect operator*(long double scalar,vect b)
{
       vect temp;
       temp.x=b.x*scalar;
       temp.y=b.y*scalar;
       temp.z=b.z*scalar;
       return temp;
}
void operator<<(ofstream &fout,vect a)
{
	fout<<"("<<a.x<<","<<a.y<<","<<a.z<<")";
}
vect operator-(vect b)
{
	vect temp;
	temp.x=-b.x;
	temp.y=-b.y;
	temp.z=-b.y;
	return temp;
}
long double mag(vect b)
{
	return sqrt((b.x*b.x+b.y*b.y+b.z*b.z));
}
/*class unsigned_int_vect:public vect
{
public:
	unsigned int x,y,z;
	unsigned_int_vect(unsigned int user_x,unsigned int user_y,unsigned int user_z)
	{
		x=user_x;
		y=user_y;
		z=user_z;
	}
	unsigned_int_vect()
	{
		x=y=z=0;
	}
	virtual unsigned_int_vect reverse_unsigned_int_vect()
	{
		unsigned_int_vect temp;
		temp.x=-x;
		temp.y=-y;
		temp.z=-z;
		return temp;
	}
	virtual unsigned_int_vect operator=(unsigned_int_vect b)
	{
		x=b.x;
		y=b.y;
		z=b.z;
		return *this;
	}
	virtual bool operator==(unsigned_int_vect b)
	{
		return (x==b.x&&y==b.y&&z==b.z);
	}
	virtual bool operator!=(unsigned_int_vect b)
	{
		return (x!=b.x&&y!=b.y&&z!=b.z);
	}
	virtual unsigned_int_vect operator+(unsigned_int_vect b)
	{
		unsigned_int_vect temp;
		temp.x=x+b.x;
		temp.y=y+b.y;
		temp.z=z+b.z;
		return temp;
	}
	virtual unsigned_int_vect operator-(unsigned_int_vect b)
	{
		unsigned_int_vect temp;
		temp.x=x-b.x;
		temp.y=y-b.y;
		temp.z=z-b.z;
		return temp;
	}
	virtual unsigned_int_vect operator*(unsigned_int_vect b)
	{
		unsigned_int_vect temp;
		temp.x=x*b.x;
		temp.y=y*b.y;
		temp.z=z*b.z;
		return temp;
	}
	virtual unsigned_int_vect operator*(unsigned int scalar)
	{
		unsigned_int_vect temp;
		temp.x=x*scalar;
		temp.y=y*scalar;
		temp.z=z*scalar;
		return temp;
	}
	virtual unsigned_int_vect operator/(unsigned int scalar)
	{
		unsigned_int_vect temp;
		temp.x=x/scalar;
		temp.y=y/scalar;
		temp.z=z/scalar;
		return temp;
	}
	virtual unsigned int operator|(unsigned_int_vect b)
	{
		return x*b.x+y*b.y+z*b.z;
	}
	virtual unsigned_int_vect operator^(unsigned_int_vect b)
	{
		unsigned_int_vect temp;
		temp.x=y*b.z-z*b.y;
		temp.y=-(x*b.z-b.x*z);
		temp.z=x*b.y-b.x*y;
		return temp;
	}
	virtual unsigned_int_vect operator+=(unsigned_int_vect b)
	{
		x+=b.x;
		y+=b.y;
		z+=b.z;
		return *this;
	}
	virtual unsigned_int_vect operator-=(unsigned_int_vect b)
	{
		x-=b.x;
		y-=b.y;
		z-=b.z;
		return *this;
	}
	virtual unsigned_int_vect operator*=(unsigned_int_vect b)
	{
		x*=b.x;
		y*=b.y;
		z*=b.z;
		return *this;
	}
	virtual unsigned_int_vect operator*=(unsigned int scalar)
	{
		x*=scalar;
		y*=scalar;
		z*=scalar;
		return *this;
	}
	virtual unsigned_int_vect operator/=(unsigned int scalar)
	{
		x/=scalar;
		y/=scalar;
		z/=scalar;
		return *this;
	}
	virtual long double mag()
	{
		return sqrt(x*x+y*y+z*z);
	}
	virtual unsigned int separation(unsigned_int_vect U)
	{
		unsigned_int_vect temp(*this-U);
		return sqrt(temp.x*temp.x+temp.y*temp.y+temp.z*temp.z);
	}
	virtual vect dir()
	{
		vect temp;
		temp.x=x;
		temp.y=y;
		temp.z=z;
		return temp/temp.mag();
	}
	virtual vect reset()
	{
		vect temp;
		temp.x=x;
		temp.y=y;
		temp.z=z;
		return temp/temp.mag();
	}
	~unsigned_int_vect()
	{

	}
};*/
#endif /* VECT_HPP_ */
