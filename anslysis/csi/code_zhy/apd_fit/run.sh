## usage: ./run.sh runNumber thread 
echo "Suggest the thread less than 16!!!"
mkdir $1
cd $1
for (( i=0; i<$2; i++ ))
do
    echo "begin thread $i:"
    mkdir $i
    cd $i
    ../pid $1 $2 $i & 
    cd ../
    sleep 2
done


