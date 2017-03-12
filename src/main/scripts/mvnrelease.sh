#!/bin/bash

echo -n "Enter a new version and press [ENTER]: "
read newVersion
echo -n "Enter an new snapshot version and press [ENTER]: "
read newSnapshot
echo
mvn clean test && \
mvn versions:set -DnewVersion=$newVersion && \
mvn versions:commit && \
git add pom.xml && \
git commit -m  "Prepare release ${newVersion}" && \
git tag $newVersion && \
mvn versions:set -DnewVersion=$newSnapshot && \
mvn versions:commit && \
git add pom.xml && \
git commit -m "prepare for next development iteration" && \
git push && \
git push origin --tags

