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
 * The package includes classes that represent the UI widgets and its metadata<br>
 * The UI widget classes are used to receive the initial values that were set by the remotely controllable device. <br>
 * In addition these classes used to perform the remote control of the device.
 * For example: <br>
 * {@link org.alljoyn.ioe.controlpanelservice.ui.ActionWidget#exec()} is used to invoke an action 
 * on the remote device <br>
 * {@link org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget#setCurrentValue(Object)} is used to set a
 * new property value on the remote device <br>  
 * {@link org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget#getCurrentValue()} is used to receive the current
 * property value <br>
 * Each UI widget has its signal handler to be notified about the state changes in the remote device.
 * The user receives these notifications by implementing the {@link org.alljoyn.ioe.controlpanelservice.ui.ControlPanelEventsListener} interface <br>
 * The signal {@link org.alljoyn.ioe.controlpanelservice.ui.ControlPanelEventsListener#metadataChanged(DeviceControlPanel, UIElement)}
 * notifies about a possible change in a widget UI state. <br>
 * The method refreshProperties, i.e: {@link org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget#refreshProperties()}
 * is used to receive the updated state of a Property 
 */
package org.alljoyn.ioe.controlpanelservice.ui;
