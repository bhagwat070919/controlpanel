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

#include <alljoyn/controlpanel/PropertyType.h>
#include <alljoyn/controlpanel/Widget.h>

namespace ajn {
namespace services {

/**
 * ConstraintRangeValue - a union combining all possible values
 * that can make up a constraint Range
 */
typedef union {
    /**
     * Value of type uint16_t
     */
    uint16_t uint16Value;
    /**
     * Value of type int16_t
     */
    int16_t int16Value;
    /**
     * Value of type uint32_t
     */
    uint32_t uint32Value;
    /**
     * Value of type int32_t
     */
    int32_t int32Value;
    /**
     * Value of type uint64_t
     */
    uint64_t uint64Value;
    /**
     * Value of type int64_t
     */
    int64_t int64Value;
    /**
     * Value of type double
     */
    double doubleValue;
} ConstraintRangeVal;

/**
 * Constraint Range class to define a range of
 * Values and constrain a property to those values
 * The Constraint is applied on the controller side.
 * No validations are done in the Controlee
 */
class ConstraintRange {
  public:

    /**
     * Constructor for ConstraintRange
     */
    ConstraintRange();

    /**
     * Destructor for ConstraintRange
     */
    virtual ~ConstraintRange();

    /**
     * get the IncrementValue of the Constraint Range
     * @return IncrementValue
     */
    const ConstraintRangeVal& getIncrementValue() const;

    /**
     * Get the MaxValue of the Constraint Range
     * @return MaxValue
     */
    const ConstraintRangeVal& getMaxValue() const;

    /**
     * Get the MinValue of the Constraint Range
     * @return MinValue
     */
    const ConstraintRangeVal& getMinValue() const;

    /**
     * Set the Min Value for the Constraint
     * @param minValue
     * @return status - success/failure
     */
    QStatus setConstraintMin(uint16_t minValue);

    /**
     * Set the Min Value for the Constraint
     * @param minValue
     * @return status - success/failure
     */
    QStatus setConstraintMin(int16_t minValue);

    /**
     * Set the Min Value for the Constraint
     * @param minValue
     * @return status - success/failure
     */
    QStatus setConstraintMin(uint32_t minValue);

    /**
     * Set the Min Value for the Constraint
     * @param minValue
     * @return status - success/failure
     */
    QStatus setConstraintMin(int32_t minValue);

    /**
     * Set the Min Value for the Constraint
     * @param minValue
     * @return status - success/failure
     */
    QStatus setConstraintMin(uint64_t minValue);

    /**
     * Set the Min Value for the Constraint
     * @param minValue
     * @return status - success/failure
     */
    QStatus setConstraintMin(int64_t minValue);

    /**
     * Set the Min Value for the Constraint
     * @param minValue
     * @return status - success/failure
     */
    QStatus setConstraintMin(double minValue);

    /**
     * Set the Max Value for the Constraint
     * @param maxValue
     * @return status - success/failure
     */
    QStatus setConstraintMax(uint16_t maxValue);

    /**
     * Set the Max Value for the Constraint
     * @param maxValue
     * @return status - success/failure
     */
    QStatus setConstraintMax(int16_t maxValue);

    /**
     * Set the Max Value for the Constraint
     * @param maxValue
     * @return status - success/failure
     */
    QStatus setConstraintMax(uint32_t maxValue);

    /**
     * Set the Max Value for the Constraint
     * @param maxValue
     * @return status - success/failure
     */
    QStatus setConstraintMax(int32_t maxValue);

    /**
     * Set the Max Value for the Constraint
     * @param maxValue
     * @return status - success/failure
     */
    QStatus setConstraintMax(uint64_t maxValue);

    /**
     * Set the Max Value for the Constraint
     * @param maxValue
     * @return status - success/failure
     */
    QStatus setConstraintMax(int64_t maxValue);

    /**
     * Set the Max Value for the Constraint
     * @param maxValue
     * @return status - success/failure
     */
    QStatus setConstraintMax(double maxValue);

    /**
     * Set the Increment Value for the Constraint
     * @param incrementValue
     * @return status - success/failure
     */
    QStatus setConstraintIncrement(uint16_t incrementValue);

    /**
     * Set the Increment Value for the Constraint
     * @param incrementValue
     * @return status - success/failure
     */
    QStatus setConstraintIncrement(int16_t incrementValue);

    /**
     * Set the Increment Value for the Constraint
     * @param incrementValue
     * @return status - success/failure
     */
    QStatus setConstraintIncrement(uint32_t incrementValue);

    /**
     * Set the Increment Value for the Constraint
     * @param incrementValue
     * @return status - success/failure
     */
    QStatus setConstraintIncrement(int32_t incrementValue);

    /**
     * Set the Increment Value for the Constraint
     * @param incrementValue
     * @return status - success/failure
     */
    QStatus setConstraintIncrement(uint64_t incrementValue);

    /**
     * Set the Increment Value for the Constraint
     * @param incrementValue
     * @return status - success/failure
     */
    QStatus setConstraintIncrement(int64_t incrementValue);

    /**
     * Set the Increment Value for the Constraint
     * @param incrementValue
     * @return status - success/failure
     */
    QStatus setConstraintIncrement(double incrementValue);

    /**
     * Fill the MsgArg passed in with the Constraint
     * @param val - msgArg to fill
     * @param languageIndx - the languageIndx for the Display value
     * @param propertyType - the property Type expected
     * @return status - success/failure
     */
    QStatus fillConstraintArg(MsgArg& val, uint16_t languageIndx, PropertyType propertyType);

  private:

    bool validateConstraintValue(PropertyType propertyType);

    ConstraintRangeVal m_MinValue;

    ConstraintRangeVal m_MaxValue;

    ConstraintRangeVal m_IncrementValue;

    PropertyType m_PropertyType;
};

} /* namespace services */
} /* namespace ajn */
#endif /* CONSTRAINTRANGE_H_ */
