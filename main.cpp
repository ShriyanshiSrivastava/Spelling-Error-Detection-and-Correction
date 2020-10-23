#include <bits/stdc++.h>
#include "auto_correct.h"
#include "windows.h"
#define ll long long
COORD cord = {0, 0};
using namespace std;

auto_correct spell;
int pos=9;
void gotox (int x, int y)
{
        cord.X = x; cord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}
void setcolour(int ForgC)
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
int main()
{
    //cout<<"Hello";
    pos++;
    gotox(43, ++pos);
    cout<<"1. Check for errors in a file"<<endl;
    pos++;
    gotox(46, ++pos);
    cout<<"2. Check spellings manually"<<endl;
    pos++;
    gotox(48, ++pos);
    cout<<"3. Enter 3 to Exit"<<endl;
    pos++;
    gotox(40, ++pos);
    setcolour(15);
	while(1){
		//cout<<"\nEnter the string to be CHECKED\n";
		int choice=0;
		cin>>choice;
		if(choice == 1){
            cout<<"Enter filename: ";
            string filename, s="";
            ifstream fin;
            cin>>filename;
            fin.open(filename);
            if(!fin){
                cout<<"File doesn't exists"<<endl;
            }
            else{
                while(fin>>s){
                    cout<<endl;
                    if(s!=""){
                        spell.correct(s);
                    }
                }
            }
            cout<<endl;
            cout<<endl;
            cout<<"1. Check for errors in a file"<<endl<<endl;
            cout<<"2. Check spellings manually"<<endl<<endl;
            cout<<"3. Enter 3 to Exit"<<endl<<endl;;
		}
		else if(choice ==2){
                while(true){
                    string s;
                    cout<<"\nEnter the string to be CHECKED or exit to go back\n";
                    cin>>s;
                    if(s=="exit"){
                        cout<<endl;
                        cout<<"1. Check for errors in a file"<<endl<<endl;
                        cout<<"2. Check spellings manually"<<endl<<endl;
                        cout<<"3. Enter 3 to Exit"<<endl<<endl;;
                        break;
                    }
                    spell.correct(s);
                    cout<<endl;
                }
		}
		else if(choice==3){
            return 0;
		}
		else {
            cout<<"You need to enter a valid choice mate!"<<endl;
		}

	}
	return 0;
}
