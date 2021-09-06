//
// Created by j473wu on 2021-03-21.
//
#include <iostream>
#include <string>

class node{
private:
    std::string key;
    node *child[26];
    node *parent;
    bool str_end;
    int num_child;

public:
    node();
    ~node();
    void set_key(const char& k);
    std::string get_key();
    void set_child(node *a, const int& pos);
    node* get_child(const int& pos);
    void set_parent(node *k);
    node* get_parent();
    void inc_child(const int& i);
    int get_num_child();
    bool leaf();
    void end_str(const bool& stat);
    bool check_end();
};



//--------------------------------

class trie{
private:
    node *root;
    int trie_size;
    std::string prt;
    int max_len;

public:
    trie();
    ~trie();
    int size();

    std::string insert(const std::string& w);
    std::string erase(const std::string& w);
    std::string search(const std::string& w);
    void print();
    void autocomplete(const std::string& prefix);
    bool empty();
    void clear();
    //bool check(std::string w);
    void preorder_print(node *k, char str[], const int& level);
    void postorder_clear(node *k);
    void auto_print(node* k, const std::string& prefix, char str[], const int& level);
    bool check_prefix(const std::string& prefix);
    void rec_insert(node* k, const std::string& str, const int& level);
    void rec_erase(node *k, const std::string& str, const int& level);
    std::string rec_search(node *k, const std::string& str, const int& level);
};

class illegal_exception{
private:
    std::string msg;
public:
    illegal_exception(const std::string& msg);
    ~illegal_exception();
};

