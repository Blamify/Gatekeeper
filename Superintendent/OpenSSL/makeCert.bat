@echo off
cd /D "%~dp0"
openssl req -config .\openssl.cnf -nodes -x509 -newkey rsa:4096 -keyout .\key.pem -out .\cert.pem -sha256 -days 365
certutil.exe -addstore root .\cert.pem
pause>nul