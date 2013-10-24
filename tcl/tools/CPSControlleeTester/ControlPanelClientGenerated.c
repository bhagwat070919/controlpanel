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

#include <alljoyn/controlpanel/Widgets/ActionWidget.h>
#include <alljoyn/controlpanel/Widgets/PropertyWidget.h>
#include <alljoyn/controlpanel/Widgets/ContainerWidget.h>
#include <alljoyn/controlpanel/Widgets/LabelWidget.h>
#include <alljoyn/controlpanel/Widgets/DialogWidget.h>
#include <alljoyn/controlpanel/Common/HttpControl.h>
#include <alljoyn/controlpanel/Common/ConstraintList.h>
#include <alljoyn/controlpanel/ControlPanelService.h>


const char rootContainerObjectPath[] = "/ControlPanel/MyDevice/rootContainer";
const char enRootcontainerObjectPath[] = "/ControlPanel/MyDevice/rootContainer/en";
const char de_ATRootcontainerObjectPath[] = "/ControlPanel/MyDevice/rootContainer/de_AT";
const char enCurrenttempObjectPath[] = "/ControlPanel/MyDevice/rootContainer/en/CurrentTemp";
const char de_ATCurrenttempObjectPath[] = "/ControlPanel/MyDevice/rootContainer/de_AT/CurrentTemp";
const char enHeatpropertyObjectPath[] = "/ControlPanel/MyDevice/rootContainer/en/heatProperty";
const char de_ATHeatpropertyObjectPath[] = "/ControlPanel/MyDevice/rootContainer/de_AT/heatProperty";
const char enOvenactionObjectPath[] = "/ControlPanel/MyDevice/rootContainer/en/ovenAction";
const char de_ATOvenactionObjectPath[] = "/ControlPanel/MyDevice/rootContainer/de_AT/ovenAction";
const char enLightactionObjectPath[] = "/ControlPanel/MyDevice/rootContainer/en/lightAction";
const char de_ATLightactionObjectPath[] = "/ControlPanel/MyDevice/rootContainer/de_AT/lightAction";
const char enLightconfirmObjectPath[] = "/ControlPanel/MyDevice/rootContainer/en/lightAction/LightConfirm";
const char de_ATLightconfirmObjectPath[] = "/ControlPanel/MyDevice/rootContainer/de_AT/lightAction/LightConfirm";
const char areYouSureObjectPath[] = "/ControlPanel/MyDevice/areYouSure";
const char enAreyousureObjectPath[] = "/ControlPanel/MyDevice/areYouSure/en";
const char de_ATAreyousureObjectPath[] = "/ControlPanel/MyDevice/areYouSure/de_AT";


/*
 * Static variables used to fill rootContainerResponse
 */


void WidgetsInit()
{

    return;
}

void* identifyMsgOrPropId(uint32_t identifier, uint16_t* widgetType, uint16_t* propType, uint16_t* language)
{
    switch (identifier) {
    default:
        return FALSE;
    }
}

void* identifyMsgOrPropIdForSignal(uint32_t identifier, uint8_t* isProperty)
{
    switch (identifier) {
    default:
        return FALSE;
    }
}

uint8_t identifyRootMsgOrPropId(uint32_t identifier)
{
    switch (identifier) {
    default:
        return FALSE;
    }
}

AJ_Status SetValueProperty(AJ_Message* replyMsg, uint32_t propId, void* context)
{
    AJ_Status status = AJ_ERR_UNEXPECTED;

    const char* variantSig;
    AJ_UnmarshalVariant(replyMsg, &variantSig);

    switch (propId) {

    }

    return status;
}

AJ_Status ExecuteAction(AJ_Message* msg, uint32_t msgId, ExecuteActionContext* context)
{
    AJ_Message reply;
    AJ_MarshalReplyMsg(msg, &reply);

    switch (msgId) {

    }

    return AJ_DeliverMsg(&reply);
}

