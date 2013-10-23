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

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import android.util.Log;

/**
 * The default implementation of the DeviceRegistry interface. <br>
 * Inherit this class in order to be notified about changes in the {@link DeviceRegistry}.  
 */
public class DefaultDeviceRegistry implements DeviceRegistry {
	private static final String TAG = "cpan" + DefaultDeviceRegistry.class.getSimpleName();
	
	/**
	 * The devices that in the proximity and may be controlled
	 */
	private Map<String, ControllableDevice> controllableDevices;
	
	/**
	 * Constructor
	 */
	public DefaultDeviceRegistry() {
		controllableDevices = new HashMap<String, ControllableDevice>();
	}

	/**
	 * Adds the device to the registry
	 * @see org.alljoyn.ioe.controlpanelservice.DeviceRegistry#foundNewDevice(org.alljoyn.ioe.controlpanelservice.ControllableDevice)
	 */
	@Override
	public void foundNewDevice(ControllableDevice device) {
		controllableDevices.put(device.getDeviceId(), device);
		Log.d(TAG, "Added device, deviceId: '" + device.getDeviceId() + "'");
	}

	/**
	 * Mark the device as not active
	 * @see org.alljoyn.ioe.controlpanelservice.DeviceRegistry#reachabilityChanged(org.alljoyn.ioe.controlpanelservice.ControllableDevice, boolean)
	 */
	@Override
	public void reachabilityChanged(ControllableDevice device, boolean isReachable) {
		Log.d(TAG, "ReachabilityChanged for device: '" + device.getDeviceId() + "' the device isReachable: '" + isReachable + "'");
	}

	/**
	 * Removes the device from the registry
	 * @see org.alljoyn.ioe.controlpanelservice.DeviceRegistry#removeDevice(org.alljoyn.ioe.controlpanelservice.ControllableDevice)
	 */
	@Override
	public void removeDevice(ControllableDevice device) {
		Log.d(TAG, "Remove device called, deviceId: '" + device.getDeviceId() + "', cancelFindAdvertise name and remove the device from the registry");
		device.stopDeviceActivities();
		controllableDevices.remove(device.getDeviceId());
	}

	/**
	 * Returns the devices list
	 * @see org.alljoyn.ioe.controlpanelservice.DeviceRegistry#getDevices()
	 */
	@Override
	public Map<String, ControllableDevice> getDevices() {
		return Collections.unmodifiableMap(controllableDevices);
	}

}//DefaultDeviceRegistry
