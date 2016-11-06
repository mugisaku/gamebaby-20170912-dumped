#ifndef GAME_XX_HPP_INCLUDED
#define GAME_XX_HPP_INCLUDED


#include<cstdint>
#include<cstdio>
#include<string>
#include<list>
#include<map>




struct Node;


using NodeList = std::list<Node*>;

using WordPool = std::map<std::u16string,NodeList>;

using Word = WordPool::value_type;


extern WordPool  word_pool;


WordPool::iterator  touch_word(const char16_t*  name, Node*  node);


void  print_word_pool();
void  print_node_pool();


struct
Node
{
  WordPool::iterator  word_iterator;

  Node*  parent;

  std::list<Node*>  children;

  Node(const char16_t*  name, Node*  parent_=nullptr);

  void  join(std::initializer_list<Node*>  children_);

  const std::u16string&  get_name() const;

  void  print_name() const;
  void  print() const;

};


struct
Variable
{
  WordPool::iterator  word_iterator;

  int32_t  value;
  float     rate;

};


struct
Thing: public Variable
{
  std::list<Thing>  thig_list;

};


enum
ConditionKind
{
  less_than,
  less_than_or_equal,
  greater_than,
  greater_than_or_equal,
  equal,
  not_equal,
  false_,
  not_false,

};


struct
Condition
{
  ConditionKind  kind;

  WordPool::iterator  word_iterator;

  virtual bool  compare(const Variable&  var) const
  {
    auto  v = word_iterator->second == var.word_iterator->second;

    return (kind == false_)? !v:v;
  }

};


struct
ValueCondition: public Condition
{
  int32_t  value;

};


struct
RateCondition: public Condition
{
  float  rate;

};


struct
Standard
{
  int  separator;

  std::list<Condition*>  condition_list;

  Standard*  next;

};


void
test();




#endif




