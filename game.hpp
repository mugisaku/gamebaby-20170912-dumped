#ifndef GAME_PROCESS_HPP_INCLUDED
#define GAME_PROCESS_HPP_INCLUDED


#include"gmbb_container.hpp"
#include"game_routine.hpp"
#include"game_commandpillar.hpp"
#include"game_message.hpp"
#include"game_tagtable.hpp"
#include"game_world.hpp"




extern gmbb::Container  container;

extern std::vector<Tag*>  belongings_list;

void  erase_belongings(const Item*  item);

extern Message  message;

extern CommandPillar  commandpillar;
extern TagTable            tagtable;

extern gmbb::Window   pillar_window;
extern gmbb::Window   table_window;




#endif




