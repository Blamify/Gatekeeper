@echo off
cd /D "%~dp0"
openssl genrsa -out .\rootCA.key.pem 4096
openssl rsa -in .\rootCA.key.pem -pubout -out .\rootCA.publickey.pem
openssl req -config .\openssl.cnf -x509 -new -nodes -key .\rootCA.key.pem -sha256 -days 1024 -out .\rootCA.crt.pem
pause>nul