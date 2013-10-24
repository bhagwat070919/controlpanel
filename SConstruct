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

env = SConscript('../../build_core/SConscript')

vars = Variables()
vars.Add('BINDINGS', 'Bindings to build (comma separated list): cpp, java', 'cpp,java')
vars.Add(EnumVariable('BUILD_SERVICES_SAMPLES',
                      'Build the services samples.',
                      'on',
                      allowed_values = ['on', 'off']))
vars.Add(PathVariable('ALLJOYN_DISTDIR',
                      'Directory containing a built AllJoyn Core dist directory.',
                      os.environ.get('ALLJOYN_DISTDIR')))

vars.Add(PathVariable('NS_DISTDIR',
                      'Directory containing a built AllJoyn Notification dist directory (ALLJOYN_DISTDIR will be used if unset).',
                      os.environ.get('NS_DISTDIR',
                                     ARGUMENTS.get('ALLJOYN_DISTDIR', os.environ.get('ALLJOYN_DISTDIR')))))

vars.Add(PathVariable('APP_COMMON_DIR',
                      'Directory containing common sample application sources.',
                      os.environ.get('APP_COMMON_DIR','../../applications/sample_apps')))


vars.Update(env)
Help(vars.GenerateHelpText(env))

if env.get('ALLJOYN_DISTDIR'):
    # normalize ALLJOYN_DISTDIR first
    env['ALLJOYN_DISTDIR'] = env.Dir('$ALLJOYN_DISTDIR')
    env.Append(CPPPATH = [ env.Dir('$ALLJOYN_DISTDIR/cpp/inc'),
                           env.Dir('$ALLJOYN_DISTDIR/about/inc') ])
    env.Append(LIBPATH = [ env.Dir('$ALLJOYN_DISTDIR/cpp/lib'),
                           env.Dir('$ALLJOYN_DISTDIR/about/lib') ])

if env.get('NS_DISTDIR'):
    # normalize NS_DISTDIR first
    env['NS_DISTDIR'] = env.Dir('$NS_DISTDIR')
    env.Append(CPPPATH = [ env.Dir('$NS_DISTDIR/notification/inc') ])
    env.Append(LIBPATH = [ env.Dir('$NS_DISTDIR/notification/lib') ])

if env.get('APP_COMMON_DIR'):
    # normalize APP_COMMON_DIR
    env['APP_COMMON_DIR'] = env.Dir('$APP_COMMON_DIR')

env['bindings'] = set([ b.strip() for b in env['BINDINGS'].split(',') ])

env.SConscript('SConscript')
