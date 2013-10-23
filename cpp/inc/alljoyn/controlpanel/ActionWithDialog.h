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

#ifndef ACTIONWITHDIALOG_H_
#define ACTIONWITHDIALOG_H_

#include "alljoyn/controlpanel/Widget.h"
#include "alljoyn/controlpanel/Dialog.h"
#include <map>

namespace ajn {
namespace services {

class ActionWithDialog : public Widget {
  public:
    ActionWithDialog(qcc::String name);
    virtual ~ActionWithDialog();

    WidgetBusObject* createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                           uint16_t langIndx, QStatus& status);

    void executeCallBack();

    QStatus addChildDialog(Dialog* childElement);

    virtual QStatus registerObjects(BusAttachment* bus, LanguageSet const& languageSet,
                                    qcc::String const& objectPathPrefix, qcc::String const& objectPathSuffix, bool isRoot);

  private:

    Dialog* m_Dialog;
};
} //namespace services
} //namespace ajn

#endif /* ACTIONWITHDIALOG_H_ */
