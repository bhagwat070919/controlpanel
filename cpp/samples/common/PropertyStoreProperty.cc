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

#include "PropertyStoreProperty.h"

PropertyStoreProperty::PropertyStoreProperty(qcc::String keyName) :
    m_Keyname(keyName), m_Public(true), m_Writable(false), m_Announcable(true), m_Language("")
{
}

PropertyStoreProperty::PropertyStoreProperty(qcc::String keyName, ajn::MsgArg value) :
    m_Keyname(keyName), m_Value(value), m_Public(true), m_Writable(false), m_Announcable(true),
    m_Language("")
{
}

PropertyStoreProperty::PropertyStoreProperty(qcc::String keyName, ajn::MsgArg value,
                                             bool isPublic, bool isWritable, bool isAnnouncable) : m_Keyname(keyName),
    m_Value(value), m_Public(isPublic), m_Writable(isWritable),
    m_Announcable(isAnnouncable), m_Language("")
{
}

PropertyStoreProperty::~PropertyStoreProperty()
{

}

void PropertyStoreProperty::setFlags(bool isPublic, bool isWritable, bool isAnnouncable)
{
    m_Public = isPublic;
    m_Writable = isWritable;
    m_Announcable = isAnnouncable;
}

void PropertyStoreProperty::setLanguage(qcc::String language)
{
    m_Language = language;
}

qcc::String& PropertyStoreProperty::getKeyName() {
    return m_Keyname;
}

const ajn::MsgArg& PropertyStoreProperty::getKeyValue() {
    return m_Value;
}

qcc::String& PropertyStoreProperty::getLanguage() {
    return m_Language;
}

bool PropertyStoreProperty::getIsPublic() {
    return m_Public;
}

bool PropertyStoreProperty::getIsWritable() {
    return m_Writable;
}

bool PropertyStoreProperty::getIsAnnouncable() {
    return m_Announcable;
}

void PropertyStoreProperty::setIsPublic(bool value) {
    m_Public = value;
}

void PropertyStoreProperty::setIsWritable(bool value) {
    m_Writable = value;
}

void PropertyStoreProperty::setIsAnnouncable(bool value) {
    m_Announcable = value;
}
