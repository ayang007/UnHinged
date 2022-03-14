//
//  MatchMaker.cpp
//  project_4
//
//  Created by Angela Yang on 3/6/22.
//

#include <stdio.h>
#include "MatchMaker.h"

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) : m_memDatabase(mdb), m_attTranslator(at) { }

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
    int actualThreshhold = threshold;
    if (threshold < 0)
        actualThreshhold = 0;
    const PersonProfile* currPerson = m_memDatabase.GetMemberByEmail(email);
    int attnum = currPerson->GetNumAttValPairs();
    AttValPair currAttVal;
    vector<std::string> compatibleEmails;
    vector<std::string> tempCompatibleEmails;
    //access all the attributes of the person presented:
    for (int i = 0; i < attnum; i++) {
        currPerson->GetAttVal(i, currAttVal);
        //for each of those attributes, get a vector of the compatible attvalpairs
        vector<AttValPair> compatibleAttValVector = m_attTranslator.FindCompatibleAttValPairs(currAttVal);
        //find the compatible emails, people with the compatible attributes.
        for (int j = 0; j < compatibleAttValVector.size(); j++) {
            tempCompatibleEmails = m_memDatabase.FindMatchingMembers(compatibleAttValVector[i]);
            for (int k = 0; k < tempCompatibleEmails.size(); k++) {
                //build the final vector with all the emails compatible with all traits of a person
                compatibleEmails.push_back(tempCompatibleEmails[k]);
            }
        }
    }
    std::vector<EmailCount> compatibleEmailList;
    std::vector<EmailCount>::iterator it;
    it = compatibleEmailList.begin();
    for (int i = 0; i < compatibleEmails.size(); i++) {
        while (it != compatibleEmailList.end()) {
            if (it->email == compatibleEmails[i]) {
                it->count++;
                break;
            }
            it++;
        }
        if (it == compatibleEmailList.end()) {
            compatibleEmailList.push_back(*new EmailCount(compatibleEmails[i], 1));
        }
    }
    for (int i = 0; i < compatibleEmailList.size(); i++) {
        if (compatibleEmailList[i].count < actualThreshhold) {
            compatibleEmailList.erase(compatibleEmailList.begin()+i);
        }
    }
    return compatibleEmailList;
}
