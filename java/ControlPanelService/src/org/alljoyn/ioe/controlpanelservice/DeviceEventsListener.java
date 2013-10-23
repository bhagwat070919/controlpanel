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

package org.alljoyn.ioe.controlpanelservice;

import java.util.Collection;

import org.alljoyn.ioe.controlpanelservice.ui.DeviceControlPanel;

/**
 *  The interface to be implemented in order to receive {@link ControllableDevice} relevant events
 */
public interface DeviceEventsListener {
	
	/**
	 * Notify the interface implementer about session establishment with the remote device
	 * @param device The {@link ControllableDevice}
	 * @param controlPanelContainer Used to request the Root UI Container and a relevant to it information
	 * @see DeviceControlPanel 
	 */
	public void sessionEstablished(ControllableDevice device, Collection<ControlPanelCollection> controlPanelContainer);
	
	/**
	 * Notify the interface implementer about loosing session with the remote device
	 * @param device The {@link ControllableDevice} where the session has lost
	 */
	public void sessionLost(ControllableDevice device);
	
	/**
	 * Notify the interface implementer about an error in the device activities
	 * @param device The {@link ControllableDevice} where the error has occurred
	 * @param reason The error reason
	 */
	public void errorOccurred(ControllableDevice device, String reason);
}
