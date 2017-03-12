def notifyObj
node(){
  env.WORKSPACE=pwd()
  env.S3_DELIVERY_BUCKET="s3://o2-delivery/${OSSIM_GIT_BRANCH}"
  env.DOCKER_REGISTRY_URI="320588532383.dkr.ecr.us-east-1.amazonaws.com"
  echo "WORKSPACE        = ${env.WORKSPACE}"
  echo "S3_DELIVERY_BUCKET   = ${env.S3_DELIVERY_BUCKET}"
   try{
    stage("Checkout") {
       dir("omar") {
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/omar.git'
       }
       dir("ossim-ci") {
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/ossim-ci.git'
       }
         notifyObj = load "${env.WORKSPACE}/ossim-ci/jenkins/pipeline/notify.groovy"
    }

       stage("Download Artifacts"){
           dir("${env.WORKSPACE}"){
               step ([$class: 'CopyArtifact',
                  projectName: "build-docs-${OSSIM_GIT_BRANCH}",
                  filter: "install.tgz",
                  target: "build-docs-${OSSIM_GIT_BRANCH}/",
                  flatten: true])
               step ([$class: 'CopyArtifact',
                  projectName: "ossim-${OSSIM_GIT_BRANCH}-src",
                  filter: "artifacts/*",
                  target: "ossim-${OSSIM_GIT_BRANCH}-src",
                  flatten: true])
               step ([$class: 'CopyArtifact',
                  projectName: "rpm-${OSSIM_GIT_BRANCH}",
                  filter: "artifacts/*",
                  target: "rpm-${OSSIM_GIT_BRANCH}",
                  flatten: true])
               step ([$class: 'CopyArtifact',
                  projectName: "ossim-${OSSIM_GIT_BRANCH}",
                  filter: "artifacts/*",
                  target: "ossim-${OSSIM_GIT_BRANCH}/",
                  flatten: true])
            }
       }

    stage("Deliver Artifacts"){
      dir("${env.WORKSPACE}"){
          step([$class: 'S3BucketPublisher',
                dontWaitForConcurrentBuildCompletion: false,
                entries: [[bucket: "o2-delivery/${OSSIM_GIT_BRANCH}/o2-install-guide",
                           excludedFile: '',
                           flatten: false,
                           gzipFiles: false,
                           keepForever: false,
                           managedArtifacts: false,
                           noUploadOnFailure: false,
                           selectedRegion: 'us-east-1',
                           showDirectlyInBrowser: true,
                           sourceFile: "build-docs-${OSSIM_GIT_BRANCH}/*",
                           storageClass: 'STANDARD',
                           uploadFromSlave: false,
                           useServerSideEncryption: false],
                           [bucket: "o2-delivery/${OSSIM_GIT_BRANCH}/src",
                           excludedFile: '',
                           flatten: false,
                           gzipFiles: false,
                           keepForever: false,
                           managedArtifacts: false,
                           noUploadOnFailure: false,
                           selectedRegion: 'us-east-1',
                           showDirectlyInBrowser: true,
                           sourceFile: "ossim-${OSSIM_GIT_BRANCH}-src/*",
                           storageClass: 'STANDARD',
                           uploadFromSlave: false,
                           useServerSideEncryption: false],
                           [bucket: "o2-delivery/${OSSIM_GIT_BRANCH}/o2-rpms",
                           excludedFile: '',
                           flatten: false,
                           gzipFiles: false,
                           keepForever: false,
                           managedArtifacts: false,
                           noUploadOnFailure: false,
                           selectedRegion: 'us-east-1',
                           showDirectlyInBrowser: true,
                           sourceFile: "rpm-${OSSIM_GIT_BRANCH}/*",
                           storageClass: 'STANDARD',
                           uploadFromSlave: false,
                           useServerSideEncryption: false],
                           [bucket: "o2-delivery/${OSSIM_GIT_BRANCH}/ossim",
                           excludedFile: '',
                           flatten: false,
                           gzipFiles: false,
                           keepForever: false,
                           managedArtifacts: false,
                           noUploadOnFailure: false,
                           selectedRegion: 'us-east-1',
                           showDirectlyInBrowser: true,
                           sourceFile: "ossim-${OSSIM_GIT_BRANCH}/*",
                           storageClass: 'STANDARD',
                           uploadFromSlave: false,
                           useServerSideEncryption: false]], 
                profileName: 'o2-cicd',
                userMetadata: []])
      }
    }
  }
  catch(e)
  {
    currentBuild.result = "FAILED"
    notifyObj?.notifyFailed()
  }
  stage("Clean Workspace"){
     step([$class: 'WsCleanup'])
  }
}
