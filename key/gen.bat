PATH = C:\Program Files\OpenSSL-Win64\bin
openssl genrsa -out ca.key 2048
openssl req -new -x509 -days 7304 -key ca.key -out ca.crt 


openssl genrsa -out server_domain.pem 2048
::制作SSL证书私钥
openssl rsa -in server_domain.pem -out server_domain.key
::生成SSL证书请求
openssl req -new -key server_domain.pem -out server_domain.csr -subj "/C=CN/ST=shandong/L=jinan/O=my domain test/OU=IT Dept/CN=my domain"
::根CA进行SSL证书签发
openssl ca -policy policy_anything -days 3652 -cert ca.crt -keyfile ca.key -in server_domain.csr -out server_domain.crt
