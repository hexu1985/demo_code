
cd $(dirname ${BASH_SOURCE[0]})
datestr=$(date +%Y%m%d_%H%M%S)
logname=test.log.$datestr
logdir=log
[ -d "$logdir" ] || mkdir -m 0777 "$logdir"
find "$logdir" -name 'test.log.*' -mtime +5 -delete
exec > $logdir/$logname 2>&1

log() {
        printf "%(%H%M%S)T $@\n"
}

log "test log-1"
log "logdir is $logdir"
