import optparse
import sys

class CmdConfig:
    _parser = optparse.OptionParser()
    _options = None 

    @classmethod
    def parse_args(cls):
        cls._options, remainder = cls._parser.parse_args()
        sys.argv[1:] = remainder

    @classmethod
    def print_all(cls):
        print("argument: %s" % cls._options) 

    @classmethod
    def has_attr(cls, name):
        if (cls._options is None):
            return False
        if (name not in cls._options.__dict__.keys()):
            return False
        return True

    @classmethod
    def get_attr(cls, name):
        if (cls._options is None):
            return None
        return cls._options.__dict__[name]

class MyCmdConfig(CmdConfig):
    CmdConfig._parser.add_option('--ini_file', dest='ini_file', default='default.ini')
    CmdConfig._parser.add_option('--log_file', dest='log_file', default='default.log')

if __name__ == '__main__':
    MyCmdConfig.parse_args()
    MyCmdConfig.print_all()
    print("ini_file: %s" % MyCmdConfig.get_attr('ini_file'))
    print("has config of xxx: %s" % MyCmdConfig.has_attr('xxx'))

