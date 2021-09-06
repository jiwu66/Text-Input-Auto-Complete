//
// Created by j473wu on 2021-03-21.
//

#include <iostream>
#include <exception>
#include "trie.h"

node::node(){
    key = "empty";
    for(int i = 0; i < 26; i++){
        child[i] = nullptr;
    }
    parent =nullptr;
    num_child = 0;
    str_end = false;
}

node::~node(){

}

void node::set_key(const char& k) {
    key = k;
}

std::string node::get_key() {
    return key;
}

void node::set_child(node *a, const int& pos) {
    child[pos] = a;
}

node* node::get_child(const int& pos) {
    return child[pos];
}

void node::set_parent(node *k) {
    parent = k;
}

node* node::get_parent() {
    return parent;
}

bool node::leaf() {
    for(int i = 0; i < 26; i++){
        if(child[i] != nullptr){
            return false;
        }
    }
    return true;
}

void node::inc_child(const int& i) {
    num_child+= i;
}

int node::get_num_child() {
    return num_child;
}

void node::end_str(const bool& stat){
    str_end = stat;
}

bool node::check_end(){
    return str_end;
}

//--------------------------------------------------------------------------------
trie::trie(){
    root = new node();
    trie_size = 0;
    max_len = 0;
}

trie::~trie(){
    clear();
    delete root;
    root = nullptr;
}

std::string trie::insert(const std::string& w) {
    if(search(w) == "found"){
        return "failure";
    }

//    node *curr = root;
//    for(int i = 0; i < w.size(); i++){
//        int pos = w[i] - 97;
//        if(curr->get_child(pos) == nullptr) {
//            node *temp = new node();
//            curr->set_child(temp, pos);
//            curr->get_child(pos)->set_parent(curr);
//            curr->inc_child(1);
//        }
//        curr = curr->get_child(pos);
//        curr->set_key(w[i]);
//    }
//    curr->end_str(true);
//
//    trie_size += 1;
//    if(w.size() > max_len){
//        max_len = w.size();
//    }
    node *curr = root;
    int level = 0;
    rec_insert(curr,w, level);

    return "success";
}

std::string trie::erase(const std::string& w) {
    if((search(w) == "not found") || (empty() == 1)){
        return "failure";
    }

    node *curr = root;

    //Traverse to the end of the string:
    for(int i = 0; i < w.size(); i++){
        int pos = w[i] - 97;
        curr = curr->get_child(pos);
    }

    //delete from the bottom:
    curr->end_str(false);
//    for(int i = w.size() - 1; i >= 0; i--){
//        if((curr->check_end() == 0) && (curr->leaf() == 1)){
//            int pos = w[i] - 97;
//            curr = curr->get_parent();
//            delete curr->get_child(pos);
//            curr->set_child(nullptr, pos);
//        }
//        else break;
//    }
    int level = w.size() - 1;
    rec_erase(curr, w, level);

    trie_size -= 1;
    return "success";

}

std::string trie::search(const std::string& w) {
//    node *curr = root;
//    for(int i = 0; i < w.size(); i++){
//        int pos = w[i] - 97;
//        if(curr->get_child(pos) == nullptr){
//            return "not found";
//        }
//        curr = curr->get_child(pos);
//    }
//    if(curr->check_end() == true){
//        return "found";
//    }
//    else return "not found";
    node *curr = root;
    int level = 0;
    return rec_search(curr, w, level);
}

void trie::print() {
    int level = 0;
    char str[max_len];

    if(empty() != 1) {
        preorder_print(root, str, level);
        std::cout << prt.substr(0, prt.size() - 1) << std::endl;
        prt.clear();
    }
}

void trie::autocomplete(const std::string& prefix) {
    if((empty() == 0) && (check_prefix(prefix) == 1)) {
        //Recursively prin:
        //node *curr = root->get_child(prefix[0] - 97);
        node *curr = root;
        int level = prefix.size() - 1;
        char str[max_len];
        for(int i = 0; i < prefix.size() - 1; i++){
            str[i] = prefix[i];
            int pos = prefix[i] - 97;
            curr = curr->get_child(pos);
        }
        auto_print(curr, prefix, str, level);
        std::cout << prt.substr(0, prt.size() - 1) << std::endl;
        prt.clear();
    }
}

