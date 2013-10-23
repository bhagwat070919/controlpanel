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
    ConstraintList();
    virtual ~ConstraintList();

    void setConstraintValue(uint16_t value);
    void setConstraintValue(int16_t value);
    void setConstraintValue(uint32_t value);
    void setConstraintValue(int32_t value);
    void setConstraintValue(uint64_t value);
    void setConstraintValue(int64_t value);
    void setConstraintValue(double value);
    void setConstraintValue(qcc::String value);

    PropertyType getPropertyType() const;

    ConstraintValue getConstraintValue() const;

    GetStringFptr getGetDisplay() const;

    void setGetDisplay(GetStringFptr getDisplay);

    const std::vector<qcc::String>& getDisplay() const;

    void setDisplay(const std::vector<qcc::String>& display);

    QStatus getConstraintForArg(MsgArg& val, int16_t languageIndx, PropertyType propertyType);

  private:
    PropertyType m_PropertyType;

    ConstraintValue m_ConstraintValue;

    std::vector<qcc::String> m_Display;

    GetStringFptr m_GetDisplay;

    qcc::String m_ConstraintValueString;

    qcc::String TAG;
};

} /* namespace services */
} /* namespace ajn */

#endif /* CONSTRAINTLIST_H_ */
