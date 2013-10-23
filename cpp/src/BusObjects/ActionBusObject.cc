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

#include "ActionBusObject.h"
#include "../ControlPanelConstants.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "alljoyn/controlpanel/Action.h"

using namespace qcc;
namespace ajn {
namespace services {
using namespace cpsConsts;

ActionBusObject::ActionBusObject(BusAttachment* bus, String const& servicePath, uint16_t langIndx,
                                 QStatus& status, Widget* widget) : WidgetBusObject(servicePath, langIndx, TAG_ACTION_BUSOBJECT, widget)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    status = ER_OK;

    String interfaceName = widget->getIsSecured() ? AJ_SECURED_ACTION_INTERFACE : AJ_ACTION_INTERFACE;
    InterfaceDescription* intf = (InterfaceDescription*) bus->GetInterface(interfaceName.c_str());
    if (!intf) {
        do {
            CHECK_AND_BREAK(bus->CreateInterface(interfaceName.c_str(), intf, widget->getIsSecured()));
            CHECK_AND_BREAK(addDefaultInterfaceVariables(intf));
            CHECK_AND_BREAK(intf->AddMethod(AJ_METHOD_EXECUTE.c_str(), AJPARAM_EMPTY.c_str(),
                                            AJPARAM_EMPTY.c_str(), AJPARAM_EMPTY.c_str()));
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
    m_SignalPropertyChanged = intf->GetMember(AJ_SIGNAL_PROPERTIES_CHANGED.c_str());
    const ajn::InterfaceDescription::Member* execMember = intf->GetMember(AJ_METHOD_EXECUTE.c_str());

    status = AddMethodHandler(execMember, static_cast<MessageReceiver::MethodHandler>(&ActionBusObject::ActionExecute));
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not register the SignalHandler");
        return;
    }
    if (logger)
        logger->debug(TAG, "Created ActionBusObject successfully");
}

void ActionBusObject::ActionExecute(const ajn::InterfaceDescription::Member* member, ajn::Message& msg)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (logger)
        logger->debug(TAG, "Execute was called");
    ((Action*)m_Widget)->executeCallBack();
}

ActionBusObject::~ActionBusObject() {
}

} /* namespace services */
} /* namespace ajn */



