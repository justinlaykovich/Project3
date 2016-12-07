/*
   MorseTree interface.
   Author: Justin Laykovich
   CS303, Fall 2016
*/
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
   ~MorseTree();
   MorseTree(const char&,const char&);
   MorseTree(std::istream&,const char&,const char&);

   void build_tree(std::istream&);

   void insert(const char&, const std::string&);

   std::string encode_letter(const char&) const;
   char decode_letter(const std::string&) const;

   std::string encode_text(const std::string&) const;
   void encode_text(const std::string&, std::ostream&) const;

   std::string decode_text(const std::string&) const;
   void decode_text(const std::string&, std::ostream&) const;

   void print_tree(std::ostream&) const;
   std::string print_tree() const;
   std::string print_tree(BTNode<char>*, std::ostringstream&) const;
private:
   char RIGHT;
   char LEFT;
   BTNode<char>* root = NULL;
   std::map<char,std::string> map;
   void delete_tree();
   void delete_tree(BTNode<char>*);
};

#endif
