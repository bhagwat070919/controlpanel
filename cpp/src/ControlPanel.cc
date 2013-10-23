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

#include "alljoyn/controlpanel/ControlPanel.h"
#include "ControlPanelConstants.h"
#include "alljoyn/about/AboutServiceApi.h"
#include "BusObjects/ControlPanelBusObject.h"
#include "BusObjects/NotificationActionBusObject.h"
#include "alljoyn/controlpanel/ControlPanelService.h"

namespace ajn {
namespace services {
using namespace cpsConsts;

ControlPanel::ControlPanel(LanguageSet const& languageSet) :
    m_LanguageSet(languageSet), m_RootContainer(0),
    m_ControlPanelBusObject(0),     m_NotificationActionBusObject(0),
    TAG(TAG_CONTROLPANEL)
{

}

ControlPanel::~ControlPanel() {
}

QStatus ControlPanel::setRootContainer(Container* rootContainer)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();

    if (!rootContainer) {
        if (logger)
            logger->warn(TAG, "Could not add a NULL rootContainer");
        return ER_BAD_ARG_1;
    }

    if (m_RootContainer) {
        if (logger)
            logger->warn(TAG, "Could not set RootContainer. Rootcontainer already set");
        return ER_BUS_PROPERTY_ALREADY_EXISTS;
    }

    m_RootContainer = rootContainer;
    return ER_OK;
}

QStatus ControlPanel::registerObjects(BusAttachment* bus, qcc::String const& unitName)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();

    if (m_ControlPanelBusObject) {
        if (logger)
            logger->warn(TAG, "Could not register Object. BusObject already exists");
        return ER_BUS_OBJ_ALREADY_EXISTS;
    }

    AboutServiceApi* aboutService = AboutServiceApi::getInstance();
    if (!aboutService) {
        if (logger)
            logger->warn(TAG, "Could not retrieve AboutService. It has not been initialized");
        return ER_BUS_TRANSPORT_NOT_STARTED;
    }

    QStatus status = ER_OK;
    qcc::String objectPath = AJ_OBJECTPATH_PREFIX + unitName + "/" + m_RootContainer->getWidgetName();
    m_ControlPanelBusObject = new ControlPanelBusObject(bus, objectPath.c_str(), status);
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not create ControlPanelBusObject");
        return status;
    }
    status = bus->RegisterBusObject(*m_ControlPanelBusObject);
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not register ControlPanelBysObject.");
        return status;
    }

    std::vector<qcc::String> interfaces;
    interfaces.push_back(AJ_CONTROLPANEL_INTERFACE);
    aboutService->AddObjectDescription(objectPath, interfaces);

    if (m_RootContainer->getIsDismissable()) {
        m_NotificationActionBusObject = new NotificationActionBusObject(bus, objectPath.c_str(), status);

        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not create NotificationActionBusObject");
            return status;
        }
        status = bus->RegisterBusObject(*m_ControlPanelBusObject);
        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not register ControlPanelBysObject.");
            return status;
        }
    }
    status = m_RootContainer->registerObjects(bus, m_LanguageSet, objectPath + "/", "", true);
    return status;
}

} /* namespace services */
} /* namespace ajn */
