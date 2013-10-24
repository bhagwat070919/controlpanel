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

#include <alljoyn/controlpanel/Common/DateTimeUtil.h>
#include <alljoyn/controlpanel/Common/ControlMarshalUtil.h>

AJ_Status marshalDatePropertyValue(DatePropertyValue* datePropertyValue, AJ_Message* reply)
{
    AJ_Status status;
    AJ_Arg outerStructArg, innerStructArg;

    CPS_CHECK(AJ_MarshalVariant(reply, DATE_PROPERTY_SIG));
    CPS_CHECK(AJ_MarshalContainer(reply, &outerStructArg, AJ_ARG_STRUCT));
    CPS_CHECK(AJ_MarshalArgs(reply, "q", DATE_PROPERTY));
    CPS_CHECK(AJ_MarshalContainer(reply, &innerStructArg, AJ_ARG_STRUCT));

    CPS_CHECK(AJ_MarshalArgs(reply, "qqq", datePropertyValue->mDay, datePropertyValue->month,
                             datePropertyValue->fullYear));

    CPS_CHECK(AJ_MarshalCloseContainer(reply, &innerStructArg));
    return AJ_MarshalCloseContainer(reply, &outerStructArg);
}

AJ_Status marshalTimePropertyValue(TimePropertyValue* timePropertyValue, AJ_Message* reply)
{
    AJ_Status status;
    AJ_Arg outerStructArg, innerStructArg;

    CPS_CHECK(AJ_MarshalVariant(reply, TIME_PROPERTY_SIG));
    CPS_CHECK(AJ_MarshalContainer(reply, &outerStructArg, AJ_ARG_STRUCT));
    CPS_CHECK(AJ_MarshalArgs(reply, "q", TIME_PROPERTY));
    CPS_CHECK(AJ_MarshalContainer(reply, &innerStructArg, AJ_ARG_STRUCT));

    CPS_CHECK(AJ_MarshalArgs(reply, "qqq", timePropertyValue->hour,
                             timePropertyValue->minute, timePropertyValue->second));

    CPS_CHECK(AJ_MarshalCloseContainer(reply, &innerStructArg));
    return AJ_MarshalCloseContainer(reply, &outerStructArg);
}

AJ_Status unmarshalDatePropertyValue(DatePropertyValue* datePropertyValue, AJ_Message* message)
{
    AJ_Status status;
    AJ_Arg outerStructArg, innerStructArg;
    uint16_t widgetType;

    CPS_CHECK(AJ_UnmarshalContainer(message, &outerStructArg, AJ_ARG_STRUCT));
    CPS_CHECK(AJ_UnmarshalArgs(message, "q", &widgetType));

    if (widgetType != DATE_PROPERTY)
        return AJ_ERR_UNEXPECTED;

    CPS_CHECK(AJ_UnmarshalContainer(message, &innerStructArg, AJ_ARG_STRUCT));
    CPS_CHECK(AJ_UnmarshalArgs(message, "qqq", &datePropertyValue->mDay, &datePropertyValue->month,
                               &datePropertyValue->fullYear));

    CPS_CHECK(AJ_UnmarshalCloseContainer(message, &innerStructArg));
    return AJ_UnmarshalCloseContainer(message, &outerStructArg);
}

AJ_Status unmarshalTimePropertyValue(TimePropertyValue* timePropertyValue, AJ_Message* message)
{
    AJ_Status status;
    AJ_Arg outerStructArg, innerStructArg;
    uint16_t widgetType;

    CPS_CHECK(AJ_UnmarshalContainer(message, &outerStructArg, AJ_ARG_STRUCT));
    CPS_CHECK(AJ_UnmarshalArgs(message, "q", &widgetType));

    if (widgetType != TIME_PROPERTY)
        return AJ_ERR_UNEXPECTED;

    CPS_CHECK(AJ_UnmarshalContainer(message, &innerStructArg, AJ_ARG_STRUCT));
    CPS_CHECK(AJ_UnmarshalArgs(message, "qqq", &timePropertyValue->hour, &timePropertyValue->minute,
                               &timePropertyValue->second));

    CPS_CHECK(AJ_UnmarshalCloseContainer(message, &innerStructArg));
    return AJ_UnmarshalCloseContainer(message, &outerStructArg);
}

