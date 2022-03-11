//
//  MatchMaker.cpp
//  project_4
//
//  Created by Angela Yang on 3/6/22.
//

#include <stdio.h>
#include "MatchMaker.h"

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) : m_memDatabase(mdb), m_attTranslator(at) {}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
    std::vector<EmailCount> a;
    return a;
}
