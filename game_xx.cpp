#include"game_xx.hpp"
#include"fcfont.hpp"
#include<vector>




WordPool
word_pool;


std::vector<Node*>
node_pool;



WordPool::iterator
touch_word(const char16_t*  name, Node*  node)
{
  auto  it = word_pool.find(name);

    if(it == word_pool.end())
    {
      it = word_pool.emplace(std::make_pair(name,NodeList())).first;
    }


  it->second.emplace_back(node);


  return it;
}


void
print_word_pool()
{
  char  buf[4];

  printf("WORD_POOL\n");

    for(auto&  w: word_pool)
    {
        for(auto  c: w.first)
        {
          fcfont::encode(c,buf);

          printf("%s",buf);
        }


      printf("[%d]\n",w.second.size());
    }
}




Node::
Node(const char16_t*  name, Node*  parent_):
word_iterator(touch_word(name,this)),
parent(nullptr)
{
  node_pool.emplace_back(this);

    if(parent_)
    {
      parent_->join({this});
    }
}


void
Node::
join(std::initializer_list<Node*>  children_)
{
    for(auto  child: children_)
    {
        if(child && !child->parent)
        {
          child->parent = this;

          children.emplace_back(child);
        }
    }
}


const std::u16string&
Node::
get_name() const
{
  return word_iterator->first;
}


void
Node::
print_name() const
{
  char  buf[4];

    for(auto  c: get_name())
    {
      fcfont::encode(c,buf);

      printf("%s",buf);
    }
}


void
Node::
print() const
{
  char  buf[4];

  print_name();

    if(children.size())
    {
      printf("{");

        for(auto  child: children)
        {
          child->print_name();

          printf(",");
        }


      printf("}");
    }


    if(parent)
    {
      printf(" -> ");

      parent->print_name();
    }


  printf("\n");
}


void
print_node_pool()
{
  printf("NODE_POOL\n");

    for(auto  nd: node_pool)
    {
      nd->print();

      printf("\n");
    }
}


void
test()
{
auto   foods_node = new Node(u"たべもの");
auto  fruits_node = new Node(u"くだもの",foods_node);
auto   snack_node = new Node(u"おやつ",foods_node);

fruits_node->join({new Node(u"りんご"),
                   new Node(u"ぶどう"),
                   new Node(u"みかん"),
                   new Node(u"もも"),
                   new Node(u"いちご")});

print_word_pool();
print_node_pool();

}


