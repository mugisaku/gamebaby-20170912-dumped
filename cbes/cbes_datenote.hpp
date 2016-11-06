#ifndef CBES_DATENOTE_HPP
#define CBES_DATENOTE_HPP


#include"cbes_object.hpp"


namespace cbes{


class
DateNote: public Object
{
  int      year;
  int     month;
  int       day;

public:
  DateNote();

  void  update() override;

  void  render(CharacterTable&  dst) override;

};


}




#endif




