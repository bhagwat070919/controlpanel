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

#include <alljoyn/controlpanel/ActionWithDialog.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include "../BusObjects/ActionBusObject.h"
#include "../ControlPanelConstants.h"

namespace ajn {
namespace services {
using namespace cpsConsts;

ActionWithDialog::ActionWithDialog(qcc::String const& name) : Widget(name, TAG_ACTION_WIDGET), m_Dialog(0)
{
}

ActionWithDialog::~ActionWithDialog()
{
}

WidgetBusObject* ActionWithDialog::createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                                         uint16_t langIndx, QStatus& status)
{
    return new ActionBusObject(bus, objectPath, langIndx, status, this);
}

QStatus ActionWithDialog::addChildDialog(Dialog* childDialog)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (!childDialog) {
        if (logger)
            logger->warn(TAG, "Cannot add a childDialog that is NULL");
        return ER_BAD_ARG_1;
    }

    m_Dialog = childDialog;

    if (logger)
        logger->debug(TAG, "Adding childDialog named: " + childDialog->getWidgetName());
    return ER_OK;
}

QStatus ActionWithDialog::registerObjects(BusAttachment* bus, LanguageSet const& languageSet,
                                          qcc::String const& objectPathPrefix, qcc::String const& objectPathSuffix, bool isRoot)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();

    QStatus status = Widget::registerObjects(bus, languageSet, objectPathPrefix, objectPathSuffix, isRoot);
    if (status != ER_OK)
        return status;

    qcc::String newObjectPathSuffix = isRoot ? objectPathSuffix : objectPathSuffix + "/" + m_Name;

    if (!m_Dialog) {
        if (logger)
            logger->warn(TAG, "Could not register. ActionWithDialog is missing the child Dialog");
        return ER_FAIL;
    }

    status = m_Dialog->registerObjects(bus, languageSet, objectPathPrefix, newObjectPathSuffix);
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not register childDialog objects");
        return status;
    }
    return status;
}

QStatus ActionWithDialog::unregisterObjects(BusAttachment* bus)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    QStatus returnStatus = ER_OK;

    QStatus status = Widget::unregisterObjects(bus);
    if (status != ER_OK) {
        if (logger)
            logger->warn(TAG, "Could not unregister BusObjects");
        returnStatus = status;
    }

    if (m_Dialog) {
        status = m_Dialog->unregisterObjects(bus);
        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not unregister Objects for the childDialog");
            returnStatus = status;
        }
    }
    return returnStatus;
}

} /* namespace services */
} /* namespace ajn */
