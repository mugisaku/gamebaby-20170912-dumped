#ifndef GMBB_OBJECT_HPP
#define GMBB_OBJECT_HPP


#include"gmbb_controller.hpp"
#include"gmbb_image.hpp"


#ifndef report
#define report  printf("[report] %s %s %d\n",__FILE__,__func__,__LINE__);
#endif


namespace gmbb{


struct
Point
{
  int  x;
  int  y;

  constexpr Point(int  x_=0, int  y_=0): x(x_), y(y_){}

  void  reset(int  x_=0, int  y_=0)
  {
    x = x_;
    y = y_;
  }

};


struct
Rectangle: public Point
{
  int  w;
  int  h;

constexpr Rectangle(int  x_=0, int  y_=0, int  w_=0, int  h_=0):
Point(x_,y_),
w(w_),
h(h_){}

void  reset(int  x_=0, int  y_=0, int  w_=0, int  h_=0)
{
  Point::reset(x_,y_);

  w = w_;
  h = h_;
}

};


class
Object
{
protected:
  Object*  parent;

  Point  relative_point;

  int   width;
  int  height;

public:
  Object();

  virtual ~Object();

  void  change_parent(Object&  new_parent, int  x, int  y);

  void  change_point(int  x, int  y);

  void  change_width(int  v);
  void  change_height(int  v);

  const Point&  get_relative_point() const;
        Point   get_absolute_point() const;

  int  get_width( ) const;
  int  get_height() const;

  virtual void  update();

  virtual void  process(Controller&  ctrl                );
  virtual void  process(Controller&  ctrl, int  x, int  y);

  virtual void  render(Image&  dst);

};


}




#endif




