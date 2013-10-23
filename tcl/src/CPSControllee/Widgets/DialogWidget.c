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

#include "alljoyn/controlpanel/Widgets/DialogWidget.h"
#include "alljoyn/controlpanel/Definitions.h"
#include "alljoyn/controlpanel/Common/ControlMarshalUtil.h"

void initializeDialogWidget(DialogWidget* widget)
{
    initializeBaseWidget(&widget->base);
    widget->numActions = 0;
    widget->message = 0;
    widget->getMessage = 0;

    widget->base.marshalOptParam = &marshalDialogOptParam;
    widget->base.marshalAllProp = &marshalAllDialogProperties;

    initializeDialogOptParam(&widget->optParams);
}

AJ_Status marshalDialogMessage(DialogWidget* widget, AJ_Message* reply, uint16_t language)
{
    if (language >= widget->base.numLanguages)
        return AJ_ERR_UNEXPECTED;

    if (widget->getMessage)
        return AJ_MarshalArgs(reply, PROPERTY_TYPE_MESSAGE_SIG, widget->getMessage(language));

    return AJ_MarshalArgs(reply, PROPERTY_TYPE_MESSAGE_SIG, widget->message[language]);
}

AJ_Status marshalDialogNumActions(DialogWidget* widget, AJ_Message* reply, uint16_t language)
{
    return AJ_MarshalArgs(reply, PROPERTY_TYPE_NUM_ACTIONS_SIG, widget->numActions);
}

void initializeDialogOptParam(DialogOptParams* optParam)
{
    optParam->labelAction1 = 0;
    optParam->getLabelAction1 = 0;
    optParam->labelAction2 = 0;
    optParam->getLabelAction2 = 0;
    optParam->labelAction3 = 0;
    optParam->getLabelAction3 = 0;
}

AJ_Status marshalDialogOptParam(BaseWidget* widget, AJ_Message* reply, uint16_t language)
{
    if (language >= widget->numLanguages)
        return AJ_ERR_UNEXPECTED;

    DialogOptParams* optParams = &((DialogWidget*)widget)->optParams;
    AJ_Status status;
    AJ_Arg dialogOptParams;

    CPS_CHECK(StartOptionalParams(reply, &dialogOptParams));

    CPS_CHECK(marshalBaseOptParam(widget, reply, language));

    if (optParams->getLabelAction1) {
        const char* labelAction1 = optParams->getLabelAction1(language);
        CPS_CHECK(AddBasicOptionalParam(reply, DIALOG_LABEL_ACTION1,
                                        DIALOG_LABEL_ACTION1_SIG, &labelAction1));
    } else if (optParams->labelAction1) {
        CPS_CHECK(AddBasicOptionalParam(reply, DIALOG_LABEL_ACTION1,
                                        DIALOG_LABEL_ACTION1_SIG, &optParams->labelAction1[language]));
    }

    if (optParams->getLabelAction2) {
        const char* labelAction2 = optParams->getLabelAction2(language);
        CPS_CHECK(AddBasicOptionalParam(reply, DIALOG_LABEL_ACTION1,
                                        DIALOG_LABEL_ACTION1_SIG, &labelAction2));
    } else if (optParams->labelAction2) {
        CPS_CHECK(AddBasicOptionalParam(reply, DIALOG_LABEL_ACTION2,
                                        DIALOG_LABEL_ACTION2_SIG, &optParams->labelAction2[language]));
    }

    if (optParams->getLabelAction1) {
        const char* labelAction3 = optParams->getLabelAction1(language);
        CPS_CHECK(AddBasicOptionalParam(reply, DIALOG_LABEL_ACTION1,
                                        DIALOG_LABEL_ACTION1_SIG, &labelAction3));
    } else if (optParams->labelAction3) {
        CPS_CHECK(AddBasicOptionalParam(reply, DIALOG_LABEL_ACTION3,
                                        DIALOG_LABEL_ACTION3_SIG, &optParams->labelAction3[language]));
    }

    return AJ_MarshalCloseContainer(reply, &dialogOptParams);
}

AJ_Status marshalAllDialogProperties(BaseWidget* widget, AJ_Message* reply, uint16_t language)
{
    AJ_Status status;
    AJ_Arg dialogGetAllArray;

    CPS_CHECK(AJ_MarshalContainer(reply, &dialogGetAllArray, AJ_ARG_ARRAY));

    CPS_CHECK(AddPropertyForGetAll(reply, PROPERTY_TYPE_VERSION_NAME, PROPERTY_TYPE_VERSION_SIG,
                                   widget, language, &marshalBaseVersion));

    CPS_CHECK(marshalAllBaseProperties(widget, reply, language));

    CPS_CHECK(AddPropertyForGetAll(reply, PROPERTY_TYPE_OPTPARAMS_NAME, PROPERTY_TYPE_OPTPARAMS_SIG,
                                   widget, language, &marshalDialogOptParam));

    CPS_CHECK(AddPropertyForGetAll(reply, PROPERTY_TYPE_MESSAGE_NAME, PROPERTY_TYPE_MESSAGE_SIG,
                                   widget, language, &marshalDialogMessage));

    CPS_CHECK(AddPropertyForGetAll(reply, PROPERTY_TYPE_NUM_ACTIONS_NAME, PROPERTY_TYPE_NUM_ACTIONS_SIG,
                                   widget, language, &marshalDialogNumActions));

    return AJ_MarshalCloseContainer(reply, &dialogGetAllArray);
}
