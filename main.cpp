/*
   Driver File.
   Author: Justin Laykovich
   CS303, Fall 2016
*/

#include"MorseTree.cpp"
#include<iostream>
#include<fstream>
#include<string>

int main() {
   std::ifstream file("morse.txt");
   MorseTree tree(file);
   file.close();

   std::string test = "abcdefghijklmnopqrstuvwxyz";
   tree.encode_text(test, std::cout);
   tree.decode_text(tree.encode_text(test), std::cout);

   test = "Three blind mice, see how they run.";
   tree.encode_text(test, std::cout);
   tree.decode_text(tree.encode_text(test), std::cout);

   return 0;
}
