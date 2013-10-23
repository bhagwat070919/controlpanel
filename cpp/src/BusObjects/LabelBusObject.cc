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

#include "LabelBusObject.h"
#include "../ControlPanelConstants.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "alljoyn/controlpanel/Label.h"

namespace ajn {
namespace services {
using namespace qcc;
using namespace cpsConsts;

LabelBusObject::LabelBusObject(BusAttachment* bus, String const& objectPath, uint16_t langIndx,
                               QStatus& status, Widget* widget) : WidgetBusObject(objectPath, langIndx,
                                                                                  TAG_LABEL_BUSOBJECT, status, widget)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (status != ER_OK) {
        if (logger)
            logger->debug(TAG, "Could not create the BusObject");
        return;
    }

    InterfaceDescription* intf = (InterfaceDescription*) bus->GetInterface(AJ_LABEL_INTERFACE.c_str());
    if (!intf) {
        do {
            CHECK_AND_BREAK(bus->CreateInterface(AJ_LABEL_INTERFACE.c_str(), intf));
            CHECK_AND_BREAK(addDefaultInterfaceVariables(intf));
            CHECK_AND_BREAK(intf->AddProperty(AJ_PROPERTY_LABEL.c_str(), AJPARAM_STR.c_str(), PROP_ACCESS_READ));
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
        logger->debug(TAG, "Created LabelBusObject successfully");
}

LabelBusObject::~LabelBusObject() {
}

QStatus LabelBusObject::Get(const char* interfaceName, const char* propName, MsgArg& val)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (logger)
        logger->debug(TAG, "Get property was called - in LabelBusObject class:\n");

    if (0 == strcmp(AJ_PROPERTY_LABEL.c_str(), propName)) {
        return ((Label*)m_Widget)->fillLabelArg(val, languageIndx);
    }

    return WidgetBusObject::Get(interfaceName, propName, val);
}
} /* namespace services */
} /* namespace ajn */




