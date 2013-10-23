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

#ifndef LANGUAGESET_H_
#define LANGUAGESET_H_

#include "qcc/String.h"
#include <vector>

namespace ajn {
namespace services {

/**
 * Class used to define a LanguageSet
 */
class LanguageSet {

  public:

    /**
     * Constructor for LanguageSet class
     * @param languageSetName - name of LanguageSet
     */
    LanguageSet(qcc::String const& languageSetName);

    /**
     * Destructor for LanguageSet class
     */
    virtual ~LanguageSet();

    /**
     * Get the LanguageSetName
     * @return LanguageSetName
     */
    const qcc::String& getLanguageSetName() const;

    /**
     * Get the number of Languages defined
     * @return number of Languages
     */
    const size_t getNumLanguages() const;

    /**
     * Add a language to the LanguageSet
     * @param language - language to Add
     */
    void addLanguage(qcc::String const& language);

    /**
     *
     * Get the Languages defined in the LanguageSet
     * @return languages vector
     */
    const std::vector<qcc::String>& getLanguages() const;

  private:

    /**
     * Name of LanguageSet
     */
    qcc::String m_LanguageSetName;

    /**
     * vector to store Languages of LanguageSet
     */
    std::vector<qcc::String> m_Languages;
};

} /* namespace services */
} /* namespace ajn */
#endif /* LANGUAGESET_H_ */
