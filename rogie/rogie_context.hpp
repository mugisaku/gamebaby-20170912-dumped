#ifndef ROGIE_CONTEXT_HPP_INCLUDED
#define ROGIE_CONTEXT_HPP_INCLUDED


#include<memory>


struct Piece;
struct Context;


using Callback = void(*)(Context&  ctx, Piece&  p);


struct
Context
{
  Callback  callback;

  int  memory[8];

  Context(Callback  cb=nullptr);

};




#endif




