#include"gmbb_formatted.hpp"
#include<cstdarg>
#include<cstdio>




namespace gmbb{




const char*
Formatted::
operator()(const char*  fmt, ...)
{
  va_list  ap;
  va_start(ap,fmt);

  vsnprintf(data,length,fmt,ap);

  va_end(ap);


  return data;
}




}




