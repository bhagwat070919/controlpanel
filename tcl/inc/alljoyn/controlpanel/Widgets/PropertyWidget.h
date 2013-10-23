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

#ifndef PROPERTYWIDGET_H_
#define PROPERTYWIDGET_H_

#include "alljoyn/controlpanel/Common/BaseWidget.h"
#include "alljoyn/controlpanel/Widgets/ListPropertyWidget.h"

#include "alljoyn/controlpanel/Common/ConstraintList.h"
#include "alljoyn/controlpanel/Common/ConstraintRange.h"

typedef enum {
    SINGLE_VALUE_PROPERTY = 0,
    DATE_VALUE_PROPERTY = 1,
    TIME_VALUE_PROPERTY = 2,
} PropertyType;
/////////////////////////* PropertyWidget OptParams *//////////////////////////////////////

typedef struct {
    const char* const* unitOfMeasure;
    const char* (*getUnitOfMeasure)(uint16_t);

    ConstraintList* constraintList;
    uint16_t numConstraints;

    ConstraintRange constraintRange;
    uint8_t constraintRangeDefined;

} PropertyOptParams;

void initializePropertyOptParam(PropertyOptParams* widget);

/////////////////////////*     PropertyWidget     *//////////////////////////////////////

typedef struct PropertyWidget {
    BaseWidget base;
    PropertyType propertyType;

    const char* signature;
    void* (*getValue)();

    ListPropertyWidget* parentListProperty;

    PropertyOptParams optParams;

} PropertyWidget;

void initializePropertyWidget(PropertyWidget* widget);

AJ_Status marshalPropertyValue(PropertyWidget* widget, AJ_Message* reply, uint16_t language);

AJ_Status unmarshalPropertyValue(PropertyWidget* widget, AJ_Message* message, void* newValue, const char* lockerId);

AJ_Status marshalPropertyOptParam(BaseWidget* widget, AJ_Message* reply, uint16_t language);

AJ_Status marshalAllPropertyProperties(BaseWidget* widget, AJ_Message* reply, uint16_t language);

#endif /* PROPERTYWIDGET_H_ */
