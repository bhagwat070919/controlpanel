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
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.ioe.controlpanelservice.ControlPanelService;

/**
 * HTTPControl interface 
 */
@BusInterface (name = HTTPControl.IFNAME)
public interface HTTPControl {
	public static final String IFNAME  = ControlPanelService.INTERFACE_PREFIX + ".HTTPControl"; 
	
	public static final int ID_MASK    = 0x02;
	
	public static final short  VERSION = 1;
	
	/**
	 * @return Interface version
	 */
	@BusProperty(signature="q")
	public short getVersion() throws BusException;
	
	/**
	 * @return Retrieve the URL of the home page
	 * @throws BusException
	 */
	@BusMethod
	public String GetRootURL() throws BusException;
	
}
