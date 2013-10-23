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

#include "alljoyn/controlpanel/ControlPanel.h"
#include "alljoyn/controlpanel/NotificationAction.h"
#include "alljoyn/controlpanel/HttpControl.h"

namespace ajn {
namespace services {

class ControlPanelControllee {
  public:
    ControlPanelControllee(qcc::String const& unitName);

    virtual ~ControlPanelControllee();

    void addControlPanel(ControlPanel* controlPanel);

    void addNotificationAction(NotificationAction* notificationAction);

    QStatus setHttpControl(HttpControl* httpControl);

    QStatus registerObjects(BusAttachment* bus);

    QStatus unregisterObjects(BusAttachment* bus);

  private:

    qcc::String const& TAG;

    qcc::String m_UnitName;

    std::vector<ControlPanel*> m_ControlPanels;

    std::vector<NotificationAction*> m_NotificationActions;

    HttpControl* m_HttpControl;
};

} /* namespace services */
} /* namespace ajn */
#endif /* CONTROLPANELCONTROLLEE_H_ */
