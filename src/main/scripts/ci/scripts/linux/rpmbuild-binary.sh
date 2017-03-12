#!/bin/bash
#
GIT_BRANCH="dev"
OSSIM_SPEC=`uname -r | grep -o el[0-9]`
############################################################
pushd `dirname $0` >/dev/null
OSSIMCI_SCRIPT_DIR=$PWD
popd > /dev/null

source $OSSIMCI_SCRIPT_DIR/ossim-env.sh
source $OSSIMCI_SCRIPT_DIR/functions.sh

if [ "$OSSIM_GIT_BRANCH" != "" ] ; then
  GIT_BRANCH=$OSSIM_GIT_BRANCH
fi

if [ -z $OSSIM_DEPS_RPMS ] ; then
  if [ -d $OSSIM_DEV_HOME/dependency-rpms ] ;then
  OSSIM_DEPS_RPMS=$OSSIM_DEV_HOME/dependency-rpms
  fi
fi

#if [ ! -d $OSSIM_DEV_HOME/rpmbuild ] ; then
mkdir -p $OSSIM_DEV_HOME/rpmbuild/{BUILD,RPMS,SOURCES,SPECS,SRPMS}
if [ $? -ne 0 ]; then
  echo; echo "ERROR: Unable to create rpmbuild directories."
  exit 1
fi
#fi

