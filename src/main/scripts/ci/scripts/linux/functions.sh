#!/bin/bash


##
# Example use: getOsInfo os major_version minor_version os_arch
#
function getOsInfo {
# Determine OS platform
#        UNAME=$(uname | tr "[:upper:]" "[:lower:]")
        local DISTRO=
        local majorVersion=
        local osArch=`uname -i`
        if [ -f /etc/redhat-release ] ; then
                DISTRO=`cat /etc/redhat-release | cut -d' ' -f1`
                if [[ $DISTRO =~ .*Red.* ]] ; then
                   DISTRO="RedHat"
                fi
                majorVersion=`cat /etc/redhat-release | grep  -o "[0-9]*\.[0-9]*\.*[0-9]*" | cut -d'.' -f1`
                minorVersion=`cat /etc/redhat-release | grep  -o "[0-9]*\.[0-9]*\.*[0-9]*" | cut -d'.' -f2`
        fi
        eval "$1=${DISTRO}"
        eval "$2=${majorVersion}"
        eval "$3=${minorVersion}"
        eval "$4=${osArch}"
}

##
# Example use: getTimeStamp TIMESTAMP
#
function getTimeStamp {
        eval $1=`date +%Y-%m-%d-%H%M`
}


function copyDependencies {
    #!/bin/bash

    if [ $# != 2 ] ; then
        echo "usage: copyDependencies PATH_TO_BINARY TARGET_FOLDER"
        return 1
    fi

    PATH_TO_BINARY="$1"
    TARGET_FOLDER="$2"

    # if we cannot find the the binary we have to abort
    if [ ! -f "$PATH_TO_BINARY" ] ; then
        echo "The file '$PATH_TO_BINARY' was not found. Aborting!"
        return 1
    fi

    mkdir -p $TARGET_FOLDER/{bin,lib64,lib}

    # copy the binary to the target folder
    # create directories if required
#    echo "---> copy binary itself"
#    cp --parents -v "$PATH_TO_BINARY" "$TARGET_FOLDER"

    # copy the required shared libs to the target folder
    # create directories if required
    echo "---> copy libraries"
    for lib in `ldd "$PATH_TO_BINARY" | cut -d'>' -f2 | awk '{print $1}'` ; do
       if [ -d "$lib" ] ; then
          mkdir -p "$lib"
       fi
       if [ -f "$lib" ] ; then
            cp -v --parents "$lib" "$TARGET_FOLDER"
       fi
    done

    # I'm on a 64bit system at home. the following code will be not required on a 32bit system.
    # however, I've not tested that yet
    # create lib64 - if required and link the content from lib to it
    if [ ! -d "$TARGET_FOLDER/lib64" ] ; then
        mkdir -v "$TARGET_FOLDER/lib64"
    fi
}


