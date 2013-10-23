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

#include "alljoyn/controlpanel/LanguageSet.h"

namespace ajn {
namespace services {

LanguageSet::LanguageSet(qcc::String const& languageSetName) :
     m_LanguageSetName(languageSetName)
{
}

LanguageSet::~LanguageSet()
{
}

void LanguageSet::addLanguage(qcc::String const& language)
{
    m_Languages.push_back(language);
}

const std::vector<qcc::String>& LanguageSet::getLanguages() const
{
	return m_Languages;
}

const qcc::String& LanguageSet::getLanguageSetName() const
{
	return m_LanguageSetName;
}

const size_t LanguageSet::getNumLanguages() const
{
	return m_Languages.size();
}

} /* namespace services */
} /* namespace ajn */
