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
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "alljoyn/controlpanel/Dialog.h"

using namespace qcc;
namespace ajn {
namespace services {
using namespace cpsConsts;

DialogBusObject::DialogBusObject(BusAttachment* bus, String const& servicePath, uint16_t langIndx,
		QStatus& status, Widget* widget) : WidgetBusObject(servicePath, langIndx, TAG_DIALOG_BUSOBJECT, widget)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
	status = ER_OK;

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

void DialogBusObject::DialogExecute(const ajn::InterfaceDescription::Member* member, ajn::Message& msg)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();

    if (member->name.compare(AJ_METHOD_ACTION1) == 0) {
        if (logger)
            logger->debug(TAG, "Execute Action was called");
        return ((Dialog*)m_Widget)->executeAction1CallBack();
    }
    else if (member->name.compare(AJ_METHOD_ACTION2) == 0) {
        if (logger)
            logger->debug(TAG, "Execute Action was called");
        return ((Dialog*)m_Widget)->executeAction2CallBack();
    }
    else if (member->name.compare(AJ_METHOD_ACTION3) == 0) {
        if (logger)
            logger->debug(TAG, "Execute Action was called");
        return ((Dialog*)m_Widget)->executeAction3CallBack();
    }
    if (logger)
        logger->warn(TAG, "Unknown Execute Action was called");
}

DialogBusObject::~DialogBusObject() {
}

} /* namespace services */
} /* namespace ajn */



