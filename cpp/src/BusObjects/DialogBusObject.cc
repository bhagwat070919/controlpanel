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

#include "DialogBusObject.h"
#include "../ControlPanelConstants.h"
#include <alljoyn/controlpanel/ControlPanelService.h>
#include <alljoyn/controlpanel/Dialog.h>

namespace ajn {
namespace services {
using namespace qcc;
using namespace cpsConsts;

DialogBusObject::DialogBusObject(BusAttachment* bus, String const& objectPath, uint16_t langIndx,
                                 QStatus& status, Widget* widget) :
    WidgetBusObject(objectPath, langIndx, TAG_DIALOG_BUSOBJECT, status, widget)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not create the BusObject");
        return;
    }

    String interfaceName = widget->getIsSecured() ? AJ_SECURED_DIALOG_INTERFACE : AJ_DIALOG_INTERFACE;
    InterfaceDescription* intf = (InterfaceDescription*) bus->GetInterface(interfaceName.c_str());
    if (!intf) {
        do {
            CHECK_AND_BREAK(bus->CreateInterface(interfaceName.c_str(), intf, widget->getIsSecured()));
            CHECK_AND_BREAK(addDefaultInterfaceVariables(intf));
            CHECK_AND_BREAK(intf->AddProperty(AJ_PROPERTY_MESSAGE.c_str(), AJPARAM_STR.c_str(), PROP_ACCESS_READ));
            CHECK_AND_BREAK(intf->AddProperty(AJ_PROPERTY_NUMACTIONS.c_str(), AJPARAM_UINT16.c_str(), PROP_ACCESS_READ));
            CHECK_AND_BREAK(intf->AddMethod(AJ_METHOD_ACTION1.c_str(), AJPARAM_EMPTY.c_str(),
                                            AJPARAM_EMPTY.c_str(), AJPARAM_EMPTY.c_str()));
            CHECK_AND_BREAK(intf->AddMethod(AJ_METHOD_ACTION2.c_str(), AJPARAM_EMPTY.c_str(),
                                            AJPARAM_EMPTY.c_str(), AJPARAM_EMPTY.c_str()));
            CHECK_AND_BREAK(intf->AddMethod(AJ_METHOD_ACTION3.c_str(), AJPARAM_EMPTY.c_str(),
                                            AJPARAM_EMPTY.c_str(), AJPARAM_EMPTY.c_str()));

            intf->Activate();
        } while (0);
    }
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not create interface");
        return;
    }

    status = AddInterface(*intf);
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not add interface");
        return;
    }

    //Get the signal methods for future use
    m_SignalPropertyChanged = intf->GetMember(AJ_SIGNAL_PROPERTIES_CHANGED.c_str());

    const ajn::InterfaceDescription::Member* execMember1 = intf->GetMember(AJ_METHOD_ACTION1.c_str());
    const ajn::InterfaceDescription::Member* execMember2 = intf->GetMember(AJ_METHOD_ACTION2.c_str());
    const ajn::InterfaceDescription::Member* execMember3 = intf->GetMember(AJ_METHOD_ACTION3.c_str());

    status = AddMethodHandler(execMember1, static_cast<MessageReceiver::MethodHandler>(&DialogBusObject::DialogExecute));
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not register the MethodHandler");
        return;
    }

    status = AddMethodHandler(execMember2, static_cast<MessageReceiver::MethodHandler>(&DialogBusObject::DialogExecute));
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not register the MethodHandler");
        return;
    }

    status = AddMethodHandler(execMember3, static_cast<MessageReceiver::MethodHandler>(&DialogBusObject::DialogExecute));
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not register the MethodHandler");
        return;
    }

    if (logger)
        logger->debug(TAG, "Created DialogBusObject successfully");
}

DialogBusObject::~DialogBusObject()
{
}

QStatus DialogBusObject::Get(const char* interfaceName, const char* propName, MsgArg& val)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (logger)
        logger->debug(TAG, "Get property was called - in DialogBusObject class:\n");

    if (0 == strcmp(AJ_PROPERTY_NUMACTIONS.c_str(), propName)) {
        return ((Dialog*)m_Widget)->fillNumActionArg(val, languageIndx);
    }

    if (0 == strcmp(AJ_PROPERTY_MESSAGE.c_str(), propName)) {
        return ((Dialog*)m_Widget)->fillMessageArg(val, languageIndx);
    }

    return WidgetBusObject::Get(interfaceName, propName, val);
}

void DialogBusObject::DialogExecute(const ajn::InterfaceDescription::Member* member, ajn::Message& msg)
{
    QStatus status = ER_OK;
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (logger)
        logger->debug(TAG, "Execute was called");

    if (member->name.compare(AJ_METHOD_ACTION1) == 0 &&
        ((Dialog*)m_Widget)->executeAction1CallBack()) {
        MsgArg replyArg;
        status = MethodReply(msg, &replyArg, 0);
        if (logger)
            logger->info(TAG, "Execute Action 1 completed successfully");
    } else if (member->name.compare(AJ_METHOD_ACTION2) == 0 &&
               ((Dialog*)m_Widget)->executeAction2CallBack()) {
        MsgArg replyArg;
        status = MethodReply(msg, &replyArg, 0);
        if (logger)
            logger->info(TAG, "Execute Action 2 completed successfully");
    } else if (member->name.compare(AJ_METHOD_ACTION3) == 0 &&
               ((Dialog*)m_Widget)->executeAction3CallBack()) {
        MsgArg replyArg;
        status = MethodReply(msg, &replyArg, 0);
        if (logger)
            logger->info(TAG, "Execute Action 3 completed successfully");
    } else {
        if (logger)
            logger->warn(TAG, "Unknown Execute Action was called, or action did not complete successfully");
        status = MethodReply(msg, AJ_ERROR_UNKNOWN.c_str(), AJ_ERROR_UNKNOWN_MESSAGE.c_str());
    }

    if (ER_OK != status) {
        if (logger)
            logger->warn(TAG, "Did not reply successfully");
    }
}

} /* namespace services */
} /* namespace ajn */



