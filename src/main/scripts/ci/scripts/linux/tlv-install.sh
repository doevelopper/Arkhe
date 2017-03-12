#!/bin/bash
pushd `dirname $0` >/dev/null
OSSIMCI_SCRIPT_DIR=`pwd -P`
popd > /dev/null

source $OSSIMCI_SCRIPT_DIR/ossim-env.sh

if [ -d $OSSIM_DEV_HOME/tlv ] ; then
   pushd $OSSIM_DEV_HOME/tlv/time_lapse/build/libs
   app=time_lapse
   for artifact in  `ls *.jar` ; do
      install -p -m644 -D $artifact ${OSSIM_INSTALL_PREFIX}/share/omar/$app/$artifact
      if [ $? -ne 0 ];then
          echo "INSTALL ERROR: $app failed to install..."
          exit 1
      fi   
   done

   if [ -d $OSSIM_DEV_HOME/ossimlabs-tlv ] ; then
      pushd $OSSIM_DEV_HOME/ossimlabs-tlv/support/linux >/dev/null

      install -d -m755 ${OSSIM_INSTALL_PREFIX}/etc/init.d
      install -d -m755 ${OSSIM_INSTALL_PREFIX}/lib/systemd/system
      install -d -m755 ${OSSIM_INSTALL_PREFIX}/share/omar/$app/service-templates
      sed -e "s/{{program_name}}/${app}/g"  -e "s/{{program_user}}/omar/g" -e "s/{{program_group}}/omar/g" < service-wrapper-systemd-template >${OSSIM_INSTALL_PREFIX}/lib/systemd/system/${app}.service 
      sed -e "s/{{program_name}}/${app}/g"  -e "s/{{program_user}}/omar/g" -e "s/{{program_group}}/omar/g" < service-wrapper-initd-template >${OSSIM_INSTALL_PREFIX}/etc/init.d/${app} 
      sed -e "s/{{program_name}}/${app}/g"  -e "s/{{OSSIM_INSTALL_PREFIX}}/\/usr/g" < tlv-shell-template >${OSSIM_INSTALL_PREFIX}/share/omar/$app/${app}.sh 
   fi

fi

if [ $? -ne 0 ]; then
  echo; echo "ERROR: Failed installation for omar binaries."
  exit 1
fi
