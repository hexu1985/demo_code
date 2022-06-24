
export PATH=.:$PATH

mainboard -p abc -x def &
mainboard -p 123 -x 456 &

ps -ef | grep '[m]ainboard'

pkill -9 -f 'mainboard -p abc'

ps -ef | grep '[m]ainboard'

pkill -9 -f 'mainboard -p 123'


ps -ef | grep '[m]ainboard'