cp $OSSIM_DEV_HOME/ossim-ci/rpm_specs/*.spec $OSSIM_DEV_HOME/rpmbuild/SPECS/
if [ $? -ne 0 ]; then
  echo; echo "ERROR: Unable to copy spec files from $OSSIM_DEV_HOME/ossim-ci/rpm_specs/*.spec to location $OSSIM_DEV_HOME/rpmbuild/SPECS."
  exit 1
fi



if ls $OSSIM_DEV_HOME/tlv*install.tgz 1> /dev/null 2>&1; then
  if [ -d $OSSIM_DEV_HOME/rpmbuild/BUILD ] ; then
    # Setup and package the new O2 distribution
    pushd $OSSIM_DEV_HOME/rpmbuild/BUILD/
    rm -rf *
    tar xvfz $OSSIM_DEV_HOME/tlv*install.tgz 
    popd
  else
    echo "ERROR: Directory $OSSIM_DEV_HOME/rpmbuild/BUILD does not exist"
    exit 1
  fi
  echo rpmbuild -ba --define "_topdir ${OSSIM_DEV_HOME}/rpmbuild" --define "TLV_VERSION ${TLV_VERSION}" --define "TLV_BUILD_RELEASE ${TLV_BUILD_RELEASE}" ${OSSIM_DEV_HOME}/rpmbuild/SPECS/tlv.spec
  rpmbuild -ba --define "_topdir ${OSSIM_DEV_HOME}/rpmbuild" --define "TLV_VERSION ${TLV_VERSION}" --define "TLV_BUILD_RELEASE ${TLV_BUILD_RELEASE}" ${OSSIM_DEV_HOME}/rpmbuild/SPECS/tlv.spec
  if [ $? -ne 0 ]; then
    echo; echo "ERROR: Build failed for TLV rpm binary build."
    exit 1
  fi

fi


if [ -d $OSSIM_DEV_HOME/rpmbuild/BUILD ] ; then
  # Setup the ossim binaries for packaging
  #
  pushd $OSSIM_DEV_HOME/rpmbuild/BUILD/
  rm -rf *
  tar xvfz $OSSIM_DEV_HOME/ossim-install/install.tgz 
  popd
else
  echo "ERROR: Directory $OSSIM_DEV_HOME/rpmbuild/BUILD  does not exist"
fi

#unzip -o $OSSIM_DEV_HOME/oldmar-install/install.zip 
#unzip -o $OSSIM_DEV_HOME/o2-install/install.zip 
echo rpmbuild -ba --define "_topdir ${OSSIM_DEV_HOME}/rpmbuild" --define "RPM_OSSIM_VERSION ${OSSIM_VERSION}" --define "BUILD_RELEASE ${OSSIM_BUILD_RELEASE}" ${OSSIM_DEV_HOME}/rpmbuild/SPECS/ossim-all.spec

rpmbuild -ba --define "_topdir ${OSSIM_DEV_HOME}/rpmbuild" --define "RPM_OSSIM_VERSION ${OSSIM_VERSION}" --define "BUILD_RELEASE ${OSSIM_BUILD_RELEASE}" ${OSSIM_DEV_HOME}/rpmbuild/SPECS/ossim-all.spec
if [ $? -ne 0 ]; then
  echo; echo "ERROR: Build failed for OSSIM rpm binary build."
  exit 1
fi


if [ -d $OSSIM_DEV_HOME/rpmbuild/BUILD ] ; then
  # Setup the oldmar for packaging
  #
  pushd $OSSIM_DEV_HOME/rpmbuild/BUILD/
    rm -rf *
    tar xvfz $OSSIM_DEV_HOME/oldmar-install/install.tgz 
  popd
else
  echo "ERROR: Directory $OSSIM_DEV_HOME/rpmbuild/BUILD does not exist"
fi

echo rpmbuild -ba --define "_topdir ${OSSIM_DEV_HOME}/rpmbuild" --define "RPM_OSSIM_VERSION ${OSSIM_VERSION}" --define "BUILD_RELEASE ${OSSIM_BUILD_RELEASE}" ${OSSIM_DEV_HOME}/rpmbuild/SPECS/oldmar-all.spec

rpmbuild -ba --define "_topdir ${OSSIM_DEV_HOME}/rpmbuild" --define "RPM_OSSIM_VERSION ${OSSIM_VERSION}" --define "BUILD_RELEASE ${OSSIM_BUILD_RELEASE}" ${OSSIM_DEV_HOME}/rpmbuild/SPECS/oldmar-all.spec

if [ $? -ne 0 ]; then
  echo; echo "ERROR: Build failed for OLDMAR rpm binary build."
  popd >/dev/null
  exit 1
fi

if [ -d $OSSIM_DEV_HOME/rpmbuild/BUILD ] ; then
  # Setup and package the new O2 distribution
  pushd $OSSIM_DEV_HOME/rpmbuild/BUILD/
  rm -rf *
  tar  xvfz $OSSIM_DEV_HOME/o2-install/install.tgz 
  popd
else
  echo "ERROR: Directory $OSSIM_DEV_HOME/rpmbuild/BUILD does not exist"
fi

echo rpmbuild -ba --define "_topdir ${OSSIM_DEV_HOME}/rpmbuild" --define "O2_VERSION ${O2_VERSION}" --define "O2_BUILD_RELEASE ${O2_BUILD_RELEASE}" ${OSSIM_DEV_HOME}/rpmbuild/SPECS/o2-all.spec
rpmbuild -ba --define "_topdir ${OSSIM_DEV_HOME}/rpmbuild" --define "O2_VERSION ${O2_VERSION}" --define "O2_BUILD_RELEASE ${O2_BUILD_RELEASE}" ${OSSIM_DEV_HOME}/rpmbuild/SPECS/o2-all.spec
if [ $? -ne 0 ]; then
  echo; echo "ERROR: Build failed for O2 rpm binary build."
  exit 1
fi

# now create the yum repo artifact tgz file
#
getOsInfo os major_version minor_version os_arch

# create the RPM dir
rpmdir=${OSSIM_DEV_HOME}/rpmbuild/RPMS/${os}/${major_version}/${GIT_BRANCH}/${os_arch}
if [ -d "$rpmdir" ] ; then
  rm -rf $rpmdir/*
fi
mkdir -p $rpmdir

pushd ${OSSIM_DEV_HOME}/rpmbuild/RPMS >/dev/null
  mv `find ./${os_arch} -name "*.rpm"` $rpmdir/
  if [ -d "${OSSIM_DEPS_RPMS}" ] ; then
    cp  `find ${OSSIM_DEPS_RPMS} -name "*.rpm"` $rpmdir/
  fi
  pushd $rpmdir >/dev/null
    createrepo --simple-md-filenames .
    if [ $? -ne 0 ]; then
      echo; echo "ERROR: createrepo failed.  Unable to execute createrepo --simple-md-filenames."
      exit 1
    fi
  popd
  tar cvfz rpms.tgz $os
  mv rpms.tgz ${OSSIM_DEV_HOME}/
popd > /dev/null
