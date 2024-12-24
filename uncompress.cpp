#include <iostream>
#include <string>
using namespace std;
#include "HCTree.hpp"

int main(int argc, char* argv[]){
    if (argc != 3) {
        cerr << "ERROR: Incorrect parameters\nUsage: ./compress <compressed_file> <uncompressed_file>"<< endl;
        return 1;
    }
    FancyInputStream readFile(argv[1]);
    string fileInput;
    FancyOutputStream writeFile(argv[2]);
    //int numChars = readFile.read_byte();
    vector<int> fqs = vector<int>(256, 0);
    int totalChars = 0; 
    if(readFile.filesize() == 0){
        return 0;
    }
    for(int i=0; i<fqs.size();i++){
        fqs[i] = readFile.read_int();
        //cout << fqs[i] << "+" << i << endl;
        totalChars += fqs[i];
    }
    HCTree testobj;
    testobj.build(fqs);
    int cnt = 0;
    while(cnt < totalChars){
      unsigned char val = testobj.decode(readFile);
      writeFile.write_byte(val);
      cnt++;
    }
    
      //  int bitVal = readFile.read_bit();
        //if(bitVal == -1){
        //    break;
        //}
        //if(bitVal == 1){
          //  curr = curr->c1;
        //}
        //if(bitVal == 0){
          //  curr = curr->c0;
        //}
        //if(curr->symbol != '['){
          //  writeFile.write_byte(curr->symbol);
            //curr = testobj.root;
            //cnt++;
        //}
    //}
    return 0;
}
