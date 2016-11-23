#ifndef TEXTADV_HPP_INCLUDED
#define TEXTADV_HPP_INCLUDED


#include"gmbb.hpp"
#include"ta_routine.hpp"
#include"ta_commandpillar.hpp"
#include"ta_tagtable.hpp"
#include"ta_world.hpp"


using namespace gmbb;


extern Container  container;

extern std::vector<Tag*>  belongings_list;

void  erase_belongings(const Item*  item);

extern Message  message;

extern CommandPillar  commandpillar;
extern TagTable            tagtable;

extern Window   pillar_window;
extern Window   table_window;




#endif




