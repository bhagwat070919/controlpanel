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
 * ControlPanelInterfaces.h
 *
 *  Created on: May 26, 2013
 */

#ifndef CONTROLPANELINTERFACES_H_
#define CONTROLPANELINTERFACES_H_

#include "alljoyn.h"
#include "aj_msg.h"

/**
 * The Description of the root Interfaces, ControlPanel and NotificationAction
 */
extern const AJ_InterfaceDescription ControlPanelInterfaces[];
extern const AJ_InterfaceDescription NotificationActionInterfaces[];

/**
 * The Description of the PropertyInterface
 */
extern const AJ_InterfaceDescription PropertyInterfaces[];
extern const AJ_InterfaceDescription SecuredPropertyInterfaces[];

/**
 * The Description of the ActionInterface
 */
extern const AJ_InterfaceDescription ActionInterfaces[];
extern const AJ_InterfaceDescription SecuredActionInterfaces[];

/**
 * The Description of the ContainerInterface
 */
extern const AJ_InterfaceDescription ContainerInterfaces[];
extern const AJ_InterfaceDescription SecuredContainerInterfaces[];

/**
 * The Description of the LabelInterface
 */
extern const AJ_InterfaceDescription LabelPropertyInterfaces[];

/**
 * The Description of the DialogInterface
 */
extern const AJ_InterfaceDescription DialogInterfaces[];
extern const AJ_InterfaceDescription SecuredDialogInterfaces[];

/**
 * The Description of the HttpControlInterfaces
 */
extern const AJ_InterfaceDescription HttpControlInterfaces[];

/**
 * The Description of the ListPropertyInterface
 */
extern const AJ_InterfaceDescription ListPropertyInterfaces[];
extern const AJ_InterfaceDescription SecuredListPropertyInterfaces[];

#endif /* CONTROLPANELINTERFACES_H_ */
