#ifndef GMBB_ENVIRONMENT_HPP_INCLUDED
#define GMBB_ENVIRONMENT_HPP_INCLUDED


#include<string>




namespace gmbb{
namespace env{


void      change_time(uint32_t  t);
uint32_t  get_time();


void                   set(const char16_t*  name, const char16_t*  value);
const std::u16string&  get(const char16_t*  name                        );


}}



#endif




