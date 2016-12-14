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


class
Object
{
protected:
  Object*  parent;

  Point           point;
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

  void  need_to_refresh(){}

  virtual void  update();

  virtual void  process(Controller&  ctrl);

  virtual void  render(Image&  dst);

};


}




#endif




