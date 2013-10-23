# Copyright 2013, Qualcomm Innovation Center, Inc.
#
#    All rights reserved.
#    This file is licensed under the 3-clause BSD license in the NOTICE.txt
#    file for this project. A copy of the 3-clause BSD license is found at:
#
#        http://opensource.org/licenses/BSD-3-Clause.
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the license is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the license for the specific language governing permissions and
#    limitations under the license.
#
import sys
import xml.etree.ElementTree as xml
import commonWidget as common

class Property (common.Widget):

    def __init__(self, generated, propertyElement, parentObjectPath, languageSetName) :
        common.Widget.__init__(self, generated, propertyElement, parentObjectPath, languageSetName)
        self.widgetName = "PropertyWidget"
        self.widgetType = "WIDGET_TYPE_PROPERTY"
        self.nonSecuredInterfaceName = "PropertyInterfaces"
        self.securedInterfaceName = "SecuredPropertyInterfaces"
        self.hintPrefix = "PROPERTY_WIDGET_HINT_"
        self.propertyCases = ""
        self.getSignatureAndVarType()
        self.signalsString = ""
        self.signalsIndx = 0

    def generateDefines(self, capName) :
        common.Widget.generateDefines(self, capName) 
        self.generated.defines += "#define {0}_VALUE_PROPERTY             AJ_APP_PROPERTY_ID({1} + NUM_PRECEDING_OBJECTS, 1, 4)\n".format(capName, self.generated.definesIndx)
        self.generated.defines += "#define {0}_SIGNAL_VALUE_CHANGED       AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 1, 5)\n".format(capName, self.generated.definesIndx)
        self.propertyCases += "\t\tcase {0}_VALUE_PROPERTY:\n".format(capName) 
        self.signalsString += "\t\t\t((SetValueContext*)context)->signals[{0}] = {1}_SIGNAL_VALUE_CHANGED; \n".format(self.signalsIndx, capName)
        self.signalsIndx += 1

    def generateIdentify(self, capName, language) :
        common.Widget.generateIdentify(self, capName, language)
        self.generated.identify += """\t\tcase {0}_VALUE_PROPERTY :
            *widgetType = WIDGET_TYPE_PROPERTY;
            *propType = PROPERTY_TYPE_VALUE;
            *language = {2};
            return &{1};\n""".format(capName, self.name, language)

        self.generated.identifySignal += """\t\tcase {0}_SIGNAL_VALUE_CHANGED :
            *isProperty = TRUE;
            return &{1};\n""".format(capName, self.name) 

    def generateMandatoryVariables (self) :
        self.generated.initFunction  += "\tinitializePropertyWidget(&{0});\n".format(self.name)
        self.setNumLanguages()
        self.setEnabled()
        self.setWritable()
        self.setPropertyVariables()
        self.generated.initFunction += "\n"

    def setPropertyVariables (self) :
        if len(self.signature) > 0 :
            self.generated.staticVars += "static const char* const {0}Signature = \"{1}\";\n".format(self.name, self.signature)  
            self.generated.initFunction += "\n"
            self.generated.initFunction += "\t{0}.signature = {0}Signature;\n".format(self.name)
        self.generated.initFunction += "\t{0}.propertyType = {1};\n".format(self.name, self.propType)
        self.generated.initFunction += "\t{0}.getValue = &{1};\n".format(self.name, self.element.getCode)
        ### setProperty
        setCode = self.element.setCode
        if self.propType == "SINGLE_VALUE_PROPERTY" :
            setCode = setCode.replace("%s", "newValue")
        else :
            setCode = setCode.replace("%s", "&newValue")
        self.generated.setWidgetPropFunc += self.propertyCases + "\t\t{0}\n".format("{")    
        self.generated.setWidgetPropFunc += "\t\t\t{0} newValue;\n".format(self.varType)
        self.generated.setWidgetPropFunc += "\t\t\tif ((status = unmarshalPropertyValue(&{0}, replyMsg, &newValue, ((SetValueContext*)context)->sender)))\n".format(self.name)
        self.generated.setWidgetPropFunc += "\t\t\t\treturn status;\n"
        self.generated.setWidgetPropFunc += "\t\t\t{0};\n".format(setCode)
        self.generated.setWidgetPropFunc += "\t\t\t((SetValueContext*)context)->numSignals = {0};\n".format(self.signalsIndx)
        self.generated.setWidgetPropFunc += self.signalsString + "\t\t}\n\t\tbreak;\n"

    def generateOptionalVariables (self) :
        self.setBgColor()
        self.setLabel()
        self.setHints() 
        self.setUnitMeasure() 
        self.setConstraintList() 
        self.setConstraintRange() 


    def getSignatureAndVarType(self) :
        self.signature = ""
        self.varType = ""
        self.propType = ""
    
        propertyType = self.element._name
        if propertyType == "stringProperty" :
            self.signature = "s"
            self.varType = "const char*"
            self.propType = "SINGLE_VALUE_PROPERTY"
        elif propertyType == "recordName" :
            self.signature = "s"
            self.varType = "const char*"
            self.propType = "SINGLE_VALUE_PROPERTY"
        elif propertyType == "booleanProperty" :
            self.signature = "b"
            self.varType = "uint32_t"
            self.propType = "SINGLE_VALUE_PROPERTY"
        elif propertyType == "dateProperty" :
            self.varType = "DatePropertyValue"
            self.propType = "DATE_VALUE_PROPERTY"
        elif propertyType == "timeProperty" :
            self.varType = "TimePropertyValue"
            self.propType = "TIME_VALUE_PROPERTY"
        elif propertyType == "scalarProperty" :
            self.propType = "SINGLE_VALUE_PROPERTY"
            dbusType = self.element.attr["dbusType"]
       	    if dbusType == "INT16":
                self.signature = "n"
                self.varType = "int16_t"
            elif dbusType == "UINT16":
                self.signature = "q"
                self.varType = "uint16_t"
            elif dbusType == "INT32":
                self.signature = "i"
                self.varType = "int32_t"
	    elif dbusType == "UINT32":
                self.signature = "u"
                self.varType = "uint32_t"
            elif dbusType == "INT64":
                self.signature = "x"
                self.varType = "int64_t"
            elif dbusType == "UINT64":
                self.signature = "t"
                self.varType = "uint64_t"
	    elif dbusType == "DOUBLE":
                self.signature = "d"
                self.varType = "double"
            else :
                print "ERROR - dbusType of property Unknown. Exiting"
                sys.exit(0)
        else :
            print "ERROR - Element Type of property Unknown. Exiting"
            sys.exit(0)






