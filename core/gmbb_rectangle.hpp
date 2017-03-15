#ifndef GMBB_RECTANGLE_HPP
#define GMBB_RECTANGLE_HPP




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


}




#endif




