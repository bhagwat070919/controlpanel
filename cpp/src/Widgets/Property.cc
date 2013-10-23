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

#include "alljoyn/controlpanel/Property.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "../ControlPanelConstants.h"
#include "../BusObjects/PropertyBusObject.h"

namespace ajn {
namespace services {
using namespace cpsConsts;

Property::Property(qcc::String name, PropertyType propertyType) : Widget(name, TAG_PROPERTY_WIDGET),
    m_PropertyType(propertyType), m_GetUnitOfMeasure(0), m_ConstraintRange(0)
{
    m_GetValue.getBoolValue = 0; // initialize to null
}

Property::~Property()
{
}

WidgetBusObject* Property::createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                                 uint16_t langIndx, QStatus& status)
{
    return new PropertyBusObject(bus, objectPath, langIndx, status, this);
}

const std::vector<qcc::String>& Property::getUnitOfMeasure() const
{
    return m_UnitOfMeasure;
}

void Property::setUnitOfMeasure(const std::vector<qcc::String>& unitOfMeasure)
{
    m_UnitOfMeasure = unitOfMeasure;
}

GetStringFptr Property::getGetUnitOfMeasure() const
{
    return m_GetUnitOfMeasure;
}

void Property::setGetUnitOfMeasure(GetStringFptr getUnitOfMeasure)
{
    m_GetUnitOfMeasure = getUnitOfMeasure;
}

const std::vector<ConstraintList>& Property::getConstraintList() const
{
    return m_ConstraintList;
}

void Property::setConstraintList(const std::vector<ConstraintList>& constraintList)
{
    m_ConstraintList = constraintList;
}

const ConstraintRange* Property::getConstraintRange() const
{
    return m_ConstraintRange;
}

void Property::setConstraintRange(ConstraintRange* constraintRange)
{
    m_ConstraintRange = constraintRange;
}

bool Property::validateGetValue(PropertyType propertyType)
{
    if (m_PropertyType != propertyType) {
        GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
        if (logger)
            logger->warn(TAG, "Could not set GetValue. Value Type is wrong");
        return false;
    }
    return true;
}

QStatus Property::setGetValue(uint16_t (*getUint16Value)())
{
    if (!validateGetValue(UINT16_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_GetValue.getUint16Value = getUint16Value;
    return ER_OK;
}

QStatus Property::setGetValue(int16_t (*getInt16Value)())
{
    if (!validateGetValue(INT16_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_GetValue.getInt16Value = getInt16Value;
    return ER_OK;
}

QStatus Property::setGetValue(uint32_t (*getUint32Value)())
{
    if (!validateGetValue(UINT32_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_GetValue.getUint32Value = getUint32Value;
    return ER_OK;
}

QStatus Property::setGetValue(int32_t (*getInt32Value)())
{
    if (!validateGetValue(INT32_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_GetValue.getInt32Value = getInt32Value;
    return ER_OK;
}

QStatus Property::setGetValue(uint64_t (*getUint64Value)())
{
    if (!validateGetValue(UINT64_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_GetValue.getUint64Value = getUint64Value;
    return ER_OK;
}

QStatus Property::setGetValue(int64_t (*getInt64Value)())
{
    if (!validateGetValue(INT64_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_GetValue.getInt64Value = getInt64Value;
    return ER_OK;
}

QStatus Property::setGetValue(double (*getDoubleValue)())
{
    if (!validateGetValue(DOUBLE_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_GetValue.getDoubleValue = getDoubleValue;
    return ER_OK;
}

QStatus Property::setGetValue(const char* (*getCharValue)())
{
    if (!validateGetValue(STRING_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_GetValue.getCharValue = getCharValue;
    return ER_OK;
}

QStatus Property::setGetValue(bool (*getBoolValue)())
{
    if (!validateGetValue(BOOL_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_GetValue.getBoolValue = getBoolValue;
    return ER_OK;
}

QStatus Property::setGetValue(const CPSDate& (*getDateValue)())
{
    if (!validateGetValue(DATE_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_GetValue.getDateValue = getDateValue;
    return ER_OK;
}

QStatus Property::setGetValue(const CPSTime& (*getTimeValue)())
{
    if (!validateGetValue(TIME_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_GetValue.getTimeValue = getTimeValue;
    return ER_OK;
}

QStatus Property::fillPropertyValueArg(MsgArg& val, uint16_t languageIndx)
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    QStatus status = ER_BUS_NO_SUCH_PROPERTY;

    if (!m_GetValue.getBoolValue) {
        if (logger)
            logger->warn(TAG, "GetValue is not defined");
        return status;
    }

    switch (m_PropertyType) {
    case UINT16_PROPERTY:
        status = val.Set(AJPARAM_VAR.c_str(), new MsgArg(AJPARAM_UINT16.c_str(), m_GetValue.getUint16Value()));
        break;

    case INT16_PROPERTY:
        status = val.Set(AJPARAM_VAR.c_str(), new MsgArg(AJPARAM_INT16.c_str(), m_GetValue.getInt16Value()));
        break;

    case UINT32_PROPERTY:
        status = val.Set(AJPARAM_VAR.c_str(), new MsgArg(AJPARAM_UINT32.c_str(), m_GetValue.getUint32Value()));
        break;

    case INT32_PROPERTY:
        status = val.Set(AJPARAM_VAR.c_str(), new MsgArg(AJPARAM_INT32.c_str(), m_GetValue.getInt32Value()));
        break;

    case UINT64_PROPERTY:
        status = val.Set(AJPARAM_VAR.c_str(), new MsgArg(AJPARAM_UINT64.c_str(), m_GetValue.getUint64Value()));
        break;

    case INT64_PROPERTY:
        status = val.Set(AJPARAM_VAR.c_str(), new MsgArg(AJPARAM_INT64.c_str(), m_GetValue.getInt64Value()));
        break;

    case DOUBLE_PROPERTY:
        status = val.Set(AJPARAM_VAR.c_str(), new MsgArg(AJPARAM_DOUBLE.c_str(), m_GetValue.getDoubleValue()));
        break;

    case STRING_PROPERTY:
        status = val.Set(AJPARAM_VAR.c_str(), new MsgArg(AJPARAM_STR.c_str(), m_GetValue.getCharValue()));
        break;

    case BOOL_PROPERTY:
        status = val.Set(AJPARAM_VAR.c_str(), new MsgArg(AJPARAM_BOOL.c_str(), m_GetValue.getBoolValue()));
        break;

    case DATE_PROPERTY: {
        CPSDate date = m_GetValue.getDateValue();
        status = val.Set(AJPARAM_VAR.c_str(), new MsgArg(AJPARAM_DATE_OR_TIME.c_str(), DATE_PROPERTY_TYPE,
                                                         date.getDay(), date.getMonth(), date.getYear()));
        break;
    }

    case TIME_PROPERTY: {
        CPSTime time = m_GetValue.getTimeValue();
        status = val.Set(AJPARAM_VAR.c_str(), new MsgArg(AJPARAM_DATE_OR_TIME.c_str(), TIME_PROPERTY_TYPE,
                                                         time.getHour(), time.getMinute(), time.getSecond()));
        break;
    }

    case UNDEFINED:
        if (logger)
            logger->warn(TAG, "Property type is not defined");
        break;
    }
    return status;
}

QStatus Property::fillOptParamsArg(MsgArg& val, uint16_t languageIndx)
{
    QStatus status;
    MsgArg* optParams = new MsgArg[OPT_PARAM_KEYS::NUM_OPT_PARAMS];

    size_t optParamIndx = 0;

    status = Widget::fillOptParamsArg(optParams, languageIndx, optParamIndx);
    if (status != ER_OK) {
        GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
        if (logger)
            logger->warn(TAG, "Could not marshal optParams");
        delete[] optParams;
        return status;
    }

    if (m_UnitOfMeasure.size() > languageIndx || m_GetUnitOfMeasure) {
        MsgArg* unitMeasureArg = new MsgArg(AJPARAM_STR.c_str(), m_GetUnitOfMeasure ?
                                            m_GetUnitOfMeasure(languageIndx) : m_UnitOfMeasure[languageIndx].c_str());

        if ((status = optParams[optParamIndx].Set(AJPARAM_DICT_UINT16_VAR.c_str(),
                                                  OPT_PARAM_KEYS::UNIT_MEASURE, unitMeasureArg)) != ER_OK) {
            delete unitMeasureArg;
            delete[] optParams;
            return status;
        }
        optParams[optParamIndx++].SetOwnershipFlags(MsgArg::OwnsArgs, true);
    }

    if (m_ConstraintList.size()) {

        MsgArg* constraintListArrayArg = new MsgArg[m_ConstraintList.size()];
        for (uint16_t indx = 0; indx < m_ConstraintList.size(); indx++) {
            status = m_ConstraintList[indx].fillConstraintArg(constraintListArrayArg[indx], languageIndx, m_PropertyType);
            if (status != ER_OK)
                break;
        }

        if (status != ER_OK) {
            delete[] constraintListArrayArg;
            delete[] optParams;
            return status;
        }

        MsgArg* constraintListArg = new MsgArg(AJPARAM_ARRAY_STRUCT_VAR_STR.c_str(),
                                               m_ConstraintList.size(), constraintListArrayArg);

        if ((status = optParams[optParamIndx].Set(AJPARAM_DICT_UINT16_VAR.c_str(),
                                                  OPT_PARAM_KEYS::CONSTRAINT_LIST, constraintListArg)) != ER_OK) {
            delete constraintListArrayArg;
            delete constraintListArg;
            delete[] optParams;
            return status;
        }
        optParams[optParamIndx++].SetOwnershipFlags(MsgArg::OwnsArgs, true);
    }

    if (m_ConstraintRange) {

        MsgArg* constraintRangeArg = new MsgArg();
        status = m_ConstraintRange->fillConstraintArg(*constraintRangeArg, languageIndx, m_PropertyType);

        if (status != ER_OK) {
            delete constraintRangeArg;
            delete[] optParams;
            return status;
        }

        if ((status = optParams[optParamIndx].Set(AJPARAM_DICT_UINT16_VAR.c_str(),
                                                  OPT_PARAM_KEYS::CONSTRAINT_RANGE, constraintRangeArg)) != ER_OK) {
            delete constraintRangeArg;
            delete[] optParams;
            return status;
        }
        optParams[optParamIndx++].SetOwnershipFlags(MsgArg::OwnsArgs, true);
    }

    return val.Set(AJPARAM_ARRAY_DICT_UINT16_VAR.c_str(), optParamIndx, optParams);
}

QStatus Property::setPropertyValue(MsgArg& val, uint16_t languageIndx)
{
    QStatus status;

    switch (m_PropertyType) {
    case UINT16_PROPERTY:
    {
        uint16_t value;
        CHECK_AND_RETURN(val.Get(AJPARAM_UINT16.c_str(), &value));
        CHECK_AND_RETURN(setValue(value));
        break;
    }

    case INT16_PROPERTY:
    {
        int16_t value;
        CHECK_AND_RETURN(val.Get(AJPARAM_INT16.c_str(), &value));
        CHECK_AND_RETURN(setValue(value));
        break;
    }

    case UINT32_PROPERTY:
    {
        uint32_t value;
        CHECK_AND_RETURN(val.Get(AJPARAM_UINT32.c_str(), &value));
        CHECK_AND_RETURN(setValue(value));
        break;
    }

    case INT32_PROPERTY:
    {
        int32_t value;
        CHECK_AND_RETURN(val.Get(AJPARAM_INT32.c_str(), &value));
        CHECK_AND_RETURN(setValue(value));
        break;
    }

    case UINT64_PROPERTY:
    {
        uint64_t value;
        CHECK_AND_RETURN(val.Get(AJPARAM_UINT64.c_str(), &value));
        CHECK_AND_RETURN(setValue(value));
        break;
    }

    case INT64_PROPERTY:
    {
        int64_t value;
        CHECK_AND_RETURN(val.Get(AJPARAM_INT64.c_str(), &value));
        CHECK_AND_RETURN(setValue(value));
        break;
    }

    case DOUBLE_PROPERTY:
    {
        double value;
        CHECK_AND_RETURN(val.Get(AJPARAM_DOUBLE.c_str(), &value));
        CHECK_AND_RETURN(setValue(value));
        break;
    }

    case STRING_PROPERTY:
    {
        char* value;
        CHECK_AND_RETURN(val.Get(AJPARAM_STR.c_str(), &value));
        CHECK_AND_RETURN(setValue(value));
        break;
    }

    case BOOL_PROPERTY:
    {
        bool value;
        CHECK_AND_RETURN(val.Get(AJPARAM_BOOL.c_str(), &value));
        CHECK_AND_RETURN(setValue(value));
        break;
    }

    case DATE_PROPERTY:
    {
        uint16_t type;
        uint16_t day;
        uint16_t month;
        uint16_t year;
        CHECK_AND_RETURN(val.Get(AJPARAM_DATE_OR_TIME.c_str(), &type, &day, &month, &year));

        if (type != DATE_PROPERTY_TYPE) {
            GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
            if (logger)
                logger->warn(TAG, "Did not receive the DateProperty type as expected");
            return ER_BUS_SIGNATURE_MISMATCH;
        }

        CPSDate value(day, month, year);
        CHECK_AND_RETURN(setValue(value));
        break;
    }

    case TIME_PROPERTY:
    {
        uint16_t type;
        uint16_t hour;
        uint16_t minute;
        uint16_t second;
        CHECK_AND_RETURN(val.Get(AJPARAM_DATE_OR_TIME.c_str(), &type, &hour, &minute, &second));

        if (type != TIME_PROPERTY_TYPE) {
            GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
            if (logger)
                logger->warn(TAG, "Did not receive the TimeProperty type as expected");
            return ER_BUS_SIGNATURE_MISMATCH;
        }

        CPSTime value(hour, minute, second);
        CHECK_AND_RETURN(setValue(value));
        break;
    }

    default:
        status = ER_BUS_NO_SUCH_PROPERTY;
        break;
    }

    if (status == ER_OK) {
        status = SendValueChangedSignal();
    }

    return status;
}

QStatus Property::SendValueChangedSignal()
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    QStatus status;

    for (size_t indx = 0; indx < m_BusObjects.size(); indx++) {
        status = ((PropertyBusObject*)m_BusObjects[indx])->SendValueChangedSignal();
        if (status != ER_OK) {
            if (logger)
                logger->warn(TAG, "Could not send Value Changed Signal");
            return status;
        }
    }
    return status;
}

QStatus Property::defaultErrorSetValue()
{
    GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
    if (logger)
        logger->warn(TAG, "setValue function not defined");
    return ER_FAIL;
}

QStatus Property::setValue(bool value)
{
    return defaultErrorSetValue();
}

QStatus Property::setValue(uint16_t value)
{
    return defaultErrorSetValue();
}

QStatus Property::setValue(int16_t value)
{
    return defaultErrorSetValue();
}

QStatus Property::setValue(uint32_t value)
{
    return defaultErrorSetValue();
}

QStatus Property::setValue(int32_t value)
{
    return defaultErrorSetValue();
}

QStatus Property::setValue(uint64_t value)
{
    return defaultErrorSetValue();
}

QStatus Property::setValue(int64_t value)
{
    return defaultErrorSetValue();
}

QStatus Property::setValue(double value)
{
    return defaultErrorSetValue();
}

QStatus Property::setValue(const char* value)
{
    return defaultErrorSetValue();
}

QStatus Property::setValue(const CPSDate& value)
{
    return defaultErrorSetValue();
}

QStatus Property::setValue(const CPSTime& value)
{
    return defaultErrorSetValue();
}

} /* namespace services */
} /* namespace ajn */
