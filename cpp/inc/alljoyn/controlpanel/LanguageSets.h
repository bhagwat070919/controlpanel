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

#ifndef LANGUAGESETS_H_
#define LANGUAGESETS_H_

#include <alljoyn/controlpanel/LanguageSet.h>
#include <map>

namespace ajn {
namespace services {

/**
 * Class to store the LanguageSets defined
 */
class LanguageSets {
  public:

    /**
     * Constructor for LanguageSets
     */
    LanguageSets();

    /**
     * Destructor for LanguageSets
     */
    virtual ~LanguageSets();

    /**
     * Add a LanguageSet
     * @param languageSetName - name of LanguageSet
     * @param languageSet - languageSet
     */
    static void add(qcc::String const& languageSetName, LanguageSet const& languageSet);

    /**
     * Get a LanguageSet
     * @param languageSetName - the name of the languageSet to get
     * @return the languageSet requested or NULL if it does not exist
     */
    static LanguageSet* get(qcc::String const& languageSetName);

  private:

    /**
     * The LanguageSets map storing the LanguageSets defined
     */
    static std::map<qcc::String, LanguageSet> languageSets;
};

} /* namespace services */
} /* namespace ajn */
#endif /* LANGUAGESETS_H_ */
