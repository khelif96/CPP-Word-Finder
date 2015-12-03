#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
vector<string> search(string input, int wordSize);

int main(){
  cout << "Crossword finder\n" << "Enter part of the word you wish to find\n";
  cout << "Use ? marks for letters you do not know\n eg. h??lo\n";
  string input = "";
  cin >> input;
  cout << "The word contains " << input.size() << " Characters\n";


  vector<string> results = search(input, input.size());
  for(int i =0; i< results.size(); i++){
    cout << results[i] << endl;
  }
}

vector<string> search(string input,int wordSize){
  cout << "Searching For the word...\n";
  ifstream wordList ("words.txt");
  string temp = "";
  vector<string> letterSections;
  vector<string> answers;
  string line;
  int found;
  int foundInInput;
  bool prevIsQues = false;
  for(int i = 0; i < input.size(); i++){
    if(input[i] != '?' && !prevIsQues){
      prevIsQues = false;
      temp = temp + input[i];
    }else if(input[i] == '?' && !prevIsQues){
      prevIsQues = true;
      letterSections.push_back(temp);
      temp = "";
    }
  }
    letterSections.push_back(temp);

  cout << "Found " << letterSections.size() << " Subsections of letters in the input\n";


  if (wordList.is_open())
  {
      cout << "Opened Wordlist\n";
      getline(wordList,line);
      cout << line << endl;
    while ( getline (wordList,line) )
    {
      if(wordSize == line.size()){
          cout << "Found one size match\n";
        for(int i = 0; i< letterSections.size(); i++){
            found = input.find(letterSections[i]);
            if (found!=std::string::npos){
              cout << "Found something \n";
              foundInInput = line.find(letterSections[i]);
              if(foundInInput!= std::string::npos){
                answers.push_back(line);
              }
            }
        }
      }
    }
    wordList.close();
  }
  return answers;
}
