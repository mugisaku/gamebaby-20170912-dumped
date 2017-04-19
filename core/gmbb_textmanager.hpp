#ifndef GMBB_TEXTMANAGER_HPP_INCLUDED
#define GMBB_TEXTMANAGER_HPP_INCLUDED


#include<cstdint>
#include<cstdio>
#include<string>
#include<queue>
#include"gmbb_rectangle.hpp"
#include"gmbb_controller.hpp"
#include"gmbb_image.hpp"
#include"gmbb_text.hpp"




namespace gmbb{


class
TextManager
{
  Rectangle  rectangle;

  Text  text;

  int  fast_flag;

  int  scroll_count;
  int  scroll_key;
  int  finished_flag;

  char16_t  character_buffer[1024];

  const char16_t*  character_iterator;
        char16_t*  character_end;

  uint32_t  last_update_time;

public:
  TextManager(int  column_number, int  row_number);

  void  clear();

  bool  is_finished() const;

  void  push(const char16_t*   src);
  void  push(std::initializer_list<const char16_t*>  ls);

  void  controll(const Controller&  ctrl);

  void  update();

  void  render(Image&  dst);

};


}




#endif




