
export PATH=.:$PATH

mainboard -p abc -x def &
mainboard -p 123 -x 456 &

pgrep 'mainboard'

pkill -9 -f 'mainboard -p abc'

pgrep 'mainboard'

pkill -9 -f 'mainboard -p 123'


pgrep 'mainboard'

