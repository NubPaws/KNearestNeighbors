#include "VectorDataSet.h"
#include "StringValidator.h"

class VectorDataSet {
    typedef std::pair<std::vector<double>, std::string> DataEntry;

private:
    std::vector<DataEntry> dEntryVectors;
    /**
     * @brief this function will calculate the num degree of vector,and will help determine the place of the plant name.
     *
     * @param s
     * @return int which represent the number of white spaces in the string.
     */

    int commasCouter(std::string s){
        int counter = 0;
        for(int i = 0; i < s.length(); i++){
            if(s[i] == ','){
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
    DataEntry createDataEntry(std::string s){
        std::string pName = "";
        std::string pVector = "";

        std::vector<double> dEntryFirst;
        DataEntry toReturn;
        int numOfCommas = commasCouter(s);
        int i = 0;

        //this while loop will create the left side of the dataEntry (vecotr)
        while(s[i]){
            //when num of white spaces is 0 we are on the name part of the string
            if(numOfCommas == 0){
                break;
            }
            if(std::isspace(s[i++])){
                //checks if the string collected is indeed in a form of "double"
                if(!StringValidator::isDouble(pVector)){
                    return toReturn; //TODO ask rami how to return null
                }else {
                    dEntryFirst.push_back(std::stod(pVector));
                    pVector.clear();
                }
            } else{
                //push the next character to the string
                pVector.push_back(s[i]);
            }
            numOfCommas--;
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
    /**
     * @brief this function will create the dentrey vector which will contain all the dataEntry pairs.
     * @param file the isstream.
     */
    void createDentryVectors(std::istream& file){
        std::string line = "";

        //this loop will go on untill there is no more data from user.
        while(std::getline(file,line)) {
            //TODO if dentery == null handle it.
            dEntryVectors.push_back(createDataEntry(line));
            line.clear();
        }
    }
public:

    VectorDataSet(std::istream file){
        createDentryVectors(file);
    }


};
