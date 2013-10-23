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

package org.alljoyn.ioe.controlpanelservice.ui.ajstruct;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.annotation.Position;
import org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget.ConstrainToValues;
import org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget.ValueType;

import android.util.Log;

public class PropertyWidgetConstrainToValuesAJ {
	
	@Position(0)
	public Variant value;
	
	@Position(1)
	public String label;
	
	/**
	 * Returns single object of PropertyWidget list of values
	 * @param valueType The property type of value
	 * @return
	 */
	public ConstrainToValues<?> getPropertyWidgetConstrainToValues(ValueType valueType) {
		Log.v("cpan" + PropertyWidgetConstrainToValuesAJ.class.getSimpleName(), "Unmarshalling PropertyWidget LOV constraint, label: '" + label + "'");
		try {
			switch (valueType) {
				case BOOLEAN: {
					Boolean valueCast = value.getObject(boolean.class);
					return new ConstrainToValues<Boolean>(valueCast, label);
				}
				case BYTE: {
					Byte valueCast    = value.getObject(byte.class);
					return new ConstrainToValues<Byte>(valueCast, label);
				}
				case DOUBLE: {
					Double valueCast  = value.getObject(double.class);
					return new ConstrainToValues<Double>(valueCast, label);					
				}
				case INT: {
					Integer valueCast = value.getObject(int.class);
					return new ConstrainToValues<Integer>(valueCast, label);					
				}
				case LONG: {
					Long valueCast    = value.getObject(long.class);
					return new ConstrainToValues<Long>(valueCast, label);					
				}
				case SHORT: {
					Short valueCast   = value.getObject(short.class);
					return new ConstrainToValues<Short>(valueCast, label);					
				}
				case STRING: {
					String valueCast  = value.getObject(String.class);
					return new ConstrainToValues<String>(valueCast, label);					
				}
				default: {
					break;
				}
			}//SWITCH
		}//TRY
		catch (BusException be) {
			 Log.e("cpan" + PropertyWidgetConstrainToValuesAJ.class.getSimpleName(), "Failed to unmarshal PropertyWidget LOV - Error: '" + be.getMessage() + "'" );
			return null;
		}
		Log.e("cpan" + PropertyWidgetConstrainToValuesAJ.class.getSimpleName(), "Failed to unmarshal PropertyWidget LOV" );
		return null;
	}//getPropertyWidgetRangeConstraint
	
}
