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

import java.util.Map;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;

/**
 * The parent interface of the {@link ActionControl} and {@link ActionControlSecured} interfaces
 */
public interface ActionControlSuper {
	
	/**
	 * @return Interface version
	 */
	public short getVersion() throws BusException;

	/**
	 * @return States bitmask 
	 * @throws BusException
	 */
	public int getStates() throws BusException;
	
	/**
	 * @return Optional parameters
	 * @throws BusException
	 */
	public Map<Short,Variant> getOptParams() throws BusException;
	
	/**
	 * Called when the action is executed on the widget
	 */
	public void Exec() throws BusException;
	
    /**
	 * Signal is sent when the UI container metadata changed 
	 * @param metadata
	 */
	public void MetadataChanged() throws BusException;

}
