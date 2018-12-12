#head -n1 insertsVaryingInitialSize.csv > other_insertsVaryingInitialSize.csv
#head -n1 deletesVaryingInitialSize.csv > other_deletesVaryingInitialSize.csv
#head -n1 uniformAccessVaryingInitialSize.csv > other_uniformAccessVaryingInitialSize.csv
#head -n1 zipfAccessVaryingInitialSize.csv > other_zipfAccessVaryingInitialSize.csv

cat insertsVaryingInitialSize.csv | grep -v "Zip" > other_insertsVaryingInitialSize.csv
cat deletesVaryingInitialSize.csv | grep -v "Zip" > other_deletesVaryingInitialSize.csv
cat uniformAccessVaryingInitialSize.csv | grep -v "Zip" > other_uniformAccessVaryingInitialSize.csv
cat zipfAccessVaryingInitialSize.csv | grep -v "Zip" > other_zipfAccessVaryingInitialSize.csv

cat insertsVaryingInitialSize.csv | grep  "ZipTree," >> other_insertsVaryingInitialSize.csv
cat deletesVaryingInitialSize.csv | grep  "ZipTree," >> other_deletesVaryingInitialSize.csv
cat uniformAccessVaryingInitialSize.csv | grep  "ZipTree," >> other_uniformAccessVaryingInitialSize.csv
cat zipfAccessVaryingInitialSize.csv | grep  "ZipTree," >> other_zipfAccessVaryingInitialSize.csv
