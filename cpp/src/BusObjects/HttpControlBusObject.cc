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

using namespace qcc;
namespace ajn {
namespace services {
using namespace cpsConsts;

HttpControlBusObject::HttpControlBusObject(BusAttachment* bus, String const& servicePath,
                                           QStatus& status, HttpControl* httpControl) : BusObject(servicePath.c_str()),
    m_HttpControl(httpControl), TAG(TAG_HTTPCONTROL_BUSOBJECT)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    status = ER_OK;

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

void HttpControlBusObject::HttpControlGetUrl(const ajn::InterfaceDescription::Member* member, ajn::Message& msg)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (logger)
        logger->debug(TAG, "Execute was called");

    MsgArg url;
    QStatus status = m_HttpControl->getUrlForArg(url);
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not set Url");
        return;
    }

    status = MethodReply(msg, &url, 1);
    if (ER_OK != status) {
        if (logger)
            logger->warn(TAG, "Did not reply successfully");
    }
}

HttpControlBusObject::~HttpControlBusObject() {
}

} /* namespace services */
} /* namespace ajn */



