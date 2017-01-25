#ifndef TRPT_ENTRYBOOK_HPP
#define TRPT_ENTRYBOOK_HPP


#include"core/gmbb_object.hpp"


namespace gmbb{
namespace trpt{


template<typename  T, int  LINE_NUMBER, int  PAGE_NUMBER>
class
EntryBook
{
public:
  using data_t = T;

  struct Item{
    bool  valid=false;

    T  data;

    operator bool() const{return valid;}

          T&  operator*()      {return data;}
    const T&  operator*() const{return data;}

  };

  struct Page{
    Item  items[LINE_NUMBER];

  } pages[PAGE_NUMBER];


        Item&  operator[](const Point&  pt)      {return pages[pt.x].items[pt.y];}
  const Item&  operator[](const Point&  pt) const{return pages[pt.x].items[pt.y];}

  constexpr int  get_line_number() const{return LINE_NUMBER;}
  constexpr int  get_page_number() const{return PAGE_NUMBER;}

  void  clear()
  {
      for(auto&  pg: pages){
      for(auto&  it: pg.items){
        it.valid = false;
      }}
  }

};


}}


#endif




