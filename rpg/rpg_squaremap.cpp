#include"rpg_squaremap.hpp"
#include<cstdio>




namespace gmbb{
namespace rpg{


      Square&  SquareMap::get(int  x, int  y){return table[(width*y)+x];}
const Square&  SquareMap::get(int  x, int  y) const{return table[(width*y)+x];}


void
SquareMap::
clear_player()
{
    for(auto&  sq: table)
    {
      sq.player = nullptr;
    }
}


void
SquareMap::
render_lower(Image&  dst) const
{
  auto&  src = *source_image;

  constexpr int  chip_size = 24;

    for(int  y = 0;  y < height;  y += 1){
    for(int  x = 0;  x <  width;  x += 1){
      auto&  sq = get(x,y);

      const int  dst_x_base = chip_size*x;
      const int  dst_y_base = chip_size*y;

      const int  src_x_base = chip_size*sq.lower.x;
      const int  src_y_base = chip_size*sq.lower.y;

        for(int  yy = 0;  yy < chip_size;  yy += 1){
        for(int  xx = 0;  xx < chip_size;  xx += 1){
          auto&  v = src.const_pixel(src_x_base+xx,src_y_base+yy);

            if(v&8)
            {
              dst.pixel(dst_x_base+xx,dst_y_base+yy) = v;
            }
        }}
    }}
}


void
SquareMap::
render_upper(Image&  dst) const
{
  auto&  src = *source_image;

  constexpr int  chip_size = 24;

    for(int  y = 0;  y < height;  y += 1){
    for(int  x = 0;  x <  width;  x += 1){
      auto&  sq = get(x,y);

      const int  dst_x_base = chip_size*x;
      const int  dst_y_base = chip_size*y;

      const int  src_x_base = chip_size*sq.upper.x;
      const int  src_y_base = chip_size*sq.upper.y;

        for(int  yy = 0;  yy < chip_size;  yy += 1){
        for(int  xx = 0;  xx < chip_size;  xx += 1){
          auto&  v = src.const_pixel(src_x_base+xx,src_y_base+yy);

            if(v&8)
            {
              dst.pixel(dst_x_base+xx,dst_y_base+yy) = v;
            }
        }}
    }}
}




void
SquareMap::
change_source(Image&  img)
{
  source_image = &img;
}


namespace{
bool
test_qbf(FILE*  f)
{
  constexpr uint8_t
  signature[4] =
  {
    'Q','B','F',0
  };


    for(int  i = 0;  i < 4;  i += 1)
    {
      auto  c = fgetc(f);

        if(c != signature[i])
        {
          return false;
        }
    }


  return true;
}
}

void
SquareMap::
load(const char*  path)
{
  auto  f = fopen(path,"rb");

    if(f)
    {
        if(test_qbf(f))
        {
          int  w = fgetc(f);
          int  h = fgetc(f);
          int  d = fgetc(f);

          width  = w;
          height = h;

          table.resize(w*h);

            for(int  y = 0;  y < h;  y += 1){
            for(int  x = 0;  x < w;  x += 1){
              auto&  sq = get(x,y);

              sq.attribute = fgetc(f);

              sq.lower.x = fgetc(f);
              sq.lower.y = fgetc(f);
              sq.upper.x = fgetc(f);
              sq.upper.y = fgetc(f);
            }}
        }


      fclose(f);
    }
}


}}




