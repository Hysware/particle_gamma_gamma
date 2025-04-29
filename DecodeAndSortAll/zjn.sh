for (( i=2; i<12; i++ ))
do
for (( j=1000; j<1005; j++ ))
do
    ./decodeandsort $[j+i*5] $[j+i*5] &
done

wait

sleep 1

done