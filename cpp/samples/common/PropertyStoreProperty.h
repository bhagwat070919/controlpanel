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

#ifndef PROPERTYSTOREPROP_H_
#define PROPERTYSTOREPROP_H_

#include "qcc/String.h"
#include "alljoyn/MsgArg.h"

/**
 * Property of Property Store Impl class
 */
class PropertyStoreProperty {

  public:

    /**
     * Constructor for PropertyStoreProperty
     * @param keyName
     */
    PropertyStoreProperty(qcc::String keyName);

    /**
     * Constructor for PropertyStoreProperty
     * @param keyName
     * @param value
     */
    PropertyStoreProperty(qcc::String keyName, ajn::MsgArg value);

    /**
     * Constructor for PropertyStoreProperty
     * @param keyName
     * @param value
     * @param isPublic
     * @param isWritable
     * @param isAnnouncable
     */
    PropertyStoreProperty(qcc::String keyName, ajn::MsgArg value, bool isPublic, bool isWritable, bool isAnnouncable);

    /**
     * Destructor for PropertyStoreProperty
     */
    virtual ~PropertyStoreProperty();

    /**
     * Set the flags for the property
     * @param isPublic
     * @param isWritable
     * @param isAnnouncable
     */
    void setFlags(bool isPublic, bool isWritable, bool isAnnouncable);

    /**
     * Set the language of the property
     * @param language
     */
    void setLanguage(qcc::String language);

    /**
     * Get the KeyName of the property
     * @return keyname
     */
    qcc::String& getKeyName();

    /**
     * Get the Value of the Property
     * @return value
     */
    const ajn::MsgArg& getKeyValue();

    /**
     * Get the Language of the Property
     * @return Language
     */
    qcc::String& getLanguage();

    /**
     * Get the isPublic boolean of the property
     * @return isPublic
     */
    bool getIsPublic();

    /**
     * Get the isWritable boolean of the Property
     * @return isWritable
     */
    bool getIsWritable();

    /**
     * Get the isAnnounceable boolean of the Property
     * @return isAnnounceable
     */
    bool getIsAnnouncable();

    /**
     * Set the isPublic boolean of the Property
     * @param value
     */
    void setIsPublic(bool value);

    /**
     * set the IsWritable boolean of the Property
     * @param value
     */
    void setIsWritable(bool value);

    /**
     * set the isAnnounce of the Property
     * @param value
     */
    void setIsAnnouncable(bool value);

  private:

    /**
     * private member keyName
     */
    qcc::String m_Keyname;

    /**
     * private member value
     */
    ajn::MsgArg m_Value;

    /**
     * private member isPublic
     */
    bool m_Public;

    /**
     * private member isWritable
     */
    bool m_Writable;

    /**
     * private member isAnnounceable
     */
    bool m_Announcable;

    /**
     * private member language
     */
    qcc::String m_Language;
};

#endif /* PROPERTYSTOREPROP */
