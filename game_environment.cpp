#include"game_environment.hpp"
#include<unordered_map>




namespace env{


namespace{
std::unordered_map<std::u16string,std::u16string>
variables;


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


}

