def notifyObj
node {
   env.WORKSPACE=pwd()
   env.KAKADU_VERSION="v7_5-01123C"
   env.JAVA_HOME="/usr/lib/jvm/java"
   try{
     stage("Checkout"){
       dir("ossim-private"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'git@ossim-private.github.com:radiantbluetechnologies/ossim-private.git'
       }
       dir("ossim-ci"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/ossim-ci.git'
       }
       notifyObj = load "${env.WORKSPACE}/ossim-ci/jenkins/pipeline/notify.groovy"
     }
     echo "${env.WORKSPACE}"
     stage("Build"){
         sh """
         mkdir -p ${env.WORKSPACE}/ossim-private/kakadu/${env.KAKADU_VERSION}/bin/Linux-x86-64-gcc
         pushd ${env.WORKSPACE}/ossim-private/kakadu/${env.KAKADU_VERSION}/coresys/make
         make -f Makefile-Linux-x86-64-gcc
         popd
         pushd ${env.WORKSPACE}/ossim-private/kakadu/${env.KAKADU_VERSION}/apps/make
         make -f Makefile-Linux-x86-64-gcc
         popd
         pushd ${env.WORKSPACE}/ossim-private/kakadu/${env.KAKADU_VERSION}/managed/make
         make -f Makefile-Linux-x86-64-gcc
         popd
         rm -rf ${env.WORKSPACE}/kakadu-${env.KAKADU_VERSION}
         pushd ${env.WORKSPACE}/ossim-private/kakadu
         cp -R ${env.KAKADU_VERSION} ${env.WORKSPACE}/kakadu-${env.KAKADU_VERSION}
         popd
         """
     }
     
     stage("Archive"){
       dir("${env.WORKSPACE}"){
           sh "tar cvfz kakadu.tgz kakadu-${env.KAKADU_VERSION}"
       }
       dir("${env.WORKSPACE}/artifacts"){
           sh "mv ${env.WORKSPACE}/kakadu.tgz ."
       }
       archiveArtifacts 'artifacts/*'
    }

   }
   catch(e)
   {
    println e
    currentBuild.result = "FAILED"
    notifyObj?.notifyFailed()
   }
  stage("Clean Workspace"){
    step([$class: 'WsCleanup'])
  }
}