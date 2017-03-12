def notifyObj
node("${DOCKER_HOST_URL}"){
   env.WORKSPACE=pwd()
   env.AWS_ACCESS_KEY_ID=AWS_ACCESS_KEY_ID
   env.AWS_SECRET_ACCESS_KEY=AWS_SECRET_ACCESS_KEY
   env.DOCKER_HOST_URL="${DOCKER_HOST_URL}"
   env.AWSDNS="sqs.us-east-1.amazonaws.com"
   env.AWSQUEUEPATH="320588532383/avro-tst"
   env.OSSIM_MAVEN_PROXY="https://artifacts.radiantbluecloud.com/artifactory/ossim-deps"
   if("${OSSIM_GIT_BRANCH}" == "master")
   {
     env.AWSQUEUEPATH="320588532383/avro-release"
   }
   try{
     stage("Checkout"){
         dir("omar"){
            git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/omar.git'
         }
         dir("ossim-ci"){
            git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/ossim-ci.git'
         }
        notifyObj = load "${env.WORKSPACE}/ossim-ci/jenkins/pipeline/notify.groovy"
    }
     stage("Configure Docker"){
         //dir("${env.WORKSPACE}/omar/build_scripts/docker"){
             sh """
             ${env.WORKSPACE}/ossim-ci/scripts/linux/o2-docker.sh
             """
         //}
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
