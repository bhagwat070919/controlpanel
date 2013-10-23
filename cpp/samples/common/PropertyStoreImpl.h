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

#ifndef PROPERTYSTOREIMPL_H_
#define PROPERTYSTOREIMPL_H_

#include "alljoyn/about/AboutService.h"
#include "alljoyn/about/PropertyStore.h"
#include "PropertyStoreProperty.h"

/**
 * A sample implementation of an ajn::PropertyStore
 */
class PropertyStoreImpl : public ajn::services::PropertyStore {

  public:

    /**
     * Constructor of PropertyStoreImpl
     * @param data
     */
    PropertyStoreImpl(std::multimap<qcc::String, PropertyStoreProperty>& data);

    /**
     * Destructor of PropertyStoreImpl
     */
    virtual ~PropertyStoreImpl();

    /**
     * Based on Filter decides how to fill the MsgArg argument all
     * @param languageTag language of properties to fill
     * @param filter READ WRITE or ANNOUNCE
     * @param all MsgArg to fill
     * @return status
     */
    virtual QStatus ReadAll(const char* languageTag, Filter filter, ajn::MsgArg& all);

  private:

    /**
     * private map of data
     */
    std::multimap<qcc::String, PropertyStoreProperty> internalMultimap;
};

#endif

