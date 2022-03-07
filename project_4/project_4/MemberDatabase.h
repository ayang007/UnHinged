//
//  MemberDatabase.h
//  project_4
//
//  Created by Angela Yang on 3/6/22.
//

#ifndef MemberDatabase_h
#define MemberDatabase_h
#include <string>
#include "provided.h"
#include "PersonProfile.h"
using namespace std;

class MemberDatabase {
public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
};

#endif /* MemberDatabase_h */
