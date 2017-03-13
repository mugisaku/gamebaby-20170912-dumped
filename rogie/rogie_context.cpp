#include"rogie_context.hpp"




Context::
Context(Callback  cb, Piece&  caller_):
callback(cb),
caller(caller_),
memory{0}
{
}




