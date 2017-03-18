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

  TaskManager  taskman;

  std::list<Piece*>  piece_list;

  Piece*  master;

public:
  Field();

  void  prepare();

  void  put(Piece*  p, int  x, int  y);
  void  put(Item&&  itm, int  x, int  y);

  void  prepare_to_search();

  bool  step();

  void  update_image(              );
  void  update_image(int  x, int  y);

  void  render(gmbb::Image&  dst);

  void  print() const;


  static void  process_input(Task&  tsk);
  static void  manage_pieces(Task&  tsk);
  static void  select_item_at_main_menu(Task&  tsk);

};




#endif




