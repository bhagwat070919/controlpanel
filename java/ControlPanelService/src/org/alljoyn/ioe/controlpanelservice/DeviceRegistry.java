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

import java.util.Map;

/**
 * Used as a callback interface to inform the interface implementer about new discovered devices
 * and changes in their reachability state
 */
public interface DeviceRegistry {
	
	/**
	 * Called when a new controllable device was found in the control panel service proximity <br>
	 * @param device
	 */
	public void foundNewDevice(ControllableDevice device);
	
	/**
	 * Called when a controllable device left the control panel service proximity <br>
	 * The method implementation should be thread safe 
	 * @param device The controllable device
	 * @param isReachable Whether the device is in reachable state
	 */
	public void reachabilityChanged(ControllableDevice device, boolean isReachable);
	
	/**
	 * Remove a device from registry <br>
	 * When a device is removed from the registry it will be inserted back after foundDevice method is called 
	 * @param device
	 */
	public void removeDevice(ControllableDevice device);
	
	/**
	 * @return Returns collection of controllable devices
	 */
	public Map<String, ControllableDevice> getDevices();
	
}