void TestsInit(CPSTest* testsToRun)
{
    testsToRun[0].msgId = EN_ROOTCONTAINER_GET_ALL_VALUES;
    testsToRun[0].numParams = 0;
    testsToRun[1].msgId = DE_AT_ROOTCONTAINER_GET_ALL_VALUES;
    testsToRun[1].numParams = 0;
    testsToRun[2].msgId = EN_CURRENTTEMP_GET_ALL_VALUES;
    testsToRun[2].numParams = 0;
    testsToRun[3].msgId = DE_AT_CURRENTTEMP_GET_ALL_VALUES;
    testsToRun[3].numParams = 0;
    testsToRun[4].msgId = EN_HEATPROPERTY_GET_ALL_VALUES;
    testsToRun[4].numParams = 0;
    testsToRun[5].msgId = DE_AT_HEATPROPERTY_GET_ALL_VALUES;
    testsToRun[5].numParams = 0;
    testsToRun[6].msgId = EN_OVENACTION_GET_ALL_VALUES;
    testsToRun[6].numParams = 0;
    testsToRun[7].msgId = EN_OVENACTION_EXEC;
    testsToRun[7].numParams = 0;
    testsToRun[8].msgId = DE_AT_OVENACTION_GET_ALL_VALUES;
    testsToRun[8].numParams = 0;
    testsToRun[9].msgId = DE_AT_OVENACTION_EXEC;
    testsToRun[9].numParams = 0;
    testsToRun[10].msgId = EN_LIGHTACTION_GET_ALL_VALUES;
    testsToRun[10].numParams = 0;
    testsToRun[11].msgId = EN_LIGHTACTION_EXEC;
    testsToRun[11].numParams = 0;
    testsToRun[12].msgId = DE_AT_LIGHTACTION_GET_ALL_VALUES;
    testsToRun[12].numParams = 0;
    testsToRun[13].msgId = DE_AT_LIGHTACTION_EXEC;
    testsToRun[13].numParams = 0;
    testsToRun[14].msgId = EN_LIGHTCONFIRM_GET_ALL_VALUES;
    testsToRun[14].numParams = 0;
    testsToRun[15].msgId = EN_LIGHTCONFIRM_EXEC_ACTION1;
    testsToRun[15].numParams = 0;
    testsToRun[16].msgId = EN_LIGHTCONFIRM_EXEC_ACTION2;
    testsToRun[16].numParams = 0;
    testsToRun[17].msgId = EN_LIGHTCONFIRM_EXEC_ACTION3;
    testsToRun[17].numParams = 0;
    testsToRun[18].msgId = DE_AT_LIGHTCONFIRM_GET_ALL_VALUES;
    testsToRun[18].numParams = 0;
    testsToRun[19].msgId = DE_AT_LIGHTCONFIRM_EXEC_ACTION1;
    testsToRun[19].numParams = 0;
    testsToRun[20].msgId = DE_AT_LIGHTCONFIRM_EXEC_ACTION2;
    testsToRun[20].numParams = 0;
    testsToRun[21].msgId = DE_AT_LIGHTCONFIRM_EXEC_ACTION3;
    testsToRun[21].numParams = 0;
    testsToRun[22].msgId = EN_AREYOUSURE_GET_ALL_VALUES;
    testsToRun[22].numParams = 0;
    testsToRun[23].msgId = EN_AREYOUSURE_EXEC_ACTION1;
    testsToRun[23].numParams = 0;
    testsToRun[24].msgId = EN_AREYOUSURE_EXEC_ACTION2;
    testsToRun[24].numParams = 0;
    testsToRun[25].msgId = EN_AREYOUSURE_EXEC_ACTION3;
    testsToRun[25].numParams = 0;
    testsToRun[26].msgId = DE_AT_AREYOUSURE_GET_ALL_VALUES;
    testsToRun[26].numParams = 0;
    testsToRun[27].msgId = DE_AT_AREYOUSURE_EXEC_ACTION1;
    testsToRun[27].numParams = 0;
    testsToRun[28].msgId = DE_AT_AREYOUSURE_EXEC_ACTION2;
    testsToRun[28].numParams = 0;
    testsToRun[29].msgId = DE_AT_AREYOUSURE_EXEC_ACTION3;
    testsToRun[29].numParams = 0;

}
