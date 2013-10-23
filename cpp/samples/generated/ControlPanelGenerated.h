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

#ifndef CONTROLPANELGENERATED_H_
#define CONTROLPANELGENERATED_H_

#include "alljoyn/controlpanel/ControlPanelControllee.h"
#include "alljoyn/controlpanel/ControlPanelHints.h"
#include "alljoyn/controlpanel/Container.h"
#include "alljoyn/controlpanel/Label.h"
#include "alljoyn/controlpanel/ActionWithDialog.h"
#include "../generated/HeatProperty.h"
#include "../generated/OvenAction.h"
#include "../generated/LightConfirm.h"
#include "../generated/AreYouSure.h"


/**
 * Generated Class - do not change code
 */
class ControlPanelGenerated {
  public:

    static QStatus PrepareWidgets(ajn::services::ControlPanelControllee*& controlPanelControllee);

    static void PrepareLanguageSets();

    static void Shutdown();

    static bool languageSetsDone;

  private:

    static ajn::services::ControlPanel* rootContainerControlPanel;
    static ajn::services::Container* rootContainer;
    static ajn::services::Label* CurrentTemp;
    static ajn::services::HeatProperty* heatProperty;
    static ajn::services::OvenAction* ovenAction;
    static ajn::services::ActionWithDialog* lightAction;
    static ajn::services::LightConfirm* lightConfirm;
    static ajn::services::NotificationAction* areYouSureNotificationAction;
    static ajn::services::AreYouSure* areYouSure;

};

#endif /* CONTROLPANELGENERATED_H_ */
