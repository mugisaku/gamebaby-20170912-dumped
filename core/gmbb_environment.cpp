#include"gmbb_environment.hpp"
#include<unordered_map>






namespace gmbb{
namespace env{


unsigned int
count_of_report;


namespace{


std::unordered_map<std::u16string,std::u16string>
variables;


uint32_t
time;


color_table::Index
base_color_index;


}


uint8_t  fn_keystate;


Controller  ctrl;


void  change_time(uint32_t  v){time = v;}
uint32_t  get_time(){return time;}




void
change_base_color_index(color_table::Index  i)
{
  base_color_index = i;
}


color_table::Index
get_base_color_index()
{
  return base_color_index;
}




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




