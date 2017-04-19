#include"gmbb_color_table.hpp"




namespace gmbb{
namespace color_table{


namespace{
color_t
data[size];
}


void
set(color_t  color, Index  i)
{
  *i = color;
}


color_t&
Index::
operator*() const
{
  return data[value&mask];
}


void  Index::assign(int  r5, int  g5, int  b5){value = (valid_flag|(r5<<10)|(g5<<5)|b5);}
void  Index::assign(                  int  l5){value = (valid_flag|(l5<<10)|(l5<<5)|l5);}


}}




