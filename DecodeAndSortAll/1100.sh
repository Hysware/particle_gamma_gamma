for (( j=1100; j<1108; j++ ))
do
    ./decodeandsort $[j+i*5] &
done

wait

sleep 1

for (( j=1200; j<1108; j++ ))
do
    ./Analysis $[j+i*5] &
done

wait