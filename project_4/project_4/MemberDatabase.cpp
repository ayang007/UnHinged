//
//  MemberDatabase.cpp
//  project_4
//
//  Created by Angela Yang on 3/6/22.
//

#include <stdio.h>
#include "MemberDatabase.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

MemberDatabase::MemberDatabase() {
    
}

MemberDatabase::~MemberDatabase() {
    
}
bool MemberDatabase::LoadDatabase(std::string filename) {
    ifstream infile(filename);
    int profileLine = 0;
    std::string tempName;
    std::string tempEmail;
    PersonProfile* currentPerson;

    // If the file cannot be found, returns false
    if (!infile)
        return false;
    
    // Loads in all lines of the document,
    std::string instring;
    while (getline(infile, instring))
    {
        profileLine++;
        if (instring == "") {
            profileLine = 0;
            continue;
        }
        else if (profileLine == 1) {
            //this is the name
            tempName = instring;
        }
        else if (profileLine == 2) {
            //this is the email
            tempEmail = instring;
            personRadixTree.insert(instring, PersonProfile(tempName,instring)); //inserts into tree mapping email to person profile
            currentPerson = personRadixTree.search(instring);
        }
        else if (profileLine == 3) {
            //number of attval pairs
        }
        else if (profileLine > 3) {
            //attvals
            std::string att;
            std::string val;
            bool isVal = true;
            for (int j = 0; j < instring.size(); j++) {
                if (instring[j] == ',') {
                    isVal = false;
                }
                else if (isVal) {
                    att += instring[j];
                }
                else if (!isVal) {
                    val += instring[j];
                }
            }

            AttValPair newPair = AttValPair(att, val);
            //inserting this email address under all att val pairs it associates with.
            currentPerson->AddAttValPair(newPair);
            vector<std::string>* emailListPointer;
            vector<std::string> emailList;
            emailListPointer = &emailList;
            if (emailRadixTree.search(att+val) != nullptr) {
                emailList = *emailRadixTree.search(att+val);
            }
            emailList.push_back(tempEmail);
            emailRadixTree.insert(att+val, emailList);
        }
    }

    // File loaded, return true
    return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
    std::string stringAttVal = input.attribute + input.value;
    vector<std::string> email;
    if (emailRadixTree.search(stringAttVal) != nullptr)
        email = *emailRadixTree.search(stringAttVal);
    return email;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const {
    return personRadixTree.search(email);
}
