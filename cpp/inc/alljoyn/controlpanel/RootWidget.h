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

#ifndef ROOTWIDGET_H_
#define ROOTWIDGET_H_

#include <alljoyn/controlpanel/Widget.h>

namespace ajn {
namespace services {

/**
 * RootWidget class. Used as base for widgets that function as a
 * rootContainer or rootDialog
 */
class RootWidget : public Widget {
  public:

    /**
     * Constructor for RootWidget
     * @param name - name of Widget
     * @param tag - Tag for logging
     */
    RootWidget(qcc::String const& name, qcc::String const& tag);

    /**
     * Destructor of RootWidget
     */
    virtual ~RootWidget();

    /**
     * Send a Signal to Dismiss the widget
     * @return stats - success/failure
     */
    QStatus SendDismissSignal();

    /**
     * Set the BusObject if RootWidget is a NotificationAction
     * @param notificationActionBusObject - the busObject to store
     * @return status - success/failure
     */
    QStatus setNotificationActionBusObject(BusObject* notificationActionBusObject);

    /**
     * Unregister the BusObjects
     * @param bus - bus used to unregister
     * @return status - success/failure
     */
    virtual QStatus unregisterObjects(BusAttachment* bus);

  protected:

    /**
     * The BusObject if this Widget is a NotificationAction
     */
    BusObject* m_NotificationActionBusObject;
};
} //namespace services
} //namespace ajn

#endif /* ROOTWIDGET_H_ */
