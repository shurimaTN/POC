
if [ "$#" -ne 1 ]; then
 echo "invalid arg add service name:"
 exit
fi

DIR="service_$1"
if [ -d "$DIR" ]; then
  echo "Dir $DIR already exist ... normal exit"
  exit
else
    echo "Mkdir $DIR"
    mkdir $DIR
fi

echo "create $DIR/Makefile"
cp ./template/newMakefile.tmpl $DIR/Makefile

echo "Create $DIR/$DIR.h "
cp ./template/new_service.h.tmpl $DIR/$DIR.h
sed -i -e "s/##NAME##/$DIR/g" $DIR/$DIR.h

echo "Create $DIR/$DIR.cc "
cp ./template/new_service.cc.tmpl $DIR/$DIR.cc
sed -i -e "s/##NAME##/$DIR/g" $DIR/$DIR.cc

echo "update main Makefile "
sed -i -e "s/ test_lib/ $DIR test_lib/" Makefile
