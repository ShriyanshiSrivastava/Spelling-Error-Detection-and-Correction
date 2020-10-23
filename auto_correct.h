#ifndef _AUTO_CORRECT_H
#define _AUTO_CORRECT_H
#include<bits/stdc++.h>

using namespace std;

class auto_correct{
    long long total_words;

    struct trie{
        long long words;
        trie *edges[26];

        trie(){
            words=0;
            for(int i=0;i<26;i++){
                edges[i]=NULL;
            }
        }
    };
    trie *root;

    set<pair<long long, string> > possible_words;

    public:
        void edits(const string& word, vector<string>& result);
        void known(vector<string>& results);
        void load(trie *, string);
        long long search(trie *, string);
        auto_correct();
        void correct(const std::string&);
};
#endif // _AUTO_CORRECT_H
