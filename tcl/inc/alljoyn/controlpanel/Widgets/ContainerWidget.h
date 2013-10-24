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

#ifndef CONTAINERWIDGET_H_
#define CONTAINERWIDGET_H_

#include <alljoyn/controlpanel/Common/BaseWidget.h>

/////////////////////////*     ContainerWidget     *//////////////////////////////////////

typedef struct {
    BaseWidget base;
} ContainerWidget;

void initializeContainerWidget(ContainerWidget* widget);

#endif /* CONTAINERWIDGET_H_ */
