#include"gmbb_image.hpp"
#include<cstring>
#include<libpng/png.h>



namespace gmbb{




namespace{
void
read(png_structp  png, png_bytep  buf, png_size_t  size)
{
  auto&  r = *static_cast<FileReader*>(png_get_io_ptr(png));

    while(size--)
    {
      *buf++ = r.get();
    }
}
}


void
Image::
load_png(FileReader&  r)
{
  png_structp  png = png_create_read_struct(PNG_LIBPNG_VER_STRING,nullptr,nullptr,nullptr);
  png_infop    png_info = png_create_info_struct(png);

  png_set_read_fn(png,&r,read);

  png_read_info(png,png_info);

  int  depth = png_get_bit_depth(png,png_info);
  int  color_type = png_get_color_type(png,png_info);

    if(color_type != PNG_COLOR_TYPE_PALETTE)
    {
      printf("パレットでないPNGは読めません\n");

      throw;
    }


  auto  w = png_get_image_width( png,png_info);
  auto  h = png_get_image_height(png,png_info);

  resize(w,h);

  png_color*  tmp_palette;

  int  color_number;

  png_get_PLTE(png,png_info,&tmp_palette,&color_number);


  png_set_packing(png);

    for(int  y = 0;  y < h;  ++y)
    {
      png_read_row(png,&pixels[w*y],nullptr);
    }


  png_read_end(png,png_info);
  png_destroy_read_struct(&png,&png_info,nullptr);
}


}





