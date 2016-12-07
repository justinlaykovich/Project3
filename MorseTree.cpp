/*
   Implementation of MorseTree class
   Author: Justin Laykovich
   CS303, Fall 2016
*/

#include"MorseTree.h"

MorseTree::MorseTree(const char& left = '.', const char& right = '_') {
   /* Allows declaration of different binary code. */

   RIGHT = right;
   LEFT = left;
}

MorseTree::~MorseTree() {

   delete_tree();
}

MorseTree::MorseTree(std::istream& stream, const char& left = '.', const char& right='_') : MorseTree(left,right) {

   build_tree(stream);
}

void MorseTree::build_tree(std::istream& stream) {

   /* Get rid of old tree, if it exists. */

   if(root != NULL)
      delete_tree();

   std::string line;
   char chr;

   root = new BTNode<char>;

   /*
      Build tree.
      Since inserts should be approx the same as for binary search trees,
      O(n log(n))
   */

   stream >> std::skipws;
   while(stream >> chr)
      if(stream >> line)
         insert(chr,line);
      else
         throw std::runtime_error("Improper formatting: only one character on last line.");

}

void MorseTree::insert(const char& chr, const std::string& string) {
   size_t size = string.size();
   BTNode<char>* curr = root;
   map[chr] = string;

   /*
      Simple binary tree logic. This should actually correspond to
      the average case for a binary search tree, or O(log(n)) average insert,
      as they are logically equivalent for a well-balanced morse tree.
   */

   for(size_t i = 0; i < size; i++) {
      if(string[i] == LEFT) {
         if(curr->left == NULL)
            curr->left = new BTNode<char>;

         curr = curr->left;
      }
      else if(string[i] == RIGHT) {
         if(curr->right == NULL)
            curr->right = new BTNode<char>;

         curr = curr->right;
      }
      else
         throw std::runtime_error("Error building tree: Invalid code.");
   }

   curr->data = chr;
}

std::string MorseTree::encode_letter(const char& chr) const {

   /*
      It is assumed that a lowercase letter is code-equivalent to
      an upper case letter unless specified.

      Map.find() is O(log(n)) and so is Map.at() and Map[]. Since I want encode_letter
      to be const (it is a query function), Map.find() is best choice.

      While decoding a bad message should probably through an error,
      encoding plaintext should just discard non-existent characters.
   */

   auto find = map.find(chr);

   if(find == map.end())
      if(find = map.find(tolower(chr)), find == map.end())
         return "";

   return find->second;
}

char MorseTree::decode_letter(const std::string& letter_code) const {
   size_t size = letter_code.size();
   BTNode<char>* curr = root;
   if(size == 0)
      return '\0';

   /*
      Pretty simple tree logic. Traverse the tree, code corresponds to
      right or left, print code if valid and non-empty.
   */

   for(size_t i = 0; i < size; i++) {
      if(letter_code[i] == LEFT) {
         if(curr->left == NULL)
            throw std::runtime_error("Decoding failed: code does not map onto character.");

         curr = curr->left;
      }
      else if(letter_code[i] == RIGHT) {
         if(curr->right == NULL)
            throw std::runtime_error("Decoding failed: code does not map onto character.");

         curr = curr->right;
      }
      else
         throw std::runtime_error("Decoding failed: Invalid code.");
   }

   return curr->data;
}

void MorseTree::encode_text(const std::string& str, std::ostream& out) const {
   out << encode_text(str) << "\n";
}

std::string MorseTree::encode_text(const std::string& str) const {
   std::istringstream istr(str);
   std::ostringstream ostr;
   char chr;

   /* Fetches characters iteratively, decoding at m log(n), m the characters to encode
      and n the alphabet */

   istr >> std::noskipws;
   while(istr >> chr)
      if(chr == ' ')
         ostr << "/ ";
      else
         ostr << encode_letter(chr) << ' ';

   return ostr.str();
}

void MorseTree::decode_text(const std::string& str, std::ostream& out) const {
   out << decode_text(str) << "\n";
}

std::string MorseTree::decode_text(const std::string& str) const {
   std::istringstream istr(str);
   std::ostringstream ostr;
   std::string letter_code;

   /* Decodes a letter at a time. / was chosen as word delimeter. */

   istr >> std::skipws;
   while(istr >> letter_code)
      if(letter_code == "/")
         ostr << " ";
      else
         ostr << decode_letter(letter_code);

   return ostr.str();
}

/* print_trees are useful to see that the tree has actually been built and built correctly. */

/* To output directly */
void MorseTree::print_tree(std::ostream& out) const {
   out << print_tree() << "\n";
}

/* Wrapper function */
std::string MorseTree::print_tree() const {
   std::ostringstream ostr;
   BTNode<char>* local_root = root;
   print_tree(local_root,ostr);
   return ostr.str();
}

std::string MorseTree::print_tree(BTNode<char>* local_root, std::ostringstream& ostr) const {
   if(local_root == NULL) {
      ostr << "NULL" << "\n";
      return ostr.str();
   }

   /* Print tree preorder. */

   ostr << local_root->data << "\n";
   print_tree(local_root->left,ostr);
   print_tree(local_root->right,ostr);
   return ostr.str();
}

void MorseTree::delete_tree() {
   delete_tree(root);
}

void MorseTree::delete_tree(BTNode<char>* local_root) {
   if(local_root == NULL)
      return;

   delete_tree(local_root->right);
   delete_tree(local_root->left);
   delete(local_root);
}
