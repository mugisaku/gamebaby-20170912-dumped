#ifndef RPG_CORE_HPP_INCLUDED
#define RPG_CORE_HPP_INCLUDED


#include"rpg_squaremap.hpp"
#include"rpg_scene.hpp"
#include"rpg_routine.hpp"
#include"gmbb.hpp"
#include<vector>




namespace gmbb{
namespace rpg{


namespace screen{
constexpr int  width  = 24*12;
constexpr int  height = 24*12;
}


namespace core{


const SquareMap&  get_squaremap();
const Event&  get_event(int  i);

enum class
Section
{
  temporary = 0,
};


bool    set_flag(Section  section, uint32_t  v);
void  unset_flag(Section  section, uint32_t  v);
bool   test_flag(Section  section, uint32_t  v);

void  change_scene(const Scene&  scn);

Counter  display_message(Context&  ctx);

void  load_character_image(const File*  f);
void   load_bg_image(const File*  f);

bool  debugging();

void  reset();

void  step(Controller&  ctrl);

void  render(Image&  dst);


}}}


#endif




