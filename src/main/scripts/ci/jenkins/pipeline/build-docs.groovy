node {
    env.WORKSPACE=pwd()
    stage("Checkout"){
        dir("omar"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/omar.git'
        }
       dir("ossim-ci"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/ossim-ci.git'
       }
    }
   stage("Build"){
       sh """
         ${env.WORKSPACE}/ossim-ci/scripts/linux/build-docs.sh
       """
   }
   stage("Archive"){
     archiveArtifacts 'install.tgz'
  }
  stage("Clean Workspace"){
    step([$class: 'WsCleanup'])
  }
}