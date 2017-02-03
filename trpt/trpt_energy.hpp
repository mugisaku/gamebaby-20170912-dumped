#ifndef TRPT_ENERGY_HPP
#define TRPT_ENERGY_HPP


namespace gmbb{
namespace trpt{


class
Energy
{
  static constexpr int  shift_amount = 10;

  int  remaining;

  int  consumption;

public:
  int  get_remaining() const;
  int  get_consumption() const;

  void  fill();

  void  change_consumption(int  v);

  bool  consume();

};


}}


#endif




