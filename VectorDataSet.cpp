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


public:




    VectorDataSet(std::istream file){

    }

};
