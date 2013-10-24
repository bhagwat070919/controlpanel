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

#ifndef NOTIFICATIONACTION_H_
#define NOTIFICATIONACTION_H_

#include <alljoyn/controlpanel/RootWidget.h>
#include <alljoyn/BusObject.h>

namespace ajn {
namespace services {

/**
 * NotificationAction class.
 */
class NotificationAction {
  public:

    /**
     * Function used to create a NotificationAction
     * @param languageSet - languageSet of NotificationAction
     * @return A newly created NotificationAction object or NULL
     */
    static NotificationAction* createNotificationAction(LanguageSet* languageSet);

    /**
     * Destructor of NotificationAction class
     */
    virtual ~NotificationAction();

    /**
     * Set the rootWidget of the NotificationAction
     * @param rootWidget - widget to set as RootWidget
     * @return status - success/failure
     */
    QStatus setRootWidget(RootWidget* rootWidget);

    /**
     * Register the BusObjects of the Notification Action
     * @param bus - bus to register the objects on
     * @param unitName - unitName to use in ObjectPath
     * @return status - success/failure
     */
    QStatus registerObjects(BusAttachment* bus, qcc::String const& unitName);

    /**
     * Unregister the BusObjects of the NotificationAction class
     * @param bus - bus used to unregister the objects
     * @return status - success/failure
     */
    QStatus unregisterObjects(BusAttachment* bus);

  private:

    /**
     * Private constructor of NotificationAction class
     * @param languageSet - languageSet of NotificationAction
     */
    NotificationAction(LanguageSet const& languageSet);

    /**
     * The LanguageSet of the NotificationAction
     */
    LanguageSet const& m_LanguageSet;

    /**
     * The RootWidget of the NotificationAction
     */
    RootWidget* m_RootWidget;

    /**
     * The BusObject of the NotificationAction
     */
    BusObject* m_NotificationActionBusObject;
};

} /* namespace services */
} /* namespace ajn */
#endif /* NOTIFICATIONACTION_H_ */


