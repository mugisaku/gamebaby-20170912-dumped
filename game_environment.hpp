#ifndef GAME_ENVIRONMENT_HPP_INCLUDED
#define GAME_ENVIRONMENT_HPP_INCLUDED


#include<string>




namespace env{


void                   set(const char16_t*  name, const char16_t*  value);
const std::u16string&  get(const char16_t*  name                        );


}



#endif




