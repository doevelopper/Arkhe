//==================================================================================================
// This is the Jenkins pipeline script for building all O2-OMAR-related docker containers including
// the spring-cloud-related components. The script accepts two parameters:
//    OSSIM_GIT_BRANCH -- Branch tag applies to *all* repositories being accessed.
// The container images are pushed to the corresponding OpenShift container registry.
//==================================================================================================


node("master"){
    env.WORKSPACE=pwd()
    env.OSSIM_MAVEN_PROXY="https://artifacts.radiantbluecloud.com/artifactory/ossim-deps"
    stage("Checkout"){
        dir("o2-paas"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'git@o2-paas.github.com:radiantbluetechnologies/o2-paas.git'
        }
        dir("ossim-ci") {
            git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/ossim-ci.git'
        }
        dir("o2-paas/docker/o2-docs") {
            step ([$class: 'CopyArtifact',
                 projectName: "build-docs-${OSSIM_GIT_BRANCH}",
                 filter: "install.tgz",
                 flatten: true])
         }
         notifyObj = load "${env.WORKSPACE}/ossim-ci/jenkins/pipeline/notify.groovy"
    }
    try{
      stage("Cleanupo docker")
      {
        dir("${env.WORKSPACE}/ossim-ci/scripts/linux"){
            sh "./docker-cleanup.sh"
        }

      }
      stage("Build")
      {
        // The base images are pulled from the modapps registry for building.
        // NOTE: The builds necessarily pull base images (o2-base, o2-ossim) from
        // a common registry for both oc2s and modapps destinations. Therefore,
        // all builds (oc2s and modapps) need to always push images to the modapps
        // registry to avoid stale base images for subsequent builds. In any case,
        // the jenkins builds will be defaulting to "all" which makes this moot.
        setupModappsRegistry()
        buildImages()
        pushImages()

        switch(EXPORT_REGISTRY) {
          case "modapps":
            // Nothing to do here since already done above.
          break
          case "oc2s":
            setupC2SRegistry()
            buildImages()
            pushImages()
          break
          default:
            // default = all
            setupC2SRegistry()
            buildImages()
            pushImages()
          break
      }
      if (SKIP_EXPORT_STAGE=="false")
      {
        stage("Export Docker Images to S3")
        {
          sh """
            pushd ${env.WORKSPACE}/o2-paas/docker
            ./docker-export.sh -a
            popd
          """
          }
        }
      }
    }
    catch(e)
    {
        echo e.toString()
        currentBuild.result = "FAILED"
        notifyObj?.notifyFailed()
    }
    if (SKIP_CLEANUP_STAGE=="false")
    {
      stage("Clean Workspace")
      {
          dir("${env.WORKSPACE}/ossim-ci/scripts/linux"){
              sh "./docker-cleanup.sh"
          }
          step([$class: 'WsCleanup'])
      }
    }
}

def setupC2SRegistry() {
  echo "Logging into C2S docker registry"
  env.DOCKER_REGISTRY_URI="docker-registry-default.cloudapps.ossimc2s.com"
  sh "oc login $C2S_OC_LOGIN --insecure-skip-tls-verify=true"
  sh "oc whoami -t > ocwhoami.txt"
  env.DOCKER_REGISTRY_PW=readFile("ocwhoami.txt").trim()
  env.OPENSHIFT_PROJECT_PATH="oc2s"
}

def setupModappsRegistry() {
  echo "Logging into ModApps docker registry"
  env.DOCKER_REGISTRY_URI="docker-registry-default.o2.radiantbluecloud.com"
  sh "oc login $MODAPPS_OC_LOGIN --insecure-skip-tls-verify=true"
  sh "oc whoami -t > ocwhoami.txt"
  env.DOCKER_REGISTRY_PW=readFile("ocwhoami.txt").trim()
  env.OPENSHIFT_PROJECT_PATH="o2"
}

def buildImages() {
  if (SKIP_BUILD_STAGE=="false")
  {
    dir("${env.WORKSPACE}/o2-paas/docker"){
        sh "./docker-build.sh"
    }
    dir("${env.WORKSPACE}/o2-paas/spring-cloud"){
        sh "./docker-build.sh"
    }
  }
}
def pushImages() {
  if (SKIP_IMAGE_PUSH=="false")
  {
    echo "############# Pushing images to repositories ###############"
    echo ""
    dir("${env.WORKSPACE}/o2-paas/docker"){
        sh "./docker-push.sh"
    }
    dir("${env.WORKSPACE}/o2-paas/spring-cloud"){
        sh "./docker-push.sh"
    }
  }
}
