#include"MorseTree.h"

MorseTree::MorseTree(char left = '.', char right = '_') {
   root = new BTNode<char>;

   /* I allow specifying different binary codes, though ./_ is default. */

   RIGHT = right;
   LEFT = left;
}

MorseTree::~MorseTree() {
   delete(root);
}

MorseTree::MorseTree(std::istream& stream, char left = '.', char right='_') : MorseTree(left,right) {
   std::string line;
   char chr;

   /*
      Build tree.
      Since inserts should be approx the same as for binary search trees,
      O(n log(n))
   */

   std::skipws;
   while(stream >> chr) {
      if(stream >> line) {
         map[chr] = line;
         insert(chr,line);
      }
      else
         throw std::runtime_error("Improper formatting: only one character on last line.");
   }
}

void MorseTree::insert(const char& chr, const std::string& string) {
   size_t size = string.size();
   BTNode<char>* curr = root;
   map[chr] = string;

   /*
      Simple binary tree logic. This should actually correspond to
      the average case for a binary search tree, or O(log(n)) average insert,
      as they are logically equivalent for a well-balanced tree.
   */

   for(int i = 0; i < size; i++) {
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
   */
   auto find = map.find(chr);

   if(find == map.end())
      if(find = map.find(tolower(chr)), find == map.end())
         return "";

   return find->second;
}

char MorseTree::decode_letter(const std::string& string) const {
   size_t size = string.size();
   BTNode<char>* curr = root;
   if(size == 0)
      return '\0';

   /*
      Pretty simple tree logic. Traverse the tree, code corresponds to
      right or left, print code if valid and non-empty. 
   */

   for(int i = 0; i < size; i++) {
      if(string[i] == LEFT) {
         if(curr->left == NULL)
            throw std::runtime_error("Decoding failed: code does not map onto character.");

         curr = curr->left;
      }
      else if(string[i] == RIGHT) {
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
   out << encode_text(str) << std::endl;
}

std::string MorseTree::encode_text(const std::string& str) const {
   std::istringstream istr(str);
   std::ostringstream ostr;
   char chr;

   istr >> std::noskipws;
   while(istr >> chr)
      if(chr == ' ')
         ostr << " / ";
      else
         ostr << encode_letter(chr) << ' ';

   return ostr.str();
}

void MorseTree::decode_text(const std::string& str, std::ostream& out) const {
   out << decode_text(str) << std::endl;
}

std::string MorseTree::decode_text(const std::string& str) const {
   std::istringstream istr(str);
   std::ostringstream ostr;
   std::string word;

   istr >> std::skipws;
   while(istr >> word)
      if(word == "/")
         ostr << " ";
      else
         ostr << decode_letter(word);

   return ostr.str();
}

/* To output directly */
void MorseTree::print_tree(std::ostream& out) const {
   std::cout << print_tree() << std::endl;
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
      ostr << "NULL" << std::endl;
      return ostr.str();
   }

   /* Print tree inorder. */

   ostr << local_root->data << std::endl;
   print_tree(local_root->left,ostr);
   print_tree(local_root->right,ostr);
   return ostr.str();
}
