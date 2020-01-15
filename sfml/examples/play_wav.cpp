#include <SFML/Audio.hpp> //导入库
#include <iostream>

int main(int argc, char ** argv)
{
    std::string wav_file = "1.wav";

    if (argc > 1) {
        wav_file = argv[1];
    }

	sf::Music music;  //创建一个音乐对象
	if (!music.openFromFile(wav_file)) return 2; //读入音乐文件，不支持mp3格式，所以可以将音乐转换成wav格式

	music.play();  //开始播放

	//music.setPlayingOffset(sf::seconds(2.f));  //快进
	//music.pause(); //暂停
	//music.stop(); //停止播放

    std::cin.get();

//	while(1){

//	}//一直循环，避免程序直接退出

	return 0;
}
