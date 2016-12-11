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
Action
{
  using Function = void  (*)(Player&  pl);

  Function  function;

  constexpr Action(Function  fn=nullptr):
  function(fn){}


  void  operator()(Player&  pl) const
  {
      if(function)
      {
        function(pl);
      }
  }

};


struct
Counter
{
  uint32_t  value=0;

};


struct
Player
{
  SquareMap*  map;

  Square*  previous_square;
  Square*   current_square;
  Square*      next_square;

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

  void  (*shapeshift)(const Player&  player, Sprite&  spr);

  Player();

  void  change_direction(int  d);
  void  change_face(int  f);

  void  standby(SquareMap&  map_, int  dir, int  fac, int  x, int  y);

  void  push_action(Action  action);
  void  pop_action();

  void  step();

  void  advance();

  const Square*  get_previous_square() const;
  const Square*   get_current_square() const;
  const Square*      get_next_square() const;

  const Point&  get_sprite_point() const;
  const Point&  get_square_point() const;

};


}}




#endif




