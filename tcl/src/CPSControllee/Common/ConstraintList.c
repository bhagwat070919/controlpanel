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

#include "alljoyn/controlpanel/Common/ConstraintList.h"
#include "alljoyn/controlpanel/Common/ControlMarshalUtil.h"

AJ_Status marshalConstraintList(ConstraintList* constraints, AJ_Message* reply, uint16_t numConstraints,
                                const char* signature, uint16_t language)
{
    AJ_Status status;
    AJ_Arg arrayArg, opParams;

    CPS_CHECK(StartComplexOptionalParam(reply, &opParams, PROPERTY_CONSTRAINT_LIST, PROPERTY_CONSTRAINT_LIST_SIG));

    CPS_CHECK(AJ_MarshalContainer(reply, &arrayArg, AJ_ARG_ARRAY));

    uint16_t cnt;
    for (cnt = 0; cnt < numConstraints; cnt++) {
        if (constraints[cnt].getDisplay != 0) {
            CPS_CHECK(AddConstraintValue(reply, signature, constraints[cnt].value, constraints[cnt].getDisplay(language)));
        } else {
            CPS_CHECK(AddConstraintValue(reply, signature, constraints[cnt].value, constraints[cnt].display[language]));
        }
    }

    CPS_CHECK(AJ_MarshalCloseContainer(reply, &arrayArg));

    return AJ_MarshalCloseContainer(reply, &opParams);
}
