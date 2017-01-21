#include"trpt_board.hpp"
#include"trpt_porter.hpp"




namespace gmbb{
namespace trpt{


namespace{
bool
test_qbf(FileReader&  r)
{
  constexpr uint8_t
  signature[4] =
  {
    'Q','B','F',0
  };


    for(int  i = 0;  i < 4;  i += 1)
    {
      auto  c = r.get();

        if(c != signature[i])
        {
          return false;
        }
    }


  return true;
}
}


void
Board::
load(const File*  f)
{
    if(f)
    {
      auto  r = f->reader();

        if(test_qbf(r))
        {
          int  w = r.get();
          int  h = r.get();
          int  d = r.get();

          width  = w;
          height = h;

          square_table.resize(w*h);

            for(int  y = 0;  y < h;  y += 1){
            for(int  x = 0;  x < w;  x += 1){
              auto&  sq = get(x,y);

              sq.index.x = x;
              sq.index.y = y;

              sq.kind = static_cast<SquareKind>(r.get()&0x7F);

              sq.image_point.x = 24*r.get();
              sq.image_point.y = 24*r.get();
              r.get();
              r.get();

              sq.facility = nullptr;
            }}
        }
    }
}




}}




