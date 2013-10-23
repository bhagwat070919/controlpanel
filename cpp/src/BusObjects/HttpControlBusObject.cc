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

#include "HttpControlBusObject.h"
#include "../ControlPanelConstants.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "alljoyn/controlpanel/HttpControl.h"

namespace ajn {
namespace services {
using namespace qcc;
using namespace cpsConsts;

#define TAG TAG_HTTPCONTROL_BUSOBJECT
#define HTTP_INTERFACE_VERSION 1

HttpControlBusObject::HttpControlBusObject(BusAttachment* bus, String const& objectPath,
                                           QStatus& status, HttpControl* httpControl) :
    BusObject(objectPath.c_str()), m_HttpControl(httpControl)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (!httpControl) {
        if (logger)
            logger->warn(TAG, "HttpControl cannot be NULL");
        status = ER_BAD_ARG_4;
        return;
    }

    InterfaceDescription* intf = (InterfaceDescription*) bus->GetInterface(AJ_HTTPCONTROL_INTERFACE.c_str());
    if (!intf) {
        do {
            CHECK_AND_BREAK(bus->CreateInterface(AJ_HTTPCONTROL_INTERFACE.c_str(), intf, false));
            CHECK_AND_BREAK(intf->AddProperty(AJ_PROPERTY_VERSION.c_str(), AJPARAM_UINT16.c_str(), PROP_ACCESS_READ));
            CHECK_AND_BREAK(intf->AddMethod(AJ_METHOD_GETROOTURL.c_str(), AJPARAM_EMPTY.c_str(),
                                            AJPARAM_STR.c_str(), AJ_PROPERTY_URL.c_str()));
            intf->Activate();
        } while (0);
    }
    if (status != ER_OK) {
        if (logger)
            logger->debug(TAG, "Could not create interface");
        return;
    }

    status = AddInterface(*intf);
    if (status != ER_OK) {
        if (logger)
            logger->debug(TAG, "Could not add interface");
        return;
    }

    //Get the signal methods for future use
    const ajn::InterfaceDescription::Member* getRootUrlMember = intf->GetMember(AJ_METHOD_GETROOTURL.c_str());

    status = AddMethodHandler(getRootUrlMember, static_cast<MessageReceiver::MethodHandler>(&HttpControlBusObject::HttpControlGetUrl));
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not register the SignalHandler");
        return;
    }
    if (logger)
        logger->debug(TAG, "Created HttpControlBusObject successfully");
}

HttpControlBusObject::~HttpControlBusObject()
{
}

uint16_t HttpControlBusObject::getInterfaceVersion()
{
    return HTTP_INTERFACE_VERSION;
}

QStatus HttpControlBusObject::Get(const char* interfaceName, const char* propName, MsgArg& val)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (logger)
        logger->debug(TAG, "Get property was called - in HttpControlBusObject class:\n");

    if (0 == strcmp(AJ_PROPERTY_VERSION.c_str(), propName)) {
        return val.Set(AJPARAM_UINT16.c_str(), getInterfaceVersion());
    }

    return ER_BUS_NO_SUCH_PROPERTY;
}

QStatus HttpControlBusObject::Set(const char* interfaceName, const char* propName, MsgArg& val)
{
    return ER_ALLJOYN_ACCESS_PERMISSION_ERROR;
}

void HttpControlBusObject::HttpControlGetUrl(const ajn::InterfaceDescription::Member* member, ajn::Message& msg)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (logger)
        logger->debug(TAG, "Get Url was called");

    MsgArg url;
    QStatus status = m_HttpControl->fillUrlArg(url);
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not set Url");
        MethodReply(msg, AJ_ERROR_UNKNOWN.c_str(), AJ_ERROR_UNKNOWN_MESSAGE.c_str());
        return;
    }

    status = MethodReply(msg, &url, 1);
    if (ER_OK != status) {
        if (logger)
            logger->warn(TAG, "Did not reply successfully");
    }
}

} /* namespace services */
} /* namespace ajn */



