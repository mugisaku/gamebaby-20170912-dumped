#ifndef CBES_CONTAINER_HPP
#define CBES_CONTAINER_HPP


#include"cbes_object.hpp"
#include<vector>


namespace cbes{


class
Container: public Object
{
protected:
  std::vector<Object*>  object_list;

public:
  void  join(Object*  obj, int  x, int  y);

  void  update() override;

  void  process(Controller&  ctrl) override;

  void  render(CharacterTable&  dst) override;

};


}




#endif




