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

#include "alljoyn/controlpanel/HttpControl.h"
#include "../ControlPanelConstants.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "../BusObjects/HttpControlBusObject.h"
#include "alljoyn/about/AboutServiceApi.h"

namespace ajn {
namespace services {
using namespace cpsConsts;

#define TAG TAG_HTTPCONTROL

HttpControl::HttpControl(qcc::String const& url) : m_Url(url),
    m_HttpControlBusObject(0)
{
}

HttpControl::~HttpControl()
{
}

const uint16_t HttpControl::getInterfaceVersion() const
{
    if (!m_HttpControlBusObject)
        return 1;
    return ((HttpControlBusObject*)m_HttpControlBusObject)->getInterfaceVersion();
}

QStatus HttpControl::registerObjects(BusAttachment* bus, qcc::String const& unitName)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();

    if (m_HttpControlBusObject) {
        if (logger)
            logger->warn(TAG, "Could not register Object. BusObject already exists");
        return ER_BUS_OBJ_ALREADY_EXISTS;
    }

    if (!bus) {
        if (logger)
            logger->warn(TAG, "Could not register Object. Bus is NULL");
        return ER_BAD_ARG_1;
    }

    if (!(bus->IsStarted() && bus->IsConnected())) {
        if (logger)
            logger->warn(TAG, "Could not register Object. Bus is not started or not connected");
        return ER_BAD_ARG_1;
    }

    AboutServiceApi* aboutService = AboutServiceApi::getInstance();
    if (!aboutService) {
        if (logger)
            logger->warn(TAG, "Could not retrieve AboutService. It has not been initialized");
        return ER_FAIL;
    }

    QStatus status = ER_OK;
    qcc::String objectPath = AJ_OBJECTPATH_PREFIX + unitName + AJ_HTTP_OBJECTPATH_SUFFIX;
    m_HttpControlBusObject = new HttpControlBusObject(bus, objectPath.c_str(), status, this);
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not create HttpControlBusObject");
        return status;
    }
    status = bus->RegisterBusObject(*m_HttpControlBusObject);
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not register HttpControlBusObject.");
        return status;
    }

    std::vector<qcc::String> interfaces;
    interfaces.push_back(AJ_HTTPCONTROL_INTERFACE);
    aboutService->AddObjectDescription(objectPath, interfaces);

    return status;
}

QStatus HttpControl::unregisterObjects(BusAttachment* bus)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();

    if (!m_HttpControlBusObject) {
        if (logger)
            logger->info(TAG, "Can not unregister. HttpControlBusObject does not exist");
        return ER_OK; //this does not need to fail
    }

    if (!bus) {
        if (logger)
            logger->warn(TAG, "Could not unregister Object. Bus is NULL");
        return ER_BAD_ARG_1;
    }

    bus->UnregisterBusObject(*m_HttpControlBusObject);
    delete m_HttpControlBusObject;
    m_HttpControlBusObject = 0;
    return ER_OK;
}

QStatus HttpControl::fillUrlArg(MsgArg& val)
{
    return val.Set(AJPARAM_STR.c_str(), m_Url.c_str());
}

} /* namespace services */
} /* namespace ajn */
