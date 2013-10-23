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

#include "ControlPanelGenerated.h"
#include "alljoyn/controlpanel/LanguageSets.h"
#include "alljoyn/controlpanel/Label.h"

using namespace ajn;
using namespace services;
#define CHECK(x) if ((x) != ER_OK) return status;

QStatus ControlPanelGenerated::PrepareLanguageSets()
{
    LanguageSet myLanguages("myLanguages");
    myLanguages.addLanguage("en");
    LanguageSets::add(myLanguages.getLanguageSetName(), myLanguages);
    return ER_OK;
}

QStatus ControlPanelGenerated::PrepareWidgets(ControlPanelControllee*& controlPanelControllee)
{
    if (controlPanelControllee)
        return ER_BAD_ARG_1;

    QStatus status = ER_OK;
    controlPanelControllee = new ControlPanelControllee("MyDevice");

    LanguageSet* langSet = LanguageSets::get("myLanguages");
    if (!langSet)
        return ER_PARSE_ERROR;

    ControlPanel* controlPanel = new ControlPanel(*langSet);
    controlPanelControllee->addControlPanel(controlPanel);

    Container* container = new Container("rootContainer");
    CHECK(controlPanel->setRootContainer(container));

    container->setBgColor(200);

    Label* label = new Label("CurrentTemp");
    CHECK(container->addChildElement(label));

    std::vector<qcc::String> labels;
    labels.push_back("TestLabel");
    label->setLabel(labels);

    return ER_OK;
}

