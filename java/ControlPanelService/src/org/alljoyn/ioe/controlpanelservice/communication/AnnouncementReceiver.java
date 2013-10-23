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
package org.alljoyn.ioe.controlpanelservice.communication;

import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

import org.alljoyn.about.AboutKeys;
import org.alljoyn.services.common.AnnouncementHandler;
import org.alljoyn.services.common.BusObjectDescription;

import android.os.Handler;
import android.os.Message;
import android.util.Log;

/**
 * Receives announcement signals
 */
public class AnnouncementReceiver implements AnnouncementHandler {
	private static final String TAG = "cpan" + AnnouncementReceiver.class.getSimpleName();
	

    /**
     * @see org.alljoyn.services.common.AnnouncementHandler#onAnnouncement(java.lang.String, short, org.alljoyn.services.common.BusObjectDescription[], java.util.Map)
     */
    @Override
	public void onAnnouncement(String serviceName, short port, BusObjectDescription[] objectDescriptions, Map<String, Object> serviceMetadata) {
    	Log.v(TAG, "Received Announcement signal");
		Handler handler = ConnectionManager.getInstance().getHandler();

		if ( handler == null ) {
			return;
		}
		
		UUID appId = (UUID)serviceMetadata.get(AboutKeys.ABOUT_APP_ID);
		if ( appId == null ) {
			Log.e(TAG, "Received an undefined AppId");
			return;
		}
		
		Map<String, Object> args = new HashMap<String, Object>();
		args.put("SENDER", serviceName);
		args.put("DEVICE_ID", (String)serviceMetadata.get(AboutKeys.ABOUT_DEVICE_ID));
		args.put("APP_ID", appId.toString());
		args.put("OBJ_DESC", objectDescriptions);
		
		Message.obtain(handler, ConnManagerEventType.ANNOUNCEMENT_RECEIVED.ordinal(), args).sendToTarget();
	}//onAnnouncement
	

    /**
     * @see org.alljoyn.services.common.AnnouncementHandler#onDeviceLost(java.lang.String)
     */
    @Override
	public void onDeviceLost(String serviceName) {}
}
