#include"gmbb_controller.hpp"




namespace gmbb{




void
Controller::
press(int  flag)
{
  pressing_key_state |= flag;
  pressed_key_state  |= flag;
}


void
Controller::
unpress(int  flag)
{
  pressing_key_state &= ~flag;
   pressed_key_state &= ~flag;

  unpressed_key_state |= flag;
}


void
Controller::
clean()
{
    pressed_key_state = 0;
  unpressed_key_state = 0;
}


bool  Controller::test_pressing(int   flag) const{return( pressing_key_state&flag);}
bool  Controller::test_pressed(int    flag) const{return(  pressed_key_state&flag);}
bool  Controller::test_unpressed(int  flag) const{return(unpressed_key_state&flag);}



}




