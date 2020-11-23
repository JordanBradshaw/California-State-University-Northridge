rm -f groupID.txt
SEATS=$1
for i in $(seq 0 $(expr $SEATS - 1)); do ./dining-p $SEATS $i &
done
