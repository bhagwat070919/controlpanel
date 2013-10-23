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

#ifndef ACTION_H_
#define ACTION_H_

#include "alljoyn/controlpanel/Widget.h"

namespace ajn {
namespace services {

/**
 * Action Class. Used to display a Button.
 * This is an abstract class. The executeCallback function needs to be overridden.
 */
class Action : public Widget {
  public:

    /**
     * Constructor for Action class
     * @param name - name of Widget
     */
    Action(qcc::String const& name);

    /**
     * Destructor for Action Class
     */
    virtual ~Action();

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
     * Callback for when Action is executed.
     * Pure virtual function that needs to be implemented.
     * @return success/failure
     */
    virtual bool executeCallBack() = 0;
};
} //namespace services
} //namespace ajn

#endif /* ACTION_H_ */
