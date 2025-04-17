#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>


#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void potentialWordsHelper (size_t size, std::string& current, const std::set<std::string>& dict, const std::string& floating,std::string& now, std::set<std::string>& options,const std::string& in);
bool isValid(std::string potentialWord, const std::string& floating,const std::string& in);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> possibleWords;
    std::string current = in;
    std::string now = floating;
    potentialWordsHelper(0, current, dict, floating, now, possibleWords, in);
    return possibleWords;
    
}

// Define any helper functions here

void potentialWordsHelper(size_t position, std::string& current, const std::set<std::string>& dict,const std::string& floating,  std::string& now, std::set<std::string>& options, const std::string& in) 
{
    if(current.size() == 0){
      return;
    }
    
    if((current.size()) == position)
    {
      if(isValid(current, now, in)){
        if(dict.find(current) != dict.end()){
          options.insert(current);
        } 
      }
      return;
    }

    if(current[position] == '-'){
       /* for(size_t i = 0; i < floating.size(); ++i){
          current[position] = floating[i];
          std::string now = floating;
          now.erase(i,1);
          potentialWordsHelper(position + 1, current, dict, now, options);
        }
        if(floating.size() < (current.size() - position)){
          for(char place = 'a'; place <= 'z'; ++place){
            if(floating.find(place) == std::string::npos) {
              current[position] = place;
              potentialWordsHelper(position + 1, current, dict, floating, options);
            } 
          }
        }
        current[position] = '-';*/

        for(size_t i = 0; i < floating.size(); ++i){
          current[position] = floating[i];
          std::string on = floating;
          on.erase(i,1);
          potentialWordsHelper(position + 1, current, dict, on, now, options, in);
        }
        if(floating.size() < (current.size() - position)){
          for(char place = 'a'; place <= 'z'; ++place){
            if(floating.find(place) == std::string::npos) {
              current[position] = place;
              potentialWordsHelper(position + 1, current, dict, floating,now, options, in); 
            }
          }
        }
        current[position] = '-';

        /*for(char place = 'a'; place <= 'z'; place++){
           size_t location = now.find(place);
           if(location != std::string::npos){
              current[position] = now[location];
               now.erase(location,1);
               potentialWordsHelper(position + 1, current, dict,floating, now, options);
           }
           else{
            current[position] = place;
            potentialWordsHelper(position + 1, current, dict, floating,now, options);
           }
        }
        current[position] = '-';*/
    }
    else{
      potentialWordsHelper(position + 1, current, dict, floating,now, options, in);
    }

}
bool isValid(std::string potentialWord, const std::string& floating, const std::string& in) 
{
  for(size_t i = 0; i < floating.size(); ++i){
    size_t location = potentialWord.find(floating[i]);
    if(location == std::string::npos){
      return false;
    }
    potentialWord[location] = '-';
  }
  return true;
}
