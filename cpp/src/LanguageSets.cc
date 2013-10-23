/******************************************************************************
 * Copyright 2013, Qualcomm Innovation Center, Inc.
 *
 *    All rights reserved.
 *    This file is licensed under the 3-clause BSD license in the NOTICE.txt
 *    file for this project. A copy of the 3-clause BSD license is found at:
 *
 *        http://opensource.org/licenses/BSD-3-Clause.
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the license is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the license for the specific language governing permissions and
 *    limitations under the license.
 ******************************************************************************/

#include "alljoyn/controlpanel/LanguageSets.h"

namespace ajn {
namespace services {
using namespace qcc;

std::map<String, LanguageSet> LanguageSets::languageSets;

LanguageSets::LanguageSets()
{
}

LanguageSets::~LanguageSets()
{
}

void LanguageSets::add(String const& languageSetName, LanguageSet const& languageSet)
{
    languageSets.insert(std::pair<String, LanguageSet>(languageSetName, languageSet));
}

LanguageSet* LanguageSets::get(String const& languageSetName)
{
    std::map<String, LanguageSet>::iterator it;
    if ((it = languageSets.find(languageSetName)) != languageSets.end())
        return &it->second;
    return 0;
}


} /* namespace services */
} /* namespace ajn */
