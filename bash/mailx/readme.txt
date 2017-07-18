1. 下载安装mailx
2. 修改mailrc中的from, smtp, smtp-auth-user和smtp-auth-password
3. mv mailrc ~/.mailrc
4. chmod 600 ~/.mailrc
5. mailx -s "test ok" someone@xxx.com.cn < xxx.txt
