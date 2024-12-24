#include <iostream>
#include <string>
using namespace std;
#include "HCTree.hpp"

int main(int argc, char* argv[]){
    //cout << argc << endl;
    if (argc != 3) {
        cerr << "ERROR: Incorrect parameters\nUsage: ./compress <original_file> <compressed_file>"<< endl;
        return 1;
    }
    FancyInputStream readFile(argv[1]);
    FancyOutputStream writeFile(argv[2]);
    if(readFile.filesize() == 0){
        return 0;
    }
    string fileInput;
    vector<int> fqs = vector<int>(256, 0);
    while(true){
        int byteVal = readFile.read_byte();
        if(byteVal == -1 ){
            break;
        }
        fqs[byteVal]++;
    }
    HCTree testobj;
    testobj.build(fqs);
    readFile.reset();
    for(int i=0; i<fqs.size();i++){
        writeFile.write_int(fqs[i]);
    }
    
    while(true){
        int byteVal = readFile.read_byte();
        if(byteVal == -1){
            break;
        }
        testobj.encode(char(byteVal), writeFile);
    }
    return 0;
}
