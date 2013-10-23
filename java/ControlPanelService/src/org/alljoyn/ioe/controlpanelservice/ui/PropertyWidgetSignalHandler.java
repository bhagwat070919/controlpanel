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

import java.util.Map;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.ioe.controlpanelservice.ControlPanelException;
import org.alljoyn.ioe.controlpanelservice.communication.ConnectionManager;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.PropertyControl;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.PropertyControlSecured;

import android.util.Log;

/**
 * The class is a signal handler that is responsible to receive signals of PropertyControl interface. <br>
 *  Signals: <br>
 *  - ValueChanged    <br>
 *  - MetadataChanged
 */
public class PropertyWidgetSignalHandler implements PropertyControlSecured, PropertyControl {
	private static final String TAG = "cpan" + PropertyWidgetSignalHandler.class.getSimpleName();

	
	/**
	 * Property widget to be notified about signal receiving
	 */
	private PropertyWidget propertyWidget;

	/**
	 * @param propertyWidget
	 */
	public PropertyWidgetSignalHandler(PropertyWidget propertyWidget) {
		this.propertyWidget = propertyWidget;
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.PropertyControl#getVersion()
	 */
	@Override
	public short getVersion() throws BusException {
		return 0;
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.PropertyControl#getValue()
	 */
	@Override
	public Variant getValue() throws BusException {
		return null;
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.PropertyControl#setValue(org.alljoyn.bus.Variant)
	 */
	@Override
	public void setValue(Variant value) throws BusException {
	}


	@Override
	public int getStates() throws BusException {
		return 0;
	}

	@Override
	public Map<Short, Variant> getOptParams() throws BusException {
		return null;
	}
	

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.PropertyControl#ValueChanged(org.alljoyn.bus.Variant)
	 */
	@Override
	public void ValueChanged(Variant value) throws BusException {
	    ConnectionManager.getInstance().getBusAttachment().enableConcurrentCallbacks();
	    ControlPanelEventsListener eventsListener = propertyWidget.controlPanel.getEventsListener();
	    
	    String msg = "Device: '" + propertyWidget.device.getDeviceId() +
                "', PropertyWidget: '" + propertyWidget.objectPath + "', received VALUE_CHANGED signal";
    
	    Log.d(TAG, msg);
	    
	    try {
			Object unmarshVal = propertyWidget.unmarshalCurrentValue(value);
			Log.d(TAG, "The new property: '" + propertyWidget.objectPath + "' value is: '" + unmarshVal +  "'");
			eventsListener.valueChanged(propertyWidget.controlPanel, propertyWidget, unmarshVal);
		} catch (ControlPanelException cpe) {
			msg += ", but failed to unmarshal the received data, Error: '" + cpe.getMessage() + "'";
			Log.e(TAG, msg);
			eventsListener.errorOccured(propertyWidget.controlPanel, msg);
		}
	}//ValueChanged

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.PropertyControl#MetadataChanged()
	 */
	@Override
	public void MetadataChanged() throws BusException {
        ConnectionManager.getInstance().getBusAttachment().enableConcurrentCallbacks();
        
        String msg = "Device: '" + propertyWidget.device.getDeviceId() +
                "', PropertyWidget: '" + propertyWidget.objectPath + "', received METADATA_CHANGED signal";

        Log.d(TAG, msg);
        
        ControlPanelEventsListener eventsListener = propertyWidget.controlPanel.getEventsListener();
        
        try {
        	propertyWidget.refreshProperties();
        }
        catch(ControlPanelException cpe) {
        	 msg += ", but failed to refresh the widget properties";
        	 Log.e(TAG, msg);
             eventsListener.errorOccured(propertyWidget.controlPanel, msg);
             return;
        }
        
        eventsListener.metadataChanged(propertyWidget.controlPanel, propertyWidget);
	}//MetadataChanged
	
}
