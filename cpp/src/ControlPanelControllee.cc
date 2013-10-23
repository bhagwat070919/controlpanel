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

#include "alljoyn/controlpanel/ControlPanelControllee.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "ControlPanelConstants.h"

namespace ajn {
namespace services {
using namespace cpsConsts;

ControlPanelControllee::ControlPanelControllee(qcc::String const& unitName) :
		TAG(TAG_CONTROLPANELCONTROLLEE), m_UnitName(unitName)
{
}

ControlPanelControllee::~ControlPanelControllee()
{

}


void ControlPanelControllee::addControlPanel(ControlPanel* controlPanel)
{
	m_ControlPanels.push_back(controlPanel);
}

void ControlPanelControllee::addNotificationAction(NotificationAction* notificationAction)
{
	m_NotificationActions.push_back(notificationAction);
}

QStatus ControlPanelControllee::registerObjects(BusAttachment* bus)
{
	GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
	QStatus status;
    for (size_t indx = 0; indx < m_ControlPanels.size(); indx++) {
        status = m_ControlPanels[indx]->registerObjects(bus, m_UnitName);
        if (status != ER_OK) {
        	if (logger)
        	    logger->warn(TAG, "Could not register Objects for the ControlPanels");
        	return status;
        }
    }

    for (size_t indx = 0; indx < m_NotificationActions.size(); indx++) {
        status = m_NotificationActions[indx]->registerObjects(bus, m_UnitName);
        if (status != ER_OK) {
        	if (logger)
        	    logger->warn(TAG, "Could not register Objects for the ControlPanels");
        	return status;
        }
    }
    return status;
}
} /* namespace services */
} /* namespace ajn */
