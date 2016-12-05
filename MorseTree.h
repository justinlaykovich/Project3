#ifndef _MORSETREE_H_
#define _MORSETREE_H_
#include<string>
#include<iostream>
#include<map>
#include<sstream>
#include<stdexcept>

template<typename T>
struct BTNode {
   T data;
   BTNode<T>* left;
   BTNode<T>* right;
   BTNode(){};
   BTNode(T data, BTNode<T>* left = NULL, BTNode<T>* right = NULL):data(data),left(left),right(right) {};
};

class MorseTree {
public:
   MorseTree(const char&,const char&);
   ~MorseTree();
   MorseTree(std::istream&,const char&,const char&);

   void insert(const char&, const std::string&);

   char decode_letter(const std::string&) const;
   std::string encode_letter(const char&) const;

   std::string decode_text(const std::string&) const;
   void decode_text(const std::string&, std::ostream&) const;

   std::string encode_text(const std::string&) const;
   void encode_text(const std::string&, std::ostream&) const;

   std::string print_tree() const;
   std::string print_tree(BTNode<char>*, std::ostringstream&) const;
   void print_tree(std::ostream&) const;
private:
   char RIGHT;
   char LEFT;
   char DELIM_LETTER;
   char DELIM_WORD;
   BTNode<char>* root;
   std::map<char,std::string> map;
};

#endif
