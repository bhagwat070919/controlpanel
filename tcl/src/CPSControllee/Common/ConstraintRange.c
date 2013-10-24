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

#include <alljoyn/controlpanel/Common/ConstraintRange.h>
#include <alljoyn/controlpanel/Common/ControlMarshalUtil.h>

void initializeConstraintRange(ConstraintRange* constraints)
{
    constraints->minValue = 0;
    constraints->maxValue = 0;
    constraints->increment = 0;
}

AJ_Status marshalConstraintRange(ConstraintRange* constraints, AJ_Message* reply)
{
    AJ_Status status;
    AJ_Arg constraintRange;

    CPS_CHECK(StartComplexOptionalParam(reply, &constraintRange, PROPERTY_CONSTRAINT_RANGE,
                                        PROPERTY_CONSTRAINT_RANGE_SIG));

    CPS_CHECK(AddConstraintRange(reply, *constraints->signature, constraints->minValue,
                                 constraints->maxValue, constraints->increment));

    return AJ_MarshalCloseContainer(reply, &constraintRange);
}
