
ps aux | grep 'uevent_monitor /tmp/[U]eventPublisher.unix.dg' | awk '{print $2}' | xargs -i kill -9 {}
