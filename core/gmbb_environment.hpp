#ifndef GMBB_ENVIRONMENT_HPP_INCLUDED
#define GMBB_ENVIRONMENT_HPP_INCLUDED


#include<string>




namespace gmbb{
namespace env{


void  change_time(uint32_t  v);
uint32_t  get_time();

void                   set_value(const char16_t*  name, const char16_t*  value);
const std::u16string&  get_value(const char16_t*  name                        );


}}



#endif




