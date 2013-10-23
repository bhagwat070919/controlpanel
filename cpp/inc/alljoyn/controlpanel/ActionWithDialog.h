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

namespace ajn {
namespace services {

/**
 * Action Class. Used to display a Button.
 * Upon pressing the button a Dialog is displayed on the Controller side
 */
class ActionWithDialog : public Widget {
  public:

    /**
     * Constructor for Action with Dialog class
     * @param name - name of Widget
     */
    ActionWithDialog(qcc::String name);

    /**
     * Destructor for Action with Dialog Class
     */
    virtual ~ActionWithDialog();

    /**
     * creates and returns the appropriate BusObject for this Widget
     * @param bus - the bus used to create the widget
     * @param objectPath - the objectPath of the widget
     * @param langIndx - the language Indx
     * @param status - the status indicating success or failure
     * @return a newly created WidgetBusObject
     */
    WidgetBusObject* createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                           uint16_t langIndx, QStatus& status);

    /**
     * add the ChildDialog for the Action With Dialog
     * @param childDialog - dialog to add as child
     * @return Status - success/failure
     */
    QStatus addChildDialog(Dialog* childDialog);

    /**
     * Register the BusObjects for this and children Widgets
     * @param bus - bus used to register the busObjects
     * @param languageSet - languageSet objects need to be registered for
     * @param objectPathPrefix - Prefix for the ObjectPath
     * @param objectPathSuffix - Suffix for the ObjectPath
     * @param isRoot - is this a Root Widget
     * @return Status - success/failure
     */
    virtual QStatus registerObjects(BusAttachment* bus, LanguageSet const& languageSet,
                                    qcc::String const& objectPathPrefix,
                                    qcc::String const& objectPathSuffix, bool isRoot = false);

    /**
     * Unregister the BusObjects for this and children Widgets
     * @param bus - the bus used to unregister the busObjects
     * @return status - success/failure
     */
    virtual QStatus unregisterObjects(BusAttachment* bus);

  private:

    Dialog* m_Dialog;
};
} //namespace services
} //namespace ajn

#endif /* ACTIONWITHDIALOG_H_ */
