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

package org.alljoyn.ioe.controlpanelservice.communication.interfaces;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.ioe.controlpanelservice.ControlPanelService;

/**
 * This interface indicates whether the object is a notification action object
 */
@BusInterface (name = NotificationAction.IFNAME)
public interface NotificationAction {
	public static final String IFNAME  = ControlPanelService.INTERFACE_PREFIX + ".NotificationAction"; 

	public static final int ID_MASK    = 0x04;
	
	public static final short  VERSION = 1;
	
	/**
	 * @return Interface version
	 */
	@BusProperty(signature="q")
	public short getVersion() throws BusException;
	
	/**
	 * The controller needs to dismiss this NotificationAction panel
	 */
	@BusSignal
	public void Dismiss() throws BusException;
	
}
