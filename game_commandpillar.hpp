#ifndef GAME_COMMANDPILLAR_HPP_INCLUDED
#define GAME_COMMANDPILLAR_HPP_INCLUDED


#include"cbes_object.hpp"




constexpr int  invalid_command = -1;


namespace MainCommand{
constexpr int  move = 0;
constexpr int  act  = 1;
constexpr int  use  = 2;
constexpr int  LAST = use;

};


namespace ActionCommand{
constexpr int  look   = 0;
constexpr int  take   = 1;
constexpr int  knock  = 2;
constexpr int  open   = 3;
constexpr int  LAST = open;

};


int    get_main_command();
int  get_action_command();

void    change_main_command(int  v);
void  change_action_command(int  v);


class
CommandPillar: public cbes::Object
{
public:
  void  process(Controller&  ctrl) override;

  void  render(cbes::CharacterTable&  dst) override;

};



#endif




