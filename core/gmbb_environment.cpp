#include"gmbb_environment.hpp"
#include<unordered_map>




namespace gmbb{
namespace env{


namespace{


std::unordered_map<std::u16string,std::u16string>
variables;


uint32_t
time;


}


uint8_t  fn_keystate;


Controller  ctrl;


void  change_time(uint32_t  v){time = v;}
uint32_t  get_time(){return time;}


void
set_value(const char16_t*  name, const char16_t*  value)
{
  variables[name] = value;
}


const std::u16string&
get_value(const char16_t*  name)
{
  return variables[name];
}


}}




