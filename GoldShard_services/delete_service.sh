if [ "$#" -ne 1 ]; then
 echo "argument invalid arg return service name:"
 exit
fi

DIR="service_$1"
if [ -d "$DIR" ]; then
    echo "Remove files $DIR"
else
    echo "$DIR does not exist"
    exit
fi

rm -rf $DIR

echo "Update Main Makefile"
sed -i -e "s/ $DIR//" Makefile
