#ifndef CBES_TIMENOTE_HPP
#define CBES_TIMENOTE_HPP


#include"cbes_object.hpp"


namespace cbes{


class
TimeNote: public Object
{
  int      hour;
  int    minute;
  int    second;

public:
  TimeNote();

  void  reset(int  h, int  m, int  s);

  void  update() override;

  void  render(CharacterTable&  dst) override;

};


}




#endif




