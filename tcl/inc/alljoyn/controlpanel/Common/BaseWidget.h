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
/*
 * BaseWidget.h
 *
 *  Created on: May 28, 2013
 */

#ifndef BASEWIDGET_H_
#define BASEWIDGET_H_

#include "alljoyn.h"
#include "aj_msg.h"

#ifndef UINT32_MAX
#define UINT32_MAX      (4294967295U)
#endif

/////////////////////////* BaseWidget OptParams *//////////////////////////////////////

typedef struct {
    const char* const* label;
    const char* (*getLabel)(uint16_t);

    uint32_t bgColor;
    uint32_t (*getBgColor)();

    uint16_t numHints;
    const uint16_t* hints;

} BaseOptParams;

void initializeBaseOptParam(BaseOptParams* optParam);

/////////////////////////*     BaseWidget     *//////////////////////////////////////

struct BaseWidget;
typedef AJ_Status (*MarshalWidgetFptr)(struct BaseWidget*, AJ_Message*, uint16_t language);

typedef struct BaseWidget {
	uint16_t interfaceVersion;
    uint32_t states;
    uint8_t (*getEnabled)();
    uint8_t (*getWritable)();

    uint16_t numLanguages;
    BaseOptParams optParams;

    MarshalWidgetFptr marshalVersion;
    MarshalWidgetFptr marshalStates;
    MarshalWidgetFptr marshalOptParam;
    MarshalWidgetFptr marshalAllProp;

} BaseWidget;

void initializeBaseWidget(BaseWidget* widget);

void setBaseEnabled(BaseWidget* widget, uint8_t enabled);

void setBaseWritable(BaseWidget* widget, uint8_t writeable);

AJ_Status marshalBaseVersion(BaseWidget* widget, AJ_Message* reply, uint16_t language);

AJ_Status marshalBaseStates(BaseWidget* widget, AJ_Message* reply, uint16_t language);

AJ_Status marshalOnlyBaseOptParam(BaseWidget* widget, AJ_Message* reply, uint16_t language);

AJ_Status marshalBaseOptParam(BaseWidget* widget, AJ_Message* reply, uint16_t language);

AJ_Status marshalAllBaseProperties(BaseWidget* widget, AJ_Message* reply, uint16_t language);

AJ_Status marshalAllOnlyBaseProperties(BaseWidget* widget, AJ_Message* reply, uint16_t language);

#endif /* BASEWIDGET_H_ */
