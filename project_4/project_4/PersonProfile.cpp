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
    m_numAttributes = 0;
}

PersonProfile::~PersonProfile() { }

std::string PersonProfile::GetName() const {
    return m_name;
}

std::string PersonProfile::GetEmail() const {
    return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval) {
    AttValPair* a = new AttValPair(attval.attribute, attval.value);
    vector<std::string>* PersonalityVectorPointer;
    vector<std::string> PersonalityVector;
    PersonalityVectorPointer = &PersonalityVector;
    if (PersonalityVectorPointer != nullptr) {
        PersonalityVectorPointer = m_personality.search(attval.attribute);
    }
    PersonalityVector.push_back(attval.value);
    m_personality.insert(attval.attribute, PersonalityVector);
    m_attributes.push_back(*a);
    m_numAttributes++;
}

int PersonProfile::GetNumAttValPairs() const {
    return m_numAttributes;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {
    cout << m_attributes.size();
    if (m_attributes.empty() || attribute_num < 0 || attribute_num >= GetNumAttValPairs()) {
        return false;
    }
    else {
        attval = m_attributes[attribute_num];
        return true;
    }
}
