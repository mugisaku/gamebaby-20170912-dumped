#ifndef TRPT_VECTOR_HPP
#define TRPT_VECTOR_HPP


#include<cstdint>
#include<cstdio>




namespace gmbb{
namespace trpt{


struct
Vector
{
  static constexpr int  shift_amount = 16;

  int  x;
  int  y;

  constexpr Vector(int  x_=0, int  y_=0):
  x(x_),
  y(y_){}


  void  reset(int  x_=0, int  y_=0)
  {
    x = x_;
    y = y_;
  }

  void  print(const char*  s="") const
  {
    printf("[vector %s] x: %8d, y:%8d\n",s,x,y);
  }

  Vector  operator+(const Vector&  rhs) const
  {
    return Vector(x+rhs.x,y+rhs.y);
  }

  Vector  operator-(const Vector&  rhs) const
  {
    return Vector(x-rhs.x,y-rhs.y);
  }

  Vector  operator*(const Vector&  rhs) const
  {
    return Vector(x*rhs.x,y*rhs.y);
  }

  Vector  operator/(const Vector&  rhs) const
  {
    return Vector(x/rhs.x,y/rhs.y);
  }


  Vector&  operator+=(int  v)
  {
    x += v;
    y += v;

    return *this;
  }

  Vector&  operator-=(int  v)
  {
    x -= v;
    y -= v;

    return *this;
  }

  Vector&  operator*=(int  v)
  {
    x *= v;
    y *= v;

    return *this;
  }

  Vector&  operator/=(int  v)
  {
    x /= v;
    y /= v;

    return *this;
  }

  Vector&  operator+=(const Vector&  rhs)
  {
    x += rhs.x;
    y += rhs.y;

    return *this;
  }

  Vector&  operator-=(const Vector&  rhs)
  {
    x -= rhs.x;
    y -= rhs.y;

    return *this;
  }

  Vector&  operator*=(const Vector&  rhs)
  {
    x *= rhs.x;
    y *= rhs.y;

    return *this;
  }

  Vector&  operator/=(const Vector&  rhs)
  {
    x /= rhs.x;
    y /= rhs.y;

    return *this;
  }

};


}}


#endif




