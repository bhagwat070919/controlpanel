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

#include "alljoyn/controlpanel/Container.h"
#include "alljoyn/BusObject.h"

namespace ajn {
namespace services {

class ControlPanel {
  public:

    static ControlPanel* createControlPanel(LanguageSet* languageSet);

    virtual ~ControlPanel();

    QStatus setRootWidget(Container* rootContainer);

    QStatus registerObjects(BusAttachment* bus, qcc::String const& unitName);

    QStatus unregisterObjects(BusAttachment* bus);

  private:

    ControlPanel(LanguageSet const& languageSet);

    LanguageSet const& m_LanguageSet;

    Container* m_RootContainer;

    BusObject* m_ControlPanelBusObject;

    static qcc::String const& TAG;
};

} /* namespace services */
} /* namespace ajn */
#endif /* CONTROLPANEL_H_ */
