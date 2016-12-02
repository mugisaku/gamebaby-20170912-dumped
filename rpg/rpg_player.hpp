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
}


struct Player;


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
  int  face;

  int  action_phase;
  Counter  action_counter;

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

  void  push(Action  action);

  void  step();

  const Point&  get_sprite_point() const;
  const Point&  get_square_point() const;

};


}}




#endif




