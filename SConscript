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

import os

Import('env')

env['_ALLJOYN_CONTROLPANEL_'] = True

# Make config library and header file paths available to the global environment
env.Append(LIBPATH = '$DISTDIR/controlpanel/lib');
env.Append(CPPPATH = '$DISTDIR/controlpanel/inc');

if not env.has_key('_ALLJOYN_ABOUT_'):
    env.SConscript('../about/SConscript')

if 'cpp' in env['bindings'] and not env.has_key('_ALLJOYNCORE_'): 
   env.SConscript('../../alljoyn_core/SConscript')

if 'java' in env['bindings'] and not env.has_key('_ALLJOYN_JAVA_'): 
   env.SConscript('../../alljoyn_java/SConscript')

cpsenv = env.Clone()

cpsenv.SConscript(['%s/SConscript' % b for b in env['bindings'] if os.path.exists('%s/SConscript' % b) ],
                  exports = ['cpsenv'])
