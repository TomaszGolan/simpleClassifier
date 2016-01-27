#!/bin/bash

folder="knnResults"
subfolders=("weighted" "unweighted")
subsubfolders=("separable" "inseparable")
subsubsubfolders=("default" "distant" "overlapped")

echo "Plotting results in $folder..."

cp gnuplot/plotKNN.gnu $folder
cd $folder
gnuplot plotKNN.gnu
cd ..

for sub in "${subfolders[@]}"
do
  for subsub in "${subsubfolders[@]}"
  do
    for subsubsub in "${subsubsubfolders[@]}"
    do
      echo "Plotting points sets from $folder/$sub/$subsub/$subsubsub"
      cp gnuplot/plotPoints.gnu $folder/$sub/$subsub/$subsubsub
      cd $folder/$sub/$subsub/$subsubsub
      gnuplot plotPoints.gnu
      cd ../../../..
    done
  done
done
