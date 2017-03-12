node {
   env.WORKSPACE=pwd()
   env.OSSIM_INSTALL_DIR="${env.WORKSPACE}/install"
   env.LD_LIBRARY_PATH="${env.OSSIM_INSTALL_DIR}/lib64:${env.LD_LIBRARY_PATH}"
   env.OSSIM_DATA="/data"
   
   echo "WORKSPACE         = ${env.WORKSPACE}"
   echo "LD_LIBRARY_PATH   = ${env.LD_LIBRARY_PATH}"
   echo "OSSIM_INSTALL_DIR = ${env.OSSIM_INSTALL_DIR}"
   echo "OSSIM_DATA        = ${env.OSSIM_DATA}"

   stage("Checkout"){
        dir("ossim-ci"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/ossim-ci.git'
        }
   }
 
   echo "${env.WORKSPACE}"
   
   stage("Download Artifacts"){
       dir("${env.WORKSPACE}"){
           step ([$class: 'CopyArtifact',
              projectName: "ossim-${OSSIM_GIT_BRANCH}",
              filter: "artifacts/install.tgz",
              flatten: true])
       }
   }
   
   stage("Test"){
       sh """
        tar xvfz install.tgz
        """
       sh """
         install/bin/ossim-info --version > foo.txt
       """
       sh """
         echo
         echo "Dump of foo.txt:"
         cat foo.txt
       """
   }

   stage("Archive"){
     archiveArtifacts 'foo.txt'
   }
   
   stage("Clean Workspace"){
       step([$class: 'WsCleanup'])
  }
}