bool trie::empty() {
    if(root->leaf() == true){
        return true;
    }
    else return false;
}

void trie::clear() {
    postorder_clear(root);
    trie_size = 0;

}

int trie::size() {
    return trie_size;
}

//bool trie::check(std::string w) {
//    for(int i = 0; i < w.size(); i++){
//        if((w[i] > 122) || (w[i] < 97)){
//            return false;
//        }
//    }
//    return true;
//}

void trie::preorder_print(node *k, char str[], const int& level) {
    if ((k->leaf() == 1) || (k->check_end() == 1)) {
        str[level] = '\0';
        prt.append(str);
        prt.append(" ");
    }
    for (int i = 0; i < 26; i++) {
        if (k->get_child(i) != nullptr) {
            str[level] = k->get_child(i)->get_key()[0];
            preorder_print(k->get_child(i), str, level + 1);
        }
    }
}

void trie::postorder_clear(node *k) {
//    if(k != nullptr){
//        for(int i = 0; i < 26; i++){
//            postorder_clear(k->get_child(i));
//        }
//
//        if(k != root) {
//            for(int i = 0; i <26 ; i++){
//                k->get_parent()->set_child(nullptr,i);
//            }
//            delete k;
//            k = nullptr;
//
//        }
//    }
    if(empty() == 0){
        node *temp = k;
        for(int i = 0; i < 26; i++){
            if(temp->get_child(i) != nullptr) {
                temp = k;
                postorder_clear(temp->get_child(i));
                temp->set_child(nullptr, i);
            }
        }

        if(k != root){
            delete temp;
            temp = nullptr;
        }
    }
}

void trie::auto_print(node *k,const std::string& prefix, char str[], const int& level) {
    if((k->leaf() == 1) || (k->check_end() == 1)){
        str[level] = '\0';
        prt.append(str);
        prt.append(" ");
    }

    for(int i = 0; i < 26; i++){
        if(k->get_child(i) != nullptr){
            str[level] = k->get_child(i)->get_key()[0];
            auto_print(k->get_child(i),prefix,str,level + 1);
        }
    }
}

bool trie::check_prefix(const std::string& prefix) {
    node *curr = root;
    for(int i = 0; i < prefix.size() - 1; i++){
        int pos = prefix[i] - 97;
        if(curr->get_child(pos) != nullptr){
            curr = curr->get_child(pos);
        }
        else return false;
    }

    return true;
}

void trie::rec_insert(node *k, const std::string& str, const int& level) {
    int pos = str[level] - 97;
    if(k->get_child(pos) == nullptr){
        node *temp = new node;
        k->set_child(temp,pos);
        k->get_child(pos)->set_parent(k);
        k->inc_child(1);
    }
    k = k->get_child(pos);
    k->set_key(str[level]);

    if(level == str.size() - 1){
        k->end_str(true);
        trie_size += 1;
        if(str.size() > max_len){
            max_len = str.size();
        }
    }

    if(level < str.size() - 1) {
        rec_insert(k, str, level + 1);
    }
}

void trie::rec_erase(node *k, const std::string& str, const int& level) {
    int pos = str[level] - 97;
    if((k->leaf() == 1) && (k->check_end() == 0)){
        k = k->get_parent();
        delete k->get_child(pos);
        k->set_child(nullptr, pos);

        if(level >= 1) {
            rec_erase(k, str, level - 1);
        }
    }

}

std::string trie::rec_search(node *k, const std::string& str, const int& level) {
    int pos = str[level] - 97;
    if(k->get_child(pos) == nullptr){
        return "not found";
    }
    k = k->get_child(pos);
    if((k->check_end() == 1) && (level == str.size() - 1)){
        return "found";
    }
    if(level < str.size() - 1){
        return rec_search(k, str, level + 1);
    }
    else return "not found";
}

//--------------------------------------------------------------------------
illegal_exception::illegal_exception(const std::string &msg) {
    std::cout << msg << std::endl;
}

illegal_exception::~illegal_exception() {

}