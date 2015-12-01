#!/bin/bash

folder="knnResults"
subfolders=("separable" "inseparable")
subsubfolders=("default" "distant" "overlapped")

echo "Plotting results in $folder..."

cp gnuplot/plotKNN.gnu $folder
cd $folder
gnuplot plotKNN.gnu
cd ..

for sub in "${subfolders[@]}"
do
  for subsub in "${subsubfolders[@]}"
  do
    echo "Plotting points sets from $folder/$sub/$subsub"
    cp gnuplot/plotPoints.gnu $folder/$sub/$subsub
    cd $folder/$sub/$subsub
    gnuplot plotPoints.gnu
    cd ../../..
  done
done
