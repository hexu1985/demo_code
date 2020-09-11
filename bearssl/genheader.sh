brssl ta 127.0.0.1.crt > client_rsa.h 
brssl chain 127.0.0.1.crt > chain-rsa.h 
brssl skey -C 127.0.0.1.key | grep -v 'RSA key (1024 bits)' > key-rsa.h 

