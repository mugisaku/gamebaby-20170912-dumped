#ifndef GMBB_CONTAINER_HPP
#define GMBB_CONTAINER_HPP


#include"gmbb_object.hpp"
#include<vector>


namespace gmbb{


class
Container: public Object
{
protected:
  std::vector<Object*>  children;

public:
  void  join(Object*  obj, int  x, int  y);

  void  update() override;

  void  process(Controller&  ctrl) override;

  void  render(Image&  dst) override;

};


}




#endif




