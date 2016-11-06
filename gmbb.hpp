#ifndef GAME_PROCESS_HPP_INCLUDED
#define GAME_PROCESS_HPP_INCLUDED


#include"game_routine.hpp"
#include"game_commandpillar.hpp"
#include"game_message.hpp"
#include"game_tagtable.hpp"
#include"game_world.hpp"




uint32_t  get_time();

extern std::vector<Tag*>  belongings_list;

void  erase_belongings(const Item*  item);

extern Message  message;

extern CommandPillar  commandpillar;
extern TagTable            tagtable;

extern cbes::Window   pillar_window;
extern cbes::Window   table_window;




#endif




