void main(void)
{
      unsigned char digest[16];  //存放结果

      //第一种用法:

     MD5_CTX md5c;
     MD5Init(&md5c); //初始化
     MD5UpdaterString(&md5c,"你要测试的字符串");
     MD5FileUpdateFile(&md5c,"你要测试的文件路径");
     MD5Final(digest,&md5c);

     //第二种用法:
     MDString("你要测试的字符串",digest); //直接输入字符串并得出结果

    //第三种用法:
    MD5File("你要测试的文件路径",digest); //直接输入文件路径并得出结果
}
