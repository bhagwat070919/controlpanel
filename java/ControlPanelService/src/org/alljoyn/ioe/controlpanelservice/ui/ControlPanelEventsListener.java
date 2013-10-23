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

package org.alljoyn.ioe.controlpanelservice.ui;


/**
 *  The interface to be implemented in order to receive {@link DeviceControlPanel} relevant events
 */
public interface ControlPanelEventsListener {
	
	/**
	 * Notify the interface implementer about the changed value in the {@link UIElement}
	 * @param panel {@link DeviceControlPanel} where the value has changed
	 * @param uielement The {@link UIElement} where the change has occurred
	 * @param newValue The new value
	 */
	public void valueChanged(DeviceControlPanel panel, UIElement uielement, Object newValue);
	
	/**
	 * Notify the interface implementer about the metadata changed in the {@link UIElement}
	 * @param panel {@link DeviceControlPanel} where the metadata has changed
	 * @param uielement The {@link UIElement} where the change has occurred
	 */
	public void metadataChanged(DeviceControlPanel panel, UIElement uielement);
	
	/**
	 * Dismiss the NotificationAction of the given {@link DeviceControlPanel} 
	 * @param panel The NotificationAction control panel to dismissed
	 */
	public void notificationActionDismiss(DeviceControlPanel panel);
	
	/**
	 * Notify the interface implementer about an error in the {@link DeviceControlPanel} activities
	 * @param panel {@link DeviceControlPanel} where the error has occurred
	 * @param reason The error reason
	 */
	public void errorOccured(DeviceControlPanel panel, String reason);
	
}
