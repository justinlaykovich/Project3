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

   tree.encode_text("abcdefghijklmnopqrstuvwxyz", std::cout);
   tree.decode_text(tree.encode_text("abcdefghijklmnopqrstuvwxyz"), std::cout);

   tree.encode_text("Three blind mice, see how they run.", std::cout);
   tree.decode_text(tree.encode_text("Three blind mice, see how they run."), std::cout);

   return 0;
}
