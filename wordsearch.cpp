#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <sstream>
#include <cstdlib>
#include <utility>
#include <algorithm>
using namespace std;

//Jonah Engelmann Word Search Function

typedef pair<int, int> location;//pair for coordinates in the grid

struct found_word{//stores a found word with its location
    location start;
    location end;
    string str;
    //constructor for the 'found_word' struct
    found_word(const string &init_str = string(), const location &init_start = location(), const location &init_end = location()){
        start=init_start;
        end=init_end;
        str=init_str;  
    }
};

//overload for < operator for found_word
bool operator <(const found_word &first, const found_word &second){ return (first.str < second.str); }

//overload << to cout a found_word with it's information
ostream & operator << (ostream &out, const found_word &in){
  out << "Word was found!: "<<in.str << " from " << "[" << in.start.first << "," << in.start.second << "] to ";
  out << "[" << in.end.first << "," << in.end.second << "]";
  return out;
}

class puzzle{ //object to store a puzzle file
public:
    puzzle(const char *name, const char *dict); //constructor to build the puzzle from a file
    vector<found_word> solve(); //function to solve the puzzle

private:
    unordered_set<string> dictionary;//unordered set with all possible words
    vector<vector<char>> matrix;//2d vector representing a matrix
};

puzzle::puzzle(const char *name, const char *dict){ //constructor for a puzzle
    cout<<"reading the puzzle... Please wait"<<endl;
    ifstream iss(name);

    //reads the puzzle file
    string line;
    int Width;
    while(getline(iss,line)){
        stringstream s1(line);
        vector<char> row;
        char col;
        while(s1 >> col)
            row.push_back(tolower(col));
        if (matrix.size() ==0)
            Width = row.size();
        else if (row.size()!= Width){
            cout<< "The puzzle is uneven" <<endl;
            exit(3);
        }
        matrix.push_back(row);
    }
    iss.close();

    cout<<"reading the dictionary... Please wait"<<endl;
    ifstream dss(dict);
    string word;
    //reads the dictionary file
    while (dss >> word)
        dictionary.insert(word); // add word to dictionary

    dss.close();
}

//function to solve the puzzle and find matching words
vector<found_word> puzzle::solve() {
    vector<found_word> val;
    if (matrix.size() == 0) return vector<found_word>(); //solves edge case or constructor error

    int Width= matrix[0].size();
    int Height= matrix.size();
    cout<<"Solving the puzzle... Dimensions: "<<Width<<"x"<<Height<<" Please wait..."<<endl;
    //iterate over every character in the matrix
    for(int row = 0; row < Height; row++)
        for(int col=0; col<Width; col++)
             for(int diagonal_1 = -1; diagonal_1<= 1; diagonal_1++)
                for(int diagonal_2 = -1; diagonal_2 <= 1; diagonal_2++){
                    if(diagonal_1==0 and diagonal_2==0){continue;}
                    //create a string that will store the possible word
                    string possible_word;
                    possible_word+= matrix[row][col];
                    //will construct a string in all 8 possible directions for the letter, while staying in bounds!
                    for(int row1 = row+ diagonal_2, col1 = col+diagonal_1; row1 >= 0 and row1 < Height and col1 >= 0 and col1 < Width; row1 += diagonal_2, col1 += diagonal_1){
                        //add the character to the string
                        possible_word+= matrix[row1][col1];
                        //check if the string is over 6 letters and in the dictionary
                        if(dictionary.find(possible_word) != dictionary.end() and possible_word.size() >= 6){
                            val.push_back(found_word(possible_word, location(row, col), location(row1, col1)));
                        }
                    }
                }
   sort(val.begin(), val.end());//sort the words
   return val; //return the vector with the words
}

int main(){
  puzzle puzzle1("puzzle.txt", "words.txt");//create puzzle object
  
  vector<found_word> vals = puzzle1.solve();//solve the puzzle and store it in vector val

  for (auto fword: vals){ //printing the found words and their locations
    cout<<fword<<endl;
  }

  return 0;
}
