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
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.ioe.controlpanelservice.ControlPanelService;
import org.alljoyn.ioe.controlpanelservice.ui.ajstruct.ListPropertyWidgetRecordAJ;

/**
 * List property interface 
 */
@BusInterface(name = ListPropertyControl.IFNAME)
public interface ListPropertyControl extends ListPropertyControlSuper {
	public static final String IFNAME = ControlPanelService.INTERFACE_PREFIX + ".ListProperty";
	
	public static final short VERSION = 1;
	
	/**
	 * @return Interface version
	 */
	@BusProperty(signature="q")
	public short getVersion() throws BusException;

	/**
	 * @return States bitmask 
	 * @throws BusException
	 */
	@BusProperty(signature="u")
	public int getStates() throws BusException; 

	/**
	 * @return Optional parameters
	 * @throws BusException
	 */
	@BusProperty(signature="a{qv}")
	public Map<Short,Variant> getOptParams() throws BusException;
	
	/**
	 * @return The array of list records
	 * @throws BusException
	 */
	@BusProperty(signature="a(qs)")
	public ListPropertyWidgetRecordAJ[] getValue() throws BusException;
	
	/**
	 * Prepare the input form for adding a new record to the list
	 * @throws BusException
	 */
	@BusMethod
	public void Add() throws BusException;
	
	/**
	 * Prepare the form for view the record prior to the delete action.
	 * @param recordId
	 * @throws BusException
	 */
	@BusMethod(signature = "q")
	public void Delete(short recordId) throws BusException;
	
	/**
	 * Prepare the display form to view the record identified by the recordID.
	 * @param recordId
	 * @throws BusException
	 */
	@BusMethod(signature = "q")
	public void View(short recordId) throws BusException;
	
	/**
	 * Prepare the input form to view the record identified by the recordID and allow the end-user to modify the fields.
	 * @param recordId
	 * @throws BusException
	 */
	@BusMethod(signature = "q")
	public void Update(short recordId) throws BusException;
	
	/**
	 * Confirm the action and save the change requested
	 * @throws BusException
	 */
	@BusMethod
	public void Confirm() throws BusException;
	
	/**
	 * Cancel the current action
	 * @throws BusException
	 */
	@BusMethod
	public void Cancel() throws BusException;
	
	/**
	 * The signal is sent when a list property value has changed, i.e. a record was added or removed from the records list
	 * @throws BusException
	 */
	@BusSignal
	public void ValueChanged() throws BusException;
	
	/**
	 * The signal is sent when there is a change in the list property metadata
	 * @throws BusException
	 */
	@BusSignal
	public void MetadataChanged() throws BusException;
}
