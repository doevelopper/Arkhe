def notifyObj
node{
    env.WORKSPACE=pwd()
    try{
        stage("Checkout"){
           dir("ossim-ci"){
              git branch: "${GIT_BRANCH}", url: "https://github.com/ossimlabs/ossim-ci.git"
           }
           notifyObj = load "${env.WORKSPACE}/ossim-ci/jenkins/pipeline/notify.groovy"
        }
        stage ("Build")
        {
            sh "${env.WORKSPACE}/ossim-ci/scripts/linux/rpmbuild-dependencies.sh"
        }
        stage("Archive"){

            archiveArtifacts 'dependency-rpms.tgz'
        }
        stage("Clean Workspace"){
            step([$class: 'WsCleanup'])
        }

    }
    catch(e)
    {
        currentBuild.result = "FAILED"
        notifyObj?.notifyFailed()
    }
}