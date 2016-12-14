#ifndef RPG_PLAYER_HPP
#define RPG_PLAYER_HPP


#include"gmbb.hpp"
#include<queue>


namespace gmbb{
namespace rpg{



namespace Face{
constexpr int  front = 0;
constexpr int   left = 1;
constexpr int  right = 2;
constexpr int   back = 3;
constexpr int  unknown = -1;
}


namespace Direction{
constexpr int     up = 0;
constexpr int   left = 1;
constexpr int  right = 2;
constexpr int   down = 3;
constexpr int  unknown = -1;
}


struct Player;
struct Square;
struct SquareMap;


struct
Counter
{
  uint32_t  value;

  constexpr Counter(uint32_t  v=0): value(v){}

  constexpr operator uint32_t() const{return value;}

};


struct
Context
{
  Player&   player;
  Counter  counter;

  Context(Player&  pl, uint32_t  v=0):
  player(pl), counter(v){}

  Player*  operator->() const{return &player;}

};


using Action = Counter  (*)(Context&  ctx);


using flag32_t = uint32_t;

constexpr flag32_t  quiet_flag = 1;
constexpr flag32_t  facefixed_flag = 2;


using Play       = void  (*)(Player&  pl, const Controller&  ctrl);
using ShapeShift = void  (*)(const Player&  player, Sprite&  spr);


class
Player
{
  SquareMap*  map;

  Square*  previous_square;
  Square*   current_square;
  Square*      next_square;

  int  flags;

  int  face;
  int  direction;

  int  action_phase;
  int   shape_phase;

  Counter  action_counter;
  Counter   shape_counter;

  Point  sprite_point;
  Point  square_point;

  uint32_t  interval_time;
  uint32_t      next_time;

  Sprite  sprite;

  std::queue<Action>  action_q;

  Action   preaction;
  Action  postaction;

  Play        play;
  ShapeShift  shapeshift;

public:
  Player();

  void  operator()(const Controller&  ctrl);

  void    set_flag(int  v);
  void  unset_flag(int  v);
  bool   test_flag(int  v) const;

  void  change_direction(int  d);
  void  change_face(int  f);
  void  turn_direction(int  f);

  void   change_shape_phase(int  v);
  int  advance_shape_phase(int  v);
  int      get_shape_phase() const;

  void              reset_shape_counter();
  const Counter&  advance_shape_counter(int  v);
  const Counter&      get_shape_counter() const;

  void  move_square_point(int  x, int  y);
  void  move_sprite_point(int  x, int  y);

  void  reset_square_point(int  x, int  y);
  void  reset_sprite_point(int  x, int  y);

  bool  test_whether_busy() const;

  int  get_face() const;
  int  get_direction() const;

  void  change_interval_time(uint32_t  v);
  uint32_t  get_interval_time() const;

  void  change_play(Play  cb);
  void  change_shapeshift(ShapeShift  cb);

  void  standby(SquareMap&  map_, int  dir, int  fac, int  x, int  y);

  void  push_action(std::initializer_list<Action>  ls);
  void  pop_action();

  void  step();

  void  advance();

  Sprite&  get_sprite();

  Square*  get_previous_square() const;
  Square*   get_current_square() const;
  Square*      get_next_square() const;

  const Point&  get_sprite_point() const;
  const Point&  get_square_point() const;

};


}}




#endif




