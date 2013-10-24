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

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <alljoyn/controlpanel/RootWidget.h>

namespace ajn {
namespace services {

/**
 * Container class. Used to represent a container widget.
 * Container widgets container children widgets and group them together
 */
class Container : public RootWidget {
  public:

    /**
     * Constructor for container Class
     * @param name - name of Widget
     */
    Container(qcc::String const& name);

    /**
     * Destructor for Container Class
     */
    virtual ~Container();

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
     * Register the BusObjects for this Widget
     * @param bus - the bus used to register the busObjects
     * @param m_LanguageSet -  the languageSet to register the busObjects for
     * @param objectPathPrefix - the objectPathPrefix of the busObject
     * @param objectPathSuffix - the objectPathSuffix of the busObject
     * @param isRoot - is this a rootWidget
     * @return status - success/failure
     */
    QStatus registerObjects(BusAttachment* bus, LanguageSet const& m_LanguageSet,
                            qcc::String const& objectPathPrefix, qcc::String const& objectPathSuffix, bool isRoot = false);

    /**
     * Unregister the BusObjects for this widget
     * @param bus
     * @return status - success/failure
     */
    QStatus unregisterObjects(BusAttachment* bus);

    /**
     * add a Child Widget to the Container
     * @param childWidget - Widget to add
     * @return status - success/failure
     */
    QStatus addChildWidget(Widget* childWidget);

    /**
     * Get the ChildWidget Vector
     * @return children widgets
     */
    const std::vector<Widget*>& getChildWidgets() const;

    /**
     * Get IsDismissable
     * @return isDismissable
     */
    bool getIsDismissable() const;

    /**
     * Set IsDismissable
     * @param isDismissable
     */
    void setIsDismissable(bool isDismissable);

  private:

    /**
     * Children Widgets of the Container
     */
    std::vector<Widget*> m_ChildWidgets;

    /**
     * Is this Container dismissable (in a Notification with Action)
     */
    bool m_IsDismissable;

};
} //namespace services
} //namespace ajn

#endif /* CONTAINER_H_ */
