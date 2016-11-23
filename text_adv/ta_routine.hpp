#ifndef TEXTADV_routine_HPP_INCLUDED
#define TEXTADV_routine_HPP_INCLUDED


#include"gmbb.hpp"
#include<queue>




enum class
RoutineState
{
  working,
  finished,
};


using Routine = RoutineState  (*)();


namespace Direct{
constexpr int  none    = 0;
constexpr int  advance = 1;
constexpr int  back    = 2;
constexpr int  cancel  = 3;

}


struct Place;


void  change_current_place();
Place*  get_current_place();
void  set_next_place(Place*  plc);


gmbb::Object*  get_current_object();
void   change_current_object(gmbb::Object*  obj);

void       set_this_place_flags(uint32_t  v);
void     unset_this_place_flags(uint32_t  v);
uint32_t  test_this_place_flags(uint32_t  v);


int   get_direct();
void  change_direct(int  v);


int  get_routine_phase();
void  change_routine_phase(int  v);


Routine  get_current_routine();

void  push_routine(Routine  r);

bool  step();




RoutineState  newgame();
RoutineState  visit_place();
RoutineState  use_belongings();
RoutineState  leave_place();

RoutineState  select_main_command();
RoutineState  select_action_command();
RoutineState  select_tag_from_destinations();
RoutineState  select_tag_from_items();
RoutineState  select_tag_from_belongings();




#endif




