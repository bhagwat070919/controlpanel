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

#include "alljoyn/controlpanel/Widget.h"

namespace ajn {
namespace services {

class RootWidget : public Widget {
  public:

    RootWidget(qcc::String name, qcc::String tag);
    virtual ~RootWidget();

    QStatus SendDismissSignal();

    QStatus setNotificationActionBusObject(BusObject* notificationActionBusObject);

  protected:

    BusObject* m_NotificationActionBusObject;
};
} //namespace services
} //namespace ajn

#endif /* ROOTWIDGET_H_ */
