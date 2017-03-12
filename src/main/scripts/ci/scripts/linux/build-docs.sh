#!/bin/bash 
pushd `dirname $0` >/dev/null
OSSIMCI_SCRIPT_DIR=`pwd -P`
popd >/dev/null
source $OSSIMCI_SCRIPT_DIR/ossim-env.sh

export OMAR_DEV_HOME=$OSSIM_DEV_HOME/omar
export OMAR_INSTALL_DOCS=$OSSIM_INSTALL_PREFIX/share/o2/docs

source $OSSIMCI_SCRIPT_DIR/ossim-env.sh


if [ -d $OSSIM_DEV_HOME/omar ]; then
   pushd $OSSIM_DEV_HOME/omar > /dev/null
   mkdocs build -d $OMAR_INSTALL_DOCS
   if [ $? -ne 0 ];then
      echo "BUILD DOCS ERROR: failed to build docs using mkdocs..."
      popd > /dev/null
      exit 1
   fi 
   popd > /dev/null
fi
pushd $OSSIM_DEV_HOME > /dev/null
tar cvfz install.tgz install
if [ $? -ne 0 ];then
    echo "BUILD DOCS ERROR: failed to zip up the docs..."
    exit 1
fi 
popd > /dev/null

