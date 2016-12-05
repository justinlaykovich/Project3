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
   MorseTree();
   MorseTree(std::istream&);

   void insert(const char&, const std::string&);

   char decode_letter(const std::string&);
   std::string encode_letter(const char&);

   std::string decode_text(const std::string&);
   void decode_text(const std::string&, std::ostream&);

   std::string encode_text(const std::string&);
   void encode_text(const std::string&, std::ostream&);
private:
   BTNode<char>* root;
   std::map<char,std::string> map;
};

#endif
