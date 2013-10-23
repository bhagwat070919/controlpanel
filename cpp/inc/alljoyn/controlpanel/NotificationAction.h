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

#include "alljoyn/controlpanel/RootWidget.h"
#include "alljoyn/BusObject.h"

namespace ajn {
namespace services {

class NotificationAction {
  public:

    static NotificationAction* createNotificationAction(LanguageSet* languageSet);

    virtual ~NotificationAction();

    QStatus setRootWidget(RootWidget* rootWidget);

    QStatus registerObjects(BusAttachment* bus, qcc::String const& unitName);

    QStatus unregisterObjects(BusAttachment* bus);

  private:

    NotificationAction(LanguageSet const& languageSet);

    LanguageSet const& m_LanguageSet;

    RootWidget* m_RootWidget;

    BusObject* m_NotificationActionBusObject;

    static qcc::String const& TAG;
};

} /* namespace services */
} /* namespace ajn */
#endif /* NOTIFICATIONACTION_H_ */


