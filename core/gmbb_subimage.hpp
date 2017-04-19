#ifndef GMBB_SUBIMAGE_HPP
#define GMBB_SUBIMAGE_HPP


#include"gmbb_palette.hpp"
#include"gmbb_filereader.hpp"
#include"gmbb_filewriter.hpp"
#include<vector>




namespace gmbb{


struct Image;


class
SubImage
{
  int  width;
  int  height;

  std::vector<Palette::index_t>  table;

  Palette  palette;

public:
  SubImage();
  SubImage(int  w, int  h);


  void  resize(int  w, int  h);

  void  load_png(FileReader&  r);
  void  load_mgf(FileReader&  r);

  void  save_mgf(FileWriter&  w) const;

  int  get_width() const;
  int  get_height() const;

  Palette::index_t  get_data(int  x, int  y) const;

  void  transfer(int  src_x, int  src_y, int  src_w, int  src_h, Image&  dst, int  dst_x, int  dst_y) const;

};


}




#endif




