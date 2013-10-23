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

#include "alljoyn/controlpanel/Widgets/LabelWidget.h"
#include "alljoyn/controlpanel/Definitions.h"
#include "alljoyn/controlpanel/Common/ControlMarshalUtil.h"

void initializeLabelWidget(LabelWidget* widget)
{
    initializeBaseWidget(&widget->base);
    widget->label = 0;
    widget->getLabel = 0;

    widget->base.marshalAllProp = &marshalAllLabelProperties;
}

AJ_Status marshalLabelLabel(LabelWidget* widget, AJ_Message* reply, uint16_t language)
{
    if (language >= widget->base.numLanguages)
        return AJ_ERR_UNEXPECTED;

    if (widget->getLabel)
        return AJ_MarshalArgs(reply, PROPERTY_TYPE_LABEL_SIG, widget->getLabel(language));

    return AJ_MarshalArgs(reply, PROPERTY_TYPE_LABEL_SIG, widget->label[language]);
}

AJ_Status marshalAllLabelProperties(BaseWidget* widget, AJ_Message* reply, uint16_t language)
{
    AJ_Status status;
    AJ_Arg labelGetAllArray;

    CPS_CHECK(AJ_MarshalContainer(reply, &labelGetAllArray, AJ_ARG_ARRAY));

    CPS_CHECK(AddPropertyForGetAll(reply, PROPERTY_TYPE_VERSION_NAME, PROPERTY_TYPE_VERSION_SIG,
                                    widget, language, &marshalBaseVersion));

    CPS_CHECK(AddPropertyForGetAll(reply, PROPERTY_TYPE_LABEL_NAME, PROPERTY_TYPE_LABEL_SIG,
                                    widget, language, &marshalLabelLabel));

    CPS_CHECK(marshalAllBaseProperties(widget, reply, language));

    CPS_CHECK(AddPropertyForGetAll(reply, PROPERTY_TYPE_OPTPARAMS_NAME, PROPERTY_TYPE_OPTPARAMS_SIG,
                                    widget, language, &marshalOnlyBaseOptParam));

    return AJ_MarshalCloseContainer(reply, &labelGetAllArray);
}
