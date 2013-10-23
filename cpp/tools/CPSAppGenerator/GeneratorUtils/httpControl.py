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

class HttpControl:

    def __init__(self, generated, url) :
        self.generated = generated
        self.url = url
        
    def generate(self) :
        self.generated.varDecl += """    static ajn::services::HttpControl* httpControl;\n"""
        self.generated.varDef += """HttpControl* ControlPanelGenerated::httpControl = 0;\n"""

        self.generated.initCode += """\n    httpControl = new HttpControl("{0}");\n""".format(self.url)
        self.generated.initCode += """    CHECK(controlPanelControllee->setHttpControl(httpControl));\n"""

        self.generated.shutdown += """    if (httpControl) {\n        delete (httpControl);\n        httpControl = 0;\n    }\n"""

