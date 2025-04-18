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
void potentialWordsHelper (size_t position, std::string& current, const std::set<std::string>& dict, const std::string& floating, const std::string& constantFloating, std::set<std::string>& options);
bool isValid(std::string potentialWord, const std::string& floating);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::string current = in;
    std::set<std::string> possibleWords;
    const std::string constantFloating = floating;
    potentialWordsHelper(0, current, dict, floating, constantFloating, possibleWords);
    return possibleWords;
    
}

// Define any helper functions here

/* Recursion function that will go through every index of the word that is covered. Through each iteration a character 
will be placed in the string until it removes all dashes. Once it removes all dashes it will check if it is a valid word
and contains all the characters from the floating string.
*/
void potentialWordsHelper(size_t position, std::string& current, const std::set<std::string>& dict,const std::string& floating, const std::string& constantFloating, std::set<std::string>& options) 
{
    if(current.size() == 0){
      return;
    }
    
    // Check if it is valid word that will go to set options once all dashes are covered.
    if((current.size()) == position)
    {
      // First check if it contains all characters from floating string before checking it is a word to be efficient.
      if(isValid(current, constantFloating)){
        //Once it is valid, then we can search within the dictionary to see if it is a real word from the list.
        if(dict.find(current) != dict.end()){
          // After meeting all conditions then we could add the word to the set of final words that could be the answer.
          options.insert(current);
        } 
      }
      return;
    }

    // This will check and go through loops if the current position is a dash thus a character is needed to be placed.
    if(current[position] == '-'){
      /* If there are more postions to be covered than floating then it must mean that we must use other characters that 
        are not the floating ones.
      */
        if(floating.size() < (current.size() - position)){
          for(char place = 'a'; place <= 'z'; ++place){
            // skip the characters in the floating string because we will check them later on.
            if(floating.find(place) == -1) {
              current[position] = place;
              potentialWordsHelper(position + 1, current, dict, floating, constantFloating, options); 
            }
          }
        }
        // Then we will place all the characters from the floating string into the dashes so that the string contains all of them.
        for(size_t i = 0; i < floating.size(); ++i){
          current[position] = floating[i];
          std::string temp = floating;
          // Will remove the character from floating so that we do not repeat it.
          temp.erase(i,1);
          potentialWordsHelper(position + 1, current, dict, temp, constantFloating, options);
        }
        current[position] = '-';
    }
    // This is the correct character in place that was given from in string, so we can just iterate to next position.
    else{
      potentialWordsHelper(position + 1, current, dict, floating, constantFloating, options);
    }

}

// This function will make sure that the potential word contains all the characters from floating.
bool isValid(std::string potentialWord, const std::string& floating) 
{
  for(size_t i = 0; i < floating.size(); ++i){
    size_t location = potentialWord.find(floating[i]);
    if(location == -1){
      return false;
    }
    potentialWord[location] = '-';
  }
  return true;
}
