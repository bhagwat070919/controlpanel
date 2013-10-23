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

#ifndef CONSTRAINTLIST_H_
#define CONSTRAINTLIST_H_

#include "alljoyn/BusAttachment.h"
#include "alljoyn/controlpanel/Widget.h"
#include "alljoyn/controlpanel/PropertyType.h"
#include <vector>

namespace ajn {
namespace services {

/**
 * ConstraintValue - a union combining all possible values
 * that can make up a constraint
 */
typedef union {
    uint16_t uint16Value;
    int16_t int16Value;
    uint32_t uint32Value;
    int32_t int32Value;
    uint64_t uint64Value;
    int64_t int64Value;
    double doubleValue;
    const char* charValue;
} ConstraintValue;

/**
 * Constraint List class to define a list of
 * Values and constrain a property to those values
 * The Constraint is applied on the controller side.
 * No validations are done in the Controllee
 */
class ConstraintList {
  public:

    /**
     * Constructor for ConstraintList
     */
    ConstraintList();

    /**
     * Destructor for ConstraintList
     */
    virtual ~ConstraintList();

    /**
     * Set the value for the Constraint
     * @param value - value to be Constrained to
     */
    void setConstraintValue(uint16_t value);

    /**
     * Set the value for the Constraint
     * @param value - value to be Constrained to
     */
    void setConstraintValue(int16_t value);

    /**
     * Set the value for the Constraint
     * @param value - value to be Constrained to
     */
    void setConstraintValue(uint32_t value);

    /**
     * Set the value for the Constraint
     * @param value - value to be Constrained to
     */
    void setConstraintValue(int32_t value);

    /**
     * Set the value for the Constraint
     * @param value - value to be Constrained to
     */
    void setConstraintValue(uint64_t value);

    /**
     * Set the value for the Constraint
     * @param value - value to be Constrained to
     */
    void setConstraintValue(int64_t value);

    /**
     * Set the value for the Constraint
     * @param value - value to be Constrained to
     */
    void setConstraintValue(double value);

    /**
     * Set the value for the Constraint
     * @param value - value to be Constrained to
     */
    void setConstraintValue(qcc::String const& value);

    /**
     * Get the Constraint Value
     * @return the Constraint Value
     */
    ConstraintValue getConstraintValue() const;

    /**
     * Get the Property Type of the Constraint
     * @return propertyType of the Constraint
     */
    PropertyType getPropertyType() const;

    /**
     * Get the Display vector
     * @return vector of the Display Values
     */
    const std::vector<qcc::String>& getDisplay() const;

    /**
     * Set the Display vector
     * @param display - vector of the display values
     */
    void setDisplay(const std::vector<qcc::String>& display);

    /**
     * Get the function pointer to get the display values
     * @return the GetDisplay function pointer
     */
    GetStringFptr getGetDisplay() const;

    /**
     * Set the GetDisplay function pointer
     * @param getDisplay - the function pointer to get the display values
     */
    void setGetDisplay(GetStringFptr getDisplay);

    /**
     * fill the MsgArg passed in with the Constraint
     * @param val - msgArg to fill
     * @param languageIndx - the languageIndx for the Display value
     * @param propertyType - the property Type expected
     * @return status - success/failure
     */
    QStatus fillConstraintArg(MsgArg& val, int16_t languageIndx, PropertyType propertyType);

  private:

    /**
     * Property Type of Constraint
     */
    PropertyType m_PropertyType;

    /**
     * The Constraint Value of the Cosntraint
     */
    ConstraintValue m_ConstraintValue;

    /**
     * The Display value of the Constraint
     */
    std::vector<qcc::String> m_Display;

    /**
     * The GetDisplay function pointer of the Constraint
     */
    GetStringFptr m_GetDisplay;

    /**
     * A local string to store the Constraint if the property Type is a string
     */
    qcc::String m_ConstraintValueString;
};

} /* namespace services */
} /* namespace ajn */

#endif /* CONSTRAINTLIST_H_ */
