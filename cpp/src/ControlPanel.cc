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

#define TAG TAG_CONTROLPANEL

ControlPanel* ControlPanel::createControlPanel(LanguageSet* languageSet)
{
    if (!languageSet) {
        GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
        if (logger)
            logger->warn(TAG, "Could not create ControlPanel. LanguageSet is NULL");
        return NULL;
    }
    return new ControlPanel(*languageSet);
}

ControlPanel::ControlPanel(LanguageSet const& languageSet) :
    m_LanguageSet(languageSet), m_RootWidget(0),
    m_ControlPanelBusObject(0)
{

}

ControlPanel::~ControlPanel() {
}

QStatus ControlPanel::setRootWidget(Container* rootWidget)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();

    if (!rootWidget) {
        if (logger)
            logger->warn(TAG, "Could not add a NULL rootWidget");
        return ER_BAD_ARG_1;
    }

    if (m_RootWidget) {
        if (logger)
            logger->warn(TAG, "Could not set the RootWidget. RootWidget already set");
        return ER_BUS_PROPERTY_ALREADY_EXISTS;
    }

    m_RootWidget = rootWidget;
    return ER_OK;
}

const Container* ControlPanel::getRootWidget() const
{
    return m_RootWidget;
}

QStatus ControlPanel::registerObjects(BusAttachment* bus, qcc::String const& unitName)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();

    if (m_ControlPanelBusObject) {
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
        return ER_BUS_TRANSPORT_NOT_STARTED;
    }

    QStatus status = ER_OK;
    qcc::String objectPath = AJ_OBJECTPATH_PREFIX + unitName + "/" + m_RootWidget->getWidgetName();
    m_ControlPanelBusObject = new ControlPanelBusObject(bus, objectPath.c_str(), status);
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not create ControlPanelBusObject");
        return status;
    }
    status = bus->RegisterBusObject(*m_ControlPanelBusObject);
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not register ControlPanelBusObject.");
        return status;
    }

    std::vector<qcc::String> interfaces;
    interfaces.push_back(AJ_CONTROLPANEL_INTERFACE);
    aboutService->AddObjectDescription(objectPath, interfaces);

    status = m_RootWidget->registerObjects(bus, m_LanguageSet, objectPath + "/", "", true);
    return status;
}

QStatus ControlPanel::unregisterObjects(BusAttachment* bus)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    QStatus status = ER_OK;
    if (!m_ControlPanelBusObject && !m_RootWidget) {
        if (logger)
            logger->info(TAG, "Can not unregister. BusObjects do not exist");
        return status; //this does not need to fail
    }

    if (!bus) {
        if (logger)
            logger->warn(TAG, "Could not unregister Object. Bus is NULL");
        return ER_BAD_ARG_1;
    }

    if (m_ControlPanelBusObject) {
        bus->UnregisterBusObject(*m_ControlPanelBusObject);

        delete m_ControlPanelBusObject;
        m_ControlPanelBusObject = 0;
    }

    if (m_RootWidget) {
        QStatus status = m_RootWidget->unregisterObjects(bus);
        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not unregister RootContainer.");
        }
    }
    return status;
}

const LanguageSet && ControlPanel::getLanguageSet() const
{
    return m_LanguageSet;
}

} /* namespace services */
} /* namespace ajn */
