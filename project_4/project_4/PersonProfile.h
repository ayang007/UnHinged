//
//  PersonProfile.h
//  project_4
//
//  Created by Angela Yang on 3/6/22.
//

#ifndef PersonProfile_h
#define PersonProfile_h
#include <string>
#include <vector>
#include "provided.h"
using namespace std;

class PersonProfile {
public:
    PersonProfile(std::string name, std::string email);

    ~PersonProfile();

    std::string GetName() const;

    std::string GetEmail() const;

    void AddAttValPair(const AttValPair& attval);

    int GetNumAttValPairs() const;

    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    std::string m_name;
    std::string m_email;
    vector<AttValPair> m_personality;
};
#endif /* PersonProfile_h */
