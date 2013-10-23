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
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.AlertDialog;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.AlertDialogSecured;

import android.util.Log;

public class AlertDialogWidgetSignalHandler implements AlertDialog, AlertDialogSecured {
    private static final String TAG = "cpan" + AlertDialogWidgetSignalHandler.class.getSimpleName();
	
    /**
     * AlertDialog to be notified about signal receiving
     */
    private AlertDialogWidget alertDialog;
	
	/**
	 * @param alertDialog
	 */
	public AlertDialogWidgetSignalHandler(AlertDialogWidget alertDialog) {
		this.alertDialog = alertDialog;
	}

	@Override
	public short getVersion() throws BusException {
		// TODO Auto-generated method stub
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

	@Override
	public String getMessage() throws BusException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public short getNumActions() throws BusException {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public void Action1() throws BusException {
		// TODO Auto-generated method stub

	}

	@Override
	public void Action2() throws BusException {
		// TODO Auto-generated method stub

	}

	@Override
	public void Action3()  throws BusException {
		// TODO Auto-generated method stub

	}

	/**
	 * Signal handler
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.AlertDialog#MetadataChanged()
	 */
	@Override
	public void MetadataChanged() throws BusException {
        ConnectionManager.getInstance().getBusAttachment().enableConcurrentCallbacks();
       
        String msg = "Device: '" + alertDialog.device.getDeviceId() +
                 "', AlertDialogWidget: '" + alertDialog.objectPath + "', received METADATA_CHANGED signal";
                     
        Log.d(TAG, msg);
             
        ControlPanelEventsListener eventsListener = alertDialog.controlPanel.getEventsListener();
        try {
            alertDialog.refreshProperties();
        } catch (ControlPanelException cpe) {
            msg += ", but failed to refresh the Container properties";
            Log.e(TAG, msg);
            eventsListener.errorOccurred(alertDialog.controlPanel, msg);
            return;
        }       
              
        eventsListener.metadataChanged(alertDialog.controlPanel, alertDialog);
	}//MetadataChanged

}
