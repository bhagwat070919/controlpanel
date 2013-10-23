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
import org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget.RangeConstraint;
import org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget.ValueType;

import android.util.Log;

/**
 * Property widget range constraint 
 */
public class PropertyWidgetRangeConstraintAJ {

	/**
	 * Minimum range value
	 */
	@Position(0)
	public Variant min;
	
	/**
	 * Maximum range value
	 */
	@Position(1)
	public Variant max;
	
	/**
	 * The value to increment/decerement
	 */
	@Position(2)
	public Variant increment;
	
	/**
	 * @param valueType The value type of this property 
	 * @param <T>
	 * @return Property widget range constraint or NULL if failed to unmarshal
	 */
	public RangeConstraint<?> getPropertyWidgetRangeConstraint(ValueType valueType) {
		Log.v("cpan" + PropertyWidgetRangeConstraintAJ.class.getSimpleName(), "Unmarshalling PropertyWidget range constraint");
		try {
			switch (valueType) {
				case BYTE: {
					 Byte minCast 		    = min.getObject(byte.class);
					 Byte maxCast 			= max.getObject(byte.class);
					 Byte incrementCast		= increment.getObject(byte.class);
					 return new RangeConstraint<Byte>(minCast, maxCast, incrementCast);
				}
				case DOUBLE: {
					 Double minCast 		= min.getObject(double.class);
					 Double maxCast			= max.getObject(double.class);
					 Double incrementCast	= increment.getObject(double.class);
					 return new RangeConstraint<Double>(minCast, maxCast, incrementCast);
				}
				case INT: {
					 Integer minCast 		= min.getObject(int.class);
					 Integer maxCast 		= max.getObject(int.class);
					 Integer incrementCast	= increment.getObject(int.class);
					 return new RangeConstraint<Integer>(minCast, maxCast, incrementCast);
				}
				case LONG: {
					 Long minCast 	 	    = min.getObject(long.class);
					 Long maxCast 		    = max.getObject(long.class);
					 Long incrementCast     = increment.getObject(long.class);
					 return new RangeConstraint<Long>(minCast, maxCast, incrementCast);
				}
				case SHORT: {
					 Short minCast 	 	    = min.getObject(short.class);
					 Short maxCast 		    = max.getObject(short.class);
					 Short incrementVal 	= increment.getObject(short.class);
					 return new RangeConstraint<Short>(minCast, maxCast, incrementVal);
				}
				default : {
					break;
				}
			}//SWITCH
		}//TRY
		catch (BusException be) {
			 Log.e("cpan" + PropertyWidgetRangeConstraintAJ.class.getSimpleName(), "Failed to unmarshal Range constraint: Error: '" + be.getMessage() + "'" );
			return null;
		}
		Log.e("cpan" + PropertyWidgetRangeConstraintAJ.class.getSimpleName(), "Failed to unmarshal Range constraint" );
		return null;
	}//getPropertyWidgetRangeConstraint
}
