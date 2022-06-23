
ls .
case $? in
    0) echo "ok";;
    *) echo "fail";;
esac


ls no-such
case $? in
    0) echo "ok";;
    *) echo "fail";;
esac
