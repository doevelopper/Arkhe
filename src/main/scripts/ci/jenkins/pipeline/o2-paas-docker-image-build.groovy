node{
    env.WORKSPACE=pwd()
    if (USE_C2S_ACCOUNT=="true") {
        echo "Using C2S account"
        env.USE_C2S_ACCOUNT="true"
        env.AWS_ACCESS_KEY_ID=AWS_ACCESS_KEY_ID_C2S
        env.AWS_SECRET_ACCESS_KEY=AWS_SECRET_ACCESS_KEY_C2S
    }
    else {
        echo "Using ModApps account"
        env.USE_C2S_ACCOUNT="false"
        env.AWS_ACCESS_KEY_ID=AWS_ACCESS_KEY_ID_MODAPPS
        env.AWS_SECRET_ACCESS_KEY=AWS_SECRET_ACCESS_KEY_MODAPPS
    }
    stage("Checkout"){
        dir("o2-paas"){
            git branch: "${OSSIM_GIT_BRANCH}", url: 'git@o2-paas.github.com:radiantbluetechnologies/o2-paas.git'
        }
        dir("ossim-ci") {
            git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/ossim-ci.git'
        }
         notifyObj = load "${env.WORKSPACE}/ossim-ci/jenkins/pipeline/notify.groovy"
    }
    try{
        stage("Build")
        {
            dir("${env.WORKSPACE}/o2-paas/spring-cloud"){
                sh "./docker-build.sh"
            }
            dir("${env.WORKSPACE}/o2-paas/docker"){
                sh "./dockeraws-build.sh"
            }
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
