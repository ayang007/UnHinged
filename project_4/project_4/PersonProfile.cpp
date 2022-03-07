//
//  PersonProfile.cpp
//  project_4
//
//  Created by Angela Yang on 3/6/22.
//

#include <stdio.h>
#include "PersonProfile.h"
#include "provided.h"

PersonProfile::PersonProfile(std::string name, std::string email) {
    m_name = name;
    m_email = email;
}

PersonProfile::~PersonProfile() {
    
}

std::string PersonProfile::GetName() const {
    return m_name;
}

std::string PersonProfile::GetEmail() const {
    return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval) {
    for (int i = 0; i < m_personality.size(); i++)
        m_personality.push_back(attval);
}

int PersonProfile::GetNumAttValPairs() const {
    return m_personality.size();
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {
    if (attribute_num > GetNumAttValPairs())
        return false;
    else {
        attval = m_personality[attribute_num];
        return true;
    }
}
