#ifndef ROGIE_FIELD_HPP_INCLUDED
#define ROGIE_FIELD_HPP_INCLUDED


#include"rogie_square.hpp"
#include"rogie_piece.hpp"
#include<list>


struct
Field
{
  static constexpr int   width = 6;
  static constexpr int  height = 6;

  Square  table[height][width];

  gmbb::Image  image;

  std::list<Piece*>          piece_list;
  std::list<Piece*>    ghost_piece_list;
  std::vector<Piece*>   dead_piece_list;

  Piece*  master;

  uint32_t  rendering_count;

public:
  Field();

  void  prepare();

  void  put(Piece*  p, int  x, int  y);
  void  put(Item*  itm, int  x, int  y);

  void  prepare_to_search(int  initial_distance=0);

  void  update_image(              );
  void  update_image(int  x, int  y);

  void  render(gmbb::Image&  dst);

  void  print() const;


  void  manage();
  void  select_item_at_main_menu();

};




#endif




