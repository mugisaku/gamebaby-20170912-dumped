#include"game_message.hpp"




struct
MessagePage::
Line
{
  std::u16string  string;

  Line*  next=nullptr;

};


MessagePage::
MessagePage(int  col_n, int  row_n):
column_number(col_n),
row_number(row_n)
{
    if(row_n > 0)
    {
      row_n -= 1;

      first = new Line;

      current = first;

        while(row_n--)
        {
          auto  line = new Line;

          current->next = line;

          current = line;
        }


      last = current        ;
             current = first;
    }
}




void
MessagePage::
clear()
{
  auto  next = first;

   while(next)
   {
     next->string.clear();

     next = next->next;
   }


  current = first;
}


void
MessagePage::
rotate()
{
  auto  old_first = first;

  first = old_first->next;

  last->next = old_first;

  last = old_first;

  last->next = nullptr;

  last->string.clear();


  current = last;
}


void
MessagePage::
push(char16_t  c)
{
    if(!is_full())
    {
        if(c == '\n')
        {
          current = current->next;
        }

      else
        {
          current->string.push_back(c);

            if(current->string.size() >= (column_number-1))
            {
              current = current->next;
            }
        }
    }
}



bool
MessagePage::
is_full() const
{
  return !current;
}


void
MessagePage::
render(gmbb::Plain&  dst, int  x, int  y) const
{
  auto  next = first;

    while(next)
    {
      dst.print_tall(next->string.data(),gmbb::font_color,x,y);

      y += gmbb::font::tall_size;

      next = next->next;
    }
}




