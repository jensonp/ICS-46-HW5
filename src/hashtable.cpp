#include "hashtable.h"
#include "stats.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Timer.h"
using namespace std;
// ListNode Implementation
ListNode* ListNode::find(string key, ListNode *L){  
    for(ListNode *temp = L; temp!=nullptr; temp=temp->next) if(temp->data == key) return temp;
    return nullptr;
}
ListNode* ListNode::insert(string key, ListNode *L){
    return new ListNode(key, L);
}
ListNode* ListNode::remove(string key, ListNode *L) {
    if (L == nullptr) return nullptr;
    if (L->data == key) {
        ListNode *temp = L->next;
        delete L;
        return temp;
    }
    ListNode *c = L;
    while (c != nullptr && c->next != nullptr){
        if (c->next->data == key) {
            ListNode *t = c->next;
            c->next = t->next;
            delete t;
            break;
        }
        c = c->next;
    }
    return L;
}
// remove

void ListNode::print(ostream & out, ListNode *L){
    for(ListNode *t=L; t!=nullptr; t=t->next){
        out << t->data << "\n";
    }
}

int ListNode::length(ListNode *L){
    int length=0;
    for(ListNode *t = L; t!=nullptr; t=t->next){ ++length; }
    return length;
}
void ListNode::delete_list(ListNode * L){
    while (L!=nullptr){
        ListNode *t = L;
        L = L->next;
        delete t;
    }
}


// HashTable Implementation

    void HashTable::insert(const string &word){
        int i = hasher.hash(word, capacity);
        buf[i] = ListNode::insert(word, buf[i]); 
    }
    bool HashTable::find(const string &word){
        int i = hasher.hash(word, capacity);
        return ListNode::find(word, buf[i]); 
    }
    void HashTable::remove(const string &word){
        int i = hasher.hash(word, capacity);
        buf[i] = ListNode::remove(word, buf[i]); 
    }
    bool HashTable::is_empty(){
        for(size_t i = 0; i<capacity; ++i){ 
            if (buf[i] != nullptr) 
                {return false;}
        }
        return true;
    }
    bool HashTable::is_full(){return false;}
    
    void HashTable::print(ostream &out){
        for(size_t i=0; i<capacity; ++i){
            if(buf[i]!=nullptr){
                ListNode::print(out, buf[i]);
            }
        }
    }
    
    HashTable::~HashTable(){
        for(size_t i=0; i<capacity; ++i){
            ListNode::delete_list(buf[i]); 
        }
        delete [] buf;
    }


    size_t HashTable::number_of_entries(){
        size_t total = 0;
        for(size_t i=0; i<capacity; ++i){ total += ListNode::length(buf[i]); }
        return total;
    }
    size_t HashTable::number_of_chains(){
        //size_t total = 0;
        //for(size_t i=0; i<capacity; ++i){ if(buf[i] != nullptr) ++total; }
        //return total;
        return capacity;
    }
    void HashTable::get_chain_lengths(vector<int> &v){
        v.clear();
        for(size_t i = 0; i < capacity; ++i){v.push_back(ListNode::length(buf[i]));}
    }

// Measurements
void error(string word, string msg) {
    cerr << "Error Word: " << word << "\n"
         << "Error Message: " << msg << "\n"; 
}

void insert_all_words(string file_name, HashTable &L){
    cout << "\n";
    Timer t;
    double eTime;
    ifstream in(file_name);
    t.start();
    for(string word; (in >> word);) { L.insert(word); }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "Insert = " << eTime << endl;
}
void find_all_words(string file_name, HashTable &L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    t.start();
    for(string word; (in >> word);) { L.find(word); }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "Find = " << eTime << endl;
}
void remove_all_words(string file_name, HashTable &L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    t.start();
    for(string word; (in >> word);) { L.remove(word); }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "Remove = " << eTime << endl;
}
void measure_hashtable(string file_name, HashTable &L){
    //cout << L.get_name() << endl;
    insert_all_words(file_name, L);

    vector<int> chain_lengths;
    L.get_chain_lengths(chain_lengths);
    Stats stats(L.get_name(), chain_lengths);
    stats.print(cout);

    find_all_words(file_name, L);
    remove_all_words(file_name, L);
}
void measure_hashtables(string input_file){
        Hasher * H[] = {
        //new ChatGPTHasher{},
        //new STLHasher{}
        //new GoodrichHasher{}
        
        new Weiss2Hasher{},
        new Weiss1Hasher{},
        new GoodrichHasher{},
        new PJWHasher{},
        new WeissHasher{},
        new MultHasher{},
        new SumHasher{}

    };
    int S[] = {1000, 100, 10, 1};

    for (int size : S)
        for (auto h : H) {
            HashTable ht(*h, size);
            measure_hashtable(input_file, ht);
        }
    for (auto h : H)  delete h;
    

}


