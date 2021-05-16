#include<bits/stdc++.h>
#include "windows.h"
#include "auto_correct.h"
#define Vector std::vector<std::string>
using namespace std;
COORD coord = {0, 0};
string toAlpha(string s){
    string str="";
    for(long long i=0;i<s.size();i++){
		if(s[i]>='A' and s[i]<='Z'){
			str+=s[i]+32;
		}
		else if(s[i]>='a' and s[i]<='z'){
			str+=s[i];
		}
	}
	return str;
}
long long auto_correct :: search(trie *vertex, string word)
{
    if(word==""){
        return vertex->words;
    }
    else{
        long long pos = word[0]-'a';
        if(vertex->edges[pos]==NULL) return 0;
        word.erase(0, 1);
        return search(vertex->edges[pos], word);
    }
}

void auto_correct :: load(trie *vertex, string word){
    if(word=="") vertex->words++;
    else{
        long long pos = word[0]-'a';
        if(vertex->edges[pos]==NULL){
            vertex->edges[pos] = new trie();
        }
        word.erase(0, 1);
        return load(vertex->edges[pos], word);
    }
}

void auto_correct :: edits(const std::string& word, vector<string>& result){
  for (string::size_type i = 0;i < word.size(); i++)    result.push_back(word.substr(0, i) + word.substr(i + 1)); //deletions
  for (string::size_type i = 0;i < word.size() - 1;i++) result.push_back(word.substr(0, i) + word[i + 1] + word[i] + word.substr(i + 2)); //transposition

  for (char j = 'a';j <= 'z';++j){
    for (string::size_type i = 0;i < word.size(); i++)    result.push_back(word.substr(0, i) + j + word.substr(i + 1)); //alterations
    for (string::size_type i = 0;i < word.size() + 1;i++) result.push_back(word.substr(0, i) + j + word.substr(i)); //insertion
  }
}
void auto_correct :: known(vector<string>& results){
    for (unsigned int i = 0;i < results.size();i++){
        long long num = search(root, results[i]);
        if(num!=0){
            possible_words.insert(make_pair(num, results[i]));
        }
    }
}

void auto_correct :: correct(const std::string& word){
    std::vector<std::string> result;
    possible_words.clear();
    long long numOfStrings = search(root, word);

    if(numOfStrings!=0){
        possible_words.insert(make_pair(numOfStrings, word));
        cout<<word<<" is correct"<<endl;
        return;
    }
    set<pair<long long, string> >::reverse_iterator it;

    edits(word, result);
    known(result);
    if(possible_words.size()==0){
        for (unsigned int i = 0;i < result.size();i++){
            vector<string> subResult;
            edits(result[i], subResult);
            known(subResult);
        }
    }
    int cnt=0;
    if(possible_words.size()>0){
        cout<<"\nPossible Correct Words may be "<<endl;
        for(it=possible_words.rbegin();it!=possible_words.rend();it++){
                cout<<(*it).second<<"         "<<(*it).first<<" "<<endl;
                cnt++;
                if(cnt>10) break;
        }
    }
    else{
        cout<<"No recommendations can be made"<<endl;
    }

}

int p=0;
void gotoxy (int x, int y)
{
        coord.X = x; coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void setcolor(int ForgC)
{
     WORD wColor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
}
auto_correct :: auto_correct(){
   // cout<<"hello"<<endl;
	total_words=0;
	root=new trie();
	ifstream fin;
	fin.open("big.txt");
	string s;
//	long long t;
	while(fin.eof()==0)
	{
		fin>>s;
		s=toAlpha(s);
		if(s!="")
		{
			load(root,s);
			total_words++;
		}
	}
	fin.close();
	p=2;
	setcolor(10);
	gotoxy(44, ++p);
	cout<<"Welcome to 'Auto Correct'"<<endl;
	p++;
	gotoxy(38, ++p);
	cout<<"Created by Shriyanshi Srivastava"<<endl;
	++p;
	gotoxy(50, ++p);
	cout<<"version 1.04"<<endl;
	p++;
	gotoxy(30, ++p);
	cout<<"Total number of known words to this program: "<<total_words<<endl;
}

