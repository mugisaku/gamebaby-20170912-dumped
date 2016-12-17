#include"gmbb_image.hpp"



namespace gmbb{




void
Image::
load_mgf(FileReader&  r)
{
  int  w = r.get_be16();
  int  h = r.get_be16();

  resize(w,h);


  int  byte_number = r.get_be32();

  const  int    n = w/2;
  const bool  odd = w&1;

    for(int  y = 0;  y < h;  y += 1)
    {
      uint8_t*  p = &pixels[w*y];

        for(int  x = 0;  x < n;  x += 1)
        {
          auto  v = r.get();

          *p++ = (v>>4)&15;
          *p++ = (v   )&15;
        }


        if(odd)
        {
          *p = r.get()>>4;
        }
    }
}


void
Image::
save_mgf(FileWriter&  w) const
{
  w.put_be16(width );
  w.put_be16(height);

  w.put_be32(width*height/2);

  const  int    n = width/2;
  const bool  odd = width&1;

    for(int  y = 0;  y < height;  y += 1)
    {
      const uint8_t*  p = &pixels[width*y];

        for(int  i = 0;  i < n;  i += 1)
        {
          auto  l = *p++;
          auto  r = *p++;

          w.put((l<<4)|r);
        }


        if(odd)
        {
          w.put((*p)<<4);
        }
    }
}




}





