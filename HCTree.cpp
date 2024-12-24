#include "HCTree.hpp"


void HCTree::build(const vector<int>& freqs){
    int i=0;
    while(i < freqs.size()){
        if(freqs[i] > 0){
            char sym = char(i);
            HCNode* val = new HCNode(freqs[i], sym); //or char(i) instead of sym
            leaves[i] = val;    
        }
        i++;
    }    
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
    for(i=0; i<leaves.size(); i++){
        if(leaves[i] != nullptr){
            pq.push(leaves[i]);
        }
    }
    HCNode* lc0 = nullptr;
    HCNode* rc1 = nullptr;
    HCNode* tparent = nullptr;
    while (pq.size() != 1) {
        lc0 = pq.top();
        pq.pop();
        rc1 = pq.top();
        pq.pop();
        int pcount = lc0->count+rc1->count;
        unsigned char pchar = ' ';
        tparent = new HCNode(pcount , pchar);
        tparent->c0 = lc0;
        tparent->c1 = rc1;
        lc0->p = tparent;
        rc1->p = tparent;
        pq.push(tparent);
    }
    root = pq.top();
}

void HCTree::DeleteRecur(HCNode* node) {
    if(node != nullptr){
        if(node->c0 != nullptr){
            DeleteRecur(node->c0);
        }
        if(node->c1 != nullptr){
            DeleteRecur(node->c1);
        }
        delete node;
    }
}

HCTree::~HCTree(){
     DeleteRecur(root);
}


void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const{
    int i=0;
    for(i=0; i<leaves.size(); i++){
        if(leaves[i] == nullptr){
            continue;
        }
        if(leaves[i]->symbol == symbol){
            break;
        }
    }
    HCNode * curr = leaves[i];
    vector<int> ret;
    while(curr != root){
        if(curr->p->c0 != nullptr){
            if(curr->p->c0 == curr){
                ret.push_back(0);        
                curr = curr->p;
                continue;
            }
        }
        if(curr->p->c1 != nullptr){
            if(curr->p->c1 == curr){
                ret.push_back(1); 
                curr = curr->p;
                continue;
            }
        }
    }
    for(i=ret.size()-1; i>=0; i--){
        out.write_bit(ret[i]);
    }

}

unsigned char HCTree::decode(FancyInputStream & in) const{
    HCNode * curr = root;
    //int header = in.read_byte();
    while(true){
        if(curr->c0 == nullptr && curr->c1 == nullptr){
            break;
        }
        int temp = in.read_bit();
        if(temp == 0){
            curr = curr->c0;
        }
        else if(temp == 1){
            curr = curr->c1;
        }
    }
    unsigned char ret = curr->symbol;
    return ret;
}
