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
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.Container;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.ContainerSecured;

import android.util.Log;

/**
 * The class is a signal handler that is responsible to receive signals of UIContainer interface. <br>
 *  Signals: <br>
 *  - MetadataChanged
 */
public class ContainerWidgetSignalHandler implements Container, ContainerSecured {
	private static final String TAG = "cpan" + ContainerWidgetSignalHandler.class.getSimpleName();
	
	
	/**
	 * Container widget to be notified about signal receiving
	 */
	private ContainerWidget containerWidget;
	
	/**
	 * Constructor
	 * @param containerWidget
	 */
	public ContainerWidgetSignalHandler(ContainerWidget containerWidget) {
		this.containerWidget = containerWidget;
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.Container#getVersion()
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
	 * Signal handler
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.Container#MetadataChanged()
	 */
	@Override
	public void MetadataChanged() throws BusException {
		ConnectionManager.getInstance().getBusAttachment().enableConcurrentCallbacks();
		
		String msg = "Device: '" + containerWidget.device.getDeviceId() + 
                "', ContainerWidget: '" + containerWidget.objectPath + "', received METADATA_CHANGED signal";
		
		Log.d(TAG, msg);
		
		ControlPanelEventsListener eventsListener = containerWidget.controlPanel.getEventsListener();
		try {
			containerWidget.refreshProperties();
		} catch (ControlPanelException cpe) {
			msg += ", but failed to refresh the Container properties";
			Log.e(TAG, msg);
			eventsListener.errorOccurred(containerWidget.controlPanel, msg);
			return;
		}
				
		eventsListener.metadataChanged(containerWidget.controlPanel, containerWidget);
	}//MetadataChanged

}
