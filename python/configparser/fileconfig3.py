import configparser
import sys

class FileConfig:
    _parser = configparser.ConfigParser()

    @classmethod
    def parse_file(cls, path):
        cls._parser.read(path)

    @classmethod
    def has_section(cls, section_name):
        return section_name in cls._parser.sections()

    @classmethod
    def get_attrs(cls, section_name):
        attr_map = dict()
        if cls.has_section(section_name):
            for name, value in cls._parser.items(section_name):
                attr_map[name] = value
        return attr_map

    @classmethod
    def get_attr(cls, section_name, name):
        return cls._parser.get(section_name, name)

    @classmethod
    def print_all(cls):
        for section_name in cls._parser.sections():
            print('Section: %s' % section_name)
            print('    Options: %s' % cls._parser.options(section_name))
            for name, value in cls._parser.items(section_name):
                print('    %s = %s' % (name, value))
            print('\n')

if __name__ == '__main__':
    path = 'example.ini'
    if len(sys.argv) >= 2:
        path = sys.argv[1]
    FileConfig.parse_file(path)
    print('')
    print('mysql config: %s' % FileConfig.get_attrs('mysql'))
    print('all config: ')
    FileConfig.print_all()


