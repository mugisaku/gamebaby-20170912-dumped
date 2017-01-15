#include"trpt_square.hpp"




namespace gmbb{
namespace trpt{


const char16_t*
get_name(SquareKind  k)
{
  const char16_t*  s = u"ERROR";

    switch(k)
    {
  case(SquareKind::null    ): s = u"";break;
  case(SquareKind::plain   ): s = u"へいち";break;
  case(SquareKind::waste   ): s = u"あれち";break;
  case(SquareKind::mud     ): s = u"ぬまち";break;
  case(SquareKind::sand    ): s = u"すなち";break;
  case(SquareKind::snow    ): s = u"せつげん";break;
  case(SquareKind::ice     ): s = u"ひょうげん";break;
  case(SquareKind::grass   ): s = u"そうげん";break;
  case(SquareKind::river   ): s = u"かわ";break;
  case(SquareKind::forest  ): s = u"もり";break;
  case(SquareKind::mountain): s = u"やま";break;
  case(SquareKind::see     ): s = u"うみ";break;
  default:
      printf("[square get_name] %d\n",static_cast<int>(k));
    }


  return s;
}


int
get_resistance(SquareKind  k)
{
  int  r = 1;

    switch(k)
    {
  case(SquareKind::null    ): r = 1;break;
  case(SquareKind::plain   ): r = 1;break;
  case(SquareKind::waste   ): r = 2;break;
  case(SquareKind::mud     ): r = 2;break;
  case(SquareKind::sand    ): r = 2;break;
  case(SquareKind::snow    ): r = 2;break;
  case(SquareKind::ice     ): r = 2;break;
  case(SquareKind::grass   ): r = 2;break;
  case(SquareKind::river   ): r = 2;break;
  case(SquareKind::forest  ): r = 4;break;
  case(SquareKind::mountain): r = 5;break;
  case(SquareKind::see     ): r = 5;break;
  default:;
//      printf("[square get_resistance] %d\n",static_cast<int>(k));
    }


  return r;
}


Square::
Square():
kind(SquareKind::null),
feature(nullptr)
{
}


}}




