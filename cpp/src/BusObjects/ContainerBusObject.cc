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

#include "ContainerBusObject.h"
#include "../ControlPanelConstants.h"
#include "alljoyn/controlpanel/ControlPanelService.h"

namespace ajn {
namespace services {
using namespace qcc;
using namespace cpsConsts;

ContainerBusObject::ContainerBusObject(BusAttachment* bus, String const& objectPath, uint16_t langIndx,
                                       QStatus& status, Widget* widget) :
    WidgetBusObject(objectPath, langIndx, TAG_CONTAINER_BUSOBJECT, status, widget)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (status != ER_OK) {
        if (logger)
            logger->debug(TAG, "Could not create the BusObject");
        return;
    }

    String interfaceName = widget->getIsSecured() ? AJ_SECURED_CONTAINER_INTERFACE : AJ_CONTAINER_INTERFACE;
    InterfaceDescription* intf = (InterfaceDescription*) bus->GetInterface(interfaceName.c_str());
    if (!intf) {
        do {
            CHECK_AND_BREAK(bus->CreateInterface(interfaceName.c_str(), intf, widget->getIsSecured()));
            CHECK_AND_BREAK(addDefaultInterfaceVariables(intf));
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
    if (logger)
        logger->debug(TAG, "Created ContainerBusObject successfully");
}

ContainerBusObject::~ContainerBusObject() {
}

} /* namespace services */
} /* namespace ajn */



