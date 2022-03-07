//
//  MatchMaker.h
//  project_4
//
//  Created by Angela Yang on 3/6/22.
//

#ifndef MatchMaker_h
#define MatchMaker_h
#include "provided.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"

class MatchMaker {
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    std::vector<EmailCount>
    IdentifyRankedMatches(std::string email, int threshold) const;
};

#endif /* MatchMaker_h */
