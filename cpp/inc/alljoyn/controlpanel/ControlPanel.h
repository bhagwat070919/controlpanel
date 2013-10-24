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

#ifndef CONTROLPANEL_H_
#define CONTROLPANEL_H_

#include <alljoyn/BusObject.h>
#include <alljoyn/controlpanel/Container.h>

namespace ajn {
namespace services {

/**
 * ControlPanel Class. Class used to create a ControlPanel
 * ControlPanels are made up of a LanguageSet and a RootContainer
 */
class ControlPanel {
  public:

    /**
     * Function used to create a ControlPanel
     * @param languageSet - languageSet of the ControlPanel
     * @return newly created ControlPanel instance
     */
    static ControlPanel* createControlPanel(LanguageSet* languageSet);

    /**
     * Destructor of ControlPanel
     */
    virtual ~ControlPanel();

    /**
     * Set the RootWidget of the ControlPanel
     * @param rootWidget - rootWidget of the ControlPanel
     * @return status - success/failure
     */
    QStatus setRootWidget(Container* rootWidget);

    /**
     * Get the RootWidget of the ControlPanel
     * @return rootWidget
     */
    const Container* getRootWidget() const;

    /**
     * Register the BusObjects for this Widget
     * @param bus - bus used to register the busObjects
     * @param unitName - the unitName of this ControlPanel
     * @return status - success/failure
     */
    QStatus registerObjects(BusAttachment* bus, qcc::String const& unitName);

    /**
     * Unregister the BusObjects for this Widget
     * @param bus - bus used to unregister the busObjects
     * @return status - success/failure
     */
    QStatus unregisterObjects(BusAttachment* bus);

    /**
     * Get the LanguageSet of the ControlPanel
     * @return
     */
    const LanguageSet& getLanguageSet() const;

  private:

    /**
     * Private Constructor for ControlPanel.
     * To construct instance of ControlPanel used createControlPanel
     * @param languageSet
     */
    ControlPanel(LanguageSet const& languageSet);

    /**
     * LanguageSet of this ControlPanel
     */
    LanguageSet const& m_LanguageSet;

    /**
     * RootWidget of this ControlPanel
     */
    Container* m_RootWidget;

    /**
     * The BusObject for this ControlPanel
     */
    BusObject* m_ControlPanelBusObject;
};

} /* namespace services */
} /* namespace ajn */
#endif /* CONTROLPANEL_H_ */
