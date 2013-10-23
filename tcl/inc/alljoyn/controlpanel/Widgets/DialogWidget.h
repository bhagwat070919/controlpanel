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

#ifndef DIALOGWIDGET_H_
#define DIALOGWIDGET_H_

#include "alljoyn/controlpanel/Common/BaseWidget.h"

/////////////////////////* DialogWidget OptParams *//////////////////////////////////////

typedef struct {
    const char* const* labelAction1;
    const char* (*getLabelAction1)(uint16_t);
    const char* const* labelAction2;
    const char* (*getLabelAction2)(uint16_t);
    const char* const* labelAction3;
    const char* (*getLabelAction3)(uint16_t);

} DialogOptParams;

void initializeDialogOptParam(DialogOptParams* optParam);

/////////////////////////*     DialogWidget     *//////////////////////////////////////

typedef struct {
    BaseWidget base;
    const char* const* message;
    const char* (*getMessage)(uint16_t);
    uint16_t numActions;

    DialogOptParams optParams;

} DialogWidget;

void initializeDialogWidget(DialogWidget* widget);

AJ_Status marshalDialogMessage(DialogWidget* widget, AJ_Message* reply, uint16_t language);

AJ_Status marshalDialogNumActions(DialogWidget* widget, AJ_Message* reply, uint16_t language);

AJ_Status marshalDialogOptParam(BaseWidget* widget, AJ_Message* reply, uint16_t language);

AJ_Status marshalAllDialogProperties(BaseWidget* widget, AJ_Message* reply, uint16_t language);

#endif /* DIALOGWIDGET_H_ */

