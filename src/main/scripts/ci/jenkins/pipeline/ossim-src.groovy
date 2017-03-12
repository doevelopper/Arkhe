node {
    env.WORKSPACE=pwd()
    stage("Checkout"){
      dir("ossim-${OSSIM_GIT_BRANCH}-src"){
        dir("ossim"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/ossim.git'
        }
        dir("ossim-video"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/ossim-video.git'
        }
        dir("ossim-planet"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/ossim-planet.git'
        }
        dir("ossim-gui"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/ossim-gui.git'
        }
        dir("ossim-oms"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/ossim-oms.git'
        }
        dir("ossim-plugins"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/ossim-plugins.git'
        }
        dir("ossim-wms"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/ossim-wms.git'
        }
        dir("ossim-ci"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/ossim-ci.git'
        }
        dir("omar"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/omar.git'
        }
        dir("oldmar"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/radiantbluetechnologies/omar.git'
        }
        dir("ossim-ci"){
          git branch: "${OSSIM_GIT_BRANCH}", url: 'https://github.com/ossimlabs/ossim-ci.git'
        }
      }
      dir("ossim-private-${OSSIM_GIT_BRANCH}-src"){
           git branch: "${OSSIM_GIT_BRANCH}", url: 'git@ossim-private.github.com:radiantbluetechnologies/ossim-private.git'
      }
      dir("o2-paas-${OSSIM_GIT_BRANCH}-src"){
           git branch: "${OSSIM_GIT_BRANCH}", url: 'git@o2-paas.github.com:radiantbluetechnologies/o2-paas.git'
      }
      dir("cucumber-${OSSIM_GIT_BRANCH}-src"){
           git branch: "${OSSIM_GIT_BRANCH}", url: 'git@cucumber-oc2s.github.com:radiantbluetechnologies/cucumber-oc2s.git'
      }
      dir("config-repo-src"){
           git branch: "master", url: 'git@config-repo.github.com:radiantbluetechnologies/config-repo.git'
      }
    }
   stage("Packaging source"){
     dir("${env.WORKSPACE}"){
         sh "rm -rf `find ossim-${OSSIM_GIT_BRANCH}-src -name .git`"
         sh "rm -rf `find cucumber-${OSSIM_GIT_BRANCH}-src -name .git`"
         sh "tar cvfz ossim-${OSSIM_GIT_BRANCH}-src.tgz ossim-${OSSIM_GIT_BRANCH}-src"
         sh "tar cvfz o2-paas-${OSSIM_GIT_BRANCH}-src.tgz o2-paas-${OSSIM_GIT_BRANCH}-src"
         sh "tar cvfz ossim-private-${OSSIM_GIT_BRANCH}-src.tgz ossim-private-${OSSIM_GIT_BRANCH}-src"
         sh "tar cvfz cucumber-${OSSIM_GIT_BRANCH}-src.tgz cucumber-${OSSIM_GIT_BRANCH}-src"
         sh "tar cvfz config-repo-src.tgz config-repo-src"
     }
   }
   stage("Archiving"){
     dir("${env.WORKSPACE}/artifacts"){
         sh "mv ${env.WORKSPACE}/ossim-${OSSIM_GIT_BRANCH}-src.tgz ."
         sh "mv ${env.WORKSPACE}/o2-paas-${OSSIM_GIT_BRANCH}-src.tgz ."
         sh "mv ${env.WORKSPACE}/ossim-private-${OSSIM_GIT_BRANCH}-src.tgz ."
         sh "mv ${env.WORKSPACE}/cucumber-${OSSIM_GIT_BRANCH}-src.tgz ."
         sh "mv ${env.WORKSPACE}/config-repo-src.tgz ."
     }
     archiveArtifacts 'artifacts/*'
  }
  stage("Clean Workspace"){
    step([$class: 'WsCleanup'])
  }
}