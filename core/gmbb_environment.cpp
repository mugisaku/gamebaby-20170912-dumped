#include"gmbb_environment.hpp"
#include<unordered_map>




namespace gmbb{
namespace env{


namespace{


std::unordered_map<std::u16string,std::u16string>
variables;


uint32_t
current_time;


}


void
change_time(uint32_t  t)
{
  current_time = t;
}


uint32_t
get_time()
{
  return current_time;
}


void
set(const char16_t*  name, const char16_t*  value)
{
  variables[name] = value;
}


const std::u16string&
get(const char16_t*  name)
{
  return variables[name];
}


}}




