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
#include "ControlPanelProvided.h"


using namespace ajn;
using namespace services;

bool ControlPanelGenerated::languageSetsDone = false;
ControlPanel* ControlPanelGenerated::rootContainerControlPanel = 0;
Container* ControlPanelGenerated::rootContainer = 0;
Label* ControlPanelGenerated::CurrentTemp = 0;
HeatProperty* ControlPanelGenerated::heatProperty = 0;
OvenAction* ControlPanelGenerated::ovenAction = 0;
ActionWithDialog* ControlPanelGenerated::lightAction = 0;
LightConfirm* ControlPanelGenerated::lightConfirm = 0;
NotificationAction* ControlPanelGenerated::areYouSureNotificationAction = 0;
AreYouSure* ControlPanelGenerated::areYouSure = 0;


#define CHECK(x) if ((status = x) != ER_OK) return status;
#define UNIT_NAME "MyDevice"

void ControlPanelGenerated::PrepareLanguageSets()
{
    if (languageSetsDone)
        return;

    LanguageSet myLanguages("myLanguages");
    myLanguages.addLanguage("en");
    myLanguages.addLanguage("de_AT");
    LanguageSets::add(myLanguages.getLanguageSetName(), myLanguages);

    languageSetsDone = true;
}

QStatus ControlPanelGenerated::PrepareWidgets(ControlPanelControllee*& controlPanelControllee)
{
    if (controlPanelControllee)
        return ER_BAD_ARG_1;

    PrepareLanguageSets();

    QStatus status = ER_OK;
    controlPanelControllee = new ControlPanelControllee(UNIT_NAME);

    rootContainerControlPanel = ControlPanel::createControlPanel(LanguageSets::get("myLanguages"));
    if (!rootContainerControlPanel)
        return ER_FAIL;
    CHECK(controlPanelControllee->addControlPanel(rootContainerControlPanel));

    rootContainer = new Container("rootContainer");
    CHECK(rootContainerControlPanel->setRootWidget(rootContainer));

    rootContainer->setEnabled(true);
    rootContainer->setIsSecured(false);
    rootContainer->setBgColor(0x200);

    std::vector<qcc::String> rootContainerlabelVec;
    rootContainerlabelVec.push_back("My Label of my container");
    rootContainerlabelVec.push_back("Container Etikett");
    rootContainer->setLabel(rootContainerlabelVec);

    std::vector<uint16_t> rootContainerHintsVec;
    rootContainerHintsVec.push_back(VERTICAL_LINEAR);
    rootContainerHintsVec.push_back(HORIZONTAL_LINEAR);
    rootContainer->setHints(rootContainerHintsVec);

    CurrentTemp = new Label("CurrentTemp");
    CHECK(rootContainer->addChildWidget(CurrentTemp));

    CurrentTemp->setEnabled(true);
    CurrentTemp->setBgColor(0x98765);

    std::vector<qcc::String> CurrentTemplabelVec;
    CurrentTemplabelVec.push_back("Current Temperature:");
    CurrentTemplabelVec.push_back("Aktuelle Temperatur:");
    CurrentTemp->setLabel(CurrentTemplabelVec);

    std::vector<uint16_t> CurrentTempHintsVec;
    CurrentTempHintsVec.push_back(TEXTLABEL);
    CurrentTemp->setHints(CurrentTempHintsVec);

    heatProperty = new HeatProperty("heatProperty", UINT16_PROPERTY);
    CHECK(rootContainer->addChildWidget(heatProperty));

    heatProperty->setEnabled(true);
    heatProperty->setIsSecured(false);
    heatProperty->setWritable(true);
    CHECK(heatProperty->setGetValue(getuint16Var));
    heatProperty->setBgColor(0x500);

    std::vector<qcc::String> heatPropertylabelVec;
    heatPropertylabelVec.push_back("Oven Temperature");
    heatPropertylabelVec.push_back("Ofentemperatur");
    heatProperty->setLabel(heatPropertylabelVec);

    std::vector<uint16_t> heatPropertyHintsVec;
    heatPropertyHintsVec.push_back(SPINNER);
    heatProperty->setHints(heatPropertyHintsVec);

    std::vector<qcc::String> heatPropertyunitMeasureVec;
    heatPropertyunitMeasureVec.push_back("Degrees");
    heatPropertyunitMeasureVec.push_back("Grad");
    heatProperty->setUnitOfMeasure(heatPropertyunitMeasureVec);

    std::vector<ConstraintList> heatPropertyConstraintListVec(3);

    std::vector<qcc::String> heatPropertyDisplay1Vec;
    heatPropertyDisplay1Vec.push_back("Regular");
    heatPropertyDisplay1Vec.push_back("Normal");
    heatPropertyConstraintListVec[0].setDisplay(heatPropertyDisplay1Vec);
    heatPropertyConstraintListVec[0].setConstraintValue((uint16_t)175);

    std::vector<qcc::String> heatPropertyDisplay2Vec;
    heatPropertyDisplay2Vec.push_back("Hot");
    heatPropertyDisplay2Vec.push_back("Heiss");
    heatPropertyConstraintListVec[1].setDisplay(heatPropertyDisplay2Vec);
    heatPropertyConstraintListVec[1].setConstraintValue((uint16_t)200);

    std::vector<qcc::String> heatPropertyDisplay3Vec;
    heatPropertyDisplay3Vec.push_back("Very Hot");
    heatPropertyDisplay3Vec.push_back("Sehr Heiss");
    heatPropertyConstraintListVec[2].setDisplay(heatPropertyDisplay3Vec);
    heatPropertyConstraintListVec[2].setConstraintValue((uint16_t)225);

    heatProperty->setConstraintList(heatPropertyConstraintListVec);

    ovenAction = new OvenAction("ovenAction");
    CHECK(rootContainer->addChildWidget(ovenAction));

    ovenAction->setEnabled(true);
    ovenAction->setIsSecured(false);
    ovenAction->setBgColor(0x400);

    std::vector<qcc::String> ovenActionlabelVec;
    ovenActionlabelVec.push_back("Start Oven");
    ovenActionlabelVec.push_back("Ofen started");
    ovenAction->setLabel(ovenActionlabelVec);

    std::vector<uint16_t> ovenActionHintsVec;
    ovenActionHintsVec.push_back(ACTIONBUTTON);
    ovenAction->setHints(ovenActionHintsVec);

    lightAction = new ActionWithDialog("lightAction");
    CHECK(rootContainer->addChildWidget(lightAction));

    lightAction->setEnabled(true);
    lightAction->setIsSecured(false);
    lightAction->setBgColor(0x400);

    std::vector<qcc::String> lightActionlabelVec;
    lightActionlabelVec.push_back("Turn on oven light");
    lightActionlabelVec.push_back("Ofenlicht anschalten");
    lightAction->setLabel(lightActionlabelVec);

    std::vector<uint16_t> lightActionHintsVec;
    lightActionHintsVec.push_back(ACTIONBUTTON);
    lightAction->setHints(lightActionHintsVec);

    lightConfirm = new LightConfirm("lightConfirm");
    CHECK(lightAction->addChildDialog(lightConfirm));

    lightConfirm->setEnabled(true);
    lightConfirm->setIsSecured(false);

    std::vector<qcc::String> lightConfirmmessageVec;
    lightConfirmmessageVec.push_back("Are you sure you want to turn on the light");
    lightConfirmmessageVec.push_back("Are you sure you want to turn on the light");
    lightConfirm->setMessage(lightConfirmmessageVec);
    lightConfirm->setNumActions(3);
    lightConfirm->setBgColor(0x789);

    std::vector<qcc::String> lightConfirmlabelVec;
    lightConfirmlabelVec.push_back("Are you sure?");
    lightConfirmlabelVec.push_back("Sind sie sicher?");
    lightConfirm->setLabel(lightConfirmlabelVec);

    std::vector<uint16_t> lightConfirmHintsVec;
    lightConfirmHintsVec.push_back(ALERTDIALOG);
    lightConfirm->setHints(lightConfirmHintsVec);

    std::vector<qcc::String> lightConfirmLabelAction1Vec;
    lightConfirmLabelAction1Vec.push_back("Yes");
    lightConfirmLabelAction1Vec.push_back("Ja");
    lightConfirm->setLabelAction1(lightConfirmLabelAction1Vec);

    std::vector<qcc::String> lightConfirmLabelAction2Vec;
    lightConfirmLabelAction2Vec.push_back("No");
    lightConfirmLabelAction2Vec.push_back("Nein");
    lightConfirm->setLabelAction2(lightConfirmLabelAction2Vec);

    std::vector<qcc::String> lightConfirmLabelAction3Vec;
    lightConfirmLabelAction3Vec.push_back("Cancel");
    lightConfirmLabelAction3Vec.push_back("Abrechen");
    lightConfirm->setLabelAction3(lightConfirmLabelAction3Vec);

    areYouSureNotificationAction = NotificationAction::createNotificationAction(LanguageSets::get("myLanguages"));
    if (!areYouSureNotificationAction)
        return ER_FAIL;
    CHECK(controlPanelControllee->addNotificationAction(areYouSureNotificationAction));

    areYouSure = new AreYouSure("areYouSure");
    CHECK(areYouSureNotificationAction->setRootWidget(areYouSure));

    areYouSure->setEnabled(true);
    areYouSure->setIsSecured(false);

    std::vector<qcc::String> areYouSuremessageVec;
    areYouSuremessageVec.push_back("Are you sure?");
    areYouSuremessageVec.push_back("Sind sie sicher?");
    areYouSure->setMessage(areYouSuremessageVec);
    areYouSure->setNumActions(1);
    areYouSure->setBgColor(0x789);

    std::vector<qcc::String> areYouSurelabelVec;
    areYouSurelabelVec.push_back("Are you sure?");
    areYouSurelabelVec.push_back("Sind sie sicher?");
    areYouSure->setLabel(areYouSurelabelVec);

    std::vector<qcc::String> areYouSureLabelAction1Vec;
    areYouSureLabelAction1Vec.push_back("Yes");
    areYouSureLabelAction1Vec.push_back("Ja");
    areYouSure->setLabelAction1(areYouSureLabelAction1Vec);

    return status;
}

void ControlPanelGenerated::Shutdown()
{
    if (rootContainerControlPanel) {
        delete (rootContainerControlPanel);
        rootContainerControlPanel = 0;
    }
    if (rootContainer) {
        delete (rootContainer);
        rootContainer = 0;
    }
    if (CurrentTemp) {
        delete (CurrentTemp);
        CurrentTemp = 0;
    }
    if (heatProperty) {
        delete (heatProperty);
        heatProperty = 0;
    }
    if (ovenAction) {
        delete (ovenAction);
        ovenAction = 0;
    }
    if (lightAction) {
        delete (lightAction);
        lightAction = 0;
    }
    if (lightConfirm) {
        delete (lightConfirm);
        lightConfirm = 0;
    }
    if (areYouSureNotificationAction) {
        delete (areYouSureNotificationAction);
        areYouSureNotificationAction = 0;
    }
    if (areYouSure) {
        delete (areYouSure);
        areYouSure = 0;
    }

}
