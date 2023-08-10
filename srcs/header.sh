FILES="*.c"
for f in $FILES
do
  echo "Processing $f file..."
  sed -i '1,11d' $f
  sed -i "1i*/" $f
  sed -i "1i* @version 1.0" $f
  sed -i "1i* @date 11/10/2019" $f
  sed -i "1i* @author alban kerloc'h" $f
  sed -i "1i* @file $f" $f
  sed -i "1i/**" $f
  # take action on each file. $f store current file name
done