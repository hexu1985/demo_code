#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/Application.h>
#include <string>
#include <iostream>

using Poco::Util::ServerApplication;
using Poco::Util::Application;

class AppServer:public ServerApplication
{
public:
    AppServer(){}
    ~AppServer(){}
protected:
    void initialize(Application& self)
    {
        ServerApplication::loadConfiguration();    //加载配置文件
        ServerApplication::initialize(self);
    }
    void uninitialize()
    {
        ServerApplication::uninitialize();
    }

    int main(const std::vector<std::string>& args)
    {
        std::string name = config().getString("name");//读取配置文件
        int sport = config().getInt("sport");//读取配置文件
        std::string appdir = config().getString("application.dir","./");
        std::string logdir = config().getString("logs.directory",appdir+"logs");
        std::cout<<"name->"<<name<<std::endl;
        std::cout<<"sport->"<<sport<<std::endl;
        std::cout<<"appdir->"<<appdir<<std::endl;
        std::cout<<"logdir->"<<logdir<<std::endl;
        return Application::EXIT_OK;
    }
};

int main(int argc,char** argv)
{
    AppServer as;
    return as.run(argc,argv);
}
