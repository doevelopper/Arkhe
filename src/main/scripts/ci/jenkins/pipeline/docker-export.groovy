node("docker_exporter"){
   env.WORKSPACE=pwd()
   env.S3_DELIVERY_BUCKET="s3://o2-delivery/${OSSIM_GIT_BRANCH}/docker"
   env.DOCKER_REGISTRY_URI="320588532383.dkr.ecr.us-east-1.amazonaws.com"
   
   echo "WORKSPACE        = ${env.WORKSPACE}"
   echo "S3_DELIVERY_BUCKET   = ${env.S3_DELIVERY_BUCKET}"
   stage("Checkout") {
       dir("omar") {
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/omar.git'
       }
   }

   stage("Export Docker Images") {
      sh """
        pushd ${env.WORKSPACE}/omar/build_scripts/docker
        ./docker-export.sh
        popd
      """
   }
 
  stage("Clean Workspace"){
     step([$class: 'WsCleanup'])
  }

}
