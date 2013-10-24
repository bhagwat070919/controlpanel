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

#ifndef CONTROLPANELCONTROLLEE_H_
#define CONTROLPANELCONTROLLEE_H_

#include <alljoyn/controlpanel/ControlPanel.h>
#include <alljoyn/controlpanel/NotificationAction.h>
#include <alljoyn/controlpanel/HttpControl.h>

namespace ajn {
namespace services {

/**
 * ControlPanelControllee Class.
 * Allows creation of a controllee to be controller by a controller
 * Made up of ControlPanels and/or NotificationWithActions and possibly
 * a HTTPControl
 */
class ControlPanelControllee {
  public:

    /**
     * Constructor of ControlPanelControllee
     * @param unitName - name of ControlPanelControllee Unit
     */
    ControlPanelControllee(qcc::String const& unitName);

    /**
     * Destructor of ControlPanelControllee
     */
    virtual ~ControlPanelControllee();

    /**
     * Get the UnitName of the ControlPanelControllee
     * @return unitName
     */
    const qcc::String& getUnitName() const;

    /**
     * Add a ControlPanel to the ControlPanelControllee
     * @param controlPanel
     * @return status - success/failure
     */
    QStatus addControlPanel(ControlPanel* controlPanel);

    /**
     * Get the ControlPanels of the Controllee
     * @return ControlPanels
     */
    const std::vector<ControlPanel*>& getControlPanels() const;

    /**
     * Add a NotificationAction to the ControlPanelControllee
     * @param notificationAction
     * @return status - success/failure
     */
    QStatus addNotificationAction(NotificationAction* notificationAction);

    /**
     * Get the NotificationActions of the ControlPanelControllee
     * @return the NotificationActions
     */
    const std::vector<NotificationAction*>& getNotificationActions() const;

    /**
     * Set the HTTPControl of the ControlPanelControllee
     * @param httpControl
     * @return status - success/failure
     */
    QStatus setHttpControl(HttpControl* httpControl);

    /**
     * Get the HttpControl of the ControlPanelControllee
     * @return HttpControl
     */
    const HttpControl* getHttpControl() const;
    /**
     * Register the busObjects of the ControlPanelControllee
     * @param bus - the bus to register the Objects with
     * @return status - success/failure
     */
    QStatus registerObjects(BusAttachment* bus);

    /**
     * UnRegister the busObjects of the ControlPanelControllee
     * @param bus - the bus to unregister the Objects with
     * @return status - success/failure
     */
    QStatus unregisterObjects(BusAttachment* bus);

  private:

    /**
     * The name of the Unit
     */
    qcc::String m_UnitName;

    /**
     * Vector of ControlPanels implemented by the Controllee
     */
    std::vector<ControlPanel*> m_ControlPanels;

    /**
     * Vector of NotificationActions implemented by the Controllee
     */
    std::vector<NotificationAction*> m_NotificationActions;

    /**
     * The HTTPControl of the Controllee
     */
    HttpControl* m_HttpControl;
};

} /* namespace services */
} /* namespace ajn */
#endif /* CONTROLPANELCONTROLLEE_H_ */
