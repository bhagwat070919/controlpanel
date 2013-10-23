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

#include "alljoyn/controlpanel/ConstraintRange.h"
#include "alljoyn/controlpanel/ControlPanelService.h"
#include "../ControlPanelConstants.h"

namespace ajn {
namespace services {
using namespace cpsConsts;

#define TAG TAG_CONSTRAINTRANGE

ConstraintRange::ConstraintRange() : m_PropertyType(UNDEFINED)
{
    m_MinValue.uint16Value = 0;
    m_MaxValue.uint16Value = 0;
    m_IncrementValue.uint16Value = 0;
}

ConstraintRange::~ConstraintRange()
{
}

const ConstraintRangeVal& ConstraintRange::getIncrementValue() const
{
    return m_IncrementValue;
}

const ConstraintRangeVal& ConstraintRange::getMaxValue() const
{
    return m_MaxValue;
}

const ConstraintRangeVal& ConstraintRange::getMinValue() const
{
    return m_MinValue;
}

bool ConstraintRange::validateConstraintValue(PropertyType propertyType)
{
    if (m_PropertyType != propertyType && m_PropertyType != UNDEFINED) {
        GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
        if (logger)
            logger->warn(TAG, "Could not set Constraint Value. Value Type is wrong");
        return false;
    }
    m_PropertyType = propertyType;
    return true;
}

QStatus ConstraintRange::setConstraintMin(uint16_t minValue)
{
    if (!validateConstraintValue(UINT16_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_MinValue.uint16Value = minValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintMin(int16_t minValue)
{
    if (!validateConstraintValue(INT16_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_MinValue.int16Value = minValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintMin(uint32_t minValue)
{
    if (!validateConstraintValue(UINT32_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_MinValue.uint32Value = minValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintMin(int32_t minValue)
{
    if (!validateConstraintValue(INT32_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_MinValue.int32Value = minValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintMin(uint64_t minValue)
{
    if (!validateConstraintValue(UINT64_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_MinValue.uint64Value = minValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintMin(int64_t minValue)
{
    if (!validateConstraintValue(INT64_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_MinValue.int64Value = minValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintMin(double minValue)
{
    if (!validateConstraintValue(DOUBLE_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_MinValue.doubleValue = minValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintMax(uint16_t maxValue)
{
    if (!validateConstraintValue(UINT16_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_MaxValue.uint16Value = maxValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintMax(int16_t maxValue)
{
    if (!validateConstraintValue(INT16_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_MaxValue.int16Value = maxValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintMax(uint32_t maxValue)
{
    if (!validateConstraintValue(UINT32_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_MaxValue.uint32Value = maxValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintMax(int32_t maxValue)
{
    if (!validateConstraintValue(INT32_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_MaxValue.int32Value = maxValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintMax(uint64_t maxValue)
{
    if (!validateConstraintValue(UINT64_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_MaxValue.uint64Value = maxValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintMax(int64_t maxValue)
{
    if (!validateConstraintValue(INT64_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_MaxValue.int64Value = maxValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintMax(double maxValue)
{
    if (!validateConstraintValue(DOUBLE_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_MaxValue.doubleValue = maxValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintIncrement(uint16_t incrementValue)
{
    if (!validateConstraintValue(UINT16_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_IncrementValue.uint16Value = incrementValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintIncrement(int16_t incrementValue)
{
    if (!validateConstraintValue(INT16_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_IncrementValue.int16Value = incrementValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintIncrement(uint32_t incrementValue)
{
    if (!validateConstraintValue(UINT32_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_IncrementValue.uint32Value = incrementValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintIncrement(int32_t incrementValue)
{
    if (!validateConstraintValue(INT32_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_IncrementValue.int32Value = incrementValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintIncrement(uint64_t incrementValue)
{
    if (!validateConstraintValue(UINT64_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_IncrementValue.uint64Value = incrementValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintIncrement(int64_t incrementValue)
{
    if (!validateConstraintValue(INT64_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_IncrementValue.int64Value = incrementValue;
    return ER_OK;
}

QStatus ConstraintRange::setConstraintIncrement(double incrementValue)
{
    if (!validateConstraintValue(DOUBLE_PROPERTY))
        return ER_BUS_SET_WRONG_SIGNATURE;

    m_IncrementValue.doubleValue = incrementValue;
    return ER_OK;
}

QStatus ConstraintRange::fillConstraintArg(MsgArg& val, uint16_t languageIndx, PropertyType propertyType)
{
    if (m_PropertyType != propertyType)
        return ER_BUS_SIGNATURE_MISMATCH;

    QStatus status;

    MsgArg* minValue = new MsgArg();
    MsgArg* maxValue = new MsgArg();
    MsgArg* incrementValue = new MsgArg();

    switch (m_PropertyType) {
    case UINT16_PROPERTY:
        CHECK_AND_BREAK(minValue->Set(AJPARAM_UINT16.c_str(), m_MinValue.uint16Value));
        CHECK_AND_BREAK(maxValue->Set(AJPARAM_UINT16.c_str(), m_MaxValue.uint16Value));
        CHECK_AND_BREAK(incrementValue->Set(AJPARAM_UINT16.c_str(), m_IncrementValue.uint16Value));
        break;

    case INT16_PROPERTY:
        CHECK_AND_BREAK(minValue->Set(AJPARAM_INT16.c_str(), m_MinValue.int16Value));
        CHECK_AND_BREAK(maxValue->Set(AJPARAM_INT16.c_str(), m_MaxValue.int16Value));
        CHECK_AND_BREAK(incrementValue->Set(AJPARAM_INT16.c_str(), m_IncrementValue.int16Value));
        break;

    case UINT32_PROPERTY:
        CHECK_AND_BREAK(minValue->Set(AJPARAM_UINT32.c_str(), m_MinValue.uint32Value));
        CHECK_AND_BREAK(maxValue->Set(AJPARAM_UINT32.c_str(), m_MaxValue.uint32Value));
        CHECK_AND_BREAK(incrementValue->Set(AJPARAM_UINT32.c_str(), m_IncrementValue.uint32Value));
        break;

    case INT32_PROPERTY:
        CHECK_AND_BREAK(minValue->Set(AJPARAM_INT32.c_str(), m_MinValue.int32Value));
        CHECK_AND_BREAK(maxValue->Set(AJPARAM_INT32.c_str(), m_MaxValue.int32Value));
        CHECK_AND_BREAK(incrementValue->Set(AJPARAM_INT32.c_str(), m_IncrementValue.int32Value));
        break;

    case UINT64_PROPERTY:
        CHECK_AND_BREAK(minValue->Set(AJPARAM_UINT64.c_str(), m_MinValue.uint64Value));
        CHECK_AND_BREAK(maxValue->Set(AJPARAM_UINT64.c_str(), m_MaxValue.uint64Value));
        CHECK_AND_BREAK(incrementValue->Set(AJPARAM_UINT64.c_str(), m_IncrementValue.uint64Value));
        break;

    case INT64_PROPERTY:
        CHECK_AND_BREAK(minValue->Set(AJPARAM_INT64.c_str(), m_MinValue.int64Value));
        CHECK_AND_BREAK(maxValue->Set(AJPARAM_INT64.c_str(), m_MaxValue.int64Value));
        CHECK_AND_BREAK(incrementValue->Set(AJPARAM_INT64.c_str(), m_IncrementValue.int64Value));
        break;

    case DOUBLE_PROPERTY:
        CHECK_AND_BREAK(minValue->Set(AJPARAM_DOUBLE.c_str(), m_MinValue.doubleValue));
        CHECK_AND_BREAK(maxValue->Set(AJPARAM_DOUBLE.c_str(), m_MaxValue.doubleValue));
        CHECK_AND_BREAK(incrementValue->Set(AJPARAM_DOUBLE.c_str(), m_IncrementValue.doubleValue));
        break;

    default:
        status = ER_BUS_BAD_SIGNATURE;
        break;
    }

    if (status != ER_OK) {
        GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
        if (logger)
            logger->warn(TAG, "Could not marshal Constraint Range");
        delete minValue;
        delete maxValue;
        delete incrementValue;
        return status;
    }

    status = val.Set(AJPARAM_STRUCT_VAR_VAR_VAR.c_str(), minValue, maxValue, incrementValue);

    if (status != ER_OK) {
        GenericLogger* logger = ControlPanelService::getInstance()->getLogger();
        if (logger)
            logger->warn(TAG, "Could not marshal Constraint Range");
        delete minValue;
        delete maxValue;
        delete incrementValue;
        return status;
    }

    return status;
}

} /* namespace services */
} /* namespace ajn */
