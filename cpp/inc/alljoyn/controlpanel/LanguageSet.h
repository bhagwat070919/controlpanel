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

class LanguageSet {

  public:
    LanguageSet(qcc::String const& languageSetName);

    virtual ~LanguageSet();

    void addLanguage(qcc::String const& language);

    const std::vector<qcc::String>& getLanguages() const;

    const qcc::String& getLanguageSetName() const;

    const size_t getNumLanguages() const;

  private:
    qcc::String m_LanguageSetName;

    std::vector<qcc::String> m_Languages;
};

} /* namespace services */
} /* namespace ajn */
#endif /* LANGUAGESET_H_ */
