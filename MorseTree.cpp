#include"MorseTree.h"

MorseTree::MorseTree() {
   root = new BTNode<char>;
}

MorseTree::MorseTree(std::istream& stream) : MorseTree() {
   std::string line;
   while(stream >> line) {
      map[line[0]] = line.substr(1);
      insert(line[0],line.substr(1));
   }
}

void MorseTree::insert(const char& chr, const std::string& string) {
   size_t size = string.size();
   BTNode<char>* curr = root;
   map[chr] = string;

   for(int i = 0; i < size; i++) {
      if(string[i] == '.') {
         if(curr->left == NULL)
            curr->left = new BTNode<char>;

         curr = curr->left;
      }
      if(string[i] == '_') {
         if(curr->right == NULL)
            curr->right = new BTNode<char>;

         curr = curr->right;
      }
   }

   curr->data = chr;
}

std::string MorseTree::encode_letter(const char& chr) {
   return map[tolower(chr)];
}

char MorseTree::decode_letter(const std::string& string) {
   size_t size = string.size();
   BTNode<char>* curr = root;

   for(int i = 0; i < size; i++) {
      if(string[i] == '.') {
         if(curr->left == NULL)
            throw;

         curr = curr->left;
      }
      if(string[i] == '_') {
         if(curr->right == NULL)
            throw;

         curr = curr->right;
      }
      if(string[i] == ' ' || string[i] == '/')
         break;
   }

   return curr->data;
}

void MorseTree::encode_text(const std::string& str, std::ostream& out) {
   out << encode_text(str) << endl;
}

std::string MorseTree::encode_text(const std::string& str, std::ostream& out) {
   std::istringstream istr(str);
   std::ostringstream ostr;
   char chr;
   while(istr >> chr) {
      if(chr == ' ')
         ostr << '/';
      else
         ostr << encode_letter(chr);
   }
   return ostr.str();
}
