#include "vcfRCommon.h"
#include <string>

//static 
//static 
void vcfRCommon::strsplit(std::string& mystring, std::vector<std::string>& vec_o_strings, char& split){
//void strsplit(std::string& mystring, std::vector<std::string>& vec_o_strings, char& split){
  // mystring is a string to be split on the character 'split'.
  // vec_o_strings is empty and will be pushed on to.

  int start = 0;
  int i=0;

  for(i = 1; i < mystring.size(); i++){
    if( mystring[i] == split){
      std::string temp = mystring.substr(start, i - start);
      vec_o_strings.push_back(temp);
      start = i+1;
      i = i+1;
    }
  }

  // Handle the last element.
  std::string temp = mystring.substr(start, i - start);
  vec_o_strings.push_back(temp);
  
}


void vcfRCommon::gtsplit(std::string& mystring,
                         std::vector<std::string>& vec_o_strings,
                         int& unphased_as_na){

  // mystring is a string of genotypes to be split a character.
  // Genotypes may be delimited as | or /.
  // vec_o_strings is empty and will be pushed on to.
  // Sometimes, genotypes delimited with / may be undesireable.
  // In this case missing data should be returned.
  
  int start = 0;
  int i=0;
  
  char split1 = '|'; // Must be single quotes!
  char split2 = '/'; // Must be single quotes!

  // Iterate through genotype string looking for delimiters.  
  for(i = 0; i < mystring.size(); i++){
    if( mystring[i] == split1 ){
      // Found a delimiter.
      std::string temp = mystring.substr(start, i - start);
      vec_o_strings.push_back(temp);
      start = i+1;
      i = i+1;
    } else if ( mystring[i] == split2 ){
      // Found a delimiter.
      if( unphased_as_na == 1 ){
        while( vec_o_strings.size() > 0 ){
          vec_o_strings.pop_back();
        }
        vec_o_strings.push_back( "." );
        return;
      } else {
        std::string temp = mystring.substr(start, i - start);
        vec_o_strings.push_back(temp);
        start = i+1;
        i = i+1;
      }
    }
  }
  
  // Handle the last element.
  std::string temp = mystring.substr(start, i - start);
  vec_o_strings.push_back(temp);
  
}

