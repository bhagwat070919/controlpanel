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

#include "PropertyStoreImpl.h"

using namespace ajn;

PropertyStoreImpl::PropertyStoreImpl(std::multimap<qcc::String, PropertyStoreProperty>& data)
{
    internalMultimap = data;
}

PropertyStoreImpl::~PropertyStoreImpl()
{
}

QStatus PropertyStoreImpl::ReadAll(const char* languageTag, Filter filter, MsgArg& all)
{
    QStatus status = ER_OK;
    if (filter == ANNOUNCE) {
        MsgArg* argsAnnounceData = new MsgArg[internalMultimap.size()];

        std::multimap<qcc::String, PropertyStoreProperty>::iterator search = internalMultimap.find("DefaultLanguage");

        qcc::String defaultLanguage;
        if (search != internalMultimap.end()) {
            char* temp;
            search->second.getKeyValue().Get("s", &temp);
            defaultLanguage.assign(temp);
        }

        int16_t announceArgCount = 0;
        std::multimap<qcc::String, PropertyStoreProperty>::const_iterator it;
        for (it = internalMultimap.begin(); it != internalMultimap.end(); ++it) {
            qcc::String key = it->first;
            PropertyStoreProperty property = it->second;
            if (!property.getIsAnnouncable())
                continue;

            // check that it is from the defaultLanguage or empty.
            if (!(property.getLanguage().empty() || property.getLanguage().compare(defaultLanguage)))
                continue;

            status = argsAnnounceData[announceArgCount].Set("{sv}", property.getKeyName().c_str(), new MsgArg(property.getKeyValue()));
            argsAnnounceData[announceArgCount].SetOwnershipFlags(MsgArg::OwnsArgs, true);
            announceArgCount++;
        }

        status = all.Set("a{sv}", announceArgCount, argsAnnounceData);
        all.SetOwnershipFlags(MsgArg::OwnsArgs, true);
    }   else if (filter == READ) {
        MsgArg* argsReadData = new MsgArg[internalMultimap.size()];
        int16_t readArgCount = 0;
        std::multimap<qcc::String, PropertyStoreProperty>::const_iterator it;
        for (it = internalMultimap.begin(); it != internalMultimap.end(); ++it) {
            qcc::String key = it->first;
            PropertyStoreProperty property = it->second;
            if (!property.getIsPublic())
                continue;

            // check that it is from the defaultLanguage or empty.
            if (!property.getLanguage().empty() && languageTag != 0)
                if (property.getLanguage().compare(languageTag) == 0)
                    continue;

            status = argsReadData[readArgCount].Set("{sv}", property.getKeyName().c_str(), new  MsgArg(property.getKeyValue()));
            argsReadData[readArgCount].SetOwnershipFlags(MsgArg::OwnsArgs, true);
            readArgCount++;
        }
        status = all.Set("a{sv}", readArgCount, argsReadData);
        all.SetOwnershipFlags(MsgArg::OwnsArgs, true);
    }   else {
        return ER_NOT_IMPLEMENTED;
    }
    return ER_OK;
}

