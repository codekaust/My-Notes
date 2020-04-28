#include <iostream>
#include <fstream>

const static int BUF_SIZE = 4096;

using std::ios_base;

int main(int argc, char** argv) {

   //input | output file could be of any format not necessary txt
   std::ifstream in("in.txt",
      ios_base::in | ios_base::binary);  // Use binary mode so we can
   std::ofstream out("out.txt",            // handle all kinds of file
      ios_base::out | ios_base::binary); // content.
   
   // Make sure the streams opened okay...

   char buf[BUF_SIZE];

   in.read(&buf[0], BUF_SIZE);      // Read at most n bytes into
      
   while (in.gcount() > 0) {
      in.read(&buf[0], BUF_SIZE);      // Read at most n bytes into
      out.write(&buf[0], in.gcount()); // buf, then write the buf to
   } 

   in.close();
   out.close();
}