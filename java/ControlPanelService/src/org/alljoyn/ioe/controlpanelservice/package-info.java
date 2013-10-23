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
/**
 * The package includes classes that allow to start the control panel service {@link org.alljoyn.ioe.controlpanelservice.ControlPanelService}, 
 * and manage the list of controllable devices {@link org.alljoyn.ioe.controlpanelservice.ControllableDevice}. <br>
 * The list of controllable devices is managed by the {@link org.alljoyn.ioe.controlpanelservice.DeviceRegistry} interface
 * and its default implementation {@link org.alljoyn.ioe.controlpanelservice.DefaultDeviceRegistry} <br>  
 * For each controllable device there is a list of the device control panels {@link org.alljoyn.ioe.controlpanelservice.ui.DeviceControlPanel}
 * that is passed to the user when {@link org.alljoyn.ioe.controlpanelservice.ControllableDevice#startSession(DeviceEventsListener)}
 * is called. By using the {@link org.alljoyn.ioe.controlpanelservice.ui.DeviceControlPanel} a user may call
 * {@link org.alljoyn.ioe.controlpanelservice.ui.DeviceControlPanel#getRootContainer(String)} to retrieve the root
 * UI container
 */
package org.alljoyn.ioe.controlpanelservice;
