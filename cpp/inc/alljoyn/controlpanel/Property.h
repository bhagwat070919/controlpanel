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

#ifndef PROPERTY_H_
#define PROPERTY_H_

#include "alljoyn/controlpanel/Widget.h"
#include "alljoyn/controlpanel/PropertyType.h"
#include "alljoyn/controlpanel/ConstraintList.h"
#include "alljoyn/controlpanel/ConstraintRange.h"
#include <map>

namespace ajn {
namespace services {

typedef union {
    uint16_t (*getUint16Value)();
    int16_t (*getInt16Value)();
    uint32_t (*getUint32Value)();
    int32_t (*getInt32Value)();
    uint64_t (*getUint64Value)();
    int64_t (*getInt64Value)();
    double (*getDoubleValue)();
    const char* (*getCharValue)();
    bool (*getBoolValue)(); //TODO not sure
    //CPSDate* (*getDateValue)(); //TODO not sure
    //CPSTime* (*getTimeValue)(); //TODO not sure
} PropertyValue;

class Property : public Widget {
  public:
    Property(qcc::String name, PropertyType propertyType);
    virtual ~Property();

    WidgetBusObject* createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                           uint16_t langIndx, QStatus& status);

    QStatus setGetValue(uint16_t (*getUint16Value)());

    QStatus setGetValue(int16_t (*getInt16Value)());

    QStatus setGetValue(uint32_t (*getUint32Value)());

    QStatus setGetValue(int32_t (*getInt32Value)());

    QStatus setGetValue(uint64_t (*getUint64Value)());

    QStatus setGetValue(int64_t (*getInt64Value)());

    QStatus setGetValue(double (*getDoubleValue)());

    QStatus setGetValue(const char* (*getCharValue)());

    QStatus setGetValue(bool (*getBoolValue)());

    GetStringFptr getGetUnitOfMeasure() const;
    void setGetUnitOfMeasure(GetStringFptr getGetUnitOfMeasure);

    const std::vector<qcc::String>& getUnitOfMeasure() const;
    void setUnitOfMeasure(const std::vector<qcc::String>& label);

    const std::vector<ConstraintList>& getConstraintList() const;
    void setConstraintList(const std::vector<ConstraintList>& constraintList);

    const ConstraintRange* getConstraintRange() const;
    void setConstraintRange(ConstraintRange* constraintRange);

    QStatus getPropertyValueForArg(MsgArg& val, int16_t languageIndx);

    QStatus setPropertyValue(MsgArg& val, int16_t languageIndx);

    QStatus getOptParamsForArg(MsgArg& val, int16_t languageIndx);

    QStatus SendValueChangedSignal();

  private:

    PropertyType m_PropertyType;

    PropertyValue m_Value;

    std::vector<qcc::String> m_UnitOfMeasure;
    GetStringFptr m_GetUnitOfMeasure;

    std::vector<ConstraintList> m_ConstraintList;

    ConstraintRange* m_ConstraintRange;

    bool validateGetValue(PropertyType propertyType);

    virtual QStatus setValue(bool value);

    virtual QStatus setValue(uint16_t value);

    virtual QStatus setValue(int16_t value);

    virtual QStatus setValue(uint32_t value);

    virtual QStatus setValue(int32_t value);

    virtual QStatus setValue(uint64_t value);

    virtual QStatus setValue(int64_t value);

    virtual QStatus setValue(double value);

    virtual QStatus setValue(const char* value);

    QStatus defaultErrorSetValue();
};
} //namespace services
} //namespace ajn

#endif /* PROPERTY_H_ */
