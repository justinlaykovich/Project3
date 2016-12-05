#include<iostream>
#include<fstream>
#include<string>
#include"MorseTree.cpp"

using std::cout;
using std::endl;

int main() {
   std::ifstream file("morse.txt");
   MorseTree tree(file);
   file.close();

   std::cout << tree.decode_letter("._") << endl;
   std::cout << tree.decode_letter("_..") << endl;

   tree.encode_text("abcdefghijklmnopqrstuvwxyz", std::cout);
   tree.decode_text(tree.encode_text("abcdefghijklmnopqrstuvwxyz"), std::cout);
   tree.encode_text("Three blind mice, see how they run.", std::cout);
   tree.decode_text(tree.encode_text("Three blind mice, see how they run."), std::cout);
   return 0;
}
