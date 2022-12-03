#include "VectorDataSet.h"
#include "StringValidator.h"

class VectorDataSet {
    typedef std::pair<std::vector<double>, std::string> DataEntry;

private:
    std::vector<DataEntry> D_EntryVectors;
    /**
     * @brief this function will calculate the num degree of vector,and will help determine the place of the plant name.
     *
     * @param s
     * @return int which represent the number of white spaces in the string.
     */

    int whiteSpaceCouter(std::string s){
        int counter = 0;
        for(int i = 0; i < s.length(); i++){
            if(isspace(s[i])){
                counter++;
            }
        }
        return counter;
    }

    /**
     * @brief (might be changed) this is a function that creates the dataEntry pair.
     *
     * @param s string that represent the data from stream.
     * @return toReturn - the dataEntry pair.
     */
    DataEntry getDataEntry(std::string s){
        std::string pName = "";
        std::string pVector = "";

        std::vector<double> dEntryFirst;
        DataEntry toReturn;
        int numOfWhitSpaces = whiteSpaceCouter(s);
        int i = 0;

        //this while loop will create the left side of the dataEntry (vecotr)
        while(s[i]){
            //when num of white spaces is 0 we are on the name part of the string
            if(numOfWhitSpaces == 0){
                break;
            }
            if(std::isspace(s[i++])){
                //checks if the string collected is indeed in a form of "double"
                if(!StringValidator::isDouble(pVector)){
                    return toReturn; //TODO ask rami how to return null
                }else {
                    dEntryFirst.push_back(std::stod(pVector));
                }
            } else{
                //push the next character to the string
                pVector.push_back(s[i]);
            }
            numOfWhitSpaces--;
        }
        // this while loop right-side of dataEntery (the name of plant)
        while(s[i]){
            pName.push_back(s[i]);
            i++;
        }

        //TODO add function that checks if the name is vaild.
        toReturn.second = pName;
        return toReturn;
    }

public:




    VectorDataSet(std::istream file){

    }

};
