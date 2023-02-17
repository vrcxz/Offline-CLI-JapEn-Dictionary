#include<iostream>
#include <fstream>
#include<conio.h>
#include<map>
#include <sstream>
#include<string>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

const int WIDTH = 55; // the width of the console in characters


void english_meaningsearch(json &data, string input){
  if (data.find(input) != data.end()) {
    string text = data[input].get<string>();

    istringstream ss(text);
    string word;
    vector<string> words;

    while (std::getline(ss, word, ' ')) {
      words.push_back(word);
    }

    int character_count = 0;
    for (const auto &w : words) {
      if (w.find("--") != string::npos||w.find('.') != string::npos && isdigit(w[w.find('.') - 1])) {
        cout << endl << endl << w << " ";
        character_count = 0;
      } else if (character_count + w.length() + 1 > 50) {
        cout << endl << w << " ";
        character_count = w.length() + 1;
      } else {
        cout << w << " ";
        character_count += w.length() + 1;
      }
    }
  } else {
    cout << "\nNo such word in the directory.\n" << endl;
  }
}





void english_search(json &data,string input){
	bool flag=false;
	for(auto &w: data["words"]){
    	for(auto &s: w["sense"]){
    		for(auto &g: s["gloss"]){
    			  if(input==g["text"]){
    			  	cout<<endl;
    			  	for(auto &kanji: w["kanji"]){
    			  		cout<<"Kanji: "<<kanji["text"].get<string>()<<endl;	 
    			  		flag=true;
    			  	}
    			  	
    			  	for(auto &kana : w["kana"]){
    			  		 cout<<"Kana: "<<kana["text"].get<string>()<<endl;
    			  		 flag=true;
    			  		}
    			  }
    			}
    		}
    	
   	}
   	
      if(!flag) cout<<"\nNo Japanese word found in the entries.\n";
	}


void japanese_search(json &data,string input){
	bool flag=false;
	cout<<endl;
	for(auto &w:data["words"]){
		for(auto &kanji:w["kanji"]){
			  if(input==kanji["text"]){
			         for(auto &sense : w["sense"]){
			         	for(auto &gloss:sense["gloss"]){
			         		cout<<"Meaning: "<<gloss["text"].get<string>()<<endl<<endl;
			         		}
			         	}
			         }
		          }
	    for(auto &kana:w["kana"]){
	    	  if(input==kana["text"]){
	    	  	   for(auto &sense : w["sense"]){
	    	  	      for(auto &gloss:sense["gloss"]){
	    	  	      	cout<<"Meaning: "<<gloss["text"].get<string>()<<endl<<endl;
	    	  	      	}
	    	  	      }
	             }
	     }
	}
	if(!flag) cout<<"\nNo English word found in the entries.\n";
}
	

int main()
{
    
    ifstream f("jmdict.json");
    json data = json::parse(f);
    
    ifstream f2("dictionary.json");
    json endata = json::parse(f2);
    
    char menu_choice;
    string input;
    bool isRunning=true;
    
    while(isRunning){		
    	clrscr();
    	textcolor(YELLOW);
    	cout<<
    	"Offline Japanese Dictionary\n\n";
    	textcolor(7);
    	cout<<
    	"1 - Search Meaning (English to Japanese)\n"
    	"2 - Search Meaning (Japanese to English)\n"
    	"3 - Exit\n\n"
    	"Enter your choice: \n";
    	cin>>menu_choice;
    	//Extra precautions from infnite loop haha
        if(input=="Exit"||input=="exit"){return 0;}
    	clrscr();
    	
    	switch(menu_choice){
    		case '1': {clrscr();
    		cout<<"Enter the English word you want to search: \n";
    		getch(); getline(cin,input);
    		english_search(data,input);
    		cout<<endl<<endl;
    		english_meaningsearch(endata,input);
    		cout<<"\n\n\nPress enter to continue...";
            getch(); break;}
            
    		case '2': {clrscr();
    		cout<<"Enter the Japanese word you want to search: \n";
    		getch(); getline(cin,input);
    		japanese_search(data,input);
    		cout<<"\n\n\nPress enter to continue...";
            getch(); break;}
            
    		case '3': {cout<<"Thank you for using the Offline Japanese Dictionary.\n"; return 0;}
    		
    		default: return 0;
    		}
    }
    
}
