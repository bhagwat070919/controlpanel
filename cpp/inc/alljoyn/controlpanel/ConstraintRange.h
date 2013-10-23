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

#ifndef CONSTRAINTRANGE_H_
#define CONSTRAINTRANGE_H_

#include "alljoyn/BusAttachment.h"
#include "alljoyn/controlpanel/PropertyType.h"
#include "alljoyn/controlpanel/Widget.h" //TODO figure out function ptrs

namespace ajn {
namespace services {

typedef union {
    uint16_t uint16Value;
    int16_t int16Value;
    uint32_t uint32Value;
    int32_t int32Value;
    uint64_t uint64Value;
    int64_t int64Value;
    double doubleValue;
} ConstraintRangeVal;

/**
 * Constraint Range class to define a range of
 * Values and constrain a property to those values
 * The Constraint is applied on the controller side.
 * No validations are done in the Controllee
 */
class ConstraintRange {
  public:
    ConstraintRange();
    ConstraintRange( const ConstraintRange &constraintRange);
    virtual ~ConstraintRange();
    const ConstraintRangeVal& getIncrementValue() const;
    const ConstraintRangeVal& getMaxValue() const;
    const ConstraintRangeVal& getMinValue() const;

    QStatus setConstraintMin(uint16_t minValue);
    QStatus setConstraintMin(int16_t minValue);
    QStatus setConstraintMin(uint32_t minValue);
    QStatus setConstraintMin(int32_t minValue);
    QStatus setConstraintMin(uint64_t minValue);
    QStatus setConstraintMin(int64_t minValue);
    QStatus setConstraintMin(double minValue);

    QStatus setConstraintMax(uint16_t maxValue);
    QStatus setConstraintMax(int16_t maxValue);
    QStatus setConstraintMax(uint32_t maxValue);
    QStatus setConstraintMax(int32_t maxValue);
    QStatus setConstraintMax(uint64_t maxValue);
    QStatus setConstraintMax(int64_t maxValue);
    QStatus setConstraintMax(double maxValue);

    QStatus setConstraintIncrement(uint16_t incrementValue);
    QStatus setConstraintIncrement(int16_t incrementValue);
    QStatus setConstraintIncrement(uint32_t incrementValue);
    QStatus setConstraintIncrement(int32_t incrementValue);
    QStatus setConstraintIncrement(uint64_t incrementValue);
    QStatus setConstraintIncrement(int64_t incrementValue);
    QStatus setConstraintIncrement(double incrementValue);

    QStatus getConstraintForArg(MsgArg& val, int16_t languageIndx, PropertyType propertyType);

  private:

    bool validateConstraintValue(PropertyType propertyType);

    ConstraintRangeVal m_MinValue;

    ConstraintRangeVal m_MaxValue;

    ConstraintRangeVal m_IncrementValue;

    PropertyType m_PropertyType;

    qcc::String TAG;
};

} /* namespace services */
} /* namespace ajn */
#endif /* CONSTRAINTRANGE_H_ */
