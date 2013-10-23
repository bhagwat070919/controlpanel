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
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.Label;

import android.util.Log;

public class LabelWidgetSignalHandler implements Label {
    private static final String TAG = "cpan" + LabelWidgetSignalHandler.class.getSimpleName();
    
    /**
     * Container widget to be notified about signal receiving
     */
    private LabelWidget labelWidget;

    /**
     * Constructor
     * @param containerWidget
     */
    public LabelWidgetSignalHandler(LabelWidget labelWidget) {
        this.labelWidget = labelWidget;
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
	public String getLabel() throws BusException {
		// TODO Auto-generated method stub
		return null;
	}
	
	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.Label#MetadataChanged()
	 */
	@Override
	public void MetadataChanged() throws BusException {
        ConnectionManager.getInstance().getBusAttachment().enableConcurrentCallbacks();
        
        String msg = "Device: '" + labelWidget.device.getDeviceId() +
                "', labelWidget: '" + labelWidget.objectPath + "', received METADATA_CHANGED signal";

        Log.d(TAG, msg);

        ControlPanelEventsListener eventsListener = labelWidget.controlPanel.getEventsListener();
        try {
            labelWidget.refreshProperties();
        } catch (ControlPanelException cpe) {
            msg += ", but failed to refresh the LabelWidget properties";
            Log.e(TAG, msg);
            eventsListener.errorOccurred(labelWidget.controlPanel, msg);
            return;
        }

        eventsListener.metadataChanged(labelWidget.controlPanel, labelWidget);
	}//MetadataChanged

}
