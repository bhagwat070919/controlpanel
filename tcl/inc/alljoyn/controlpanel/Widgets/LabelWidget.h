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

#ifndef LABELWIDGET_H_
#define LABELWIDGET_H_

#include <alljoyn/controlpanel/Common/BaseWidget.h>

/////////////////////////*     LabelWidget     *//////////////////////////////////////

typedef struct {
    BaseWidget base;

    const char* const* label;
    const char* (*getLabel)(uint16_t);
} LabelWidget;

void initializeLabelWidget(LabelWidget* widget);

AJ_Status marshalLabelLabel(LabelWidget* widget, AJ_Message* reply, uint16_t language);

AJ_Status marshalAllLabelProperties(BaseWidget* widget, AJ_Message* reply, uint16_t language);

#endif /* LABELWIDGET_H_ */

