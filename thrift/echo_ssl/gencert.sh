#!/bin/sh

# create self-signed server certificate:

read -p "Enter your domain [www.example.com]: " DOMAIN

echo "Create server key..."

openssl genrsa -des3 -out $DOMAIN.key 1024

echo "Create server certificate signing request..."

SUBJECT="/C=US/ST=Mars/L=iTranswarp/O=iTranswarp/OU=iTranswarp/CN=$DOMAIN"

openssl req -new -subj $SUBJECT -key $DOMAIN.key -out $DOMAIN.csr

echo "Remove password..."

mv $DOMAIN.key $DOMAIN.origin.key
openssl rsa -in $DOMAIN.origin.key -out $DOMAIN.key

echo "Sign SSL certificate..."

openssl x509 -req -days 3650 -in $DOMAIN.csr -signkey $DOMAIN.key -out $DOMAIN.crt

echo "TODO:"
echo "Copy $DOMAIN.crt to /etc/nginx/ssl/$DOMAIN.crt"
echo "Copy $DOMAIN.key to /etc/nginx/ssl/$DOMAIN.key"
echo "Add configuration in nginx:"
echo "server {"
echo "    ..."
echo "    listen 443 ssl;"
echo "    ssl_certificate     /etc/nginx/ssl/$DOMAIN.crt;"
echo "    ssl_certificate_key /etc/nginx/ssl/$DOMAIN.key;"
echo "}"

exit 0

# add for convert to jks
echo "openssl pkcs12 -export -clcerts -in $DOMAIN.crt -inkey $DOMAIN.key -out $DOMAIN.p12"

openssl pkcs12 -export -clcerts -in $DOMAIN.crt -inkey $DOMAIN.key -out $DOMAIN.p12


echo "keytool -import -v -trustcacerts -alias client -file $DOMAIN.crt -keystore $DOMAIN.trust.jks"

keytool -import -v -trustcacerts -alias client -file $DOMAIN.crt -keystore $DOMAIN.trust.jks


echo "keytool -importkeystore -srckeystore $DOMAIN.p12 -srcstoretype PKCS12 -deststoretype JKS -destkeystore $DOMAIN.jks"

keytool -importkeystore -srckeystore $DOMAIN.p12 -srcstoretype PKCS12 -deststoretype JKS -destkeystore $DOMAIN.jks

