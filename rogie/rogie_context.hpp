#ifndef ROGIE_CONTEXT_HPP_INCLUDED
#define ROGIE_CONTEXT_HPP_INCLUDED


#include<memory>


struct Piece;
struct Context;


using Callback = void(*)(Context&  ctx);


struct
Context
{
  Callback  callback;

  Piece&  caller;

  int  memory[8];

  Context(Callback  cb, Piece&  caller_);

};




#endif




