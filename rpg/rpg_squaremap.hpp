#ifndef RPG_SQUAREMAP_HPP_INCLUDED
#define RPG_SQUAREMAP_HPP_INCLUDED


#include"gmbb.hpp"
#include<vector>




namespace gmbb{
namespace rpg{


struct Player;
struct Square;




enum class
Trigger
{
  begin_to_enter,
    end_to_enter,
  begin_to_leave,
    end_to_leave,

  press,

};


struct
Event
{
  const char*  name;

  using Process = void  (*)(Square&  sq, Trigger  trig);

  Process  process;

  Event(const char*  name_, Process  proc):
  name(name_),
  process(proc){}

  void  operator()(Square&  sq, Trigger  trig) const{if(process){process(sq,trig);}}

};


constexpr int  noentry_flag = 0x80;


struct
Square
{
  int  attribute=0;

  Point  lower;
  Point  upper;

  Player*  player=nullptr;

  bool  is_enterable() const;

  const Event&  get_event() const;

};


class
SquareMap
{
  std::string  path;

  const Image*  source_image;

  int  width;
  int  height;

  std::vector<Square>  table;

public:
        Square&  get(int  x, int  y)      ;
  const Square&  get(int  x, int  y) const;

  int  get_width() const;
  int  get_height() const;

  void  render_lower(Image&  dst) const;
  void  render_upper(Image&  dst) const;

  void  clear_player();

  void  change_source(Image&  img);

  void  load(const char*  path);

};


}}


#endif




