#ifndef GAME_MESSAGE_HPP_INCLUDED
#define GAME_MESSAGE_HPP_INCLUDED


#include<cstdint>
#include<cstdio>
#include<string>
#include<queue>
#include"gmbb_object.hpp"




class
MessagePage
{
  struct Line;

  int  column_number;
  int     row_number;

  Line*    first;
  Line*  current;
  Line*     last;

  char16_t  last_char;

public:
  MessagePage(int  col_n, int  row_n);

  void  clear();

  void  rotate();

  void  push(char16_t  c);

  bool  is_full() const;

  void  render(gmbb::Plain&  dst, int  x, int  y) const;

};


class
Message: public gmbb::Object
{
  MessagePage  page;

  int  fast_flag;

  int  scroll_count;
  int  scroll_key;
  int  finished_flag;

  char16_t  character_buffer[1024];

  const char16_t*  character_iterator;
        char16_t*  character_end;

  uint32_t  last_update_time;

public:
  Message(int  w, int  h);

  void  clear();

  bool  is_finished() const;

  void  push(const char16_t*   src);
  void  push(std::initializer_list<const char16_t*>  ls);

  void  process(Controller&  ctrl) override;

  void  update() override;

  void  render(gmbb::Plain&  dst) override;

};


#endif




