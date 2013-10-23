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
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.ActionControl;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.ActionControlSecured;

import android.util.Log;

/**
 * The class is a signal handler that is responsible to receive signals of ActionControl interface. <br>
 *  Signals: <br>
 *  - MetadataChanged
 */
public class ActionWidgetSignalHandler implements ActionControl, ActionControlSecured {
	private static final String TAG = "cpan" + ActionWidgetSignalHandler.class.getSimpleName();

    /**
     * Container widget to be notified about signal receiving
     */
    private ActionWidget actionWidget;
	
	/**
	 * Constructor
	 * @param actionWidget
	 */
	public ActionWidgetSignalHandler(ActionWidget actionWidget) {
		this.actionWidget = actionWidget;
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ActionControl#getVersion()
	 */
	@Override
	public short getVersion() throws BusException {
		return 0;
	}

	@Override
	public int getStates() throws BusException {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public Map<Short, Variant> getOptParams() throws BusException {
		// TODO Auto-generated method stub
		return null;
	}	
	
	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ActionControl#Exec()
	 */
	@Override
	public void Exec() {
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ActionControl#MetadataChanged()
	 */
	@Override
	public void MetadataChanged() {
        ConnectionManager.getInstance().getBusAttachment().enableConcurrentCallbacks();
       
        String msg = "Device: '" + actionWidget.device.getDeviceId() +
                "', ActionWidget: '" + actionWidget.objectPath + "', received METADATA_CHANGED signal";
        
        Log.d(TAG, msg);
        
        ControlPanelEventsListener eventsListener = actionWidget.controlPanel.getEventsListener();
        try{
        	actionWidget.refreshProperties();
        }
        catch(ControlPanelException cpe) {
            msg += ", but failed to refresh the ActionWidget properties";
            Log.e(TAG, msg);
            eventsListener.errorOccured(actionWidget.controlPanel, msg);
            return;
        }

        eventsListener.metadataChanged(actionWidget.controlPanel, actionWidget);
	}//MetadataChanged

}
