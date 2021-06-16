# rfcapi-test

This sample uses RFC and builds for RDK.

###### build

```shell script
devtool add --autorev --src-subdir rfcapi-test rfcapi-test "https://github.com/npoltorapavlo/c_samples.git;branch=main"
echo -e \
  'CXXFLAGS += " -I${STAGING_DIR_TARGET}${includedir}/wdmp-c/ "\n' \
  'CXXFLAGS += " -I${STAGING_DIR_TARGET}${includedir}/trower-base64/ "\n' \
  >> workspace/recipes/rfcapi-test/rfcapi-test_git.bb
devtool build rfcapi-test
devtool reset rfcapi-test
rm -rf workspace/sources/rfcapi-test
```

###### run

```shell script

```
